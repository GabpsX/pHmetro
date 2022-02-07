//GABRIEL P.S
//V: 5.1 >> pHmetro
#include <Nextion.h>
#include <EEPROM.h>
//sensor temperatura
#include <OneWire.h>
#include <DallasTemperature.h>
// O fio de dados é conectado no pino digital 2 no Arduino
#define ONE_WIRE_BUS 2
// Prepara uma instância oneWire para comunicar com qualquer outro dispositivo oneWire
OneWire oneWire(ONE_WIRE_BUS);
// Passa uma referência oneWire para a biblioteca DallasTemperature
DallasTemperature sensors(&oneWire);
#include <LinearRegression.h>
//update //
class tempr {
  public:
    float temperature;
};
//===========================================================//
const int analogInPin = A0;
int current_page = 0;
int buf[10], temp;

//===========================================================//


#define    pot    A0   //potenciômetro na analógica 0

#define    led    13   //led onboard pino digital 13

//Calibração
//========page0========
//É necessário adicionar botao na inteface gráfica, para funcionar.
NexDSButton calib1 = NexDSButton(0, 1, "calib1");
//simbolo.
NexText  nothing = NexText(0, 8, "graus");
// imprime na tela o valor imformado pelo eletrodo, sonda de ph.
NexText  valorph = NexText(0, 3, "phvar");
// imprime na tela o valor imformado pelo sensor de temperatura.
NexText  valortemp = NexText(0, 2, "temp");
//
NexScrolltext scrolltext = NexScrolltext(0, 7, "g0");

//OK
//========page1========

//OK
//========page2========

//OK

//===========================Calibração com 3 pontos==========================
//========page3========
//Texto
NexText  ponto_1_page3 = NexText(3, 4, "volt1_page3");

//========page4========

//OK

//========page5========
//Texto
NexText  ponto_1_page5 = NexText(5, 5, "pon_1ok");
NexText  ponto_2_page5 = NexText(5, 4, "volt2_page5");

//========page6========

//OK

//========page7========
//Texto

NexText  coe__angu1_page7 = NexText(7, 5, "coe__angu1");

NexText  ponto_3_page7 = NexText(7, 4, "volt3_page7");

//========page8========
//Texto

NexText  coe_angu1_page8 = NexText(8, 4, "coe_angu1");

NexText  coe_linear1_page8 = NexText(8, 5, "coe_linear1");

//===========================F 3 pontos==========================

//===========================Calibração com 2 pontos (meio alcalino)==========================
//========page9========

//OK
//========page10========
//Texto

NexText  volt_1_page10 = NexText(10, 4, "volt1_page10");

//========page11========

//OK
//========page12========
//Texto

NexText  volt_1_page12 = NexText(12, 4, "volt1_page12");
NexText  coe_angu1_page12 = NexText(12, 5, "coe__angu2");


//========page13========
//Texto

NexText  coe_angu1_page13 = NexText(13, 4, "coe_angu2");
NexText  coe_linear1_page13 = NexText(13, 5, "coe_linear2");


//===========================F 2 pontos (meio alcalino)==========================

//===========================Calibração com 2 pontos (meio ácido)==========================
//========page14========

//OK
//========page15========
//Texto

NexText  volt_1_page15 = NexText(15, 4, "volt1_page15");



//========page16========

//OK
//========page17========
//Texto

NexText  coe_angu1_page17 = NexText(17, 5, "coe_angu3");
NexText  volt_1_page17 = NexText(17, 4, "volt1_page17");


//========page18========
//Texto

NexText  coe_angu1_page18 = NexText(18, 4, "coe__angu3");
NexText  coe_linear1_page18 = NexText(18, 5, "coe_linear3");



// --- Variáveis Globais ---
float   pot_value = 0;    //valor ad do potenciômetro ou sensor de temp


char    txt[10];         //texto para conversão e exibição
float   pHVol;





//variaveis (meioacido) , (alcalino) e 3 pontos
float salvarponto1 = 0.00;
float salvarponto2 = 0.00;
float salvarponto3 = 0.00;
LinearRegression lr = LinearRegression();
float r, a, b, n;  // coeficientes da correlação

//=======salvar os coeficientes =========
float pontom = 30;
float pontob = 35;

void quebra_linha() {

  Serial.println();
}

