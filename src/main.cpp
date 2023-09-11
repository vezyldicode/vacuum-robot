#include <Arduino.h>

int coi = 2;
//L298N pins 
const int ENA = 3; // dieu khien toc do motor trai;
const int INA = 4; // chan am ben trai; // HIGH DE DI THANG
const int INB = 5; // chan duong ben trai; // LOW DE DI THANG
const int INC = 6; // chan am ben phai; // HIGH DE DI THANG
const int IND = 7; // chan duong ben phai; // LOW DE DI THANG
const int ENB = 11; // dieu khien toc do motor phai;
int speed = 255;

//khai bao cam bien chong roi
int cbroitrai = 8;
int cbroigiua = 9;
int cbroiphai = 10;
int giatriL; // gia tri cam bien trai (GIA TRI ==0(LOW) KHI ROBOT TREN MAT DAT)
int giatriM; // gia tri cam bien giua (GIA TRI ==0(LOW) KHI ROBOT TREN MAT DAT)
int giatriR; // gia tri cam bien phai (GIA TRI ==0(LOW) KHI ROBOT TREN MAT DAT)

//cam bien va cham
const int cbphai = 13; // cam bien va cham phai
const int cbtrai = 12; // cam bien va cham trai
int giatriT; // gia tri cam bien va cham trai (GIA TRI ==1(HIGH) KHI ROBOT KHONG VA CHAM)
int giatriP; // gia tri cam bien va cham phai (GIA TRI ==1(HIGH) KHI ROBOT KHONG VA CHAM)

boolean turnright = true; //
boolean error = true;
boolean previous;

void docgiatricambien()
{
  giatriL = digitalRead(cbroitrai);
  Serial.print("gia tri cam bien roi ben trai la:");
  Serial.println(giatriL);
  giatriM = digitalRead(cbroigiua);
  Serial.print("gia tri cam bien roi o giua la:");
  Serial.println(giatriM);
  giatriR = digitalRead(cbroiphai);
  Serial.print("gia tri cam bien roi ben phai la:");
  Serial.println(giatriR);
  giatriT = digitalRead(cbtrai);
  giatriP = digitalRead(cbphai);

}

void start() 
{
  tone(coi, 1500);
  delay (100);
  noTone(coi);
  delay(100);
  tone(coi, 1900);
  delay(100);
  noTone(coi);
}


// BASIC MOVEMENT
void forward()        //  DI THANG
{
  Serial.println("Forward");
  Serial.println("");
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(INA, HIGH); 
  digitalWrite(INB, LOW);  
  digitalWrite(INC, HIGH); 
  digitalWrite(IND, LOW); 
}

void forwardLeft()       // TIEN LEN BEN TRAI
{
  Serial.println("forward Left");
  Serial.println("");
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(INA, LOW);
  digitalWrite(INB, LOW);  
  digitalWrite(INC, HIGH);
  digitalWrite(IND, LOW);
}

void forwardRight()     // TIEN LEN BEN PHAI
{
  Serial.println("Forward Right");
  Serial.println("");
  analogWrite(ENA,speed);
  analogWrite(ENB,speed);
  digitalWrite(INA, HIGH);
  digitalWrite(INB, LOW);  
  digitalWrite(INC, LOW);
  digitalWrite(IND, LOW);
}

void checkLeft()
{
  analogWrite(ENA, speed-100);
  analogWrite(ENB, speed);
  digitalWrite(INA, HIGH); 
  digitalWrite(INB, LOW);  
  digitalWrite(INC, HIGH); 
  digitalWrite(IND, LOW); 
}

void checkRight()
{
  analogWrite(ENA, speed);
  analogWrite(ENB, speed-100);
  digitalWrite(INA, HIGH); 
  digitalWrite(INB, LOW);  
  digitalWrite(INC, HIGH); 
  digitalWrite(IND, LOW); 
}

void left()    // RE TRAI                                                                              
{
  Serial.println("DI CHUYEN SANG TRAI");
  Serial.println("");
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(INA, LOW);
  digitalWrite(INB, HIGH);  
  digitalWrite(INC, HIGH);
  digitalWrite(IND, LOW);
}

void right()    // RE PHAI                                                                              
{
  Serial.println("DI CHUYEN SANG PHAI");
  Serial.println("");
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(INA, HIGH);
  digitalWrite(INB, LOW);  
  digitalWrite(INC, LOW);
  digitalWrite(IND, HIGH);
}

void stop()      // DUNG LAI
{
  Serial.println("DUNG LAI");
  Serial.println("");
  analogWrite(ENA,LOW);
  analogWrite(ENB,LOW);
  digitalWrite(INA, LOW);
  digitalWrite(INB, LOW);  
  digitalWrite(INC, LOW);
  digitalWrite(IND, LOW);
}

