// Variáveis da configuração WIFI - SPIFFS
String REDE="";  char ssid[30];   int tamanho_rede = 0;
String SENHA=""; char pw[30];     int tamanho_senha = 0;
String NOME="";  char device[30]; int tamanho_nome = 0;

char auth[] = "nL-NSMx5WlWx50DsNgXT7-DMkoa_kTL7"; // placa 1

int tempo = 1500;

float volts = 0;
float i1 = 0;
float i2 = 0;
float i3 = 0;
float i4 = 0;

float ACS712_v = 0.000; String AC_V = "";
float ACS712_i = 0.000; String AC_I = "";

float v_const  = 1.00;
float i1_const = 1.00;
float i2_const = 1.00;
float i3_const = 1.00;
float i4_const = 1.00;
float i1_limit = 0.00;
float i2_limit = 0.00;
float i3_limit = 0.00;
float i4_limit = 0.00;
float i_total = 0.00;
float potencia = 0.00;

bool i1_trava = false;
bool i2_trava = false;
bool i3_trava = false;
bool i4_trava = false;
bool inverter_display = false;
bool inverter = false;
bool serial_ativo  = false;
bool error_conect = false;
bool iniciar = false;
bool modo_config = false;

String aviso = "";
String volts_str = "";
String i1_str = "";
String i2_str = "";
String i3_str = "";
String i4_str = "";
String i_total_str = "";
String potencia_str = "";
String valores_DC = "";
String valores_DC1 = "";
String conexao = "";
String device_str = "";
String pw_str = "";
String ssid_str = "";
String IP = "";
String sinal_wifi = "";
String currentTime = "";
String hora = "";
String data_ = "";
String dia_semana = "";
