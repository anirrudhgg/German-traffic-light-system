#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <LittleFS.h> // Include the LittleFS library

// --- WiFi Credentials ---
const char* ssid = "iphone";
const char* password = "abcdefgh";

// --- Hardware Pin Definitions ---
const int redLedPin = D1;
const int yellowLedPin = D2;
const int greenLedPin = D3;

// --- State Machine Logic ---
enum LightState {
  STATE_RED,
  STATE_GREEN,
  STATE_YELLOW_SOLID,
  STATE_YELLOW_BLINK,
  STATE_RED_YELLOW_TRANSITION
};
LightState currentLightState = STATE_RED;

// --- Timing Logic ---
unsigned long previousMillis = 0;
const long yellowDuration = 2000;
const long redYellowDuration = 1500;
const long blinkInterval = 500;
bool blinkLedState = false;

// --- Web Server ---
ESP8266WebServer server(80);


// --- Core Functions ---

void setPhysicalLeds(bool red, bool yellow, bool green) {
  digitalWrite(redLedPin, red ? HIGH : LOW);
  digitalWrite(yellowLedPin, yellow ? HIGH : LOW);
  digitalWrite(greenLedPin, green ? HIGH : LOW);
}

// --- Web Server Handlers ---

// MODIFIED: This function now serves the HTML file from LittleFS
void handleRoot() {
  File file = LittleFS.open("/index.html", "r");
  if (!file) {
    server.send(500, "text/plain", "500: File not found");
    return;
  }
  // Use streamFile to send the file content. It's memory-efficient.
  // It automatically sets the Content-Type to "text/html" based on the file extension.
  server.streamFile(file, "text/html");
  file.close();
}

void handleState() {
  String stateString = "";
  switch (currentLightState) {
    case STATE_RED: stateString = "red"; break;
    case STATE_GREEN: stateString = "green"; break;
    case STATE_YELLOW_SOLID: stateString = "yellow"; break;
    case STATE_RED_YELLOW_TRANSITION: stateString = "red,yellow"; break;
    case STATE_YELLOW_BLINK:
      if (blinkLedState) { stateString = "yellow"; }
      else { stateString = ""; }
      break;
  }
  server.send(200, "text/plain", stateString);
}

void handleSet() {
  if (!server.hasArg("light")) {
    server.send(400, "text/plain", "Bad Request");
    return;
  }
  String lightColor = server.arg("light");

  if (lightColor == "red") {
    if (currentLightState == STATE_GREEN || currentLightState == STATE_YELLOW_BLINK) {
      currentLightState = STATE_YELLOW_SOLID;
      previousMillis = millis();
    }
  }
  else if (lightColor == "green") {
    if (currentLightState == STATE_RED || currentLightState == STATE_YELLOW_BLINK) {
      currentLightState = STATE_RED_YELLOW_TRANSITION;
      previousMillis = millis();
    }
  }
  else if (lightColor == "yellow") {
    if (currentLightState != STATE_YELLOW_BLINK) {
      currentLightState = STATE_YELLOW_BLINK;
      previousMillis = millis();  
      blinkLedState = false;
    }
  }

  server.send(200, "text/plain", "OK");
}

// --- Setup ---

void setup() {
  Serial.begin(115200);

  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);

  setPhysicalLeds(true, false, false);

  // ADDED: Initialize the LittleFS filesystem
  if (!LittleFS.begin()) {
    Serial.println("An error has occurred while mounting LittleFS");
    return;
  }
  Serial.println("LittleFS mounted successfully.");

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, handleRoot);
  server.on("/state", HTTP_GET, handleState);
  server.on("/set", HTTP_POST, handleSet);
  server.begin();
  Serial.println("HTTP server started");
}


// --- Main Loop ---

void loop() {
  server.handleClient();

  unsigned long currentMillis = millis();

  switch (currentLightState) {
    case STATE_RED:
      setPhysicalLeds(true, false, false);
      break;

    case STATE_GREEN:
      setPhysicalLeds(false, false, true);
      break;

    case STATE_YELLOW_SOLID:
      setPhysicalLeds(false, true, false);
      if (currentMillis - previousMillis >= yellowDuration) {
        currentLightState = STATE_RED;
      }
      break;
    
    case STATE_RED_YELLOW_TRANSITION:
      setPhysicalLeds(true, true, false);
      if (currentMillis - previousMillis >= redYellowDuration) {
        currentLightState = STATE_GREEN;
      }
      break;

    case STATE_YELLOW_BLINK:
      if (currentMillis - previousMillis >= blinkInterval) {
        previousMillis = currentMillis;
        blinkLedState = !blinkLedState;
        setPhysicalLeds(false, blinkLedState, false);
      }
      break;
  }
}
