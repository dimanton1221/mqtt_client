#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Inisialisasi koneksi WiFi
const char *ssid = "Barulah Kamar";
const char *password = "gantipassword";

// LED BUILD IN
const int ledPin = LED_BUILTIN;

// Inisialisasi klien WiFi
WiFiClient wifiClient;

// Inisialisasi klien MQTT
PubSubClient mqttClient(wifiClient);

void setup()
{
    // Inisialisasi pin LED
    pinMode(ledPin, OUTPUT);
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
    const char *mqttServer = "192.168.2.100";

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
    // nyalahkan led
    digitalWrite(ledPin, HIGH);
    
}