void pH() {
  unsigned long int avgValue;
  for (int i = 0; i < 10; i++)
  {
    buf[i] = analogRead(analogInPin);
  }
  for (int i = 0; i < 9; i++)
  {
    for (int j = i + 1; j < 10; j++)
    {
      if (buf[i] > buf[j])
      {
        temp = buf[i];
        buf[i] = buf[j];
        buf[j] = temp;
      }
    }
  }
  avgValue = 0;
  for (int i = 2; i < 8; i++)
    avgValue += buf[i];
  pHVol = (float)avgValue * 5.0 / 1024 / 6;
}


// pages
NexPage page0 = NexPage(0, 0, "page0");  // Page added as a touch event
NexPage page1 = NexPage(1, 0, "page1");  // Page added as a touch event
NexPage page2 = NexPage(2, 0, "page2");  // Page added as a touch event
NexPage page3 = NexPage(3, 0, "page3");  // Page added as a touch event
NexPage page4 = NexPage(4, 0, "page4");  // Page added as a touch event
NexPage page5 = NexPage(5, 0, "page5");  // Page added as a touch event
NexPage page6 = NexPage(6, 0, "page6");  // Page added as a touch event
NexPage page7 = NexPage(7, 0, "page7");  // Page added as a touch event
NexPage page8 = NexPage(8, 0, "page8");  // Page added as a touch event
NexPage page9 = NexPage(9, 0, "page9");  // Page added as a touch event

//

NexPage page21 = NexPage(21, 0, "page21");  // Page added as a touch event




NexTouch *nex_listen_list[] =
{
  &page0,
  &page1,
  &page2,
  &page3,
  &page4,
  &page5,
  &page6,
  &page7,
  &page8,
  &page9,

  &page21,


  NULL
};

//
void page0PushCallback(void *ptr)
{
  current_page = 0;
}

void page1PushCallback(void *ptr)
{
  current_page = 1;
}

void page2PushCallback(void *ptr)
{
  current_page = 2;
}

void page3PushCallback(void *ptr)
{
  current_page = 3;
}

void page4PushCallback(void *ptr)
{
  current_page = 4;
}

void page5PushCallback(void *ptr)
{
  current_page = 5;
}

void page6PushCallback(void *ptr)
{
  current_page = 6;
}

void page7PushCallback(void *ptr)
{
  current_page = 7;
}

void page8PushCallback(void *ptr)
{
  current_page = 8;
}

void page9PushCallback(void *ptr)
{
  current_page = 9;
}




//
void page10PushCallback(void *ptr)
{
  current_page = 21;
}


// -------------=====================-------------------
void homepage()
{
  tempr self;
  pH();
  //valores
  float doangular;
  float dolinear;
  float varm = EEPROM.get(pontom, doangular );
  float varb = EEPROM.get(pontob, dolinear );
  Serial.print("varm = ");
  Serial.println(varm);
  Serial.print("varb = ");
  Serial.println(varb);

  Serial.print("volt = ");
  Serial.println(pHVol);
  //y = mx+b
  float pH1val = varm * pHVol + varb ;
  Serial.print("pH = ");
  Serial.println(pH1val);

  quebra_linha();
  //                      pH
  static char varph[5];
  dtostrf(pH1val , 2, 2, varph);
  valorph.setText(varph);
  //                                  temperatura
  sensors.requestTemperatures();
  self.temperature = sensors.getTempCByIndex(0);
  static char temp1[14];
  dtostrf(self.temperature , 2, 2, temp1);
  valortemp.setText(temp1);

  if (pH1val > 7.2 and pH1val < 15)
  {
    scrolltext.setText("Alcal...");
  }
  if (pH1val > 0 and pH1val < 7.2)
  {
    scrolltext.setText("Acid...");
  }
  if (pH1val > 6.8 and pH1val < 7.2)

  {
    scrolltext.setText("Neut...");
  }

}

double values[3];

float pot1a;
float pot2a;
float pot3a;
void calib2pontos_ponto1_meio_alcalino()
//==============================******tampao pH 6.86 *********=====dois pontos meio alcalino
{
  //Tela  7 /***********************************************************************************
  quebra_linha();
  digitalWrite(13, 1);
  //===================================================================
  show_pH_calib();
  pH();
  pot1a = pHVol;
  static char valorm1[5];
  dtostrf(pHVol , 2, 2, valorm1);
  volt_1_page10.setText(valorm1);

}


