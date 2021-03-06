
	#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#include<windows.h>
#include "SerialPort.h"
#define MAX_DATA_LENGTH 255

typedef struct{
	char fecha[26];
	char dato[30];
}Recep;

/*Funciones prototipo*/
void fecha(char[]);
void lectura(char*);
void guardar_datosbn(Recep *);
void autoConnect(SerialPort *arduino,char*);


int main(void)
{
 /*Arduino SerialPort object*/
 SerialPort *arduino;
 /* Puerto serie en el que está Arduino*/
 char* portName = "COM7";
 /* Buffer para datos procedentes de Arduino*/
 char incomingData[MAX_DATA_LENGTH];

 /* Crear estructura de datos del puerto serie*/
 arduino = (SerialPort *)malloc(sizeof(SerialPort));
 /* Apertura del puerto serie*/
 Crear_Conexion(arduino,portName);
 autoConnect(arduino,incomingData);
 
}


void autoConnect(SerialPort *arduino,char *incomingData)
{
 int readResult;

/* Espera la conexión con Arduino*/
while (!isConnected(arduino))
{
Sleep(100);
Crear_Conexion(arduino,arduino->portName);
}
 /*Comprueba si arduino está connectado*/
if (isConnected(arduino))
{
printf ("Conectado con Arduino en el puerto %s\n",arduino->portName);
}
 /*Bucle de la aplicación*/
while (isConnected(arduino))
{
 readResult = readSerialPort(arduino,incomingData,MAX_DATA_LENGTH);
if (readResult!=0){
	printf("%s\n", incomingData);
	lectura(incomingData);
}
  Sleep(10);
 
}
if (!isConnected(arduino))
 printf ("Se ha perdido la conexión con Arduino\n");
}


void guardar_datosbn(Recep *r){
		int i;
	FILE *salida;
	salida = fopen("Info.bn","ab");
	
	if(salida==NULL)
		printf("No se ha podido guardar los datos");
	else{
	
	fwrite(r,sizeof(Recep),1,salida);
	
		fclose(salida);
}
}

void lectura(char *d){
	Recep info;
	char Intruso[]="Intruso en la zona";
	char Activa[]="Alarma Activada";
	char NoIntruso[]="Intruso fuera de la zona";
	char Desactivar[]="Alarma Desactivada";
	
	switch(d[0]){
		case '1':
			fecha(info.fecha);
			strcpy(info.dato,Activa);
			break;
		case '2':
			fecha(info.fecha);
			strcpy(info.dato,Intruso);
			break;
		case '3':
			fecha(info.fecha);
			strcpy(info.dato,NoIntruso);
			break;
		case '4':
			fecha(info.fecha);
			strcpy(info.dato,Desactivar);
			break;
		
	}
	
	guardar_datosbn(&info);
	
}



void fecha(char fecha[]){
	      time_t current_time;
    current_time=time(NULL);
    ctime(&current_time);
    strcpy(fecha, ctime(&current_time));
	
}
