#include "definicoes.h"
#include "configs.h"
#include "variaveis.h"
#include "Pinos.h"
#include "funcoes_gerais.h"
#include "Modulos.h"

BLYNK_WRITE(V3){ // Comandos terminal
  String log_terminal = param.asStr();
       if(log_terminal.substring(0,4)  == "Info")        {
        terminal.clear();
        terminal.println("Placa: " + NOME);
        terminal.println("IP: " + IP);
        terminal.println("Rede: " + String(ssid));
        terminal.println("Limite Bateria: " + String(bat_minima,1) + "V");
        terminal.println("Bateria Normal: " + String(bat_normal,1) + "V");
        terminal.flush();
  }
  else if(log_terminal.substring(0,3)  == "Cmd")         {
        terminal.clear();
        terminal.println(F("Limpar Limpar o terminal"));
        terminal.println(F("Info Mostra as configurações salvas "));
        terminal.println(F("Reset Da um reboot no sistema"));
        terminal.println(F("Bateria-10.8 Liga Relé em 10.8V"));
        terminal.println(F("Bateria+12.6 Desliga Relé em 12.6V"));

        terminal.flush();
  }
  else if(log_terminal.substring(0,6)  == "Limpar")      {
    terminal.clear();
  }
  else if(log_terminal.substring(0,5)  == "Reset")       {
  terminal.clear();
  delay(500);
  mostrar_terminal ("Resetando...");
  delay(2000);
  ESP.restart();
  }
  else if(log_terminal.substring(0,8)  == "Bateria-")    {
    String local = log_terminal.substring(8);
    bat_minima = local.toFloat();
    if(bat_minima == 0){
      terminal.println("Digite um número válido!"); terminal.flush();
    }
    else{
      terminal.println("Limite Bateria: " + String(bat_minima) + " Volts"); terminal.flush();
      tensao_minima = bat_minima * 10;
      EEPROM.write(0, tensao_minima);
      EEPROM.commit();
      delay(50);
    }
  }
  else if(log_terminal.substring(0,8)  == "Bateria+")    {
    String local = log_terminal.substring(8);
    bat_normal = local.toFloat();
    if(bat_normal == 0){
      terminal.println("Digite um número válido!"); terminal.flush();
    }
    else{
      terminal.println("Bateria normaliza em: " + String(bat_normal) + " Volts"); terminal.flush();
      tensao_normal = bat_normal * 10;
      EEPROM.write(1, tensao_normal);
      EEPROM.commit();
      delay(50);
    }
  }
  else{
    terminal.println("Comando Inválido!");        terminal.flush();  
  }
}

BLYNK_READ(V4) {Blynk.virtualWrite(V4, bat1_str + "  " + sinal_wifi);}

void normal(){
  readFile();
  converter_strings();
  conecta_wifi_blynk(ssid, pw);

  //Se não conseguir conectar a rede ao iniciar, reseta o ESP8266
  if (WiFi.status() != WL_CONNECTED){ ESP.restart(); }
  
  iniciar_OTA();
  setSyncInterval(10 * 60);
  timer.setInterval(  1000L,  verifica_conexao);
  timer.setInterval(  8000L,  Formatar_data_hora);
  timer.setInterval( 30000L,  chama_conecta_wifi_blynk);
  
}

void normal_loop(){
  restart_();
  ArduinoOTA.handle();
  timer.run();
  if(error_conect == true){ Blynk.run(); };
  error_conect = Blynk.connected();
}

void setup() {
  iniciar_PINs();
  if(serial_ativo  == true){ Serial.begin(9600); log_serial("  "); log_serial("Iniciando..."); delay(100); }
  openFS(); delay(500);

  WiFi.disconnect(); 
  delay(500);

  EEPROM.begin(10);
  tensao_minima = EEPROM.read(0);
  tensao_normal = EEPROM.read(1);
  bat_minima = tensao_minima / 10.0;
  bat_normal = tensao_normal / 10.0;
  
  if(digitalRead(config_wifi)){modo_config = true;} // Iniciar normalmente ou modo Config
  if(modo_config == true){config_rede();} else {normal();}
}

void loop() {
  if(modo_config){
    server.handleClient();
    delay(100);
  }
  else {
    normal_loop();
  }
}
