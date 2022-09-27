•	/*Práctica de OLED DHT22 Y Reloj
•	Observación: por falta de material se usa un LCD*/
•	// Importar librerias
•	#include <LiquidCrystal_I2C.h>
•	// #include <U8glib.h>
•	#include <RTClib.h>
•	#include <DHT.h>
•	#include <DHT_U.h>
•	LiquidCrystal_I2C lcd(0x27, 16, 2);  // Crear lcd
•	// Configurar el dht
•	#define DHTPIN 2
•	#define DHTTYPE DHT22
•	DHT dht(DHTPIN, DHTTYPE);  // Crear el dht
•	RTC_DS1307 rtc;  // Crear rtc
•	void setup() {
•	  rtc.begin();  // Inicialización del rtc
•	  dht.begin();  // Inicialización del dht
•	  lcd.init();   // Inicialización del lcd
•	  lcd.backlight();  // Encender lcd
•	  lcd.print("Bienvenido");
•	  delay(1500);
•	}
•	void loop() {
•	  sensores();  // Ejecutar simulación de las pantallas
•	}
•	void sensores() {
•	  DateTime now = rtc.now();
•	  //DateTime fecha = rtc.now();                 // Obtener fecha actual
•	  float humedad = dht.readHumidity();         // Obtener humedad
•	  float temperatura = dht.readTemperature();  // Obtener temperatura
•	  // Mostrar pantalla con información de la hora
•	  lcd.clear();
•	  lcd.print("* Hora *");
•	  lcd.setCursor(0, 1);
•	  imprimirDigito(now.hour());
•	  lcd.print(":");
•	  imprimirDigito(now.minute());
•	  lcd.print(":");
•	  imprimirDigito(now.second());
•	  delay(1500);
•	  // Mostrar pantalla con informacióN
•	  lcd.clear();
•	  lcd.print("* Fecha *");
•	  lcd.setCursor(0, 1);
•	  imprimirDigito(now.day());
•	  lcd.print("/");
•	  imprimirDigito(now.month());
•	  lcd.print("/");
•	  imprimirDigito(now.year());
•	  delay(1500);
•	  // Mostrar pantalla con información 
•	  lcd.clear();
•	  lcd.print("* Temperatura *");
•	  lcd.setCursor(0, 1);
•	  lcd.print("Temp:");
•	  lcd.print(temperatura);
•	  lcd.print("C");
•	  delay(1500);
•	  // Mostrar pantalla con información de la humedad
•	  lcd.clear();
•	  lcd.print("* Humedad *");
•	  lcd.setCursor(0, 1);
•	  lcd.print("Hum:");
•	  lcd.print(humedad);
•	  lcd.print("%");
•	  delay(1500);
•	  segundero(now.second());
•	}
•	void imprimirDigito(int num) {
•	  // Imprimir valor en formato de dos digitos (00)
•	  if (num < 10) {
•	    // oled.print("0");
•	    lcd.print("0");
•	  }
•	  // oled.print(num, DEC);
•	  lcd.print(num);
•	}
•	void segundero(int segundo) {
•	  float cuadrante = ((float)128 / 59) - 0.01;
•	  float operacion = cuadrante + segundo;•	}
