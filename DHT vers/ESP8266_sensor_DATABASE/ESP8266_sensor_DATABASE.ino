#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2
int relay = A1;

OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

char server[] = "192.168.123.100";

const char* ssid     = "Carrot"; // Your ssid
const char* password = "jussayur"; // Your Password


void setup() {
  
sensors.begin();
pinMode(relay, OUTPUT);
  Serial.begin(115200);
  delay(10);
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
  
  dht.begin();
}
void loop() {

  delay(2000);

  sensors.requestTemperatures(); // Send the command to get temperatures

  
  float a = sensors.getTempCByIndex(0) ;

   Serial.print("\n Temperature is: ");
   Serial.print(a);
  
  if (isnan(a)){
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

// Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;

  if (client.connect(server, httpPort)){

    String data1 = "value1=" + (String)a;
    String url = "GET /Insert_data.php?" + data1 + data2 + " HTTP/1.1";
    client.println(url);
    client.println("Host: 192.168.123.100");
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
