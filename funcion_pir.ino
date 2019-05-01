#define maxa 10


const int PIR=12;
int flag=0,a=0;
unsigned long t_i; // tiempo inicial
int contador=0;

void setup() {
Serial.begin(9600);
pinMode(PIR,INPUT);
delay(10000);
}

void loop() {
  unsigned long t_a;//tiempo actual
  int pir;
  pir=digitalRead(PIR);
  
  InfraRedSensor(pir,&t_a);
  }
  
void InfraRedSensor(int pir,unsigned long * t_a){
   int d_on,d_off;//desfases de tiempo para cuando pir==1 y para pir==0
   
  if(pir==1){

    if(d_off>0){
      a=0;
    d_off=0}
    
    intervalo(&d_on,*t_a);
     
     if(d_on>Max_on && flag==0){
       Serial.print('2');
       flag=1;
       d_off=0;
    }
 
  }else {
    
    if(flag==1){
 
   if(d_on > 0){
    a=0;
    d_on=0}
    
    intervalo(&d_off,*t_a);
    
    if(d_off>Max_off){
    Serial.print('3');
    flag=0;
    d_on=0;
    } 
   }
    }
delay(50);
    }


void intervalo(int * des,unsigned long tiempo_actual){
   if(a==0)
 {
   tiempo_inicial=millis()/1000;
    *des = 0;
   Serial.println(*des);
   a=1;
  }else{
    tiempo_actual=millis()/1000;
    *des=tiempo_actual-tiempo_inicial;
    Serial.println(*des);
    }
 }
 
