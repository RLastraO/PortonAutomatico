# Documentación proyecto portón

Automatización de apertura y cierre de portón utilizando Arduino 1 y placa de recpeción transmisión de radio frecuencias con 2 controles.

## Materiales

* Placa arudino 1
* Relay Shield 4 reles
* Placa recpeción de radio

## Entradas

Se utiliza 1 entrada de interrupciones de la placa arduino 1, pin2, equivalente a la declaración de entrada 0 en la función attachInterrupt. La función ServicioPortonChange será nuestra implementación de la función de interrupción.
> attachInterrupt( 0, ServicioPortonChange, CHANGE);

## Salidas

Se delcaran 3 salidas correspondientes a las entradas de control a los relays de la placa relayShield.
> relay1Input1: pin 7 de la placa arduino. Controla la salida del relay 1.
>
> relay1Input2: pin 6 de la placa arduino. Controla la salida del relay 2.
>
> relay1Input3: pin 5 de la placa arduino. Controla la salida del relay 3.
>
> relay1Input4: pin 4 de la placa arduino. Controla la salida del relay 4.

La distriución en el circuito de control es la siguiente:

| Relay    | Voltaje  | Propósito                |
|----------|----------|--------------------------|
| 1        | 12  DC V | Control cerradura        |
| 2        | 220 AC V | Control baliza           |
| 3        | 220 AC V | Control 1 actuador portón|
| 4        | 220 AC V | Control 2 actuador portón|