//Comunicación wifi y ESP8266 como servidor web

//Control de un LED en puerto digital GPI02 del ESP12 desde un navegador web.

#include <ESP8266WiFi.h> // Archivo de cabecera del modumo wifi del ESP8266

const char* ssid = "HOME-14C2"; // Nombre de la red
const char* password = "AABFFC15EF2B3366"; //Pasword


WiFiServer server(80); //Crea un servidor que escucha las conexiones entrantes en el puerto especificado.

void setup() {
  Serial.begin(9600);
  delay(10);

  //Configuración  del GPIO2
  pinMode(2, OUTPUT);
  digitalWrite(2,LOW);
  pinMode(5, OUTPUT);
  digitalWrite(5,LOW);
  pinMode(4, OUTPUT);
  digitalWrite(4,LOW);
//analogWrite(2,255); //ROJO
//analogWrite(4,204); //VERDE
//analogWrite(5X,255); // AZUL
  Serial.println();
  Serial.println();
  Serial.print("Conectandose a red : ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password); //Conexión a la red
  
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");
  
  
  server.begin(); //Iniciamos el servidor
  Serial.println("Servidor Iniciado");


  Serial.println("Ingrese desde un navegador web usando la siguiente IP:");
  Serial.println(WiFi.localIP()); //Obtenemos la IP
}

void loop() {
  
  WiFiClient client = server.available();
  if (client) //Si hay un cliente presente
  { 
    Serial.println("Nuevo Cliente");
    
    //esperamos hasta que hayan datos disponibles
    while(!client.available()&&client.connected())
    {
    delay(1);
    }
    
    // Leemos la primera línea de la petición del cliente.
    String linea1 = client.readStringUntil('r');
    Serial.println(linea1);

    if (linea1.indexOf("LED1=ON")>0) //Red
    {
      digitalWrite(2,255);
      digitalWrite(5,0);
      digitalWrite(4,0);
    }
    if (linea1.indexOf("LED2=ON")>0)//Green
    {
      digitalWrite(2,0);
      digitalWrite(5,204);
      digitalWrite(4,0);
    }
    if (linea1.indexOf("LED3=ON")>0)//Blue
    {
      digitalWrite(2,0);
      digitalWrite(5,0);
      digitalWrite(4,255);
    }
    if (linea1.indexOf("LED4=ON")>0)//Magenta
    {
      digitalWrite(2,255);
      digitalWrite(5,255);
      digitalWrite(4,0);
    }
     if (linea1.indexOf("LED5=ON")>0)//PURPLE
    {
      digitalWrite(2,255);
      digitalWrite(5,0);
      digitalWrite(4,255);
    }
     if (linea1.indexOf("LED6=ON")>0)//Cyan
    {
      digitalWrite(2,0);
      digitalWrite(5,204);
      digitalWrite(4,255);
    }
    if (linea1.indexOf("LED=OFF")>0)//Buscamos un LED=OFF en la 1°Linea
    {
      digitalWrite(2,0);
      digitalWrite(5,0);
      digitalWrite(4,0);
    }
    
    client.flush(); 
                
    Serial.println("Enviando respuesta...");   
    //Encabesado http    
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");// La conexión se cierra después de finalizar de la respuesta
    client.println();
    //Pagina html  para en el navegador
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<head>");
    client.println("<meta charset='utf-8'>");
    client.println("<link rel='stylesheet' href='estilos.css'>");
    client.println("<title>RGB</title>");
    client.println("</head>");            
    client.println("<body bgcolor=#55DAB1>");           
    client.println("<h1 align='center'>Botones RGB</h1>");
    client.println("<div style='text-align:center;'>");
    client.println("<br />");
    client.println("<button style='border: 3px solid #000; border-radius: 50%;width: 100px;height: 100px; box-shadow: 2px 2px 2px #000;background: rgb(197, 8, 2);' onClick=location.href='./?LED1=ON'></button>");
    client.println("<button style='border: 3px solid #000; border-radius: 50%;width: 100px;height: 100px; box-shadow: 2px 2px 2px #000;background: rgb(14, 102, 3);' onClick=location.href='./?LED2=ON'></button>");
    client.println("<button style='border: 3px solid #000; border-radius: 50%;width: 100px;height: 100px; box-shadow: 2px 2px 2px #000;background: rgb(4, 48, 243);' onClick=location.href='./?LED3=ON'></button>");
    client.println("<br />");
    client.println("<br />");
    client.println("<button style='border: 3px solid #000; border-radius: 50%;width: 100px;height: 100px; box-shadow: 2px 2px 2px #000;background: rgb(176, 245, 16);' onClick=location.href='./?LED4=ON'></button>");
    client.println("<button style='border: 3px solid #000; border-radius: 50%;width: 100px;height: 100px; box-shadow: 2px 2px 2px #000;background: rgb(116, 5, 219);' onClick=location.href='./?LED5=ON'></button>");
    client.println("<button style='border: 3px solid #000; border-radius: 50%;width: 100px;height: 100px; box-shadow: 2px 2px 2px #000;background: rgb(5, 219, 208);' onClick=location.href='./?LED6=ON'></button>");
    client.println("<br />");
    client.println("<br />");
    client.println("<button style='border: 3px solid #000; border-radius: 20%;width: 100px;height: 100px; box-shadow: 2px 2px 2px #000;background: rgb(243, 241, 241);' onClick=location.href='./?LED=OFF'>LED OFF</button>");
    client.println("<br />");    
    client.println("</div>");
    client.println("</body>");
    client.println("</html>");
    
    delay(1);
    Serial.println("respuesta enviada");
    Serial.println();

  }
}
