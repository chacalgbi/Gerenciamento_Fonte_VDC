#include "definicoes.h"
#include "configs.h"
#include "variaveis.h"
#include "Pinos.h"
#include "funcoes_gerais.h"
#include "Modulos.h"

BLYNK_WRITE(V1){ // Comandos terminal
  String log_terminal = param.asStr();
       if(log_terminal.substring(0,4)  == "info")        {
        terminal.clear();
        terminal.println("Placa: " + NOME);
        terminal.println("IP: " + IP);
        terminal.println("Sinal Wifi: " + sinal_wifi);
        terminal.println("Rede: " + String(ssid));
        terminal.println("Limite Porta1: " + String(i1_limit, 2));
        terminal.println("Limite Porta2: " + String(i2_limit, 2));
        terminal.println("Limite Porta3: " + String(i3_limit, 2));
        terminal.println("Limite Porta4: " + String(i4_limit, 2));
        
        terminal.flush();
  }
  else if(log_terminal.substring(0,3)  == "cmd")         {
        terminal.clear();
        terminal.println(F("limpar - Limpar o terminal"));
        terminal.println(F("info - Mostra as configurações salvas"));
        terminal.println(F("reset - Da um reboot no sistema"));
        terminal.println(F("limite1:0.45 - Imax da porta1 p/ 0.45A"));

        terminal.flush();
  }
  else if(log_terminal.substring(0,6)  == "limpar")      {
    terminal.clear();
  }
  else if(log_terminal.substring(0,5)  == "reset")       {
  terminal.clear();
  delay(500);
  mostrar_terminal ("Resetando...");
  delay(2000);
  ESP.restart();
  }
  else if(log_terminal.substring(0,8)  == "limite1:")    {
    String local = log_terminal.substring(8);
    i1_limit = local.toFloat();
    if(i1_limit == 0){
      terminal.println("Digite um número válido!"); terminal.flush();
    }
    else{
      terminal.println("Limite Porta1: " + String(i1_limit, 2) + " Amp"); terminal.flush();
      EEPROM.put(25,i1_limit);
      EEPROM.commit();
    }
  }
  else if(log_terminal.substring(0,8)  == "limite2:")    {
    String local = log_terminal.substring(8);
    i2_limit = local.toFloat();
    if(i2_limit == 0){
      terminal.println("Digite um número válido!"); terminal.flush();
    }
    else{
      terminal.println("Limite Porta2: " + String(i2_limit, 2) + " Amp"); terminal.flush();
      EEPROM.put(30,i2_limit);
      EEPROM.commit();
    }
  }
  else if(log_terminal.substring(0,8)  == "limite3:")    {
    String local = log_terminal.substring(8);
    i3_limit = local.toFloat();
    if(i3_limit == 0){
      terminal.println("Digite um número válido!"); terminal.flush();
    }
    else{
      terminal.println("Limite Porta3: " + String(i3_limit, 2) + " Amp"); terminal.flush();
      EEPROM.put(35,i3_limit);
      EEPROM.commit();
    }
  }
  else if(log_terminal.substring(0,8)  == "limite4:")    {
    String local = log_terminal.substring(8);
    i4_limit = local.toFloat();
    if(i4_limit == 0){
      terminal.println("Digite um número válido!"); terminal.flush();
    }
    else{
      terminal.println("Limite Porta4: " + String(i4_limit, 2) + " Amp"); terminal.flush();
      EEPROM.put(40,i4_limit);
      EEPROM.commit();
    }
  }

  //Configurações minhas
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
  else if(log_terminal.substring(0,6)  == "apagar")      {
    String local = log_terminal.substring(6);
    int i = local.toInt();
    if(i == 0){
      terminal.println("Digite um número válido!"); terminal.flush();
    }
    else{
        terminal.clear();
        terminal.println("Apagando EEPROM..."); terminal.flush();
        for(int a = 0; a <= i; a++){
          EEPROM.write(a, 0);
          EEPROM.commit();
        }
        terminal.println("EEPROM Apagada"); terminal.flush();
        
        for(int a = 0; a <= i; a++){
          terminal.println(String(a) + "=> " + EEPROM.read(a));
          terminal.flush();
          delay(5);
        }
    }
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
  else if(log_terminal.substring(0,3)  == "i2c")         {
    terminal.clear();
    procura_i2c();
  }
  else{
    terminal.println("Comando Inválido!"); terminal.flush();  
  }
}

BLYNK_READ(V2) {Blynk.virtualWrite(V2, valores_DC1);}
BLYNK_READ(V3) {Blynk.virtualWrite(V3, valores_DC2);}
BLYNK_READ(V4) {Blynk.virtualWrite(V4, valores_DC3);}

void limites(){
  aviso = "";
  
  if(i1 > i1_limit && i1_trava == false){
    aviso = F("Porta1 IMAX");
    i1_trava = true;
    mostrar_terminal(aviso);
    Blynk.notify(NOME + ": " + aviso);
    }

  if(i2 > i2_limit && i2_trava == false){
    aviso = F("Porta2 IMAX");
    i2_trava = true;
    mostrar_terminal(aviso);
    Blynk.notify(NOME + ": " + aviso);
    }

  if(i3 > i3_limit && i3_trava == false){
    aviso = F("Porta3 IMAX");
    i3_trava = true;
    mostrar_terminal(aviso);
    Blynk.notify(NOME + ": " + aviso);
    }

  if(i4 > i4_limit && i4_trava == false){
    aviso = F("Porta4 IMAX");
    i4_trava = true;
    mostrar_terminal(aviso);
    Blynk.notify(NOME + ": " + aviso);
    }



  if(i1 < i1_limit && i1_trava == true) {
    i1_trava = false;
    mostrar_terminal(F("Porta1 OK"));
    }

  if(i2 < i2_limit && i2_trava == true) {
    i2_trava = false;
    mostrar_terminal(F("Porta2 OK"));
    }

  if(i3 < i3_limit && i3_trava == true) {
    i3_trava = false;
    mostrar_terminal(F("Porta3 OK"));
    }

  if(i4 < i4_limit && i4_trava == true) {
    i4_trava = false;
    mostrar_terminal(F("Porta4 OK"));
    }

}

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
  timer.setInterval(  2500L,  ler_ads1115);
  timer.setInterval(  6000L,  Formatar_data_hora);
  timer.setInterval(  8000L,  limites);
  timer.setInterval( 30000L,  chama_conecta_wifi_blynk);
  
}