void backward()   // LUI LAI                                                                            
{
  Serial.println("DI LUI LAI");
  Serial.println("");
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(INA, LOW);
  digitalWrite(INB, HIGH);  
  digitalWrite(INC, LOW);
  digitalWrite(IND, HIGH);
}

void backwardRight()                                                                            // LUI LAI BEN PHAI
{
  Serial.println("Backward Right");
  Serial.println("");
  analogWrite(ENA,speed);
  analogWrite(ENB,speed);
  digitalWrite(INA, LOW);
  digitalWrite(INB, HIGH);  
  digitalWrite(INC, LOW);
  digitalWrite(IND, LOW);
}

void backwardLeft()                                                                            // LUI LAI BEN TRAI
{
  Serial.println("Backward Left");
  Serial.println("");
  analogWrite(ENA,speed);
  analogWrite(ENB,speed);
  digitalWrite(INA, LOW);
  digitalWrite(INB, LOW);  
  digitalWrite(INC, LOW);
  digitalWrite(IND, HIGH);
}

//COMPLICATED MOVEMENT

void delaylui()   // LUI TRONG 300MS
{
  Serial.println("LUI TRONG 300MS");
  unsigned long starttime=millis();
  while(millis() - starttime<=300)     
  {
    backward();
    Serial.println(starttime);
  }
    stop();
    delay(500);
    docgiatricambien();
}

void delayluitrai()
{
  unsigned long starttime=millis();
  while(millis()-starttime<=200)   
  {
    backwardLeft();
    
    Serial.println(starttime);
  }
    docgiatricambien();
    stop();
    delay(100);
}

void delayluiphai()
{
  unsigned long starttime=millis();
  while(millis()-starttime<=200)   
  {
    backwardRight();
    docgiatricambien();
    Serial.println(starttime);}
    stop();
    delay(100);
}

void delaytrai()   // RE TRAI TRONG 500MS
{
  turnright = true;
  Serial.println("RE TRAI TRONG 500MS");
  unsigned long starttime=millis();
  while(millis()-starttime<=400 && giatriL !=1 && giatriT == 1 && giatriM != 1 && giatriR != 1 && giatriP ==1) // DO ROI TRAI VA VA CHAM TRAI    
  {
    left();
    docgiatricambien();
    Serial.println(starttime);
    if ( giatriL ==1 || giatriT != HIGH || giatriM == 1 || giatriR != 1 || giatriP !=1 )
    {
      turnright = false;
    }
  }
  if(millis()-starttime>=400 || giatriL ==1 || giatriT != HIGH || giatriM == 1 || giatriR != 1 || giatriP !=1 )
  {
    stop();
    delay(500);
}
docgiatricambien();
}

void delaychecktrai()   // RE TRAI TRONG 500MS
{
  Serial.println("RE TRAI TRONG 500MS");
  unsigned long starttime=millis();
  while(millis()-starttime<=1000 && giatriL !=1 && giatriT == 1 && giatriM != 1 && giatriR != 1 && giatriP ==1) // DO ROI TRAI VA VA CHAM TRAI    
  {
    checkLeft();
    docgiatricambien();
    Serial.println(starttime);
  }
docgiatricambien();
}

void delayphai()    // RE PHAI TRONG 500MS
{
  turnright = false;
  Serial.println("RE PHAI TRONG 500MS");
  unsigned long starttime=millis();
  while (millis()-starttime<=400 && giatriL !=1 && giatriT == 1 && giatriM != 1 && giatriR != 1 && giatriP ==1)
  {
    right();
    docgiatricambien();
    Serial.println(starttime);
    if (giatriL ==1 || giatriT != HIGH || giatriM == 1 || giatriR != 1 || giatriP !=1)
    {
      turnright = true;
    }
  }
  if(millis()-starttime>=400 || giatriL ==1 || giatriT != HIGH || giatriM == 1 || giatriR != 1 || giatriP !=1)
  {
    stop();
    delay(500);
}
docgiatricambien();
}

void delaycheckphai()    // RE PHAI TRONG 500MS
{
  Serial.println("RE PHAI TRONG 500MS");
  unsigned long starttime=millis();
  while (millis()-starttime<=1000 && giatriL !=1 && giatriT == 1 && giatriM != 1 && giatriR != 1 && giatriP ==1)
  {
    checkRight();
    docgiatricambien();
    Serial.println(starttime);
  }
docgiatricambien();
}