void calib2pontos_ponto2_meio_alcalino()
{
  quebra_linha();
  //**********************************************************
  show_pH_calib();
  pH();
  pot2a = pHVol;
  static char ph7[5];
  dtostrf(pot2a , 2, 2, ph7);
  volt_1_page12.setText(ph7);
  LinearRegression lr = LinearRegression(0, 100);
  lr.learn(pot1a, 6.86);
  lr.learn(pot2a, 9.18);
  lr.getValues(values);
  r = lr.correlation();  // coef correlacao
  a = values [0];    // coef angular
  b = values [1];    // coef linear
  n = values [2];    // numero de pontos

  static char ph2[5];
  dtostrf(a , 2, 2, ph2);
  coe_angu1_page12.setText(ph2);
  //point x 1000 --> to save
  salvarponto1 = a * 1000;
  salvarponto2 = b * 1000;

}

void salvando_coeficientes_meio_alcalino()
{
  EEPROM.put(pontom, a);
  EEPROM.put(pontob, b);
  quebra_linha();
  //Tela9 /*****************************************************************************************
  digitalWrite(13, 1);
  pH();
  float exibe_angular = salvarponto1 / 1000;
  float exibe_linear = salvarponto2 / 1000;

  static char ph40[14];
  dtostrf(exibe_angular  , 2, 2, ph40);
  coe_angu1_page13.setText(ph40);

  static char ph50[5];
  dtostrf(exibe_linear  , 2, 2, ph50);
  coe_linear1_page13.setText(ph50);

}

//****************************************************************************************
void calib2pontos_ponto1_meio_acido()
//==============================*********tampao pH 4.18 *********=====dois pontos meio acido
{
  quebra_linha();
  digitalWrite(13, 1);
  //===================================================================
  show_pH_calib();
  pH();
  pot1a = pHVol;
  static char valorm1[5];
  dtostrf(pHVol , 2, 2, valorm1);
  volt_1_page15.setText(valorm1);

}


void calib2pontos_ponto2_meio_acido()
{
  quebra_linha();
  //**********************************************************
  show_pH_calib();
  pH();
  pot2a = pHVol;
  static char ph7[5];
  dtostrf(pot2a , 2, 2, ph7);
  volt_1_page17.setText(ph7);
  LinearRegression lr = LinearRegression(0, 100);
  lr.learn(pot1a, 4.18);
  lr.learn(pot2a, 6.86);
  lr.getValues(values);
  r = lr.correlation();  // coef correlacao
  a = values [0];    // coef angular
  b = values [1];    // coef linear
  n = values [2];    // numero de pontos

  static char ph2[5];
  dtostrf(a , 2, 2, ph2);
  coe_angu1_page17.setText(ph2);
  //point x 1000 --> to save
  salvarponto1 = a * 1000;
  salvarponto2 = b * 1000;

}

void salvando_coeficientes_meio_acido()
{
  EEPROM.put(pontom, a);
  EEPROM.put(pontob, b);
  quebra_linha();
  //*********************************************************
  digitalWrite(13, 1);
  pH();
  float exibe_angular = salvarponto1 / 1000;
  float exibe_linear = salvarponto2 / 1000;

  static char ph40[14];
  dtostrf(exibe_angular  , 2, 2, ph40);
  coe_angu1_page18.setText(ph40);

  static char ph50[5];
  dtostrf(exibe_linear  , 2, 2, ph50);
  coe_linear1_page18.setText(ph50);

}



//****************************************************************************************


