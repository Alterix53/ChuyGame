import express from 'express'

const app = express();
const port = 3000;

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
    const { weaponName, armorName, tenNguoiChoi, idNguoiChoi } = req.body;

    if (!Array.isArray(weaponName) || !Array.isArray(armorName) || !tenNguoiChoi || !idNguoiChoi) {
        return res.status(400).json({ message: "khong hop le" });
    }

    const newPlayer = { weaponName, armorName, tenNguoiChoi, idNguoiChoi };
    players.push(newPlayer);

    res.status(201).json({ message: "Them thanh cong", newPlayer });
});

app.listen(port, () => {
    console.log(`http://localhost:${port}`);
});
