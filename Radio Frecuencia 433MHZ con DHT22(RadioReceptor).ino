// Práctica de Radio Frecuencia 433MHZ con DHT22
//Receptor
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <VirtualWire.h>
#define CIRCLE 0
#define TEMP 1
#define HUM 2
LiquidCrystal_I2C lcd(0x27, 16, 2);
byte gradoChar[8] = {
  B00100,
  B01010,
  B00100,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte temperaturaChar[8] = {
  B00100,
  B01110,
  B01110,
  B01110,
  B01110,
  B11101,
  B11101,
  B01110
};
byte humedadChar[8] = {
  B00100,
  B00100,
  B01110,
  B01010,
  B10001,
  B10001,
  B01110,
  B00000
};
const int dataPin = 9;
float mensajeHumedad = 0.0;
float mensajeTemperatura = 0.0;
String datoCon = "";
void setup() {
  Serial.begin(9600);
  Serial.println("Modulo receptror");
  Serial.println("*** Humedad y Temperatura ****");
  delay(1500);
  vw_setup(2000);
  vw_set_rx_pin(dataPin);
  vw_rx_start();
}
void loop() {
  uint8_t receptor[VW_MAX_MESSAGE_LEN];
  uint8_t receptorLen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message((uint8_t *)receptor, &receptorLen)) {
    if ((char)receptor[0] == 'h') {
      for (int i = 1; i < receptorLen; i++) {
        datoCon.concat((char)receptor[i]);
      }

      mensajeHumedad = datoCon.toFloat();

      Serial.println("");
      Serial.println("Humedad:");
      Serial.print(mensajeHumedad);
      Serial.print(" %");
      Serial.println();
    } else if ((char)receptor[0] == 't') {
      for (int i = 1; i < receptorLen; i++) {
        datoCon.concat((char)receptor[i]);
      }
      mensajeTemperatura = datoCon.toFloat();
      Serial.println("");
      Serial.println("Temperatura: ");
      Serial.print(mensajeTemperatura);
      Serial.print(" C");
      Serial.println();
    }
    datoCon = "";
  }
}