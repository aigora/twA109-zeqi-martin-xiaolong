#define D_MAX 10

const int TriggerPin = 9;
const int EchoPin =8;
const int PUL_Puerta= 3;
const int PUL_Desactivar=4;
int distancia_o;
int a=0;

void setup() {
  
Serial.begin(9600);
pinMode(PUL_Puerta,INPUT);
pinMode(TriggerPin,OUTPUT);
pinMode(EchoPin,INPUT);
pinMode(PUL_Desactivar,INPUT);
delay(1000);
distancia_o=ping(TriggerPin,EchoPin);

}

void loop() {
  
int lectura;
lectura=digitalRead(PUL_Puerta);

if(lectura==1 && a==0){
pulsador(&a);
}
if(a==1)
{
  Serial.print('4');
  a=0;
 }
}

void pulsador(int* c){
    int distancia_f;
    int diferencia;
  
    distancia_f = ping(TriggerPin,EchoPin);
   diferencia=abs(distancia_f-distancia_o);

   if(diferencia > D_MAX){
      Serial.print('1');
       *c=1;
  }
  *c=0
  }




int ping(int TriggerPin,int EchoPin){
  long duration, distanceCm;
  digitalWrite(TriggerPin,LOW);
  delayMicroseconds(4);
  digitalWrite(TriggerPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerPin,LOW);

  duration= pulseIn(EchoPin,HIGH);
  distanceCm = duration *10 /292 /2;
  return distanceCm;
  }
