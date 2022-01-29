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

//float temperature = 0.00;
//update //
class tempr {
  public:
    float temperature;
};
//===========================================================//
const int analogInPin = A0;

unsigned long int avgValue;
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
//Botão
NexDSButton calib3 = NexDSButton(3, 2, "calib3");

//========page4========

//OK

//========page5========
//Texto
NexText  ponto_1_page5 = NexText(5, 5, "pon_1ok");
NexText  ponto_2_page5 = NexText(5, 4, "volt2_page5");
//Botão
NexDSButton calib5 = NexDSButton(5, 2, "calib5 ");

//========page6========

//OK

//========page7========
//Texto

NexText  coe__angu1_page7 = NexText(7, 5, "coe__angu1");

NexText  ponto_3_page7 = NexText(7, 4, "volt3_page7");
//Botão
NexDSButton calib7 = NexDSButton(7, 2, "calib7 ");

//========page8========
//Texto

NexText  coe_angu1_page8 = NexText(8, 4, "coe_angu1");

NexText  coe_linear1_page8 = NexText(8, 5, "coe_linear1");
//Botão
NexDSButton calib8 = NexDSButton(8, 1, "calib8 ");
//===========================F 3 pontos==========================

//===========================Calibração com 2 pontos (meio alcalino)==========================
//========page9========

//OK
//========page10========
//Texto

NexText  volt_1_page10 = NexText(10, 4, "volt1_page10");

//Botão
NexDSButton calib10 = NexDSButton(10, 2, "calib10 ");
//========page11========

//OK
//========page12========
//Texto

NexText  volt_1_page12 = NexText(12, 4, "volt1_page12");
NexText  coe_angu1_page12 = NexText(12, 5, "coe__angu2");

//Botão
NexDSButton calib12 = NexDSButton(12, 2, "calib12 ");

//========page13========
//Texto

NexText  coe_angu1_page13 = NexText(13, 4, "coe_angu2");
NexText  coe_linear1_page13 = NexText(13, 5, "coe_linear2");

//Botão
NexDSButton calib13 = NexDSButton(13, 1, "calib13 ");

//===========================F 2 pontos (meio alcalino)==========================

//===========================Calibração com 2 pontos (meio ácido)==========================
//========page14========

//OK
//========page15========
//Texto

NexText  volt_1_page15 = NexText(15, 4, "volt1_page15");

//Botão
NexDSButton calib15 = NexDSButton(15, 2, "calib15 ");


//========page16========

//OK
//========page17========
//Texto

NexText  coe_angu1_page17 = NexText(17, 5, "coe_angu3");
NexText  volt_1_page17 = NexText(17, 4, "volt1_page17");

//Botão
NexDSButton calib17 = NexDSButton(17, 2, "calib17 ");

//========page18========
//Texto

NexText  coe_angu1_page18 = NexText(18, 4, "coe__angu3");
NexText  coe_linear1_page18 = NexText(18, 5, "coe_linear3");

//Botão
NexDSButton calib18 = NexDSButton(18, 1, "calib18 ");

//===========================F 2 pontos (meio ácido))==========================



//****************************************************************calib 2 pontos(meio acido)


// --- Variáveis Globais ---
float   pot_value = 0;    //valor ad do potenciômetro ou sensor de temp


char    txt[10];         //texto para conversão e exibição
float   pHVol;

NexTouch *nex_listen_list[] =
{
  //events that will be expected by the serial interface.
  &calib3,
  &calib5,
  &calib7,
  &calib8,
  &calib10,
  &calib12,
  &calib13,
  &calib15,
  &calib17,
  &calib18,
  NULL
};

//(Data type = uint32_t) and (size = 4 byte unsigned integer).
//button storage variables.


uint32_t number2;
uint32_t number3;
uint32_t number4;
uint32_t number5;
uint32_t number7;
uint32_t number8;
uint32_t number9;
uint32_t number10;
uint32_t number11;
uint32_t number12;


//variaveis 3 pontos




//variaveis (meioacido) e (alcalino)
float salvarponto1 = 0.00;
float salvarponto2 = 0.00;
float salvarponto3 = 0.00;
float calculandoangular = 0.00;
float calculandoangular1 = 0.00;

//====================================
float salvarponto1_1 = 0.00;
float salvarponto2_1 = 0.00;
float salvarponto3_1 = 0.00;


