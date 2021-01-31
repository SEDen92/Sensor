void UDP_Send(IPAddress IP, int Port, String message )  {
  char Buffer[sizeof(message)];
  UDP.beginPacket(IP, Port);
  strcpy(Buffer, message.c_str());
  UDP.write(Buffer);
  UDP.endPacket();
}

void UDP_Receive() {
  char incomingPacket[255];
  if (TimerUDP <= millis()) {
    TimerUDP = millis() + 300;
    int packetSize = UDP.parsePacket();
    if (packetSize)
    {
      int len = UDP.read(incomingPacket, UDP_TX_PACKET_MAX_SIZE);
      if (len > 0)
      {
        incomingPacket[len] = 0;
      }
      Serial.println(incomingPacket);
      if (String(incomingPacket) == "reset") ESP.restart();
      if (String(incomingPacket) == "sensor") SEND_SENSOR_DATA();
    }
  }
}
