#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <WiFi.h>
#include <HTTPClient.h>

// DHT Sensor settings
#define DHTPIN 4        // GPIO pin where the DHT sensor is connected
#define DHTTYPE DHT11   // Change to DHT22 if you're using the DHT22 sensor

// Replace with your network credentials
const char* ssid = "Name_of_your_WIFI_network";         
const char* password = "Name_of_your_WIFI_network"; 

const char* serverName = "IP_address_of_your_localhost"; // Replace with your computer's IP address

DHT dht(DHTPIN, DHTTYPE);

uint32_t delayMS;  // Delay time in milliseconds

float temperature;
float humidity;

void setup() {
  Serial.begin(115200);

  // Initialize the DHT sensor
  dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("OK! IP=");
  Serial.println(WiFi.localIP());

  Serial.print("Fetching " + String(serverName) + "... ");
  delayMS = 1000;
}

void loop() {
  // Delay according to sensor's min_delay
  delay(delayMS);

  // Get temperature event and print its value
  temperature = dht.readTemperature();
  Serial.print(F("Temperature: "));
  Serial.print(temperature);
  Serial.println(F("°C"));


  // Get humidity event and print its value
  humidity = dht.readHumidity();
    Serial.print(F("Humidity: "));
    Serial.print(humidity);
    Serial.println(F("%"));

    // Serial.println(temperature);

    // Send data to the server if Wi-Fi is connected
    if (WiFi.status() == WL_CONNECTED) {
      // Create an HTTPClient object
      HTTPClient http;

      // Specify the URL for the POST request
      http.begin(serverName);

      // Specify the content-type header for JSON
      http.addHeader("Content-Type", "application/json");

      // Create JSON payload with temperature and humidity values
      String jsonPayload = "{\"temperature\": " + String(temperature) + ", \"humidity\": " + String(humidity) + "}";

      // Send the POST request
      int httpResponseCode = http.POST(jsonPayload);

      // Check the response from the server
      if (httpResponseCode > 0) {
        String response = http.getString();  // Get the response payload
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        Serial.println("Server response: " + response);
      } else {
        Serial.print("Error on sending POST: ");
        Serial.println(httpResponseCode);
      }

      // End the HTTP connection
      http.end();
    } else {
      Serial.println("WiFi not connected");
    }
}
