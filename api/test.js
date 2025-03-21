import axios from 'axios';
import dotenv from 'dotenv';

dotenv.config()

const args = process.argv.slice(2);
if (args.length === 0) {
    process.exit(1);
}

const jsonString = args[0];

try {
    const cleanJsonString = jsonString
        .replace(/\\\"/g, '"')
        .replace(/[\r\n\t]/g, '')
        .trim();
    
    const data = JSON.parse(cleanJsonString);
    console.log(data);


    const apiUrl =  'https://chuygame.vercel.app/players';

    axios.post(apiUrl, data)
        .then(response => {
            console.log(response.data);
        })
        .catch(error => {
            if (error.response) {
                console.error('loi API:', error.response.data);
            } else {
                console.error('loi ket noi:', error.message);
            }
        });
    
} catch (error) {
    console.error(error);
    console.error("JSON string received:", jsonString);
}