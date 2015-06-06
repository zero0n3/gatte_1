#include <SoftwareServo.h> 
 
SoftwareServo myservo;  // create servo object to control a servo 
 
int aperto = 0;   //variabile per switch case per aprire o chiudere i cassetti
int sn = 0;    //porte sono già aperte o chiuse? 0 = chiuse / 1 = perla / 2 = tigre
int motore = 90;  //giro del servo che all'inizio viene impostato a neutro
const int limite = 600;
int fsrPin = 0;     // the FSR and 10K pulldown are connected to a0
int peso;     // the analog reading from the FSR resistor divider

void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
} 
 
void loop() 
{ 
 peso = analogRead(fsrPin);

//scelta della gatta in base al peso
  if (peso >= 0 && peso <= 100) {
    aperto = 0;    //nessuna gatta sulla bilancia
  } else if (peso > 100 && peso <= limite) {
    aperto = 1;    //perla sulla bilancia 
  } else {
    aperto = 2;    //tigre sulla bilancia
  }
  
//in base alla gatta apro o chiudo o non faccio nulla se già aperto
  switch (aperto) {
  case 0:    //nessuna gatta sulla bilancia
    if (sn > 0) {
       myservo.write(90);   // se una gabbia è aperta le chiudo
       sn = 0;          //e identifico che è chiuso
    }
    delay(15);
    SoftwareServo::refresh(); 
    break;  
  
  case 1:    //parte perla
    if (sn < 1 || sn > 1) {
       myservo.write(150);   // se una gabbia è chiusa o aperta per la tigre, apro la perla
       sn = 1;          //e identifico che è già aperta per lei
    }
    delay(15); 
    SoftwareServo::refresh();
    break;  
  
  case 2:    //parte tigre
    if (sn < 2) {
       myservo.write(30);   // se una gabbia è chiusa o aperta per la perla, apro la tigre
       sn = 2;          //e identifico che è già aperta per lei
    }
    delay(15); 
    SoftwareServo::refresh();
    break;  
  } 
  
  delay(1000);
}
