#include <ESP8266WiFi.h>

const char* ssid     = "satish"; // Your ssid

const char* password = "satish123"; // Your Password

float temp_celsius = 0;

float temp_fahrenheit = 0;

WiFiServer server(80);

void setup() {

 Serial.begin(115200);

  pinMode(A0, INPUT);   

Serial.println();

Serial.println();

Serial.print("Connecting to ");

Serial.println(ssid);

WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED) {

delay(500);

Serial.print(".");

}

Serial.println("");

Serial.println("WiFi is connected");

server.begin();

Serial.println("Server started");

Serial.println(WiFi.localIP());

}

void loop() {

temp_celsius = (analogRead(A0) * 330.0) / 1023.0;   1023 = celsius

temp_fahrenheit = celsius * 1.8 + 32.0;

Serial.print("  Temperature = ");

Serial.print(temp_celsius);

Serial.print(" Celsius, ");

Serial.print(temp_fahrenheit);

Serial.println(" Fahrenheit");


WiFiClient client = server.available();

client.println("HTTP/1.1 200 OK");

client.println("Content-Type: text/html");

client.println("Connection: close"); 

client.println("Refresh: 10");  

client.println();

client.println("<!DOCTYPE HTML>");

client.println("<html>");

client.print("<p style='text-align: center;'><span style='font-size: x-large;'><strong>Digital Thermometer</strong></span></p>");

client.print("<p style='text-align: center;'><span style='color: #0000ff;'><strong style='font-size: large;'>Temperature (*C)= ");

client.println(temp_celsius);

client.print("<p style='text-align: center;'><span style='color: #0000ff;'><strong style='font-size: large;'>Temperature (F) = ");

client.println(temp_fahrenheit);

client.print("</p>");

client.println("</html>");

delay(5000);

}

