#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Inisialisasi koneksi WiFi
const char *ssid = "Barulah Kamar";
const char *password = "gantipassword";

const int ledPin = LED_BUILTIN;

// Inisialisasi klien WiFi
WiFiClient wifiClient;

// Inisialisasi klien MQTT
PubSubClient mqttClient(wifiClient);


void callback(char* topic, byte* payload, unsigned int length) {
    Serial.printf("Message arrived [%s] %.*s\n", topic, length, payload);

    if (strncmp((char*)payload, "ON", length) == 0) {
        digitalWrite(ledPin, LOW);
    }
    else if (strncmp((char*)payload, "OFF", length) == 0) {
        digitalWrite(ledPin, HIGH);
    }
}

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
    mqttClient.setCallback(callback);
    while (!mqttClient.connected())
    {
        Serial.println("Connecting to MQTT...");
        if (mqttClient.connect("ESP8266Client"))
        {
            Serial.println("connected");
            mqttClient.subscribe("lampu");
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
    if (!mqttClient.connected()) {
        setup();
    }
    mqttClient.loop();
}
