#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

// Define constants
const char *ssid = "sk2_z7s";
const char *password = "tanumuyo";
const int maxRetries = 5;

bool relayState[10]; // Local relay states

AsyncWebServer server(80);

// Function to initialize WiFi in AP+STA mode with retries
void initWiFi()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP("ESP32_AP", "12345678");

  int retries = 0;
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED && retries < maxRetries)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
    retries++;
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("WiFi connected");
    Serial.println(WiFi.localIP());
  }
  else
  {
    Serial.println("Failed to connect to WiFi");
  }
}

// Handle relay toggle request
void handleToggleRelay(AsyncWebServerRequest *request, int relayNum)
{
  if (relayNum >= 0 && relayNum < 10)
  {
    relayState[relayNum] = !relayState[relayNum];
    request->send(200, "text/plain", "Relay toggled");
  }
  else
  {
    request->send(400, "text/plain", "Invalid relay number");
  }
}

// Setup LittleFS and serve files
void setupLittleFS()
{
  if (!LittleFS.begin())
  {
    Serial.println("An error has occurred while mounting LittleFS");
    return;
  }
  server.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");
}

// Main setup function
void setup()
{
  Serial.begin(115200);
  initWiFi();

  // Handle HTTP requests for toggling relays
  server.on("/toggleRelay/0", HTTP_GET, [](AsyncWebServerRequest *request)
            { handleToggleRelay(request, 0); });
  server.on("/toggleRelay/1", HTTP_GET, [](AsyncWebServerRequest *request)
            { handleToggleRelay(request, 1); });
  server.on("/toggleRelay/2", HTTP_GET, [](AsyncWebServerRequest *request)
            { handleToggleRelay(request, 2); });
  server.on("/toggleRelay/3", HTTP_GET, [](AsyncWebServerRequest *request)
            { handleToggleRelay(request, 3); });
  server.on("/toggleRelay/4", HTTP_GET, [](AsyncWebServerRequest *request)
            { handleToggleRelay(request, 4); });

  // Initialize LittleFS for serving static files
  setupLittleFS();

  // Start web server
  server.begin();
}

// Main loop function
void loop()
{
  // Placeholder for future logic
}
