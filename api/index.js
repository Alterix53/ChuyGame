import express from 'express';
import axios from 'axios';

const app = express();
app.use(express.json());

const players = [];

app.get("/players", (req, res) => {
    res.json(players);
});

const DISCORD_WEBHOOK_URL = process.env.DISCORD_WEBHOOK_URL;

app.delete("/players", (req, res) => {
    players.splice(0, players.length);
    players.length = 0;
    res.json({ message: "Đã xoá toàn bộ người chơi" });
});

app.get("/players/:id", (req, res) => {
    const idNguoiChoi = req.params.id;
    const player = players.find(p => p.idNguoiChoi === idNguoiChoi);

    if (!player) {
        return res.status(404).json({ message: "Khong ton tai id" });
    }

    res.json(player);
});

app.post("/players", async (req, res) => {
    const { weapon, armor, name, id } = req.body;

    if (!Array.isArray(weapon) || !Array.isArray(armor)) {
        return res.status(400).json({ message: "weapon va armor phai la mang" });
    }

    const newPlayer = { weapon, armor, name, id, createdAt: new Date() };
    players.push(newPlayer);

    await axios.post(DISCORD_WEBHOOK_URL, {
        content: `🛡️ Người chơi mới: **${name}** (ID: ${id}) vừa tham gia!`
    });

    res.status(201).json({ message: "Them nguoi choi thanh cong", player: newPlayer });
});

app.put("/players/:id", (req, res) => {
    const idNguoiChoi = req.params.id;
    const { weapon, armor, tenNguoiChoi } = req.body;
    
    const playerIndex = players.findIndex(p => p.idNguoiChoi === idNguoiChoi);
    
    if (playerIndex === -1) {
        return res.status(404).json({ message: "Khong tim thay nguoi choi" });
    }

    const updatedPlayer = {
        ...players[playerIndex],
        weapon: weapon || players[playerIndex].weapon,
        armor: armor || players[playerIndex].armor,
        tenNguoiChoi: tenNguoiChoi || players[playerIndex].tenNguoiChoi,
        updatedAt: new Date()
    };

    players[playerIndex] = updatedPlayer;

    res.json({
        message: "Cap nhat thanh cong",
        player: updatedPlayer
    });
});
export default app;

// const port = 3000;
// app.listen(port, () => {
//     console.log(`http://localhost:${port}`);
// });