void setup() {
  // put your setup code here, to run once:
  nexInit();
  sensors.begin();
  Serial.begin(57600);
  page21.attachPush(page10PushCallback);
  //
  page0.attachPush(page0PushCallback);
  page1.attachPush(page1PushCallback);
  page2.attachPush(page2PushCallback);
  page3.attachPush(page3PushCallback);
  page4.attachPush(page4PushCallback);
  page5.attachPush(page5PushCallback);
  page6.attachPush(page6PushCallback);
  page7.attachPush(page7PushCallback);
  page8.attachPush(page8PushCallback);
  page9.attachPush(page9PushCallback);



}
//----------------------------------calibração de 3 pontos
void calib3pontos_ponto1()
//==============================********* tampao pH 4.18 *********=====3 pontos
{
  //Tela  2 /***********************************************************************************
  quebra_linha();
  digitalWrite(13, 1);
  //===================================================================
  show_pH_calib();
  pH();
  pot1a = pHVol;
  static char valorm1[5];
  dtostrf(pHVol , 2, 2, valorm1);
  ponto_1_page3.setText(valorm1);

}
void calib3pontos_ponto2()
//==============================*********SCREEN 3==> tampao pH 6.86 *********=====3 pontos
{
  //Tela  3 /***********************************************************************************
  quebra_linha();
  digitalWrite(13, 1);
  //===================================================================
  show_pH_calib();
  pH();

  pot2a = pHVol;


  static char val_[5];
  dtostrf(pot1a  , 2, 2, val_);
  ponto_1_page5.setText(val_);

  static char valorm1[5];
  dtostrf(pot2a , 2, 2, valorm1);
  ponto_2_page5.setText(valorm1);
}


void calib3pontos_ponto3()
//==============================*********SCREEN 4==> tampao pH 9.18 *********=====3 pontos
{
  //Tela  4 /***********************************************************************************
  quebra_linha();
  digitalWrite(13, 1);
  //===================================================================
  show_pH_calib();
  pH();
  pot3a = pHVol;

  static char ph7[5];
  dtostrf(pot3a , 2, 2, ph7);
  ponto_3_page7.setText(ph7);

  LinearRegression lr = LinearRegression(0, 100);
  lr.learn(pot1a, 4.18);
  lr.learn(pot2a, 6.86);
  lr.learn(pot3a, 9.18);
  lr.getValues(values);
  r = lr.correlation();  // coef correlacao
  a = values [0];    // coef angular
  b = values [1];    // coef linear
  n = values [2];    // numero de pontos

  static char ph2[5];
  dtostrf(a , 2, 2, ph2);
  coe__angu1_page7.setText(ph2);
  //point x 1000 --> to save
  salvarponto1 = a * 1000;
  salvarponto2 = b * 1000;



}
void salvando_os_coeficientes_3pontos()
//==============================*********SCREEN 5
{
  //Tela  5 /***********************************************************************************
  quebra_linha();
  digitalWrite(13, 1);
  //===================================================================
  EEPROM.put(pontom, a);
  EEPROM.put(pontob, b);
  pH();
  float exibe_angular = salvarponto1 / 1000;
  float exibe_linear = salvarponto2 / 1000;

  static char ph40[14];
  dtostrf(exibe_angular  , 2, 2, ph40);
  coe_angu1_page8.setText(ph40);

  static char ph50[5];
  dtostrf(exibe_linear  , 2, 2, ph50);
  coe_linear1_page8.setText(ph50);

}


//------------------------------------------

NexText  pH1 = NexText(1, 4, "pH1");
NexText  pH2 = NexText(2, 5, "pH2");
NexText  pH3 = NexText(3, 5, "pH3");

NexText  pH4 = NexText(5, 4, "pH4");
NexText  pH5 = NexText(6, 5, "pH5");

