
void CHECK_RELAY()  {
  if (digitalRead(LEDRelay) == 0)  {
    Blynk.virtualWrite(V1, 0);
  }
  else  {
    Blynk.virtualWrite(V1, 1);
  }
}

void SWITCH_RELAY(boolean relay, boolean manual_mode)  {
  //Serial.print("Switch relay");
  if (relay == true)  {
    digitalWrite(LEDRelay, 1);
  }
  else  {
    digitalWrite(LEDRelay, 0);
  }
  LED_Manual_Mode = manual_mode;
  CHECK_RELAY();
}
