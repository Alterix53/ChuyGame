import discord
from discord.ext import commands
import psutil
import requests
import asyncio
import config
import random
import time
from typing import Dict, List, Any

intents = discord.Intents.default()
intents.message_content = True
clients = commands.Bot(command_prefix='chuygame ', intents=intents)

game_running = False

async def fetch_players():
    try:
        return await asyncio.to_thread(requests.get, config.API_URL)
    except requests.exceptions.RequestException as e:
        print(f"Lỗi gọi API: {e}")
        return None


async def clear_players():
    try:
        response = await asyncio.to_thread(requests.delete, config.API_URL)
        if response.status_code == 200:
            print("Đã xóa toàn bộ danh sách người chơi.")
        else:
            print(f"Lỗi xóa danh sách: {response.status_code} - {response.text}")
    except requests.exceptions.RequestException as e:
        print(f"Lỗi gọi API xóa: {e}")


class CombatSystem:
    def __init__(self):
        self.log = []
        
    def calculate_damage(self, attacker: Dict[str, Any], defender: Dict[str, Any]) -> tuple:
        if attacker.get('weapon') and len(attacker['weapon']) > 0:
            weapon = random.choice(attacker['weapon'])
            
            if weapon.get('type') == 'Unknown' or weapon.get('damage', 0) == 0:
                weapon = {'name': 'Basic Attack', 'damage': 10, 'atkSpeed': 1.0, 'type': 'Unarmed'}
        else:
            weapon = {'name': 'Basic Attack', 'damage': 10, 'atkSpeed': 1.0, 'type': 'Unarmed'}
        
        if defender.get('armor') and len(defender['armor']) > 0:
            armor = random.choice(defender['armor'])
            
            if 'part' not in armor or armor.get('part') == 'Unknown':
                armor['part'] = random.choice(['Head', 'Chest', 'Legs', 'Arms'])
        else:
            armor = {'name': 'Unarmored', 'defense': 0, 'part': 'Body', 'type': 'None', 'health': 100}
        
        base_damage = weapon.get('damage', 10) * (0.8 + random.random() * 0.4)
        
        damage_reduction = armor.get('defense', 0) / 100
        actual_damage = max(1, base_damage * (1 - damage_reduction))
        
        is_critical = random.random() < 0.1
        if is_critical:
            actual_damage *= 2
        
        return round(actual_damage, 1), weapon, armor, is_critical
        
    async def simulate_combat(self, player1: Dict[str, Any], player2: Dict[str, Any]) -> discord.Embed:
        self.log = []
        
        p1_health = sum(a.get('health', 0) for a in player1.get('armor', []))
        p2_health = sum(a.get('health', 0) for a in player2.get('armor', []))
        
        if p1_health <= 0:
            p1_health = 1000
        if p2_health <= 0:
            p2_health = 1000
            
        p1_max_health = p1_health
        p2_max_health = p2_health
        
        self.log.append(f"⚔️ **{player1['name']}** ({p1_health} HP) VS **{player2['name']}** ({p2_health} HP)")
        self.log.append("─" * 50)
        
        turn = 0
        while p1_health > 0 and p2_health > 0 and turn < 20: 
            turn += 1
            self.log.append(f"**Vòng {turn}**")
            
            if p1_health > 0:
                damage, weapon, armor, critical = self.calculate_damage(player1, player2)
                p2_health = max(0, p2_health - damage)
                
                if critical:
                    self.log.append(f"💥 **Chí mạng** {player1['name']} đánh vào {armor['part']} của {player2['name']}  với {weapon['name']} khoảng **{damage}** damage!")
                else:
                    self.log.append(f"🗡️ {player1['name']} tấn công {armor['part']} đánh vào {player2['name']}  với {weapon['name']} khoảng **{damage}** damage!")
                
                health_percent = int((p2_health / p2_max_health) * 100)
                health_bar = self.generate_health_bar(health_percent)
                self.log.append(f"❤️ {player2['name']}: {health_bar} ({p2_health:.1f}/{p2_max_health})")
                self.log.append("")
            
            if p2_health <= 0:
                break
                
            if p2_health > 0:
                damage, weapon, armor, critical = self.calculate_damage(player2, player1)
                p1_health = max(0, p1_health - damage)
                
                if critical:
                    self.log.append(f"💥 **Chí mạng!** {player2['name']} đánh vào {armor['part']} của {player1['name']} với {weapon['name']} khoảng **{damage}** damage!")
                else:
                    self.log.append(f"🗡️ {player2['name']} tấn công {armor['part']} của {player1['name']} với {weapon['name']} khoảng **{damage}** damage!")
                
                health_percent = int((p1_health / p1_max_health) * 100)
                health_bar = self.generate_health_bar(health_percent)
                self.log.append(f"❤️ {player1['name']}: {health_bar} ({p1_health:.1f}/{p1_max_health})")
                self.log.append("")
            
            await asyncio.sleep(0.5)
        
        self.log.append("─" * 50)
        if p1_health <= 0:
            winner = player2['name']
            self.log.append(f"🏆 **{player2['name']}** thắng!")
        elif p2_health <= 0:
            winner = player1['name']
            self.log.append(f"🏆 **{player1['name']}** thắng")
        else:
            if p1_health > p2_health:
                winner = player1['name']
                self.log.append(f"🏆 **{player1['name']}** thắng do nhiều máu hơn")
            elif p2_health > p1_health:
                winner = player2['name']
                self.log.append(f"🏆 **{player2['name']}** thắng do nhiều máu hơn")
            else:        
                winner = "Draw"
                self.log.append("⚠️ Hoà!")
            
        embed = self.create_combat_embed(player1, player2, winner)
        return embed
    
    def generate_health_bar(self, percent: int) -> str:
        filled_blocks = int(percent / 10)
        empty_blocks = 10 - filled_blocks
        
        if percent <= 25:
            color = "🟥" 
        elif percent <= 50:
            color = "🟨"
        else:
            color = "🟩"
            
        return color * filled_blocks + "⬜" * empty_blocks
    
    def create_combat_embed(self, player1: Dict[str, Any], player2: Dict[str, Any], winner: str) -> discord.Embed:
        if winner == player1['name']:
            color = discord.Color.blue()
            title = f"🏆 {player1['name']} hạ gục {player2['name']}!"
        elif winner == player2['name']:
            color = discord.Color.red()
            title = f"🏆 {player2['name']} hạ gục {player1['name']}!"
        else:
            color = discord.Color.gold()
            title = f"⚔️ Trận chiến giữa {player1['name']} và {player2['name']} kết thúc với kết quả hòa!"
            
        embed = discord.Embed(title=title, color=color)
        embed.set_author(name="Combat Results")
        embed.set_footer(text=f"Trận chiến diễn ra vào {time.strftime('%H:%M:%S')}")
        
        p1_weapons = []
        for w in player1.get('weapon', []):
            if w.get('type') == 'Unknown':
                damage = w.get('damage', 0)
                if damage > 0:
                    p1_weapons.append(f"Weapon ({damage} DMG)")
                else:
                    p1_weapons.append("Basic Attack")
            else:
                p1_weapons.append(w.get('name', 'Weapon'))
        p1_weapons_str = ", ".join(p1_weapons)

        p1_armor = []
        for a in player1.get('armor', []):
            if a.get('type') == 'Unknown':
                defense = a.get('defense', 0)
                health = a.get('health', 0)
                part = a.get('part', 'Unknown')
                if part != 'Unknown':
                    p1_armor.append(f"{part} Armor ({defense} DEF, {health} HP)")
                else:
                    p1_armor.append(f"Armor ({defense} DEF, {health} HP)")
            else:
                p1_armor.append(a.get('name', 'Armor'))
        p1_armor_str = ", ".join(p1_armor)


        #p2
        p2_weapons = []
        for w in player2.get('weapon', []):
            if w.get('type') == 'Unknown':
                damage = w.get('damage', 0)
                if damage > 0:
                    p2_weapons.append(f"Weapon ({damage} DMG)")
                else:
                    p2_weapons.append("Basic Attack")
            else:
                p2_weapons.append(w.get('name', 'Weapon'))
        p2_weapons_str = ", ".join(p2_weapons)

        p2_armor = []
        for a in player2.get('armor', []):
            if a.get('type') == 'Unknown':
                defense = a.get('defense', 0)
                health = a.get('health', 0)
                part = a.get('part', 'Unknown')
                if part != 'Unknown':
                    p2_armor.append(f"{part} Armor ({defense} DEF, {health} HP)")
                else:
                    p2_armor.append(f"Armor ({defense} DEF, {health} HP)")
            else:
                p2_armor.append(a.get('name', 'Armor'))
        p2_armor_str = ", ".join(p2_armor)
        
        embed.add_field(name=f"👤 {player1['name']}", value=f"⚔️ Weapons: {p1_weapons_str or 'None'}\n🛡️ Armor: {p1_armor_str or 'None'}", inline=True)
        embed.add_field(name=f"👤 {player2['name']}", value=f"⚔️ Weapons: {p2_weapons_str or 'None'}\n🛡️ Armor: {p2_armor_str or 'None'}", inline=True)
        
        return embed

    async def send_battle_log(self, channel: discord.TextChannel, log_chunks: List[str] = None):
        if log_chunks is None:
            log_chunks = []
            current_chunk = ""
            
            for line in self.log:
                if len(current_chunk) + len(line) + 1 > 1900:
                    log_chunks.append(current_chunk)
                    current_chunk = line
                else:
                    if current_chunk:
                        current_chunk += "\n" + line
                    else:
                        current_chunk = line
                        
            if current_chunk:
                log_chunks.append(current_chunk)
        
        for chunk in log_chunks:
            await channel.send(f"```markdown\n{chunk}\n```")
            await asyncio.sleep(1)

