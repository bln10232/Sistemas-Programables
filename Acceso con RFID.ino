//Práctica de Acceso RFID
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
//Pines
#define RST_PIN 9
#define SS_PIN 10
#define pinBuzzer 8
#define pinBoton 7
//Crear objetos de los dispositivos
MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x2F, 16, 2);
//Datos del usuario del mod RFID
byte usuario[7] = {0x04, 0xE6, 0xAA, 0xAA, 0x9E, 0x33, 0x80};
//Variables
byte lectorUID[7];
int estadoBoton = 0;
int estadoBotonAnt = 0;
int contador = 0;
bool menuBool = false;
void setup() {
  //Inicializar pines y objetos
  Serial.begin(9600);
  pinMode(pinBuzzer, OUTPUT);
  pinMode(pinBoton, INPUT);
  SPI.begin();
  mfrc522.PCD_Init();
}
void loop() {
  estadoBotonRFID();
  if(contador == 0){
    Serial.print("Presione boton");
    Serial.println(" Para una opcion");
  }else if(contador == 1){
    Serial.println("Escanear Tarjeta");
    if(!mfrc522.PICC_IsNewCardPresent()){
      return;
    }
    if(!mfrc522.PICC_ReadCardSerial()){
      return;
    }
    sonido(100,100);
    //Escanear tarjeta
    escanearUsuario();
    mfrc522.PICC_HaltA();
  }else if(contador == 2){
    Serial.print("Acerque la");
    Serial.println(" Tarjeta");
    if(!mfrc522.PICC_IsNewCardPresent()){
      return;
    }
    if(!mfrc522.PICC_ReadCardSerial()){
      return;
    }
    sonido(100,100);
    //Guardar código de la tarjeta 
    for(byte i = 0; i < mfrc522.uid.size; i++){
      lectorUID[i] = mfrc522.uid.uidByte[i];
    }
    Serial.print("Comprobando");
    Serial.println(" Acceso");
   delay(5000);
    //Comparar códigos
    if(compararUID(lectorUID,usuario)){
      Serial.print("Bienvenido");
      Serial.println(" - Equipo");
      delay(3000);
      Serial.print("Iniciado");
      Serial.println(" Sesion...");
      delay(5000);
      menuBool = true;
      mfrc522.PICC_HaltA();
      //Acceder al menú
      menu();
    }else{
      Serial.print("Error Usuario");
      Serial.println(" - No permitido");
      sonido(1000, 500);
      mfrc522.PICC_HaltA();
    }
  }
  mfrc522.PICC_HaltA();
}
void estadoBotonRFID(){
  //Comprobar si se presionó el botón
  estadoBoton = digitalRead(pinBoton);
  if(estadoBoton != estadoBotonAnt){
    if(estadoBoton == HIGH){
      contador++;
      if(contador == 3){
        contador = 0;
      }
    }
    delay(5000);
  }
  estadoBotonAnt = estadoBoton;
}
void sonido(int T1, int T2){
  //Generar pitido con el buzzer
  digitalWrite(pinBuzzer,HIGH);
  delay(T1);
  digitalWrite(pinBuzzer,LOW);
  delay(T2);
}
void escanearUsuario(){
  //Leer tarjeta ingresada 
  Serial.print("UID: ");
  //Hexadecimal
  for(byte i = 0; i < mfrc522.uid.size; i++){
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.print("  HEX\t\t");
  //Decimal
  for(byte i = 0; i < mfrc522.uid.size; i++){
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
  }
  Serial.print("  DEC");
}
bool compararUID(byte lector[], byte usuario[]){
  for(byte i = 0; i < mfrc522.uid.size; i++){
    if(lector[i] != usuario[i]){
      return false;
    }
  }
  return true;
}
void menu(){
  //Mostrar menu  
  while(menuBool == true){
    inicio:
    Serial.println("Opcion 1");
    Serial.println("Opcion 2");
    //Volver a escanear tarjeta para salir del menu
    if(!mfrc522.PICC_IsNewCardPresent()){
      goto inicio;
    }
    if(!mfrc522.PICC_ReadCardSerial()){
      goto inicio;
    }
    for(byte i = 0; i < mfrc522.uid.size; i++){
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
    }
    //Guardar código de la tarjeta ingresada
    for(byte i = 0; i < mfrc522.uid.size; i++){
      lectorUID[i] = mfrc522.uid.uidByte[i];
    }
    //Comparar códigos
    if(compararUID(lectorUID,usuario)){
      menuBool = false;
      Serial.println("");
      Serial.println("Cerrando sesion");
      delay(5000);
      sonido(300,300);
      sonido(300,300);
      contador = 0;
    }else{
      //Bloquear en caso de no ser el mismo
      while(true){
        Serial.print("No eres usuario");
        Serial.println(" - Bloqueado !!!");
        sonido(10,10);
      }
    }
    mfrc522.PICC_HaltA();
  }
}
