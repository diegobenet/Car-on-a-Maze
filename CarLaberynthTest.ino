#include <Servo.h>
Servo servoMotor;
const int EchoPin = 3;
const int TriggerPin = 2;
float distancia;
long tiempo;

void setup() {
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  servoMotor.attach(9);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(10,OUTPUT); //llanta derecha
  pinMode(11,OUTPUT); //llanta derecha
  pinMode(12,OUTPUT); //llanta izquierda
  pinMode(13,OUTPUT); //llanta izquierda
}

void loop() {
  analogWrite(5, 120); //velocidad en 120
  analogWrite(6, 120); //velocidad en 120
  //izq prim
  avanza();
  delay(500);
  frenar();

  //Derecha prim
  digitalWrite(11, HIGH);//derecha
  digitalWrite(13, HIGH);// izquierda
  digitalWrite(12, LOW); //izquierda      CARRO avanza
  digitalWrite(10, LOW); //derecha
  delay(500);
  frenar();
  delay(100);
  
  servoMotor.write(90);           //sensor voltea al frente
  distancia = calcularDist();     //mide distancia
  delay(1000);

  analogWrite(5, 175);    //velocidad en 175
  analogWrite(6, 175);
  
  if(distancia<5){ 
    servoMotor.write(180);  //voltea sensor a la izquierda
    distancia = calcularDist();
    delay(1000);
    
    if(distancia>7){      //si distancia menos de 7cm
      rotaIzquierda();
      delay(2000);
      frenar();
    }
    else{
      servoMotor.write(0);        //sensor a la derecha
      distancia = calcularDist();
      delay(1000);
      if(distancia>5){    //si distancia menos a 5
        rotaDerecha();
        delay(2000);
        frenar();
      }
      else{
        avanza();
        delay(1000);
        frenar();
      }
    }
  }
}

float calcularDist(){
  digitalWrite(TriggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerPin, LOW);
  tiempo = (pulseIn(EchoPin, HIGH)/2);
  
  return float(tiempo * 0.0343);
}

void frenar(){
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);    //frena
  digitalWrite(10, LOW);
 }
 
void avanza(){
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);    //avanza
  digitalWrite(11, HIGH);
  digitalWrite(10, LOW);
}

void rotaDerecha(){
  digitalWrite(13,HIGH);
  digitalWrite(12,LOW);     //rota derecha
  digitalWrite(11,LOW);
  digitalWrite(10,HIGH);
}
void rotaIzquierda(){
  digitalWrite(13,LOW);
  digitalWrite(12,HIGH);      //rota izquierda
  digitalWrite(11,HIGH);
  digitalWrite(10,LOW);
}
   
