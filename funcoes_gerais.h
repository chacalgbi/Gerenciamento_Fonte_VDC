void restart_(){
  yield();      //Alimenta o Watchdog de Software. 3 Segundos.
  ESP.wdtFeed();//Alimenta o Watchdog de Hardware. 8 Segundos.
}

void barra_progresso(int p1, int p2, int p3, int p4, int p5, int tempo){
  for (int x=0; x<p5; x++){ // p5 é o valor total da barra
    display1.drawProgressBar(p1, p2, p3, p4, x); // Onde começa a barra a esquerda
                                                 // Linha onde a barra vai ficar
                                                 // Onde finaliza a barra a Direita
                                                 // Largura da Barra
                                                 // Valor a ser mostrado na progressao da barra
    display1.display();
    delay(tempo);
  }
}

void mostrar_display(String t1, String t2, String t3, String t4, byte fonte, float segundos){
  restart_();
  int tempo = segundos * 1000;
  display1.clear();
  display1.setTextAlignment(TEXT_ALIGN_CENTER);
  if(fonte == 10){display1.setFont(ArialMT_Plain_10);}
  if(fonte == 16){display1.setFont(ArialMT_Plain_16);}
  display1.drawString(64,  0, t1);
  display1.drawString(64, 16, t2);
  display1.drawString(64, 32, t3);
  display1.drawString(64, 48, t4);
  display1.display();
  delay(tempo);
}

void mostrar_terminal (String aviso){
  terminal.print(currentTime);
  terminal.print(" - ");
  terminal.println(aviso);
  terminal.flush();
}

void log_serial(String x){
  if(serial_ativo == true){
    Serial.println(x);
  }
}

void verifica_conexao(){ // Pisca o LED do App.
  if(error_conect == true){
    conexao = F("OnLine");
    if(inverter){led_ativo.on();}
    else{led_ativo.off(); }
  }
  else{
    conexao = "OffLine";
  }
  inverter = !inverter;
}

void converter_strings(){
  tamanho_rede  = REDE.length();
  tamanho_senha = SENHA.length();
  tamanho_nome  = NOME.length();
  
  REDE.toCharArray (ssid,  tamanho_rede);
  SENHA.toCharArray(pw,    tamanho_senha);
  NOME.toCharArray(device, tamanho_nome);
  
}
 
void formatFS(void){
  LittleFS.format();
}

void createFile(void){
  File wFile;
 
  //Cria o arquivo se ele não existir
  if(LittleFS.exists("/log.txt")){
    log_serial("Arquivo ja existe!");
  } else {
    log_serial("Criando o arquivo...");
    wFile = LittleFS.open("/log.txt","w+");
 
    //Verifica a criação do arquivo
    if(!wFile){
      log_serial("Erro ao criar arquivo!");
    } else {
      log_serial("Arquivo criado com sucesso!");
    }
  }
  wFile.close();
}
 
void deleteFile(void) {
  //Remove o arquivo
  if(!LittleFS.remove("/log.txt")){
    log_serial("Erro ao remover arquivo!");
    mostrar_display("Erro ao", "remover o", "arquivo", "", 16, 0); 
  } else {
    log_serial("Arquivo removido com sucesso!");
    mostrar_display("Arquivo", "removido", "com", "sucesso", 16, 0); 
  }
}
 
void writeFile(String msg) {
 
  //Abre o arquivo para adição (append)
  //Inclue sempre a escrita na ultima linha do arquivo
  File rFile = LittleFS.open("/log.txt","a+");
 
  if(!rFile){
    log_serial("Erro ao abrir arquivo!");
    mostrar_display("Erro ao", "abrir o", "arquivo", ":(", 16, 2); 
  } else {
    rFile.println(msg);
    log_serial(msg);
  }
  rFile.close();
}
 
void readFile(void) {
  byte cont = 1;
  File rFile = LittleFS.open("/log.txt","r");
  log_serial("Lendo Arquivo SPIFFS...");
  while(rFile.available()) {
    if(cont == 1){REDE  = rFile.readStringUntil('\n'); log_serial(REDE);  }
    if(cont == 2){SENHA = rFile.readStringUntil('\n'); log_serial(SENHA); }
    if(cont == 3){NOME  = rFile.readStringUntil('\n'); log_serial(NOME);  }
    cont++;
    delay(10);
  }
  rFile.close();
}
 
void closeFS(void){
  LittleFS.end();
}
 
void openFS(void){
  //Abre o sistema de arquivos
  if(!LittleFS.begin()){
    log_serial("Erro ao abrir o sistema de arquivos");
    mostrar_display("Erro ao", "abrir o", "sistema de", "arquivos", 16, 1); 
  } else {
    log_serial("Sistema de arquivos aberto com sucesso!");
    //mostrar_display("FS", "aberto", "com", "sucesso", 16, 1);
  }
  delay(tempo);
}

void handleRoot() {
  mostrar_display("Modo Config", "Digite as", "informacoes", "", 16, 0);
  //Go to http://192.168.4.1 in a web browser
String html  = "<!DOCTYPE html><head><html lang='pt-br'><meta charset='UTF-8'><meta http-equiv='X-UA-Compatible' content='IE=edge'><meta name='viewport' content='width=device-width, initial-scale=1'><title>Configurar WIFI</title>";
       html += "</head><body align='center'>";
       html += "<h3>CONFIGURAÇÃO<br> WIFI</h3>";
       html += "<form method='POST' action='/form'>";
       html += "<input type=text placeholder='DIGITE O NOME DA REDE'  name=txt_ssid /><br><br>";
       html += "<input type=text placeholder='DIGITE A SENHA DA REDE' name=txt_pw   /><br><br>";
       html += "<input type=text placeholder='NOME DO LOCAL'          name=txt_nome /><br><br>";
       html += "<input type=submit name=botao value=Enviar />";
       html += "</form>";
       html += "</body></html>";
server.send(200, "text/html", html);
}

