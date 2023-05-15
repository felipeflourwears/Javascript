#include <ESP8266WiFi.h> // Libreria del microcontrolador
//http://70.37.95.128/BD_Sensor/index1.php?temp=20&hum=25.4 >>Enviar datos a través de php
// Datos de conexión
const char* ssid     = "HITRON-2D80";  // Nombre de la red WiFi
const char* password = "58DCQ73KF9";   // Contraseña
const char* host = "70.37.95.128";  // Dirección IP de nuestro servidor
const int   port = 80;            // Puerto
const int   watchdog = 8000;        // Frecuencia du watchdog,
//cuanto tiempo va a esperar para reintentar la conexión cuando hay un error
unsigned long previousMillis = millis(); 
 //Entradas de entrada y respuesta/disparo ultrasonico
#include <Ultrasonic.h>
#define PIN_TRIG D5
#define PIN_ECHO D6

//Definir entradas de los 2 RGB's
#define LED_GREEN     16 // D0
#define LED_RED   05 // D1
#define LED_BLUE    04 // D2
#define LED2_GREEN 13 // D7
#define LED2_RED 15 // D8
#define LED2_BLUE 2 // D4

//Uso de entradas del ultrasonico
Ultrasonic ultradis(D5,D6);
int distancia;
#include "DHT.h"        // Se incluye la libreria del sensor DHT11
#define DHTTYPE DHT11   // Variable que va implementar la libreria DHT.h
#define dht_dpin 0      // Pin en donde se conecta el DHT11
DHT dht(dht_dpin, DHTTYPE); 
void setup(void)
{ 
  WiFi.begin(ssid, password); // Conectate a la red
  while (WiFi.status() != WL_CONNECTED) { // Si la conexión es correcta seguimos
    delay(500);
    Serial.print("."); 
  }

  Serial.println("");
  Serial.println("WiFi connected"); // Imprime que ya se conecto al WiFi 
  Serial.println("IP address: "); // Imprime la IP que nos asignó el router en esa conexión
  Serial.println(WiFi.localIP());
  
  dht.begin(); // Se inicializa la libreria DHT
  Serial.begin(9600); // Se inicializa la consola serial
  Serial.println("Humedad y Temperatura\n\n"); // Se muestra el texto "Humedad y Temperatura"
  delay(700);
 //Salidas
 //LED RGB 1
 pinMode(LED_GREEN,OUTPUT);
 pinMode(LED_RED,OUTPUT);
 pinMode(LED_BLUE,OUTPUT);
 //LED RGB 2
 pinMode(LED2_RED,OUTPUT);
 pinMode(LED2_GREEN,OUTPUT);
 pinMode(LED2_BLUE,OUTPUT);

}

//Función del ultrasonico
void MideDistancia(){
  distancia = 0;
  for (int i=0; i <=10; i++){
      distancia=distancia + ultradis.distanceRead();
  }
  distancia = distancia/10; //promedio de lecturas sensor
//Mostrar valores en el monitor serial
  Serial.print("Sensor Ultrasonico: ");
  Serial.print(distancia); 
  Serial.println(" cm " );
  delay (1000);
}
void loop() {
      MideDistancia();
      float h = dht.readHumidity(); // Define una variable llamada h y lee humedad
      float t = dht.readTemperature();  // Define un avariable llamada t y lee temperatura      
      Serial.print("Humedad = ");
      Serial.print(h); // Imprime el valor leido
      Serial.print("%  ");
      Serial.print("Temperatura = ");
      Serial.print(t); // Imprime el valor leido
      Serial.println("°C  ");

//De acuerdo al ultrasonico empieza a guardar datos cuando haya un bebé
if (distancia>0 & distancia<5)
{
  analogWrite(LED_GREEN,255); //ROJO
  analogWrite(LED_RED,0); //VERDE
  analogWrite(LED_BLUE,0); // AZUL
  delay(100);
    unsigned long currentMillis = millis();

 // Es para el watchdog, si no responde que vaya cambiando
  if ( currentMillis - previousMillis > watchdog ) {
    previousMillis = currentMillis;
    WiFiClient client;
  
    if (!client.connect(host, port)) { // Te conectas al servidor, pasas el host y el puerto
      Serial.println("Fallo al conectar");
      return;
    }
    /////////////////
    else
    {

      if(t>10& t<25)
      {
        analogWrite(LED2_RED,0); //ROJO
        analogWrite(LED2_GREEN,255); //VERDE
        analogWrite(LED2_BLUE,0); // AZUL
      }
      else if(t>25 & t<35)
      {
        analogWrite(LED2_RED,255); //ROJO
        analogWrite(LED2_GREEN,0); //VERDE
        analogWrite(LED2_BLUE,0); // AZUL
      }
    }
    // Construye la URL con los datos del sensor
    
