WiFiClient client;
ESP8266WebServer server(80);

Adafruit_ADS1115 ads1;
Adafruit_ADS1115 ads2;
SSD1306Wire display1(0x3c, 4, 5);

WidgetRTC rtc;
BlynkTimer timer;
BLYNK_CONNECTED() {rtc.begin();}
WidgetLED led_ativo(V0);
WidgetTerminal terminal(V1);
