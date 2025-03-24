# ChuyGame = Chinh + Duy
>[!Important]
>**Duy la gai anime nup duoi gam giuong**
## Cấu hình
### API
- cấu hình `DISCORD_WEBHOOK_URLDISCORD_WEBHOOK_URL` bằng
```bash
cp .env.example .env
```
- Và cả `Environment Variables` trên [Vercel](https://vercel.com/).
Sau đó chạy (Nếu không liên kết với github):
```bash
vercel --prod
```
- Thay thế `API URL` trong `test.js` nếu đã deploy lên vercel:
```js
const apiUrl =  'https://your_api_deploy.vercel.app/players';
```
### BOT DISCORD
```bash
cp example.config.py config.py
```
```py
TOKEN = 'TOKEN HERE'
API_URL= 'API URL HERE'
CHANNEL_ID= 'CHANNEL ID HERE'
```
### CPP
- Cài đặt file json.hpp
```bash
curl -L https://github.com/nlohmann/json/releases/latest/download/json.hpp -o src/data/json.hpp
```
- Build và chạy thử
```bash
cd src
g++ *.cpp data/*.cpp GameFlow/*.cpp -o main.exe; if ($?) { ./main.exe }
```
## Workflow 
```mermaid
sequenceDiagram  
    autonumber

    participant User as Người dùng (Console)
    participant API as API Backend
    participant Bot as Bot Discord
    participant Discord as Máy chủ Discord

    User ->> API: Gửi yêu cầu API
    API ->> Bot: Gửi dữ liệu đến bot
    Bot ->> Discord: Gửi kết quả vào server
    Discord ->> Bot: Nhận phản hồi từ server
    Bot ->> API: Reset dữ liệu API