NexText  pH6 = NexText(8, 4, "pH6");
NexText  pH7 = NexText(9, 5, "pH7");
void show_pH_calib() {
  if (current_page == 1) { //////////////////page
    pH();
    //valores
    float doangular;
    float dolinear;
    float varm = EEPROM.get(pontom, doangular );
    float varb = EEPROM.get(pontob, dolinear );
    float pH1val = varm * pHVol + varb ;

    static char ph40[5];
    dtostrf(pH1val  , 2, 2, ph40);
    pH1.setText(ph40);
  }
  if (current_page == 2) { //////////////////page
    pH();
    //valores
    float doangular;
    float dolinear;
    float varm = EEPROM.get(pontom, doangular );
    float varb = EEPROM.get(pontob, dolinear );
    float pH1val = varm * pHVol + varb ;

    static char ph40[5];
    dtostrf(pH1val  , 2, 2, ph40);
    pH2.setText(ph40);
  }
  if (current_page == 3) { //////////////////page
    pH();
    //valores
    float doangular;
    float dolinear;
    float varm = EEPROM.get(pontom, doangular );
    float varb = EEPROM.get(pontob, dolinear );
    float pH1val = varm * pHVol + varb ;

    static char ph40[5];
    dtostrf(pH1val  , 2, 2, ph40);
    pH3.setText(ph40);
  }
  if (current_page == 5) { //////////////////page
    pH();
    //valores
    float doangular;
    float dolinear;
    float varm = EEPROM.get(pontom, doangular );
    float varb = EEPROM.get(pontob, dolinear );
    float pH1val = varm * pHVol + varb ;

    static char ph40[5];
    dtostrf(pH1val  , 2, 2, ph40);
    pH4.setText(ph40);
  }
  if (current_page == 6) { //////////////////page
    pH();
    //valores
    float doangular;
    float dolinear;
    float varm = EEPROM.get(pontom, doangular );
    float varb = EEPROM.get(pontob, dolinear );
    float pH1val = varm * pHVol + varb ;

    static char ph40[5];
    dtostrf(pH1val  , 2, 2, ph40);
    pH5.setText(ph40);
  }
  if (current_page == 8) { //////////////////page
    pH();
    //valores
    float doangular;
    float dolinear;
    float varm = EEPROM.get(pontom, doangular );
    float varb = EEPROM.get(pontob, dolinear );
    float pH1val = varm * pHVol + varb ;

    static char ph40[5];
    dtostrf(pH1val  , 2, 2, ph40);
    pH6.setText(ph40);
  }
  if (current_page == 9) { //////////////////page
    pH();
    //valores
    float doangular;
    float dolinear;
    float varm = EEPROM.get(pontom, doangular );
    float varb = EEPROM.get(pontob, dolinear );
    float pH1val = varm * pHVol + varb ;

    static char ph40[5];
    dtostrf(pH1val  , 2, 2, ph40);
    pH7.setText(ph40);
  }
}
void loop() {
  //3 pontos
  if (current_page == 0)//////////////////page
  {
    Serial.println("MEASURING pH");///////potentio meter value in gauge

    homepage();
  }
  if (current_page == 1)//////////////////page
  {
    Serial.println("CALIBRANDO PONTO 1 - 3 PONTOS");///////potentio meter value in gauge
    calib3pontos_ponto1();
  }
  if (current_page == 2)//////////////////page
  {
    Serial.println("CALIBRANDO PONTO 2 - 3 PONTOS");///////potentio meter value in gauge
    calib3pontos_ponto2();
  }
  if (current_page == 3)//////////////////page
  {
    Serial.println("CALIBRANDO PONTO 3 - 3 PONTOS");///////potentio meter value in gauge
    calib3pontos_ponto3();

  }
  if (current_page == 4)//////////////////page
  {
    Serial.println("FINALIZANDO CALIBRAÇÃO - 3 PONTOS");///////potentio meter value in gauge
    salvando_os_coeficientes_3pontos();

  }


  //meio alcalino
  if (current_page == 5)//////////////////page
  {
    Serial.println("CALIBRANDO PONTO 1 - 2 MEIO ALCALINO");///////potentio meter value in gauge
    calib2pontos_ponto1_meio_alcalino();

  }
  if (current_page == 6)//////////////////page
  {
    Serial.println("CALIBRANDO PONTO 2 - 2 MEIO ALCALINO");///////potentio meter value in gauge
    calib2pontos_ponto2_meio_alcalino();

  }
  if (current_page == 7)//////////////////page
  {
    Serial.println("FINALIZANDO CALIBRAÇÃO - 2 MEIO ALCALINO");///////potentio meter value in gauge
    salvando_coeficientes_meio_alcalino();

  }


  //meio acido
  if (current_page == 8)//////////////////page
  {
    Serial.println("CALIBRANDO PONTO 1 - 2 MEIO ACIDO");///////potentio meter value in gauge
    calib2pontos_ponto1_meio_acido();

  }
  if (current_page == 9)//////////////////page
  {
    Serial.println("CALIBRANDO PONTO 2 - 2 MEIO ACIDO");///////potentio meter value in gauge
    calib2pontos_ponto2_meio_acido();

  }
  //
  if (current_page == 21)//////////////////page
  {
    Serial.println("FINALIZANDO CALIBRAÇÃO - 2 MEIO ACICO");///////potentio meter value in gauge
    salvando_coeficientes_meio_acido();
  }

  nexLoop(nex_listen_list);
}
