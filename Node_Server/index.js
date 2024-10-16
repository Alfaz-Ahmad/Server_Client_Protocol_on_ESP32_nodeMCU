const express = require("express");
const cors = require("cors");

const app = express();

// Middleware to parse JSON data from requests
app.use(express.json());
app.use(cors());

// Simple GET route
app.get('/', function (req, res) {
    res.send({
        message: "Hello from the server!"
    });
});

// POST route to handle sensor data
app.post('/data', function (req, res) {
    // Extract temperature and humidity from the request body
    const { temperature, humidity } = req.body;

    if (temperature !== undefined && humidity !== undefined) {
        console.log("Temperature:", temperature);
        console.log("Humidity:", humidity);

        // Send a response back to the client
        res.send({
            temperature: temperature,
            humidity: humidity,
            status: 200,
            message: "Data received successfully"
        });
    } else {
        // Handle the case where temperature or humidity is missing
        res.status(400).send({
            status: 400,
            message: "Temperature or humidity not provided in the request"
        });
    }
});

// Start the server
const port = 5001;
app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});
