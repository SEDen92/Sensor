unsigned long check_time_timer;

int UNIX(unsigned long unix_time)
{
  const unsigned long seventyYears = 2208988800UL;
  unsigned long epoch = unix_time - seventyYears;
  hour = (epoch  % 86400L) / 3600;
  if (hour + 3 >= 24)  {
    hour = (hour + 3) - 24;
  }
  else  {
    hour = hour + 3;
  }
  minute = (epoch  % 3600) / 60;
  second = epoch % 60;
}

void CHECK_TIME() {
  if (check_time_timer <= millis()) {
    check_time_timer = millis() + 250;
    if (SynchTimeFlag == false && wifi_connection == true)
    {
      SynchTime();
      if (digitalRead(BLUE_LED_PIN) == 0)  {
        digitalWrite(BLUE_LED_PIN, 1);
      }
      else  {
        digitalWrite(BLUE_LED_PIN, 0);
      }
    }
    else  {
      if (SynchTimeFlag == true)
      {
        UNIX(secsSince1900 + ((millis() / 1000) - time_path));
        digitalWrite(BLUE_LED_PIN, 1);
        digitalWrite(GREEN_LED_PIN, 0);
      }
    }
    if (LED_Manual_Mode == false) {
      SWITCH_RELAY(Timer_Table(), false);
    }
  }
}

int SynchTime()
{
  LOG("Synchronization time start");
  boolean connect_ntp;
  WiFi.hostByName(ntpServerName, timeServerIP);
  sendNTPpacket(timeServerIP); // send an NTP packet to a time server
  int cb = NTPUDP.parsePacket();
  if (!cb) {
    LOG("Synchronization time failed");
    return connect_ntp = false;
  }
  else {
    NTPUDP.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer
    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    secsSince1900 = highWord << 16 | lowWord;
    LOG("UNIX Time= " + String(secsSince1900) + " milliseconds");
    UNIX(secsSince1900);
  }
  SynchTimeFlag = true;
  LOG("Synchronization time successfully");
  time_path = millis() / 1000;
  return connect_ntp = true;
}

unsigned long sendNTPpacket(IPAddress & address)
{
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;
  NTPUDP.beginPacket(address, 123); //NTP requests are to port 123
  NTPUDP.write(packetBuffer, NTP_PACKET_SIZE);
  NTPUDP.endPacket();
}
