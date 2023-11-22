#include <Arduino.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <Servo.h>

Servo Servoku;

WiFiClient espClient;
PubSubClient client(espClient);

const char *ssid = "Barulah Kamar";
const char *password = "gantipassword";
const char *mqttServer = "192.168.2.100";

// KETERANGAN PIN
const int Gerbang = D5;
const int IR_Gerbang = D1;
const int IR_Gerbang2 = D0;
const int Parkir_1 = D3;
const int Parkir_2 = D2;

void setup_wifi()
{
  // delay(10);
  // Serial.println();
  // Serial.print("Mencoba terhubung ke: ");
  // Serial.println(ssid);
  WiFi.setHostname("Parkir");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  // Serial.println("");
  // Serial.println("WiFi connected");
  // Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect()
{
  while (!client.connected())
  {
    // Serial.print("");
    if (client.connect("ParkiRIOT"))
    {
      // Serial.println("connected");
    }
    else
    {
      delay(5000);
    }
  }
}

void setup()
{
  const int pos = 180; // variable to store the servo position
  client.setServer(mqttServer, 1883);
  Servoku.attach(Gerbang);
  Servoku.write(pos);
  Serial.begin(9600);
  setup_wifi();
  reconnect();
}

void loop()
{

  if (!client.connected())
  {
    reconnect();
  }
  client.loop();

  if (digitalRead(IR_Gerbang) == LOW || digitalRead(IR_Gerbang2) == LOW)
  {
    Servoku.write(0);
    delay(1000);
  }
  else
  {
    Servoku.write(180);
  }

  if (digitalRead(Parkir_1) == LOW)
  {
    client.publish("Parkir/1", "1");
    // Serial.println("Parkir 1 Terisi");
  }
  else
  {
    client.publish("Parkir/1", "0");
    // Serial.println("Parkir 1 Kosong");
  }

  if (digitalRead(Parkir_2) == LOW)
  {
    client.publish("Parkir/2", "1");
    // Serial.println("Parkir 2 Terisi");
  }
  else
  {
    client.publish("Parkir/2", "0");
    // Serial.println("Parkir 2 Kosong");
  }
}