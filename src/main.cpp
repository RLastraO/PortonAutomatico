#include <Arduino.h>

#define ABIERTO 1
#define CERRADO 0
const int relay1Input1 = 7; //Pin control relay 1
const int relay1Input2 = 6; //Pin control relay 2
const int relay1Input3 = 5; //Pin control relay 3
const int relay1Input4 = 4; //Pin control relay 4
int pin_control = 2; //Pin control interrupciones

int estado_pin_control;
bool portonLow;
bool portonHigh;
bool portonChange;
int estado_porton;

void ServicioPortonChange() 
{
    portonChange = true;
}

void setup() {
    // put your setup code here, to run once:
      
    Serial.begin(9600);
    attachInterrupt( 0, ServicioPortonChange, CHANGE);
    portonChange = false;
    estado_pin_control = LOW;
    estado_porton = CERRADO;
    pinMode(relay1Input1, OUTPUT);
    pinMode(relay1Input2, OUTPUT);
    pinMode(relay1Input3, OUTPUT);
    pinMode(relay1Input4, OUTPUT);
}

void loop() {
    // put your main code here, to run repeatedly:
    Serial.println("1");
    if (portonChange){    
        Serial.println("CHANGE");
        estado_pin_control = digitalRead(pin_control);
        Serial.println(estado_pin_control);
        delay(1000);
        portonChange = false;
    }
}

void actuar()
{
    switch (estado_porton){
        case ABIERTO:
            digitalWrite(relay1Input1, HIGH);
            digitalWrite(relay1Input2, HIGH);  
            digitalWrite(relay1Input3, HIGH);
            estado_porton = CERRADO;
            break;
        case CERRADO:
            digitalWrite(relay1Input1, HIGH);
            digitalWrite(relay1Input2, HIGH);  
            digitalWrite(relay1Input3, HIGH);
            break;
        default:
            break;
    }
}

void parar()
{
    switch (estado_porton)
    {
        case ABIERTO:
            digitalWrite(relay1Input1, LOW);
            digitalWrite(relay1Input2, HIGH);  
            digitalWrite(relay1Input3, HIGH);
            estado_porton = CERRADO;
            break;
        case CERRADO:
            digitalWrite(relay1Input1, HIGH);
            digitalWrite(relay1Input2, HIGH);  
            digitalWrite(relay1Input3, HIGH);
            break;
        default:
            break;
    }
}