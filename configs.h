WiFiClient client;
ESP8266WebServer server(80);

WidgetRTC rtc;
BlynkTimer timer;
BLYNK_CONNECTED() {rtc.begin();}
WidgetLED led_ativo(V0);
WidgetTerminal terminal(V3);
