#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Inisialisasi koneksi WiFi
const char *ssid = "modules";
const char *password = "12345678";

// Inisialisasi klien WiFi
WiFiClient wifiClient;

// Inisialisasi klien MQTT
PubSubClient mqttClient(wifiClient);

void setup()
{
    // Mulai serial
    Serial.begin(9600);

    // Hubungkan ke WiFi
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    // Tunggu sampai terhubung ke WiFi
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");
    }

    // Tampilkan informasi WiFi
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Gateway: ");
    Serial.println(WiFi.gatewayIP());
    const char *mqttServer = "192.168.137.1";

    // Hubungkan ke MQTT broker
    mqttClient.setServer(mqttServer, 1883);
    while (!mqttClient.connected())
    {
        Serial.println("Connecting to MQTT...");
        if (mqttClient.connect("ESP8266Client"))
        {
            Serial.println("connected");
        }
        else
        {
            Serial.print("failed with state ");
            Serial.print(mqttClient.state());
            delay(2000);
        }
    }
}

void loop()
{
    // Generate a random number between 0 and 100
    int randomNumber = rand() % 101;

    // Convert the random number to a string
    char message[4];
    itoa(randomNumber, message, 10);

    // Publish the random number to the "randomTOPIK" topic
    mqttClient.publish("random", message);

    // Wait for 5 seconds before generating and publishing the next random number
    delay(1);
}
