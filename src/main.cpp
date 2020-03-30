#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include "AsyncJson.h"

const char *ssid = "Nom du réseau";
const char *password = "Mot de passe";

//const int led = 2;
//const int capteurLuminosite = 34;

AsyncWebServer server(80);

void setup()
{
    //----------------------------------------------------Serial
    Serial.begin(115200);
    Serial.println("\n");

    //----------------------------------------------------GPIO
    // pinMode(led, OUTPUT);
    // digitalWrite(led, LOW);
    // pinMode(capteurLuminosite, INPUT);

    //----------------------------------------------------SPIFFS
    if (!SPIFFS.begin())
    {
        Serial.println("Erreur SPIFFS...");
        return;
    }

    File root = SPIFFS.open("/");
    File file = root.openNextFile();

    while (file)
    {
        Serial.print("File: ");
        Serial.println(file.name());
        file.close();
        file = root.openNextFile();
    }

    //----------------------------------------------------WIFI
    WiFi.begin(ssid, password);
    Serial.print("Tentative de connexion...");

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(100);
    }

    Serial.println("\n");
    Serial.println("Connexion etablie!");
    Serial.print("Adresse IP: ");
    Serial.println(WiFi.localIP());

    //----------------------------------------------------SERVER
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/index.html", "text/html");
    });

    server.on("/css/button_material.css", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/css/button_material.css", "text/css");
    });

    server.on("/css/input_material.css", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/css/button_material.css", "text/css");
    });

    server.on("/css/styles.css", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/css/button_material.css", "text/css");
    });

    server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/script.js", "text/javascript");
    });

    server.on("/getParameters", HTTP_GET, [](AsyncWebServerRequest *request) {
        File fileParameters = SPIFFS.open("/db/parameters.txt", FILE_WRITE);
        std::string parameters = "";
        while (fileParameters.available())
        {
            parameters += fileParameters.read();
        }

        fileParameters.close();
        char param[parameters.size() + 1];
        strcpy(param, parameters.c_str());
        request->send(200, "application/json", param);
    });

    server.begin();
    Serial.println("Serveur actif!");
}

void loop()
{
}