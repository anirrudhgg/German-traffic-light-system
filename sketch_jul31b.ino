void turnOffAllLEDs() {
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN, LOW);
}

void handleRedOn() {
  turnOffAllLEDs();
  digitalWrite(LED_RED, HIGH);
  server.send(200, "text/plain", "Red LED ON");
}


void handleYellowOn() {
  turnOffAllLEDs();
  digitalWrite(LED_YELLOW, HIGH);
  server.send(200, "text/plain", "Yellow LED ON");
}


void handleGreenOn() {
  turnOffAllLEDs();
  digitalWrite(LED_GREEN, HIGH);
  server.send(200, "text/plain", "Green LED ON");
}


void setup() {

  server.on("/redon", handleRedOn);
  server.on("/yellowon", handleYellowOn);
  server.on("/greenon", handleGreenOn);

  server.begin();
}
