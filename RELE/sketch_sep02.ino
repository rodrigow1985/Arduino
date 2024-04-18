#include <ESP8266WiFi.h>

const char* ssid = "Linksys";
const char* password = "rodri1985";

//int PIN_RELE = 1;
boolean rele_status = false;

WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  delay(10);

  //Configuración  del GPIO2
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);

  // RELE
  pinMode(D1, OUTPUT);
  
  Serial.println();
  Serial.println();
  Serial.print("Conectandose a red : ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password); //Conexión a la red
  
  while (WiFi.status() != WL_CONNECTED) {
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
  if (client) { //Si hay un cliente presente
    Serial.println("Nuevo Cliente");
    
    //esperamos hasta que hayan datos disponibles
    while(!client.available()&&client.connected()) {
      delay(1);
    }
    
    // Leemos la primera línea de la petición del cliente.
    String linea1 = client.readStringUntil('r');
    Serial.println(linea1);

    if (linea1.indexOf("LED=ON")>0) { //Buscamos un LED=ON en la 1°Linea
      digitalWrite(2, HIGH);
    }
    if (linea1.indexOf("LED=OFF")>0) { //Buscamos un LED=OFF en la 1°Linea
      digitalWrite(2, LOW);
    }
    
    if (linea1.indexOf("RELE=ON")>0) { //Buscamos un LED=ON en la 1°Linea
      digitalWrite(D1, HIGH);
      rele_status = true;
      //encenderApagarRele(1, true);
    }
    if (linea1.indexOf("RELE=OFF")>0) { //Buscamos un LED=OFF en la 1°Linea
      digitalWrite(D1, LOW);
      rele_status = false;
      //encenderApagarRele(1, false);
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
    client.println("<head><title>Smart House</title>");
    client.println("<body>");
    client.println("<h1 align='center'>Test ESP8266</h1>");
    // LED buttons
    client.println("<div style='text-align:center;'>");
    client.println("<br />");            
    client.println("<button onClick=location.href='./?LED=ON'>LED ON</button>");           
    client.println("<button onClick=location.href='./?LED=OFF'>LED OFF</button>");
    client.println("<br />");
    client.println("</div>");
    // RELE buttons
    client.println("<div style='text-align:center;'>");
    client.println("<br />");            
    client.println("<button onClick=location.href='./?RELE=ON'>RELE ON</button>");           
    client.println("<button onClick=location.href='./?RELE=OFF'>RELE OFF</button>");
    client.println("<br />");
    client.println("<label>RELE: ");
    client.println(rele_status);
    client.println("</label>");
    client.println("</div>");
    
    client.println("</body>");
    client.println("</html>");
    
    delay(1);
    Serial.println("respuesta enviada");
    Serial.println();

  }
}

void encenderApagarRele(int PIN, boolean VALOR) {
  if(VALOR) {
    digitalWrite(PIN, HIGH);
    rele_status=true;
    Serial.println("Se encendió el Relé");
  } else {
    digitalWrite(PIN, LOW);
    rele_status=false;
    Serial.println("Se apagó el Relé");
  }
}
