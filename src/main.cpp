#include <Arduino.h>

int horn = 2;
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
int valueL; // gia tri cam bien trai (GIA TRI ==0(LOW) KHI ROBOT TREN MAT DAT)
int valueM; // gia tri cam bien giua (GIA TRI ==0(LOW) KHI ROBOT TREN MAT DAT)
int valueR; // gia tri cam bien phai (GIA TRI ==0(LOW) KHI ROBOT TREN MAT DAT)

//cam bien va cham
const int cbphai = 13; // cam bien va cham phai
const int cbtrai = 12; // cam bien va cham trai
int valueT; // gia tri cam bien va cham trai (GIA TRI ==1(HIGH) KHI ROBOT KHONG VA CHAM)
int valueP; // gia tri cam bien va cham phai (GIA TRI ==1(HIGH) KHI ROBOT KHONG VA CHAM)

boolean turnright = true; //
boolean error = true;
boolean previous;
boolean mode2 = false;

void readsensorvalue()
{
  valueL = digitalRead(cbroitrai);
  Serial.print("gia tri cam bien roi ben trai la:");
  Serial.println(valueL);
  valueM = digitalRead(cbroigiua);
  Serial.print("gia tri cam bien roi o giua la:");
  Serial.println(valueM);
  valueR = digitalRead(cbroiphai);
  Serial.print("gia tri cam bien roi ben phai la:");
  Serial.println(valueR);
  valueT = digitalRead(cbtrai);
  valueP = digitalRead(cbphai);

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

void delaybackward()   // LUI TRONG 300MS
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
    readsensorvalue();
}

void delaybackwardLeft()
{
  unsigned long starttime=millis();
  while(millis()-starttime<=200)   
  {
    backwardLeft();
    
    Serial.println(starttime);
  }
    readsensorvalue();
    stop();
    delay(100);
}

void delaybackwardRight()
{
  unsigned long starttime=millis();
  while(millis()-starttime<=200)   
  {
    backwardRight();
    readsensorvalue();
    Serial.println(starttime);}
    stop();
    delay(100);
}

void delayLeft()   // RE TRAI TRONG 500MS
{
  turnright = true;
  Serial.println("RE TRAI TRONG 500MS");
  unsigned long starttime=millis();
  while(millis()-starttime<=400 && valueL !=1 && valueT == 1 && valueM != 1 && valueR != 1 && valueP ==1) // DO ROI TRAI VA VA CHAM TRAI    
  {
    left();
    readsensorvalue();
    Serial.println(starttime);
    if ( valueL ==1 || valueT != HIGH || valueM == 1 || valueR != 1 || valueP !=1 )
    {
      turnright = false;
    }
  }
  if(millis()-starttime>=400 || valueL ==1 || valueT != HIGH || valueM == 1 || valueR != 1 || valueP !=1 )
  {
    stop();
    delay(500);
}
readsensorvalue();
}

void delaychecktrai()   // RE TRAI TRONG 500MS
{
  Serial.println("RE TRAI TRONG 500MS");
  unsigned long starttime=millis();
  while(millis()-starttime<=1000 && valueL !=1 && valueT == 1 && valueM != 1 && valueR != 1 && valueP ==1) // DO ROI TRAI VA VA CHAM TRAI    
  {
    checkLeft();
    readsensorvalue();
    Serial.println(starttime);
  }
readsensorvalue();
}

void delayRight()    // RE PHAI TRONG 500MS
{
  turnright = false;
  Serial.println("RE PHAI TRONG 500MS");
  unsigned long starttime=millis();
  while (millis()-starttime<=400 && valueL !=1 && valueT == 1 && valueM != 1 && valueR != 1 && valueP ==1)
  {
    right();
    readsensorvalue();
    Serial.println(starttime);
    if (valueL ==1 || valueT != HIGH || valueM == 1 || valueR != 1 || valueP !=1)
    {
      turnright = true;
    }
  }
  if(millis()-starttime>=400 || valueL ==1 || valueT != HIGH || valueM == 1 || valueR != 1 || valueP !=1)
  {
    stop();
    delay(500);
}
readsensorvalue();
}

void delaycheckphai()    // RE PHAI TRONG 500MS
{
  Serial.println("RE PHAI TRONG 500MS");
  unsigned long starttime=millis();
  while (millis()-starttime<=1000 && valueL !=1 && valueT == 1 && valueM != 1 && valueR != 1 && valueP ==1)
  {
    checkRight();
    readsensorvalue();
    Serial.println(starttime);
  }
readsensorvalue();
}

void rotateRight()
{
  turnright = false;
  Serial.println("RE PHAI TRONG 1500MS");
  unsigned long starttime=millis();
  while (millis()-starttime<=3000 && valueL !=1 && valueT == 1 && valueM != 1 && valueR != 1 && valueP ==1)
  {
    forwardRight();
    readsensorvalue();
    Serial.println(starttime);
    if (valueL ==1 || valueT != HIGH || valueM == 1 || valueR == 1 || valueP !=1)
    {
      turnright = true;
      delaybackwardLeft();
    }
  }
  if(millis()-starttime>=3000 || valueL ==1 || valueT != HIGH || valueM == 1 || valueR == 1 || valueP !=1)
  {
    stop();
    delay(100);
    
}
readsensorvalue();
}

