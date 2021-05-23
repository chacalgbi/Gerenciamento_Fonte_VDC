void iniciar_modulos(){
  mostrar_display("Iniciando", "", "Modulos", "", 16, 1);
  ads1.setGain(GAIN_ONE); delay(10); ads1.begin(0X48); delay(10); // Correntes
  ads2.setGain(GAIN_ONE); delay(10); ads2.begin(0X49); delay(10); //Tensão
}

void iniciar_display(){
  display1.init();
  display1.flipScreenVertically();
  display1.setTextAlignment(TEXT_ALIGN_LEFT);
  display1.setFont(ArialMT_Plain_16);
  display1.drawString(0, 0, "Iniciando...");
  display1.display();
  barra_progresso(0, 30, 127, 10, 100, 20);
  display1.clear();
  display1.display();
}

float ADS1115(String ADSx, byte porta_adc, byte QTD_leituras, float multiplicador){
  float media     = 0.0;
  float tensao    = 0.0;

  for ( int h=0; h < QTD_leituras; h++) {
    if(ADSx == "ADS1"){media+= ads1.readADC_SingleEnded(porta_adc);}
    if(ADSx == "ADS2"){media+= ads2.readADC_SingleEnded(porta_adc);}
    delay(4);
  }
  
  media = media / QTD_leituras;
  if(ADSx == "ADS1"){tensao = ads1.computeVolts(media);}
  if(ADSx == "ADS2"){tensao = ads2.computeVolts(media);}
  tensao = tensao * multiplicador;
  delay(10); // Tempo entre leituras
  return tensao;
}
