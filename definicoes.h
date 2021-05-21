// Sempre lembrar de definir o tamanho pra 4MB (FS:1Mb OTA:~1019)
#include "FS.h"
#include <ArduinoOTA.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <LittleFS.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <EEPROM.h>
#include <WidgetRTC.h>
#include <TimeLib.h>
#include <Adafruit_Sensor.h>

#define config_wifi 16 // Input
