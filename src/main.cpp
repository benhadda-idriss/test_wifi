#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>

const char *ssid = "batwifi";
const char *password = "12345678";

WiFiUDP udp;

const unsigned int localPort = 8080;

char capteurVitesse[50];
char capteurTension1[50];
char capteurTension2[50];
char capteurTension3[50];
char capteurTension4[50];
char capteurTension5[50];
char capteurCourant[50];
char capteurLuminosite[50];

int val = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println("\n[*] Creating AP");
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  Serial.print("[+] AP Created with IP Gateway ");
  Serial.println(WiFi.softAPIP());
  udp.begin(localPort);
}

void loop()
{

  val += 1;
  int sizePacket = udp.parsePacket();

  if (sizePacket)
  {
    Serial.print("Received packet of size ");
    Serial.println(sizePacket);
    Serial.print("From IP: ");
    Serial.println(udp.remoteIP());
    Serial.print("From port: ");
    Serial.println(udp.remotePort());

    // Read the packet into a buffer
    char packetBuffer[255];
    int len = udp.read(packetBuffer, 255);
    if (len > 0)
    {
      packetBuffer[len] = '\0'; // Null-terminate the string
    }
    Serial.println("Contents:");
    Serial.println(packetBuffer);
  }
  udp.beginPacket("192.168.4.2", 8080);
  sprintf(capteurCourant, "courant : %d", val);
  udp.write((uint8_t *)capteurCourant, strlen(capteurCourant));
  udp.endPacket();

  udp.beginPacket("192.168.4.2", 8080);
  sprintf(capteurTension1, "tension1 : %d", val);
  udp.write((uint8_t *)capteurTension1, strlen(capteurTension1));
  udp.endPacket();

  udp.beginPacket("192.168.4.2", 8080);
  sprintf(capteurTension2, "tension2 : %d", val);
  udp.write((uint8_t *)capteurTension2, strlen(capteurTension2));
  udp.endPacket();

  udp.beginPacket("192.168.4.2", 8080);
  sprintf(capteurTension3, "tension3 : %d", val);
  udp.write((uint8_t *)capteurTension3, strlen(capteurTension3));
  udp.endPacket();

  udp.beginPacket("192.168.4.2", 8080);
  sprintf(capteurTension4, "tension4 : %d", val);
  udp.write((uint8_t *)capteurTension4, strlen(capteurTension4));
  udp.endPacket();

  udp.beginPacket("192.168.4.2", 8080);
  sprintf(capteurTension5, "tension5 : %d", val);
  udp.write((uint8_t *)capteurTension5, strlen(capteurTension5));
  udp.endPacket();

  udp.beginPacket("192.168.4.2", 8080);
  sprintf(capteurVitesse, "vitesse : %d", val);
  udp.write((uint8_t *)capteurVitesse, strlen(capteurVitesse));
  udp.endPacket();

  udp.beginPacket("192.168.4.2", 8080);
  sprintf(capteurLuminosite, "luminosite : %d", val);
  udp.write((uint8_t *)capteurLuminosite, strlen(capteurLuminosite));
  udp.endPacket();
}