float ACS712(){
  long somaDasCorrentes = 0;
  long mediaDasCorrentes = 0;
  int ref = 20014;
  int leituras = 1000;
  float tensao = 0.0;

  for ( int h=0; h < leituras; h++) {
    somaDasCorrentes += pow((ads2.readADC_SingleEnded(2) - ref),2); 
    delay(1);
  }
  
  mediaDasCorrentes = sqrt(somaDasCorrentes / leituras);
  tensao = ads2.computeVolts(mediaDasCorrentes);
  
  return tensao;
}

void ler_ads1115(){
  inverter_display = !inverter_display;

  //ACS712_v = ACS712();
  //ACS712_i = ACS712_v / 0.1;

  //AC_V = String(ACS712_v,3) + "V";
  //AC_I = String(ACS712_i,3) + "A";

  volts = ADS1115("ADS2", 3, 10, v_const);
     i1 = ADS1115("ADS1", 3, 10, i1_const);
     i2 = ADS1115("ADS1", 2, 10, i2_const);
     i3 = ADS1115("ADS1", 1, 10, i3_const);
     i4 = ADS1115("ADS1", 0, 10, i4_const);
     i_total = i1 + i2 + i3 + i4;
     potencia = i_total * volts;
     pot1 = i1 * volts;
     pot2 = i2 * volts;
     pot3 = i3 * volts;
     pot4 = i4 * volts;


  volts_str    = String(volts,0)    + "V"; 
  potencia_str = String(potencia) + "W";
  i_total_str  = String(i_total,2)  + "A";
  i1_str    = "P1 " + String(i1, 2) + "A " + String(pot1) + "W";
  i2_str    = "P2 " + String(i2, 2) + "A " + String(pot2) + "W";
  i3_str    = "P3 " + String(i3, 2) + "A " + String(pot3) + "W";
  i4_str    = "P4 " + String(i4, 2) + "A " + String(pot4) + "W";

  valores_DC1 = volts_str + "  " + i_total_str + "  " + potencia_str;
  valores_DC2 = i1_str + "  " + i2_str;
  valores_DC3 = i3_str + "  " + i4_str;

  if(inverter_display)  { mostrar_display(i1_str, i2_str, i3_str, i4_str, 16, 0); }
  else{ mostrar_display(volts_str, conexao, IP, sinal_wifi, 16, 0); }
  
}

void normal_loop(){
  restart_();
  ArduinoOTA.handle();
  timer.run();
  if(error_conect == true){ Blynk.run(); };
  error_conect = Blynk.connected();

  if(digitalRead(config_wifi)){
    mostrar_display("PEREIRA", "INVERSORES", "(81)9.8808", "9699", 16, 3);
  }
}

void setup() {
  iniciar_PINs();
  iniciar_display();

  if(digitalRead(config_wifi)){modo_config = true;} // Iniciar normalmente ou modo Config
  if(modo_config == true){
    mostrar_display("MODO", "CONFIG", "ATIVADO", "", 16, 3); 
  } else {
    mostrar_display("Iniciando...", "PEREIRA", "INVERSORES", "", 16, 2);
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
  
  EEPROM.get(25,i1_limit);
  EEPROM.get(30,i2_limit);
  EEPROM.get(35,i3_limit);
  EEPROM.get(40,i4_limit);

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
