#include "definicoes.h"
#include "configs.h"
#include "variaveis.h"
#include "Pinos.h"
#include "funcoes_gerais.h"
#include "Modulos.h"

BLYNK_WRITE(V1){ // Comandos terminal
  String log_terminal = param.asStr();
       if(log_terminal.substring(0,4)  == "Info")        {
        terminal.clear();
        terminal.println("Placa: " + NOME);
        terminal.println("IP: " + IP);
        terminal.println("Rede: " + String(ssid));
        
        terminal.flush();
  }
  else if(log_terminal.substring(0,7)  == "ajustes")     {
        terminal.clear();
        terminal.println("v_const:  " + String(v_const, 3));
        terminal.println("i1_const: " + String(i1_const,3));
        terminal.println("i2_const: " + String(i2_const,3));
        terminal.println("i3_const: " + String(i3_const,3));
        terminal.println("i4_const: " + String(i4_const,3));
        terminal.flush();    
  }
  else if(log_terminal.substring(0,6)  == "eeprom")      {
    String local = log_terminal.substring(6);
    int i = local.toInt();
    if(i == 0){
      terminal.println("Digite um número válido!"); terminal.flush();
    }
    else{
        terminal.clear();
        for(int a = 0; a <= i; a++){
          terminal.println(String(a) + "=> " + EEPROM.read(a));
          terminal.flush();
          delay(10);
        }
    }
  }
  else if(log_terminal.substring(0,3)  == "Cmd")         {
        terminal.clear();
        terminal.println(F("Limpar Limpar o terminal"));
        terminal.println(F("Info Mostra as configurações salvas "));
        terminal.println(F("Reset Da um reboot no sistema"));

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
  else if(log_terminal.substring(0,4)  == "vdc:")        {
    String local = log_terminal.substring(4);
    v_const = local.toFloat();
    if(v_const == 0){
      terminal.println("Digite um número válido!"); terminal.flush();
    }
    else{
      terminal.println("v_const: " + String(v_const, 3) + " Volts"); terminal.flush();
      EEPROM.put(0,v_const);
      EEPROM.commit();
    }
  }
  else if(log_terminal.substring(0,3)  == "i1:")         {
    String local = log_terminal.substring(3);
    i1_const = local.toFloat();
    if(i1_const == 0){
      terminal.println("Digite um número válido!"); terminal.flush();
    }
    else{
      terminal.println("i1_const: " + String(i1_const, 3) + " Amp"); terminal.flush();
      EEPROM.put(5,i1_const);
      EEPROM.commit();
    }
  }
  else if(log_terminal.substring(0,3)  == "i2:")         {
    String local = log_terminal.substring(3);
    i2_const = local.toFloat();
    if(i2_const == 0){
      terminal.println("Digite um número válido!"); terminal.flush();
    }
    else{
      terminal.println("i2_const: " + String(i2_const, 3) + " Amp"); terminal.flush();
      EEPROM.put(10,i2_const);
      EEPROM.commit();
    }
  }
  else if(log_terminal.substring(0,3)  == "i3:")         {
    String local = log_terminal.substring(3);
    i3_const = local.toFloat();
    if(i3_const == 0){
      terminal.println("Digite um número válido!"); terminal.flush();
    }
    else{
      terminal.println("i3_const: " + String(i3_const, 3) + " Amp"); terminal.flush();
      EEPROM.put(15,i3_const);
      EEPROM.commit();
    }
  }
  else if(log_terminal.substring(0,3)  == "i4:")         {
    String local = log_terminal.substring(3);
    i4_const = local.toFloat();
    if(i4_const == 0){
      terminal.println("Digite um número válido!"); terminal.flush();
    }
    else{
      terminal.println("i4_const: " + String(i4_const, 3) + " Amp"); terminal.flush();
      EEPROM.put(20,i4_const);
      EEPROM.commit();
    }
  }
  else{
    terminal.println("Comando Inválido!");        terminal.flush();  
  }
}

BLYNK_READ(V2) {Blynk.virtualWrite(V2, valores_DC);}
BLYNK_READ(V3) {Blynk.virtualWrite(V3, valores_DC1);}

void normal(){
  readFile();
  converter_strings();
  iniciar_modulos();
  conecta_wifi_blynk(ssid, pw);

  //Se não conseguir conectar a rede ao iniciar, reseta o ESP8266
  if (WiFi.status() != WL_CONNECTED){ ESP.restart(); }
  
  iniciar_OTA();
  setSyncInterval(10 * 60);
  timer.setInterval(  1000L,  verifica_conexao);
  timer.setInterval(  4000L,  ler_ads1115);
  timer.setInterval(  8000L,  Formatar_data_hora);
  timer.setInterval( 30000L,  chama_conecta_wifi_blynk);
  
}

void ler_ads1115(){
  inverter_display = !inverter_display;

  volts = ADS1115("ADS2", 3, 10, v_const);
     i1 = ADS1115("ADS1", 3, 10, i1_const);
     i2 = ADS1115("ADS1", 2, 10, i2_const);
     i3 = ADS1115("ADS1", 1, 10, i3_const);
     i4 = ADS1115("ADS1", 0, 10, i4_const);


  volts_str = String(volts,2) + "V";
  i1_str    = String(i1, 2) + "A1";
  i2_str    = String(i2, 2) + "A2";
  i3_str    = String(i3, 2) + "A3";
  i4_str    = String(i4, 2) + "A4";
  valores_DC  = i1_str + "  " + i2_str + "  " + i3_str + "  " + i4_str;
  valores_DC1 = volts_str + "  " + IP + "  " + sinal_wifi;

  if(inverter_display)  { mostrar_display(i1_str, i2_str, i3_str, i4_str, 16, 0); }
  else{ mostrar_display(volts_str, conexao, IP, sinal_wifi, 16, 0); }
  
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
  iniciar_display();

  if(digitalRead(config_wifi)){modo_config = true;} // Iniciar normalmente ou modo Config
  if(modo_config == true){
    mostrar_display("MODO", "CONFIG", "ATIVADO", "", 16, 4); 
  } else {
    mostrar_display("Iniciando...", "PEREIRA", "INVERSORES", "", 16, 4);
  }
  
  if(serial_ativo  == true){ Serial.begin(9600); log_serial("  "); log_serial("Iniciando..."); delay(100); }
  
  openFS(); delay(500);

  WiFi.disconnect(); 
  delay(500);

  EEPROM.begin(100);
  EEPROM.get(0, v_const);
  EEPROM.get(5, i1_const);
  EEPROM.get(10,i2_const);
  EEPROM.get(15,i3_const);
  EEPROM.get(20,i4_const);

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
