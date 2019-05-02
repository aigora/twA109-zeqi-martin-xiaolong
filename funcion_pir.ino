#define Max_on 10
#define Max_off 10

const int PIR=12;
int flag=0,a=0;
unsigned long t_i; // tiempo inicial


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

     if(flag==1){
         a=0;
         d_off=0;
        intervalo(&d_on,*t_a);
     }else{
         intervalo(&d_on,*t_a);
        if(d_on>Max_on){
           Serial.print('2');
           flag=1;
            d_off=0;
         }
     }
 
  }else {
    
  
    if(flag==1){
      intervalo(&d_off,*t_a);    
      if(d_off>Max_off){
        Serial.print('3');
        flag=0;
        d_on=0;
      } 
    }else{
      a=0;
    intervalo(&d_off,*t_a);
    d_on=0;
    }
    
  }
}


void intervalo(int * des,unsigned long tiempo_actual){
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
 
