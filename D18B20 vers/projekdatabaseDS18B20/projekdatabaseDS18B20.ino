#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into pin D1 on the ESP8266 12-E - GPIO 5 - D1
#define ONE_WIRE_BUS 5

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature DS18B20(&oneWire);
char temperatureCString[7];
char temperatureFString[7];
float tempC;
float tempF;

char server[] = "192.168.0.100";
// Web Server on port 80
//WiFiServer server(80);

const char* ssid     = "hotspot-ntc"; // Your ssid
const char* password = "32213221"; // Your Password


void setup() {
  Serial.begin(115200);
  delay(10);

// IC Default 9 bit. If you have troubles consider upping it 12. 
// Ups the delay giving the IC more time to process the temperature measurement
  DS18B20.begin(); 

  // We start by connecting to a WiFi network

  //Serial.println();
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  

}

//void getTemperature() {
//  float tempC;
//  float tempF;
//  do {
//    DS18B20.requestTemperatures(); 
//    tempC = DS18B20.getTempCByIndex(0);
//    dtostrf(tempC, 2, 2, temperatureCString);
//    tempF = DS18B20.getTempFByIndex(0);
//    dtostrf(tempF, 3, 2, temperatureFString);
//    delay(100);
//  } while (tempC == 85.0 || tempC == (-127.0));
//}


void loop() {
  tempC = DS18B20.getTempCByIndex(0);
  tempF = DS18B20.getTempFByIndex(0);
  Serial.print("Temperature *C: ");
  Serial.print(tempC);
  Serial.print("*C");
  Serial.println();
  Serial.print("Temperature *F: ");
  Serial.print(tempF);
  Serial.print( "*F");
  Serial.println();
  
  if (isnan(tempC)){
    Serial.println("Failed to read from DS18B20 sensor!");
    return;
  }

// Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;

  if (client.connect(server, httpPort)){

    String data1 = "value1=" + (String)tempC;
    String data2 = "&value2=" + (String)tempF;
    String url = "GET /latihan_joshua/insert_waterheater.php?" + data1 + data2 + " HTTP/1.1";
    client.println(url);
    client.println("Host: 192.168.0.100");
    client.println("Connection: close");
    client.println();
    client.println();
    client.stop();
  }
  else{
    Serial.println("--> connection failed\n");
  }
  
  //ESP.deepSleep(60U*60*1000000); //U for unsigned
  delay(1000); //for above sleep
}
