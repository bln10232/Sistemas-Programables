/*Arduino 1, Praáctica 2:  Motor arranque/ Paro */
const int pinBoton = 2;
const int pinMotor = 3;
const int pinLed = 4;
int velocidad;
boolean encendido = false;
void setup() {
 pinMode(pinBoton, INPUT);
 pinMode(pinMotor, OUTPUT);
 pinMode(pinLed, INPUT);
 Serial.begin(9600);
}
void loop() {
Serial.println("\n\nPresione el botón");
   while (digitalRead(pinBoton) == LOW);
    if(encendido == false){
  Serial.println("Arrancando Motor:");
  digitalWrite(pinLed, HIGH);
  for(velocidad = 0; velocidad <= 255; velocidad++){
    analogWrite(pinMotor, velocidad);
    delay(30);
    Serial.println(porcentaje(velocidad));
    Serial.print("%");
  }
   Serial.println("Motor arrancando al 100%");
    for(int i = 1; i <= 3; i++){
      estadoLed();
    }
      digitalWrite(pinLed, HIGH);
      encendido = true;
    }else{
     Serial.println("Parando motor:");
      for(velocidad = 255; velocidad >= 0; velocidad--){
        analogWrite(pinMotor, velocidad);
        delay(30);
        Serial.println(porcentaje(velocidad));
        Serial.println("%");
      }
      digitalWrite(pinLed, LOW);
      encendido = false;
    }
}
    int porcentaje(int velocidad){
      int operacion = velocidad *100;
      int resultado = operacion / 25;
      return resultado;
    }
    void estadoLed(){
      digitalWrite(pinLed, HIGH);
      delay(500);
      digitalWrite(pinLed, LOW);
      delay(500);
    }

