#include <ESP8266WiFi.h>

char* ssid_name_temp;
char* ssid_password_temp;

unsigned long wifi_timer;

void WIFI_ON_CONNECT()  {
  ArduinoOTA.setHostname(toChar(host_name + "_OTA"));
  ArduinoOTA.setPassword((const char *)"0816"); // Задаем пароль доступа для удаленной прошивки
  ArduinoOTA.begin();
  LOG("ArduinoOTA start : HostName =" + String(host_name) + "_OTA");
  server.begin();
  NBNS.begin(toChar(host_name));
  LOG("NetBIOS Started >>> http://" + host_name + ".local");
  WEBServer();
  LOG("HTTP Server Started");
  Blynk.begin(auth, ssid_name_temp, ssid_password_temp);
  LOG("Blynk Service Started: Token =" + String(auth) + " WIFI SSID Name=" + String(ssid_name_temp) + " WIFI SSID Password=" + String(ssid_password_temp));
}

void WIFI_ON_DISCONNECT()  {
  wifi_connection = false;
}

void WIFI_CREATE_AP(char ssid_ap_name[], char ssid_ap_password[], int channel_ap, int ssid_ap_hide) {
  WiFi.softAP(ssid_ap_name, ssid_ap_password, channel_ap, ssid_ap_hide);
  LOG("WIFI Access point name = " + String(ssid_ap_name));
  LOG("WIFI Access point password = " + String(ssid_ap_password));
  LOG("WIFI Access point channel = " + String(channel_ap));
  LOG("WIFI Hide access point = " + String(ssid_ap_hide));
}

void WIFI_CREATE_STA(char ssid_name[], char ssid_password[]) {
  WiFi.disconnect();
  WiFi.begin(ssid_name, ssid_password);
  LOG("WIFI Access point name = " + String(ssid_name));
  LOG("WIFI Access point password = " + String(ssid_password));
}

void WIFI_CHECK() {
  if (wifi_timer <= millis()) {
    wifi_timer = millis() + 500;
    if (WiFi.status() != WL_CONNECTED)  {
      if (wifi_connection == true) {
        WIFI_CREATE_STA(ssid_name_temp, ssid_password_temp);
      }
      LOG("WIFI Attempt connect = fail");
      WIFI_ON_DISCONNECT();
      digitalWrite(GREEN_LED_PIN, 1);
      digitalWrite(BLUE_LED_PIN, 1);
      if (digitalRead(RED_LED_PIN) == 0)  {
        digitalWrite(RED_LED_PIN, 1);
      }
      else  {
        digitalWrite(RED_LED_PIN, 0);
      }
    }
    else  {
      if (wifi_connection == false) {
        LOG("WIFI Connected");
        LOG("WIFI IP address =" + WiFi.localIP().toString());
        LOG("WIFI MAC address =" + String(WiFi.macAddress()));
        WIFI_ON_CONNECT();
        digitalWrite(RED_LED_PIN, 1);
      }
      wifi_connection = true;
      LOG("WIFI Signal power: " + String(WiFi.RSSI()) + " dBm");
    }
  }
}

void WIFIConnect(char ssid_name[], char ssid_password[], int wifi_mode, char ssid_ap_name[], char ssid_ap_password[], int channel_ap, int ssid_ap_hide)  {
  ssid_name_temp = ssid_name;
  ssid_password_temp = ssid_password;
  if (wifi_mode == 1)  {
    WiFi.mode(WIFI_STA);
    LOG("WIFI Mode = STA (Client)");
    WIFI_CREATE_STA(ssid_name, ssid_password);
  }
  if (wifi_mode == 2)  {
    WiFi.mode(WIFI_AP);
    LOG("WIFI Mode = AP (Access point)");
    WIFI_CREATE_AP(ssid_ap_name, ssid_ap_password, channel_ap, ssid_ap_hide);
  }
  if (wifi_mode == 3)  {
    WiFi.mode(WIFI_AP_STA);
    LOG("WIFI Mode = AP+STA (Mixed)");
    WIFI_CREATE_AP(ssid_ap_name, ssid_ap_password, channel_ap, ssid_ap_hide);
    WIFI_CREATE_STA(ssid_name, ssid_password);
  }
}



/* Самодостаточный модуль для работы с Wi-Fi
    Описание применения метода WIFIConnect
    WIFIConnect(char ssid[], char password[], boolean wifi_mode, char ssidname[], char ssid_password[], int channel_ap, int ssid_hide)
    char ssid_name[] Имя точки доступа к которой нужно подключиться
    char ssid_password[] Пароль точки доступа к кеоторой необходимо подключиться
    int wifi_mode Режим работы ( 1 - STA режим клиента, 2 - AP режим точки доступа, 3 - AP+STA режим смешанный )
    char ssid_ap_name[] Имя создаваемой точки доступа
    char ssid_ap_password[] Пароль создаваемой точки доступа
    int channel_ap Канал для создаваемой точки доступа от 1 до 13
    int ssid_ap_hide Нужно ли скрыть создаваемую точку доступа ( 0 - нет, 1 - да)



    unsigned long wifi_timer;

    if (wifi_timer <= millis()) {                 Таймер опроса статуса соединения
      wifi_timer = millis() + 500;
      WIFI_CHECK();
    }
*/
