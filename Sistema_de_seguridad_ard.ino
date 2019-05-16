#define Max_on 30 
#define Max_off 30 //en segundos
#define D_MAX 20 // en cm

const int PIR=12;
char flag=0,a=0;
unsigned long t_i; // tiempo inicial
const int TriggerPin = 9;
const int EchoPin =8;
const int PUL_Puerta= 4;
const int PUL_Desactivar=5;
int distancia_o,h=0,p=0;



void setup() {
Serial.begin(9600);
pinMode(PIR,INPUT);
pinMode(PUL_Puerta,INPUT);
pinMode(TriggerPin,OUTPUT);
pinMode(EchoPin,INPUT);
pinMode(PUL_Desactivar,INPUT);
delay(1000);
distancia_o=ping(TriggerPin,EchoPin);
}

void loop() {
  int pir,lectura,p_des;
  lectura=digitalRead(PUL_Puerta);
  pir=digitalRead(PIR);
  p_des=digitalRead(PUL_Desactivar);
  InfraRedSensor(pir);

  
  if(lectura==1 && h==0){
    h = pulsador();
   }
  if(p_des==1 && p==0)
  {
    Serial.print('4');
    p=1;
      h=0;
  }
 
}
  
void InfraRedSensor(int pir){
   int d_on,d_off;//desfases de tiempo para cuando pir==1 y para pir==0
   
  if(pir==1){
     
    if(flag==1){
      a=0;
    d_off=0;
   intervalo(&d_on);
  }else{
     intervalo(&d_on);
     if(d_on>Max_on){
       Serial.print('2');
       flag=1;
       d_off=0;
    }
     }
     
  }else {
     
    if(flag==1){
    intervalo(&d_off);
    
    if(d_off>Max_off){
    Serial.print('3');
    flag=0;
    d_on=0;
    } 

  }else{
      a=0;
    intervalo(&d_off);
    d_on=0;
    }
    }

}


void intervalo(int * des){
   unsigned long tiempo_actual
  if(a==0)
 {
   t_i=millis()/1000;
    *des = 0;
   a=1;
  }else{
    tiempo_actual=millis()/1000;
    *des=tiempo_actual-t_i;
    }
 }



 int pulsador(void){
    int distancia_f;
    int diferencia;
    int c=0;
    distancia_f = ping(TriggerPin,EchoPin);
   diferencia=abs(distancia_f-distancia_o);

   if(diferencia > D_MAX){
      Serial.print('1');
     p=0;
       c=1;
  }
  return c;
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
 
