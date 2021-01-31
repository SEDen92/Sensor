#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <ESP8266NetBIOS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <BlynkSimpleEsp8266.h>
#include <WakeOnLan.h>

#define BLYNK_PRINT Serial

Adafruit_BMP280 bmp;

char ssid[] = "B.E.N.D.E.R."; //  your network SSID (name)
char pass[] = "25112003";
//char ssid[] = "SE-Den Wi-Fi NetWork";  //  your network SSID (name)
//char pass[] = "4815162342";// your network password (use for WPA, or use as key for WEP)

char auth[] = "_0pqLxSzg7EWSrOoJLzoqosJrE1cAIFc";

const char* ntpServerName = "time.nist.gov";
const String host_name = "Sensor";
const int serial_port_speed = 115200;
//const char* ntpServerName = "time.windows.com";
const char *MACAddress = "30:9C:23:28:85:7E";
const int NTP_PACKET_SIZE = 48;

ESP8266WebServer server(80);


WiFiUDP UDP;
WiFiUDP UDPCommand;
WiFiUDP NTPUDP;
WakeOnLan WOL(UDP);

IPAddress IPClock (192, 168, 0, 255);
IPAddress IPServer (192, 168, 0, 10);
IPAddress timeServerIP;

const int Port = 3555, NTPUDPPort = 2390;
float Pressure, Temperature;
byte packetBuffer[ NTP_PACKET_SIZE];
boolean SynchTimeFlag, wifi_connection, Frost, LED_Manual_Mode;

unsigned long TimerUDP, timer, time_path, secsSince1900;
byte second = 88, minute = 88, hour = 88;

const int RED_LED_PIN = 14;
const int GREEN_LED_PIN = 12;
const int BLUE_LED_PIN = 13;
const int SDA_PIN = 4;
const int SCL_PIN = 5;
const int LEDRelay = 15;

void setup() {
  Serial.begin(serial_port_speed);
  bmp.begin();
  NTPUDP.begin(NTPUDPPort);
  UDP.begin(Port);
  pinMode(LEDRelay, OUTPUT);
  digitalWrite(LEDRelay, 0);
  pinMode(RED_LED_PIN, OUTPUT);
  digitalWrite(RED_LED_PIN, 1);
  pinMode(GREEN_LED_PIN, OUTPUT);
  digitalWrite(GREEN_LED_PIN, 1);
  pinMode(BLUE_LED_PIN, OUTPUT);
  digitalWrite(BLUE_LED_PIN, 1);
  Initialization();
  WIFIConnect(ssid, pass, 1, "", "", 5, 0);
}

BLYNK_WRITE(V1)
{
  int pinValue = param.asInt();
  if (pinValue == 1)  SWITCH_RELAY(1, true);
  if (pinValue == 0)  SWITCH_RELAY(0, true);
}

BLYNK_WRITE(V2)
{
  int pinValue = param.asInt();
  if (pinValue == 1)  {
    WOL.sendMagicPacket(MACAddress);
    LOG("Send MagicPacket : " + String(MACAddress));
  }
}

void loop() {
  ArduinoOTA.handle();
  server.handleClient();
  Blynk.run();
  UDP_Receive();
  CHECK_TIME();
  WIFI_CHECK();
  if (timer <= millis()) {
    timer = millis() + 6000;
    if (millis() >= 86400000) ESP.restart();
    SEND_SENSOR_DATA();
  }
}