async def game_loop(channel):
    global game_running
    combat_system = CombatSystem()
    
    while game_running:
        response = await fetch_players()
        if response and response.status_code == 200:
            players = response.json()
            if len(players) >= 2:
                player1, player2 = players[:2]
                
                await channel.send(f"⚔️{player1['name']} với {player2['name']}")
                await asyncio.sleep(2)
                
                result_embed = await combat_system.simulate_combat(player1, player2)
                
                await combat_system.send_battle_log(channel)
                
                await channel.send(embed=result_embed)
                
                await clear_players()

        await asyncio.sleep(10)

@clients.tree.command(description="Bắt đầu game")
async def game_start(interaction: discord.Interaction):
    global game_running
    if game_running:
        await interaction.response.send_message("Game đã chạy rồi!")
        return

    game_running = True
    channel = clients.get_channel(config.CHANNEL_ID)
    if channel:
        await interaction.response.send_message("Game đã bắt đầu!")
        clients.loop.create_task(game_loop(channel))
    else:
        await interaction.response.send_message("Không tìm thấy kênh, kiểm tra lại quyền bot!")


@clients.tree.command(description="Dừng game")
async def game_end(interaction: discord.Interaction):
    global game_running
    if not game_running:
        await interaction.response.send_message("Game chưa bắt đầu!")
        return

    game_running = False
    await interaction.response.send_message("Game đã dừng!")


@clients.tree.command(description="Log memory usage")
async def log_memory_usage(interaction: discord.Interaction):
    process = psutil.Process()
    mem_info = process.memory_info()
    await interaction.response.send_message(f"RSS: {mem_info.rss / 1024 / 1024:.2f} MB")


@clients.event
async def on_ready():
    print(f'Bot đã đăng nhập với tên {clients.user}')
    await clients.tree.sync()

clients.run(config.TOKEN)