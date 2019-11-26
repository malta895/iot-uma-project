/*
  PRACTICA 1 "SENSOR DE ULTRASONIDOS"
  Muestra la distancia a la que se encuentran los objetos
*/

#define pulso 1   //define la salida por donde se manda el pulso
#define rebote 4 //define la salida por donde se recibe el rebote

int distancia;  //crea la variable "distancia"
float tiempo;  //crea la variable tiempo (como float)

void setup()
{
  Serial.begin(9600);  //inicializa el puerto serie
  pinMode(pulso, OUTPUT); //Declaramos el pin 9 como salida (pulso ultrasonido)
  pinMode(rebote, INPUT); //Declaramos el pin 8 como entrada (recepción del pulso)
}

void loop()
{
  digitalWrite(pulso,LOW); //Por cuestión de estabilización del sensor
  delayMicroseconds(5);
  digitalWrite(pulso, HIGH); //envío del pulso ultrasónico
  delayMicroseconds(10);
  tiempo = pulseIn(rebote, HIGH);  //funcion para medir el tiempo y guardarla en la variable "tiempo"
  distancia = 0.01715*tiempo; //fórmula para calcular la distancia

  /*Monitorización en centímetros por el monitor serial*/
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");
  delay(3000);
}
