#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <SimpleTimer.h>
char auth[] = "Substituir pela Chave do Blynk"; // Chave do Blynk
SimpleTimer timer;
char ssid[] = "Substituir pelo Nome do Wifi"; // Nome do Wifi
char pass[] = "Substituir pela Senha do Wifi"; // Senha do Wifi
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(8, 9); // RX, TX

float h;
float t;
float a;

#define rele1 3
#define rele2 4
#define cooler 5
// Your ESP8266 baud rate:
#define ESP8266_BAUD 9600

ESP8266 wifi(&EspSerial);

#include <DHT.h>

#define DHTPIN 6     // what digital pin we're connected to

#define DHTTYPE DHT11  // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);

#include <Wire.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;


void setup() {
  Serial.begin(9600);
  delay(10);
  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
  timer.setInterval(1000L, sendUptime);
  Blynk.begin(auth, wifi, ssid, pass);
  Serial.println("DHTxx test!");
  bmp.begin();
  dht.begin();
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(7, INPUT);

}
void sendUptime() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  h = dht.readHumidity();

  t = dht.readTemperature();

  a = (bmp.readAltitude(101500));

  Blynk.virtualWrite(V3, t);
  Blynk.virtualWrite(V2, h);
  Blynk.virtualWrite(V1, a);





}
void loop()
{
  h = dht.readHumidity();

  t = dht.readTemperature();
  Blynk.run();
  timer.run();

  if (digitalRead(7) == HIGH)
  {
    if (t <= 26)
    {
      digitalWrite(cooler, HIGH);
      digitalWrite(rele1, LOW);
    }
    else
    {
      digitalWrite(cooler, LOW);
      digitalWrite(rele1, HIGH);
    }
    if (h <= 43)
    {
      digitalWrite(rele2, LOW);
    }
    else
    {
      digitalWrite(rele2, HIGH);
    }
  }
  else
  {
    digitalWrite(cooler, HIGH);
    digitalWrite(rele1, HIGH);
    digitalWrite(rele2, HIGH);
  }
}
