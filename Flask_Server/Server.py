from flask import Flask, request, jsonify
import csv
import os
import datetime

app = Flask(__name__)

CSV_FILE = 'sensor_data.csv'

# Ensure CSV file exists with headers
if not os.path.exists(CSV_FILE):
    with open(CSV_FILE, mode='w', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(["Temperature", "Humidity", "Address", "Timestamp"])

# Route to handle POST requests
@app.route('/', methods=['POST'])
def receive_data():
    data = request.get_json()

    if 'temperature' in data and 'humidity' in data:
        temperature = data['temperature']
        humidity = data['humidity']

        # Append data to CSV file
        with open(CSV_FILE, mode='a', newline='') as file:
            writer = csv.writer(file)
            writer.writerow([temperature, humidity, request.remote_addr, datetime.datetime.now()])

        return jsonify({"message": "Data received successfully"}), 200
    else:
        return jsonify({"error": "Invalid data"}), 400

# Route to display CSV data
@app.route('/display_csv', methods=['GET'])
def display_csv():
    with open(CSV_FILE, mode='r') as file:
        csv_content = file.read()
    return f"<pre>{csv_content}</pre>"

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
