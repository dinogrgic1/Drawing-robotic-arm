#include <Servo.h>

Servo s1;      // pocetni servo
Servo s2;      // slobodni servo

//  kutevi serva
float s1_A = 90;
float s2_A = 90;

const float a = 20;      // duljina članka 2017.(cm)
const float b = 16.9;    // duljinea članka 2017.(cm)

const float s1_corr = -15;    // Kalibriranje ruke kod papaze za ruku
const float s2_corr = -5;     

const float x_corr = 8;       // X direction correction factor (cm)
const float y_corr = 8;       // Y direction correction factor (cm)

float A;            //kut nasuprot sranici a
float B;            //kut nasuprot stanici b
float C;            //kut nasuprot stanici c
float theta;

float x;          
float y;          
float c;            //duljina hipotenuze
const float pi = M_PI;

const float Radius = 3;       
const int cenX = 4;   
const int cenY = 4;

///////////////////////////////////////////

void setup()
{
  s1.attach(12);
  s2.attach(11);
  Serial.begin(9600);
}

///////////////////////////////////////////

void loop()
{
  // ocekuje input od serial monitora koji je broj 1
  // kako bi se krug jednom nacrtao
  if(Serial.available() > 0)
  {
    char input = Serial.read();
    if(input == '1')
    {
      for (int t = 0; t<360; t++)        
      {
        // petlja za crtanje kruga
        x = Radius * cos(t *(pi/180)) + cenX; 
        y = Radius * sin(t *(pi/180)) + cenY;
        Serial.println(x, y);
        kalibracijaXY(x,y);         
        kutServo();         
        move();                        
        delay(10);
      }
    }
  }
}

///////////////////////////////////////////

// funkcija za kalibriranje x,y osi na papiru
void kalibracijaXY(float x_input, float y_input)
{
  x = x_input + x;
  y = y_input + y;
}

// izracunaj kutove za pokretanje ruke
void kutServo()
{
  c = sqrt( sq(x) + sq(y) );    // pitagorin poučak
  // kosinus, gornji clanak
  B = (acos( (sq(b) - sq(a) - sq(c))/(-2*a*c) )) * (180/pi);  
  // kosinus, kut nasuprot hipotenuze
  C = (acos( (sq(c) - sq(b) - sq(a))/(-2*a*b) )) * (180/pi);            
  // izračunaj kut koji kalibrira utjecaj donjeg clanka na prvi
  theta = (asin( y / c )) * (180/pi);                               
  // izracunaj kutove na kraju i dodaj korekciju
  s1_A = B + theta + s1_A;          
  s2_A = C + s2_A;                            
}

///////////////////////////////////////////

// funkcija za pokret ruke
void move()
{
  s1.write(s1_A);              
  s2.write(s2_A);            
}

///////////////////////////////////////////
