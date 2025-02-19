import express from 'express';

const app = express();
app.use(express.json());

const players = [];

app.get("/players", (req, res) => {
    res.json(players);
});

app.get("/players/:id", (req, res) => {
    const idNguoiChoi = req.params.id;
    const player = players.find(p => p.idNguoiChoi === idNguoiChoi);

    if (!player) {
        return res.status(404).json({ message: "Khong ton tai id" });
    }

    res.json(player);
});

app.post("/players", (req, res) => {
    const { weapon, armor, tenNguoiChoi, idNguoiChoi } = req.body;

    if (!weapon || !armor || !tenNguoiChoi || !idNguoiChoi) {
        return res.status(400).json({ message: "Thieu thong tin nguoi choi" });
    }

    if (!weapon.type || !weapon.name || typeof weapon.damage !== 'number' || 
        typeof weapon.atkSpeed !== 'number' || typeof weapon.cost !== 'number') {
        return res.status(400).json({ message: "Thong tin vu khi khong hop le" });
    }

    if (!armor.type || !armor.name || !armor.part || 
        typeof armor.defense !== 'number' || typeof armor.health !== 'number') {
        return res.status(400).json({ message: "Thong tin giap khong hop le" });
    }

    const newPlayer = {
        weapon,
        armor,
        tenNguoiChoi,
        idNguoiChoi,
        createdAt: new Date()
    };

    players.push(newPlayer);

    res.status(201).json({ 
        message: "Them nguoi choi thanh cong", 
        player: newPlayer 
    });
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

const port = 3000;
app.listen(port, () => {
    console.log(`http://localhost:${port}`);
});

// export default app;