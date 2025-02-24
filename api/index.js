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
    const { weapon, armor, name, id } = req.body;

    if (!Array.isArray(weapon) || !Array.isArray(armor)) {
        return res.status(400).json({ message: "weapon va armor phai la mang" });
    }

    const validWeapon = weapon.every(w => 
        w.type && 
        w.name && 
        typeof w.damage === 'number' && 
        typeof w.atkSpeed === 'number' && 
        typeof w.cost === 'number'
    );

    if (!validWeapon) {
        return res.status(400).json({ message: "Thong tin vu khi khong hop le" });
    }

    const validArmor = armor.every(a => 
        a.type && 
        a.name && 
        a.part && 
        typeof a.defense === 'number' && 
        typeof a.health === 'number'
    );

    if (!validArmor) {
        return res.status(400).json({ message: "Thong tin giap khong hop le" });
    }

    const newPlayer = {
        weapon,
        armor,
        name,
        id,
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