void rotateLeft()
{
  
  Serial.println("RE TRAI TRONG 1500MS");
  unsigned long starttime=millis();
  while (millis()-starttime<=3000 && valueL !=1 && valueT == 1 && valueM != 1 && valueR != 1 && valueP ==1)
  {
    forwardLeft();
    readsensorvalue();
    Serial.println(starttime);
    if ( valueL ==1 || valueT != HIGH || valueM == 1 || valueR == 1 || valueP !=1  )
    {
      delaybackwardRight();
    }
  }
  if(millis()-starttime>=3000 || valueL ==1 || valueT != HIGH || valueM == 1 || valueR == 1 || valueP !=1  )
  {
    stop();
    delay(100);
  }
  readsensorvalue();
}

//SOUND TRACK
void errorsound()
{
  tone(horn, 1900);
  delay (500);
  noTone(horn);
  delay(100);
  tone(horn, 1900);
  delay(500);
  noTone(horn);
  error = false;
}

void startsound()
{
  tone(horn, 1500);
  delay (100);
  noTone(horn);
  delay(100);
  tone(horn, 1900);
  delay(100);
  noTone(horn);
}

void mode2sound ()
{ 
  tone(horn, 1500);
  delay (100);
  noTone(horn);
  delay(100);
  tone(horn, 1900);
  delay(100);
  noTone(horn);
  delay(100);
  tone(horn, 1500);
  delay(100);
  noTone(horn);
  delay(100);
  tone(horn, 1900);
  delay(100);
  noTone(horn);
}

//MODE
void mode()
{
  while (mode2 ==true && valueL !=1 && valueT == 1 && valueM != 1 && valueR != 1 && valueP ==1)
  {
    forwardRight();
    readsensorvalue();
    if ( valueL ==1 || valueT != HIGH || valueM == 1 || valueR == 1 || valueP !=1  )
    {
      delaybackwardRight();
      mode2 = false;
    }
  }
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
  pinMode (horn, OUTPUT);
  mode2 = false;
  stop();
  Serial.begin (9600);
  startsound();
}

void loop()
{
  if (mode2 == true)
  {
    mode2sound();
    mode();
  }
  else
  {
    readsensorvalue();
    if (valueT == HIGH && valueP==HIGH) // khong va cham
    { 
      if (valueL !=0 && valueM !=0 && valueR != 0)  //robot khong nam tren mat dat
      {
        stop();
        if (error == true)
        {
          errorsound();
        }
        if (valueT == LOW && valueP == LOW)
        {
          if (mode2 == false)
          {
          mode2 = true;
          }
          else mode2 = false;
        }
      }
      else if (valueL ==0 && valueM ==0 && valueR == 0)
      {
        forward();
        error = true;
      }
      else if (valueL !=0 && valueM !=0 && valueR == 0 ) // ben trai va o giua roi
      {  if (turnright == true)
        {
          delaybackward();
          delayRight();
        }
        else {delaybackward(); delayLeft();}
        //Serial.println("het chuong trinh 1-1-0");
      }
      else if (valueL ==0 && valueM !=0 && valueR == 0 ) // o giua roi
      {
        
        delaybackward();
        delayRight();
        //Serial.println("het chuong trinh 0-1-0");
      }
      else if ( valueL !=0 && valueM ==0 && valueR == 0) // ben trai roi
      {
        if (turnright == true)
        {
          delaybackward();
          delayRight();
        }
        else {delaybackward(); delayLeft();}
        //Serial.println("het chuong trinh 1-0-0");
      }
      else if ( valueL !=0 && valueM ==0 && valueR != 0) // ben trai va phai roi
      {
        
        delaybackward();
        delayRight();
        //Serial.println("het chuong trinh 1-0-1");
      }
      else if (valueL ==0 && valueM ==0 && valueR != 0 ) // ben phai roi
      {
        
        if (turnright == true)
        {
          delaybackward();
          delayRight();
        }
        else {delaybackward(); delayLeft();}
        //Serial.println("het chuong trinh 0-0-1");
      }
      else if (valueL ==0 && valueM !=0 && valueR != 0 ) // ben phai o giua roi
      
      {
        if (turnright == true)
        {
          delaybackward();
          delayRight();
        }
        else {delaybackward(); delayLeft();}
        //Serial.println("het chuong trinh 0-1-1");
      }
      else {
      readsensorvalue();
      }
    }
    else if (valueP == LOW && valueT==LOW) // va cham o giua
    {
      //Serial.println("phat hien va cham o giua");
      if (turnright == true)
      {
        delaybackward();
        rotateRight();
        turnright = false;
      }
      else {delaybackward(); rotateLeft(); turnright = true;}
    }
    else if (valueT == HIGH && valueP==LOW) // va cham ben phai
      {
      //Serial.println("phat hien va cham ben phai");
      delaybackwardRight();
      delaycheckphai();
      }
    else if (valueT == LOW && valueP== HIGH) // va cham ben trai
    {
      //Serial.println("phat hien va cham ben trai");

      delaybackwardLeft();
      delaychecktrai();
    }
  }
}