//=======salvar os coeficientes =========
float pontom = 30;
float pontob = 35;

void quebra_linha() {

  Serial.println();
}
void funcao1()
{
  tempr self;
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
  float pHVol = (float)avgValue * 5.0 / 1024 / 6;
  //valores
  float doangular;
  float dolinear;
  float varm = EEPROM.get(pontom, doangular );
  float varm1conv = varm / 1000;
  float varb = EEPROM.get(pontob, dolinear );
  //y = mx+b
  float pH1val = (varm1conv * pHVol) + varb;

  quebra_linha();
  //                      pH
  static char varph[14];
  dtostrf(pH1val , 2, 2, varph);
  valorph.setText(varph);

  // ---------------------------------------------------------------------------

  quebra_linha();
  Serial.print("m = ");
  Serial.println(varm1conv);

  quebra_linha();

  Serial.print("b = ");
  Serial.println(varb);
  quebra_linha();

  Serial.print("Volt = ");
  Serial.println(pHVol);
  Serial.println("=============================");


  Serial.print("pH = ");
  Serial.println(pH1val);

  Serial.println("=============================");
  // ---------------------------------------------------------------------------
  //                                  temperatura
  sensors.requestTemperatures();
  self.temperature = sensors.getTempCByIndex(0);
  Serial.print("Sensor, Temperatura: ");
  Serial.println(self.temperature);
  static char temp1[14];
  dtostrf(self.temperature , 2, 2, temp1);
  valortemp.setText(temp1);


  Serial.println("========================pH==============================");
  if (pH1val > 7.2 and pH1val < 15)
  {
    scrolltext.setText("Alcal...");
    Serial.print("Alcal...: ");
    Serial.println(pH1val);
  }
  if (pH1val > 0 and pH1val < 7.2)
  {
    scrolltext.setText("Acid...");
    Serial.print("Acid...: ");
    Serial.println(pH1val);
  }
  if (pH1val > 6.8 and pH1val < 7.2)

  {
    Serial.print("Neut...: ");
    Serial.println(pH1val);
    scrolltext.setText("Neut...");
  }
  Serial.println("========================================================");
}