void quay180phai()
{
  turnright = false;
  Serial.println("RE PHAI TRONG 1500MS");
  unsigned long starttime=millis();
  while (millis()-starttime<=3000 && giatriL !=1 && giatriT == 1 && giatriM != 1 && giatriR != 1 && giatriP ==1)
  {
    forwardRight();
    docgiatricambien();
    Serial.println(starttime);
    if (giatriL ==1 || giatriT != HIGH || giatriM == 1 || giatriR == 1 || giatriP !=1)
    {
      turnright = true;
      delayluitrai();
    }
  }
  if(millis()-starttime>=3000 || giatriL ==1 || giatriT != HIGH || giatriM == 1 || giatriR == 1 || giatriP !=1)
  {
    stop();
    delay(100);
    
}
docgiatricambien();
}

void quay180trai()
{
  
  Serial.println("RE TRAI TRONG 1500MS");
  unsigned long starttime=millis();
  while (millis()-starttime<=3000 && giatriL !=1 && giatriT == 1 && giatriM != 1 && giatriR != 1 && giatriP ==1)
  {
    forwardLeft();
    docgiatricambien();
    Serial.println(starttime);
    if ( giatriL ==1 || giatriT != HIGH || giatriM == 1 || giatriR == 1 || giatriP !=1  )
    {
      delayluiphai();
    }
  }
  if(millis()-starttime>=3000 || giatriL ==1 || giatriT != HIGH || giatriM == 1 || giatriR == 1 || giatriP !=1  )
  {
    stop();
    delay(100);
  }
  docgiatricambien();
}

//SOUND TRACK
void errorsound()
{
  tone(coi, 1900);
  delay (500);
  noTone(coi);
  delay(100);
  tone(coi, 1900);
  delay(500);
  noTone(coi);
  error = false;
}

void setup()
{
  { //3 cam bien roi
  pinMode(cbroitrai, INPUT);
  pinMode(cbroigiua, INPUT);
  pinMode(cbroiphai, INPUT);
  }

  {//dieu khien dong co
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);
  pinMode(INC, OUTPUT);
  pinMode(IND, OUTPUT);
  }
  
  pinMode (cbphai, INPUT_PULLUP);
  pinMode (cbtrai, INPUT_PULLUP);
  pinMode (coi, OUTPUT);
  stop();
  Serial.begin (9600);
  start();
}
void loop()
{
docgiatricambien();

if (giatriT == HIGH && giatriP==HIGH) // khong va cham
{ 
  if (giatriL !=0 && giatriM !=0 && giatriR != 0)  //robot khong nam tren mat dat
  {
    stop();
    if (error == true)
    {
      errorsound();
    }
  }
  else if (giatriL ==0 && giatriM ==0 && giatriR == 0)
  {
    forward();
    error = true;
  }
  else if (giatriL !=0 && giatriM !=0 && giatriR == 0 ) // ben trai va o giua roi
  {  if (turnright == true)
    {
      delaylui();
      delayphai();
    }
    else {delaylui(); delaytrai();}
  Serial.println("het chuong trinh 1-1-0");
  }
  else if (giatriL ==0 && giatriM !=0 && giatriR == 0 ) // o giua roi
  {
    
    delaylui();
    delayphai();
    Serial.println("het chuong trinh 0-1-0");
  }
  else if ( giatriL !=0 && giatriM ==0 && giatriR == 0) // ben trai roi
  {

    if (turnright == true)
    {
      delaylui();
      delayphai();
    }
    else {delaylui(); delaytrai();}
    Serial.println("het chuong trinh 1-0-0");
  }
  else if ( giatriL !=0 && giatriM ==0 && giatriR != 0) // ben trai va phai roi
  {
    
    delaylui();
    delayphai();
    Serial.println("het chuong trinh 1-0-1");
  }
  else if (giatriL ==0 && giatriM ==0 && giatriR != 0 ) // ben phai roi
  {
    
    if (turnright == true)
    {
      delaylui();
      delayphai();
    }
    else {delaylui(); delaytrai();}
    Serial.println("het chuong trinh 0-0-1");
  }
  else if (giatriL ==0 && giatriM !=0 && giatriR != 0 ) // ben phai o giua roi
  
  {
    if (turnright == true)
    {
      delaylui();
      delayphai();
    }
    else {delaylui(); delaytrai();}
    Serial.println("het chuong trinh 0-1-1");
  }
  else {
  docgiatricambien();
  }
}
else if (giatriP == LOW && giatriT==LOW) // va cham o giua
{
  Serial.println("phat hien va cham o giua");
  if (turnright == true)
  {
    delaylui();
    quay180phai();
    turnright = false;
  }
  else {delaylui(); quay180trai(); turnright = true;}
}
else if (giatriT == HIGH && giatriP==LOW) // va cham ben phai
  {
  
  Serial.println("phat hien va cham ben phai");
  delayluiphai();
  delaycheckphai();
  }
else if (giatriT == LOW && giatriP== HIGH) // va cham ben trai
{
  Serial.println("phat hien va cham ben trai");

  delayluitrai();
  delaychecktrai();
}
}