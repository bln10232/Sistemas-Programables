/*Arduino 1, Praáctica 1:  Fotoresistencia como alarma */
const int pinLed = 12;
const int pinBuzzer = 11;
const int pinLDR = A0;
int valorLDR;
void setup() {
 pinMode(pinLed, OUTPUT);
 pinMode(pinBuzzer, OUTPUT);
  pinMode(pinLDR, INPUT);
  Serial.begin(9600);
}
void loop() {
 valorLDR = analogRead(pinLDR);
Serial.println(valorLDR);
 if(valorLDR <= 120){
    for(int i = 0;i <= 3; i++){
    sonido();
 }
}
delay(500);
}
void sonido(){
  digitalWrite(pinBuzzer, HIGH);
  digitalWrite(pinLed, HIGH);
  delay(1000);
  digitalWrite(pinBuzzer, LOW);
  digitalWrite(pinLed, LOW);
  delay(500);
}