void funcao7()
//==============================*********SCREEN 7==> tampao pH 6.86 *********=====dois pontos meio alcalino
{
  //Tela  7 /***********************************************************************************
  quebra_linha();
  calib10.getValue(&number7);
  if (number7 == 1)
  {
    digitalWrite(13, 1);
    //===================================================================
    for (int i = 0; i < 10; i++)
    {
      buf[i] = analogRead(analogInPin);
      delay(5);
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
    salvarponto1_1 = pHVol;

    static char valorm1[14];
    dtostrf(salvarponto1_1 , 2, 2, valorm1);
    volt_1_page10.setText(valorm1);
    Serial.print("funcao7 = ");
    Serial.println("executado !");
  }
}


void funcao8()
{
  quebra_linha();
  calib12.getValue(&number8);

  //Tela8 /*****************************************************************************************
  if (number8 == 1)
  {
    digitalWrite(13, 1);
    for (int i = 0; i < 10; i++)
    {
      buf[i] = analogRead(analogInPin);
      delay(5);
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
    float pHVol = (float)avgValue * 5.0 / 1024 / 6;
    salvarponto2_1 = pHVol;
    Serial.print("teste ponto salvo = ");
    Serial.println(salvarponto1_1 );
    Serial.print("soma = ");
    float sum = salvarponto1_1 + salvarponto2_1;
    Serial.println(sum );

    /*
        static char ph[14];
        dtostrf(salvarponto1_1 , 2, 2, ph);
        pon1.setText(ph);
    */
    static char ph1[14];
    dtostrf(salvarponto2_1 , 2, 2, ph1);
    volt_1_page12.setText(ph1);

    //coeficiente angular
    calculandoangular1 = (6.86 - 9.18) / (salvarponto1_1 - salvarponto2_1);
    calculandoangular = (6.86 - 9.18) / (salvarponto1_1 - salvarponto2_1) * 1000;

    static char ph2[14];
    dtostrf(calculandoangular1 , 2, 2, ph2);
    coe_angu1_page12.setText(ph2);

    EEPROM.put(pontom, calculandoangular);
    Serial.print("funcao8 = ");
    Serial.println("executado !");
  }
}

void funcao9()
{
  quebra_linha();
  calib13.getValue(&number9);
  //Tela9 /*****************************************************************************************
  if (number9 == 1)
  {
    digitalWrite(13, 1);
    for (int i = 0; i < 10; i++)
    {
      buf[i] = analogRead(analogInPin);
      delay(5);
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
    float pHVol1 = (float)avgValue * 5.0 / 1024 / 6;



    float calculandob = ((calculandoangular1 * pHVol1 - 9.18) * (-1));
    Serial.print("calculandob = ");
    Serial.println("calculandob");
    static char ph40[14];
    dtostrf(calculandoangular1  , 2, 2, ph40);
    coe_angu1_page13.setText(ph40);

    static char ph50[14];
    dtostrf(calculandob  , 2, 2, ph50);
    coe_linear1_page13.setText(ph50);


    EEPROM.put(pontob, calculandob);

    Serial.print("funcao9 = ");
    Serial.println("executado !");

  }
}


void funcao10()
//==============================*********SCREEN 10==> tampao pH 4.18 *********=====dois pontos meio acido
{

  //Tela  7 /***********************************************************************************
  quebra_linha();
  calib15.getValue(&number10);
  if (number10 == 1)
  {
    digitalWrite(13, 1);
    //===================================================================
    for (int i = 0; i < 10; i++)
    {
      buf[i] = analogRead(analogInPin);
      delay(5);
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
    salvarponto1 = pHVol;

    static char valorm2[14];
    dtostrf(salvarponto1 , 2, 2, valorm2);
    volt_1_page15.setText(valorm2);
    Serial.print("funcao10 = ");
    Serial.println("executado !");
  }
}


void funcao11()
{
  quebra_linha();
  calib17.getValue(&number11);

  //Tela11 /*****************************************************************************************
  if (number11 == 1)
  {
    digitalWrite(13, 1);
    for (int i = 0; i < 10; i++)
    {
      buf[i] = analogRead(analogInPin);
      delay(5);
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
    float pHVol = (float)avgValue * 5.0 / 1024 / 6;
    salvarponto2 = pHVol;
    Serial.print("teste ponto salvo = ");
    Serial.println(salvarponto1 );
    Serial.print("soma = ");
    float sum = salvarponto1 + salvarponto2;
    Serial.println(sum );
    /*

        static char ph6[14];
        dtostrf(salvarponto1 , 2, 2, ph6);
        varponto1.setText(ph6);
    */
    static char ph7[14];
    dtostrf(salvarponto2 , 2, 2, ph7);
    volt_1_page17.setText(ph7);

    //coeficiente angular
    calculandoangular1 = (4.18 - 6.86) / (salvarponto1 - salvarponto2);
    calculandoangular = (4.18 - 6.86) / (salvarponto1 - salvarponto2) * 1000;

    static char ph2[14];
    dtostrf(calculandoangular1 , 2, 2, ph2);
    coe_angu1_page17.setText(ph2);

    EEPROM.put(pontom, calculandoangular);
    Serial.print("funcao11 = ");
    Serial.println("executado !");
  }
}

void funcao12()
{
  quebra_linha();
  calib18.getValue(&number12);
  //Tela12 /*****************************************************************************************
  if (number12 == 1)
  {
    digitalWrite(13, 1);
    for (int i = 0; i < 10; i++)
    {
      buf[i] = analogRead(analogInPin);
      delay(5);
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
    float pHVol1 = (float)avgValue * 5.0 / 1024 / 6;



    float calculandob = ((calculandoangular1 * pHVol1 - 6.86) * (-1));
    Serial.print("calculandob = ");
    Serial.println("calculandob");
    static char ph8[14];
    dtostrf(calculandoangular1  , 2, 2, ph8);
    coe_angu1_page18.setText(ph8);

    static char ph9[14];
    dtostrf(calculandob  , 2, 2, ph9);
    coe_linear1_page18.setText(ph9);


    EEPROM.put(pontob, calculandob);
    Serial.print("funcao12 = ");
    Serial.println("executado !");
  }
}


float ponto1page2_ = 0.00;

float ponto2page3_ = 0.00;

float ponto3page4_ = 0.00;

float pontompage4 = 0.00;


void funcao2()
//==============================*********SCREEN 2==> tampao pH 4.18 *********=====3 pontos
{
  //Tela  2 /***********************************************************************************
  quebra_linha();
  calib3.getValue(&number2);
  if (number2 == 1)
  {
    digitalWrite(13, 1);
    //===================================================================
    for (int i = 0; i < 10; i++)
    {
      buf[i] = analogRead(analogInPin);
      delay(5);
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
    ponto1page2_ = pHVol;

    static char val_[14];
    dtostrf(ponto1page2_ , 2, 2, val_);
    ponto_1_page3.setText(val_);
    Serial.print("funcao2 = ");
    Serial.println("executado !");
  }
}
void funcao3()
//==============================*********SCREEN 3==> tampao pH 6.86 *********=====3 pontos
{
  //Tela  3 /***********************************************************************************
  quebra_linha();
  calib5.getValue(&number3);
  if (number3 == 1)
  {
    digitalWrite(13, 1);
    //===================================================================
    for (int i = 0; i < 10; i++)
    {
      buf[i] = analogRead(analogInPin);
      delay(5);
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
    ponto2page3_ = pHVol;

    static char val_[14];
    dtostrf(ponto1page2_ , 2, 2, val_);
    ponto_1_page5.setText(val_);



    static char val_1[14];
    dtostrf(ponto2page3_, 2, 2, val_1);
    ponto_2_page5.setText(val_1);
    Serial.print("funcao3 = ");
    Serial.println("executado !");
  }
}


void funcao4()
//==============================*********SCREEN 4==> tampao pH 9.18 *********=====3 pontos
{
  //Tela  4 /***********************************************************************************
  quebra_linha();
  calib7.getValue(&number4);
  if (number4 == 1)
  {
    digitalWrite(13, 1);
    //===================================================================
    for (int i = 0; i < 10; i++)
    {
      buf[i] = analogRead(analogInPin);
      delay(5);
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
    ponto3page4_ = pHVol;


    /*
        static char val1_[14];
        dtostrf(ponto1page2_, 2, 2, val1_);
        ponto1page4.setText(val1_);



        static char val_1[14];
        dtostrf(ponto2page3_, 2, 2, val_1);
        ponto2page4.setText(val_1);

    */
    static char val2_[14];
    dtostrf(ponto3page4_ , 2, 2, val2_);
    ponto_3_page7.setText(val2_);

    pontompage4 = ((4.18 - 6.86) + (6.86 - 9.18)) / ((ponto1page2_ - ponto2page3_) + (ponto2page3_ - ponto3page4_));
    float convpontompage4 = pontompage4 * 1000;
    EEPROM.put(pontom, convpontompage4);

    static char val3_1[14];
    dtostrf(pontompage4, 2, 2, val3_1);
    coe__angu1_page7.setText(val3_1);
    Serial.print("funcao4 = ");
    Serial.println("executado !");

  }
}
void funcao5()
//==============================*********SCREEN 5
{
  //Tela  5 /***********************************************************************************
  quebra_linha();
  calib8.getValue(&number5);
  if (number5 == 1)
  {
    digitalWrite(13, 1);
    //===================================================================
    for (int i = 0; i < 10; i++)
    {
      buf[i] = analogRead(analogInPin);
      delay(5);
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


    static char val_10[14];
    dtostrf(pontompage4, 2, 2, val_10);
    coe_angu1_page8.setText(val_10);

    float calcb1 = ((pontompage4 * pHVol) - 9.18) * (-1);


    static char val_100[14];
    dtostrf(calcb1 , 2, 2, val_100);
    coe_linear1_page8.setText(val_100);

    EEPROM.put(pontob, calcb1);
    Serial.print("funcao5 = ");
    Serial.println("executado !");
  }
}



void setup()
{
  //Inicializa a comunicacao com o display
  nexInit();
  sensors.begin();
  delay(5);
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, 0);

  dbSerialPrintln("Setup finalizado");
  delay(2);
}


void loop(void)

{
  nexLoop(nex_listen_list);
  funcao1();
  funcao2();
  funcao3();
  funcao4();
  funcao5();
  funcao7();
  funcao8();
  funcao9();
  funcao10();
  funcao11();
  funcao12();
  delay(200);
}
