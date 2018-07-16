#include <Arduino.h>

#define DETENIDO 0
#define ABRIENDO 1
#define CERRANDO 2

const int relay1Input1 = 7; //Pin control relay 1 , power source actuador cerradura.
const int relay1Input2 = 6; //Pin control relay 2 , power source actuador baliza.
const int relay1Input3 = 5; //Pin control relay 3 , power source actuador 1 porton.
const int relay1Input4 = 4; //Pin control relay 4 , power source actuador 2 porton.
int pin_control = 2; //Pin control interrupciones

volatile byte estado_pin_control;
volatile byte control_state;

int estado_actual;
int estado_anterior;
bool first;

void controlChange() 
{
    control_state = HIGH;
    estado_pin_control = digitalRead(pin_control);
    delay(100);
}

void parar()
{
    //digitalWrite(relay1Input1, LOW);    // Apagamos cerradura (debería estar apagada desde antes, opera con timer).
    //digitalWrite(relay1Input2, LOW);    // Apagamos baliza
    /*Se apagan entradas al actuador del porton*/
    //digitalWrite(relay1Input3, LOW); 
    //digitalWrite(relay1Input4, LOW);
    /*******************************************/
    estado_anterior = estado_actual;
    estado_actual = DETENIDO;
}

void actuar()
{
    //digitalWrite(relay1Input2, HIGH);   // Baliza, operando mientras opera actuador.
    //digitalWrite(relay1Input1, HIGH);   // Se opera cerradura a 12 volts.
    //delay(2000);                        // Se espera 2 segundo para asegurar apertura de cerradura.
    //digitalWrite(relay1Input1, LOW);    // Se opera cerradura a 12 volts.
    if(estado_actual == DETENIDO)
    {
        switch (estado_anterior)
        {
            case ABRIENDO:
                //digitalWrite(relay1Input3, HIGH);
                //digitalWrite(relay1Input4, LOW);
                estado_actual = CERRANDO;
                break;
            case CERRANDO:
                //digitalWrite(relay1Input3, LOW);
                //digitalWrite(relay1Input4, HIGH);  
                estado_actual = ABRIENDO;
                break;
            default:
                break;
        }
    }
    else
    {
        parar();
    }  
}

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(pin_control, INPUT_PULLUP);
    control_state = LOW;
    attachInterrupt( digitalPinToInterrupt(pin_control), controlChange, CHANGE);
    estado_pin_control = LOW;
    estado_actual = DETENIDO;
    estado_anterior = CERRANDO;
    pinMode(relay1Input1, OUTPUT);
    pinMode(relay1Input2, OUTPUT);
    pinMode(relay1Input3, OUTPUT);
    pinMode(relay1Input4, OUTPUT);
    first = true;
}

void loop() {
    // put your main code here, to run repeatedly:
    if (control_state && estado_pin_control==1)
    { 
        Serial.println("EJECUTAR ACTUAR");
        actuar();
        Serial.print("Anterior  ");
        Serial.println(estado_anterior);
        Serial.print("Actual    ");
        Serial.println(estado_actual);
        control_state = LOW;

    } 
    if (control_state && estado_pin_control==0)
    { 
        Serial.println("EJECUTAR PARAR");
        parar();
        Serial.print("Anterior  ");
        Serial.println(estado_anterior);
        Serial.print("Actual    ");
        Serial.println(estado_actual);
        control_state = LOW;
    }     
}