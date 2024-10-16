
# Server Client Protocol on ESP32 NodeMCU

This project demonstrates a **client-server protocol** using an **ESP32 NodeMCU** microcontroller and a **DHT11 sensor** for temperature and humidity measurements. The ESP32 NodeMCU acts as the **client**, collecting sensor data and sending it to two different servers: one written in **Python** and the other in **Node.js**. Communication between the client and servers is handled via **REST API**.

## Features

- **ESP32 NodeMCU Client**: Reads temperature and humidity data from the DHT11 sensor and sends it to a server.
- **Python Server**: A server running locally to receive and process data from the ESP32 client.
- **Node.js Server**: Another server implemented in Node.js that also receives and processes data from the ESP32 client.
- **REST API**: Data transfer from the ESP32 NodeMCU to the servers is facilitated through HTTP POST requests.

## Hardware Requirements

- **ESP32 NodeMCU** (ESP32 DevKit)
- **DHT11 Sensor**
- Jumper wires
- Breadboard

## Software Requirements

- **Arduino IDE**: For programming the ESP32 NodeMCU.
- **Python**: For running the Python server.
- **Node.js**: For running the Node.js server.
- **REST API Libraries**: 
  - For ESP32: Use the `WiFi.h` and `HTTPClient.h` libraries in Arduino IDE for HTTP requests.
  - For Python: Use Flask to handle incoming HTTP requests.
  - For Node.js: Use Express.js to create the server and handle the requests.

## Circuit Diagram

1. **DHT11 Sensor** connections to ESP32 NodeMCU:
   - VCC -> 3.3V
   - GND -> GND
   - DATA -> GPIO Pin (GPIO 4)

## Project Structure

```plaintext
Server_Client_Protocol_on_ESP32_nodeMCU/
│
├── esp32_client/
│   ├── esp32_client.ino      # ESP32 client code (Arduino sketch)
│   └── dht.h                 # DHT sensor library (install from Arduino Library Manager)
│
├── python_server/
│   ├── server.py             # Python server code (Flask-based)
│   └── requirements.txt      # Python dependencies
│
├── nodejs_server/
│   ├── server.js             # Node.js server code (Express.js-based)
│   └── package.json          # Node.js dependencies
│
└── README.md                 # Project documentation
```

## Setup

### 1. ESP32 Client Setup
1. Install the **ESP32 board** in Arduino IDE.
2. Install the **DHT11 sensor library** from the Arduino Library Manager.
3. Connect the DHT11 sensor to the ESP32 as per the circuit diagram.
4. Upload the `esp32_client.ino` file to the ESP32 board.

### 2. Python Server Setup
1. Install Python 3.x.
2. Install Flask using the following command:

   ```bash
   pip install -r requirements.txt
   ```

3. Run the Python server:

   ```bash
   python server.py
   ```

### 3. Node.js Server Setup
1. Install Node.js.
2. Install dependencies:

   ```bash
   npm install
   ```

3. Run the Node.js server:

   ```bash
   node server.js
   ```

## How It Works

1. The ESP32 NodeMCU reads temperature and humidity data from the DHT11 sensor.
2. The ESP32 sends the data to either the Python server or the Node.js server using HTTP POST requests.
3. Both servers listen for incoming data on specified routes and log the received data.

## REST API Endpoints

### Python Server

- **Endpoint**: `/data`
- **Method**: `POST`
- **Expected Data Format**:
  ```json
  {
      "temperature": 25.5,
      "humidity": 60
  }
  ```

### Node.js Server

- **Endpoint**: `/api/data`
- **Method**: `POST`
- **Expected Data Format**:
  ```json
  {
      "temperature": 25.5,
      "humidity": 60
  }
  ```

## Future Enhancements

- Add more sensors to the ESP32.
- Store the data in a database (e.g., SQLite or MongoDB).
- Visualize the sensor data in real-time on a web interface.

  #-signing off!
