void LOG(String message)  {
  message = "***" + SYS_TIME() + "/" + UTC_TIME() + "*** " + message;
  Serial.println(message);
}

String UTC_TIME() {
  if (hour == 88)  {
    return "don't connect NTP server";
  }
  else  {
    return Time_convert(hour) + ":" + Time_convert(minute) + ":" + Time_convert(second);
  }
}

String SYS_TIME() {
  int hour_system, minute_system, second_system;
  int sys_seconds = (millis() / 1000);
  if (sys_seconds >= 3600)  {
    hour_system = sys_seconds / 3600;
  }
  else  {
    hour_system = 0;
  }
  if (sys_seconds >= 60)  {
    minute_system = (sys_seconds - (hour_system * 3600)) / 60;
  }
  else  {
    minute_system = 0;
  }
  second_system = (sys_seconds - (minute_system * 60));
  return Time_convert(hour_system) + ":" + Time_convert(minute_system) + ":" + Time_convert(second_system);
}

String Time_convert(int t)  {
  if (t < 10)  {
    return "0" + String(t);
  }
  else  {
    return String(t);
  }
}

char* toChar(String str)  {
  static char char_array[sizeof(str)];
  //Serial.println(message.length());
  str.toCharArray(char_array, sizeof(str));
  //Serial.println(symbol_temp);
  return char_array;
}

void Initialization()  {
  Serial.println("");
  Serial.println("***************************");
  LOG("Sketch : " + host_name);
  LOG("Version : 3.0");
  LOG("Start Serial port speed =" + String(serial_port_speed));
  LOG("I2C start : SDA =" + String(SDA_PIN) + " SCL =" + String(SCL_PIN));
  LOG("LED Relay pin =" + String(LEDRelay));
  LOG("LED Red pin =" + String(RED_LED_PIN));
  LOG("LED Green pin =" + String(GREEN_LED_PIN));
  LOG("BMP280 Start");
  LOG("NTPUDP port =" + String(NTPUDPPort));
}