void formularioEnviado() {
String html =  "<!DOCTYPE html><head><html lang='pt-br'><meta charset='UTF-8'><meta http-equiv='X-UA-Compatible' content='IE=edge'><meta name='viewport' content='width=device-width, initial-scale=1'><title>WIFI Configurado</title></head><body align='center'><h3>Seu dispositivo foi<br> configurado</h3>";
       html += "<h1><font color='red'>SSID: ";
       html += server.arg("txt_ssid");
       html += "</h1></font><br><h1><font color='green'>SENHA: ";
       html += server.arg("txt_pw");
       html += "</font></h1></body></html>";
       server.send(200, "text/html", html);

  REDE  = server.arg("txt_ssid"); REDE.trim();  writeFile(REDE);
  SENHA = server.arg("txt_pw");   SENHA.trim(); writeFile(SENHA);
  NOME  = server.arg("txt_nome"); NOME.trim();  writeFile(NOME);
  //mostrar(1, false,  "Sucesso", REDE, SENHA, NOME,0,0,0,0);
  mostrar_display("Salvo", REDE, SENHA, NOME, 16, 1);
}

void config_rede(){
  WiFi.softAP("Fonte");
  server.on("/", handleRoot);
  server.on("/form", HTTP_POST, formularioEnviado);
  server.begin();
  deleteFile();
  delay(100);
  createFile();
  delay(100);
}

void Formatar_data_hora(){ // A cada 8 segundos atualiza a Hora, Apita de Hora em Hora, Avisa se Iniciou e Envia os LOGs OffLine
       if(weekday() == 1){dia_semana = "Dom";}
  else if(weekday() == 2){dia_semana = "Seg";}
  else if(weekday() == 3){dia_semana = "Ter";}
  else if(weekday() == 4){dia_semana = "Qua";}
  else if(weekday() == 5){dia_semana = "Qui";}
  else if(weekday() == 6){dia_semana = "Sex";}
  else if(weekday() == 7){dia_semana = "Sab";}

  String hora1 = hour()   < 10 ? "0" + String(hour())   : String(hour());
  String minu1 = minute() < 10 ? "0" + String(minute()) : String(minute());
  String segu1 = second() < 10 ? "0" + String(second()) : String(second());
  String dia1  = day()    < 10 ? "0" + String(day())    : String(day());
  String mes1  = month()  < 10 ? "0" + String(month())  : String(month());
  String ano1  = year()   < 10 ? "0" + String(year())   : String(year());

  IP = WiFi.localIP().toString().c_str();
  sinal_wifi = String(WiFi.RSSI()) + "dB";
  
  hora  = hora1 + ":" + minu1 + ":" + segu1;
  data_ = dia1  + "/" + mes1  + "/" + ano1;
  
  currentTime = hora + " " + data_;

  if(error_conect == true && iniciar == false){  // apenas quando ligar
    iniciar = true;
    mostrar_terminal("Iniciado");
  }
}

void iniciar_OTA(){
  ArduinoOTA.setHostname("Fonte");
  ArduinoOTA.begin();
  ArduinoOTA.onStart([]() {
      LittleFS.end();
      display1.clear();
      display1.setFont(ArialMT_Plain_16);
      display1.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
      display1.drawString(display1.getWidth()/2, display1.getHeight()/2 - 10, "Atualizando...");
      display1.display();
  });
  ArduinoOTA.onEnd([](){
      mostrar_display("UPDATE", "OTA", "", "OK", 16, 1);    
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total){
    unsigned int progress1;
    display1.drawProgressBar(4, 32, 120, 8, progress / (total / 100) );
    display1.display(); 
    });

}

void conecta_wifi_blynk(char* ssid_, char* pw_){

  if(WiFi.status() != WL_CONNECTED){
    mostrar_display("Desconectando", "WIFI", "", "", 16, 1);
    WiFi.disconnect(); 
    delay(500);
    WiFi.mode(WIFI_STA);
    mostrar_display("Conectando", "WIFI", "", ssid, 16, 1);
    delay(500);
    WiFi.begin(ssid_, pw_);
    delay(500);
    int x = 0;
    String y = "";
    while ( x <= 20) {
      restart_();
      if (WiFi.status() == WL_CONNECTED){ x = 50; break; }
      x++;
      y = String(x) + " de 20";
      mostrar_display("Conectando", "Ao WIFI", y, "", 16, 1);
    }
    if (WiFi.status() == WL_CONNECTED){
      mostrar_display("", "WIFI OK", "", "",16, 1);
    }
    else{
      mostrar_display("", "WIFI", "Nao conectado", "",16, 1);
    }
  }
  
  if(!Blynk.connected()) {
      if (WiFi.status() == WL_CONNECTED){ // Só entra se já tiver conectado no WIFI
        Blynk.disconnect();
        mostrar_display("Conectando", "", "Blynk" , "",16, 1);
        Blynk.config(auth);
        delay(500);
        restart_();
        Blynk.connect(9000);
        error_conect = Blynk.connected();
        if (!error_conect) {
          mostrar_display("CONEXAO", "Blynk", "FALHOU" , "",16, 1);
        }
        else{
          Blynk.run();
          mostrar_display("CONEXAO", "Blynk", "OK", "",16, 1);
        }
        error_conect = Blynk.connected();
    }
  }

}

void chama_conecta_wifi_blynk(){
  conecta_wifi_blynk(ssid, pw);
}
