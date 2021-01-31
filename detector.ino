void SEND_SENSOR_DATA() {
  float Temperature = GET_TEMPERATURE();
  float Pressure = GET_PRESSURE();
  UDP_SEND(IPClock, Port, "Ts=" + String(Temperature).substring(0, String(Temperature).length() - 1));
  UDP_SEND(IPClock, Port, "Pr=" + String(Pressure).substring(0, String(Pressure).length() - 1));
  if (Temperature > 0)  {
    Frost = false;
    Blynk.virtualWrite(V5, "+" + String(Temperature).substring(0, String(Temperature).length() - 1) + " C");
  }
  else  {
    Frost = true;
    Blynk.virtualWrite(V5, String(Temperature).substring(0, String(Temperature).length() - 1) + " C");
  }
  Blynk.virtualWrite(V6, String(Pressure).substring(0, String(Pressure).length() - 1) + " мм.рт.ст.");
  CHECK_RELAY();
}

float GET_TEMPERATURE() {
  return bmp.readTemperature();
}

float GET_PRESSURE() {
  return bmp.readPressure() / 133.3224;
}
