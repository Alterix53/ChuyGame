import discord
from discord.ext import commands
import psutil
import config

intents = discord.Intents.default()  
intents.message_content = True 
intents.members = True
intents.guilds = True
intents.presences = True

clients = commands.Bot(command_prefix='chuygame', intents=intents)

is_ready = False

@clients.event
async def on_ready():
    global is_ready
    if not is_ready:
        is_ready = True
        print("ready !!!")
        print("----------")

        try:
            await clients.tree.sync()
            print("Slash commands synced ngon :3!")
        except Exception as e:
            print(f"Failed to sync slash commands :< : {e}")

        print("----------")
        print('Servers bot đã tham gia:')
        for guild in clients.guilds:
            print(f' - {guild.name} (ID: {guild.id})')

@clients.tree.command(description="log memory usage")
async def log_memory_usage(interaction: discord.Interaction):
    process = psutil.Process()
    mem_info = process.memory_info()
    await interaction.response.send_message(f"RSS: {mem_info.rss / 1024 / 1024:.2f} MB")

clients.run(config.TOKEN) 