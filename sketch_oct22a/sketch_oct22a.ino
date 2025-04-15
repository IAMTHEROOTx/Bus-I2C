#include <Wire.h>

class MonAfficheurLcd {
private:

    unsigned char data, rs, rw, e, r;
    unsigned char OctetAtransmettreAu8574;
    //void OctetAtransmettreAu8574();
    void TransmettreOctetAu8574();
    void EcrireDataSurLCD();
    void EcrireOctetSurLcd(unsigned char a);

public:

    void Initialiser();
    void EcrireSurLaLigne1(char* ptr);
    void EcrireSurLaLigne2(char* ptr);
};


//void MonAfficheurLcd::OctetAtransmettreAu8574(){
  
  //}
void MonAfficheurLcd::TransmettreOctetAu8574(void){
  OctetAtransmettreAu8574 = 16 * data + 8 * r + 4 * e + 2 * rw + rs; //création de l'octet
  Wire.beginTransmission(0x27); 
  Wire.write(OctetAtransmettreAu8574);
  Wire.endTransmission();
  delay(1);
}

void MonAfficheurLcd::EcrireDataSurLCD(){
  e = 1;
  TransmettreOctetAu8574();
  e = 0;
  TransmettreOctetAu8574();
}

void MonAfficheurLcd::EcrireOctetSurLcd(unsigned char a){
  data = a / 16;
  EcrireDataSurLCD();
  data = a % 16; 
  EcrireDataSurLCD();
  
}

void MonAfficheurLcd::EcrireSurLaLigne1(char* ptr){
  unsigned char i;
  unsigned char findechaine;
  char c;
  rs = 0;
  EcrireOctetSurLcd(0x80);

  rs = 1;
  findechaine = 0;
  for(i = 1; i <= 16; i++){
    if(findechaine == 0){
      c = *ptr;
      ptr++;
      if (c == 0){findechaine = 1; c = ' ';}
    }else
    c = ' ';
    EcrireOctetSurLcd(c);
  }
}

void MonAfficheurLcd::EcrireSurLaLigne2(char* ptr){
  unsigned char i;
  unsigned char findechaine;
  char c;
  rs = 0;
  EcrireOctetSurLcd(0xC0);

  rs = 1;
  findechaine = 0;
  for(i = 1; i <= 16; i++){
    if(findechaine == 0){
      c = *ptr;
      ptr++;
      if (c == 0){findechaine = 1; c = ' ';}
    }else
    c = ' ';
    EcrireOctetSurLcd(c);
  }
}

void MonAfficheurLcd::Initialiser(){
  rs = 0;
  e = 0;
  rw = 0;
  r = 0;
  data = 3;

  EcrireDataSurLCD();
  delay(5); 

  
  r = 1;

  data = 3; EcrireDataSurLCD(); delay(5);
  data = 3; EcrireDataSurLCD();
  data = 3; EcrireDataSurLCD(); 

  data = 2; EcrireDataSurLCD();

  data = 2; EcrireDataSurLCD();
  data = 8; EcrireDataSurLCD();

  data = 0; EcrireDataSurLCD();
  data = 0xC; EcrireDataSurLCD();

  data = 0; EcrireDataSurLCD();
  data = 6; EcrireDataSurLCD();

  data = 0; EcrireDataSurLCD();
  data = 1; EcrireDataSurLCD();

  rs = 1;
 
}

void setup(){
  MonAfficheurLcd MonAfficheurLcd1;

  Wire.begin();
  
  MonAfficheurLcd1.Initialiser();
  MonAfficheurLcd1.EcrireSurLaLigne1("IAM");
  MonAfficheurLcd1.EcrireSurLaLigne2("THEROOT");

}
  


void loop()
{
}
