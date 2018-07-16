#include <Arduino.h>

#define DETENIDO 0
#define ABRIENDO 1
#define CERRANDO 2

const int relay1Input1 = 7; //Pin control relay 1 , power source actuador cerradura.
const int relay1Input2 = 6; //Pin control relay 2 , power source actuador baliza.
const int relay1Input3 = 5; //Pin control relay 3 , power source actuador 1 porton.
const int relay1Input4 = 4; //Pin control relay 4 , power source actuador 2 porton.
int pin_control = 2; //Pin control interrupciones

int estado_pin_control;
bool portonLow;
bool portonHigh;
bool portonChange;
int estado_actual;
int estado_anterior;

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
    estado_actual = DETENIDO;
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
    digitalWrite(relay1Input2, HIGH); // Baliza, operando mientras opera actuador.
    digitalWrite(relay1Input1, HIGH); // Se opera cerradura a 12 volts.
    delay(2000); // Se espera 2 segundo para asegurar apertura de cerradura.
    
    switch (estado_anterior)
    {
        case ABRIENDO:
            digitalWrite(relay1Input3, HIGH);
            break;
        case CERRANDO:
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
    digitalWrite(relay1Input2, LOW); // Baliza, operando mientras opera actuador.
    estado_actual = DETENIDO;
}