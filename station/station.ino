
/* This code is to use with Adafruit BMP280           (Metric)
 * It measures both temperature and pressure and it displays them on the Serial monitor with the altitude
 * It's a modified version of the Adafruit example code
 * Refer to www.surtrtech.com or SurtrTech Youtube channel
 */


#include <Arduino.h>
#include <string>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <MQTT.h>
#include <ESP8266HTTPClient.h>

#include <SDS011.h>

using namespace std;
ESP8266WiFiMulti WiFiMulti;
MQTTClient mqtt_client ;
WiFiClient wifi_client ;
int error;
SDS011 my_sds;

float p10, p25;

// wifi configuration .. 
const char* ssid = "Ahmad'sPhone";
const char* pass = "12345678";
int status = WL_IDLE_STATUS; 
String ID = "123456" ;

// mqtt configuration 
const char* mqtt_host = "test.mosquitto.org" ;
const char* mqtt_user     = "majinfo2019";
const char* mqtt_password = "Y@_oK2";
const uint16_t mqtt_port =  1883;


// API credentials.. 

const char host[] = "territoire.emse.fr";
const int httpsPort = 443;

// Use web browser to view and copy
// SHA1 fingerprint of the certificate
const char fingerprint[] PROGMEM = "1A AC 5B 42 7C F6 4E 4B F1 E3 5B 7C 62 D8 C2 71 36 BC 64 6D";
boolean startSending = false;
void setup() {
  Serial.begin(9600);
  Serial.println(F("Initilializing... !"));
  


  connect();
  my_sds.begin(5, 4);
}

void loop() {

   if (!mqtt_client.connected()) {
      connect();
   }
   mqtt_client.loop();
   //read dust data ....
   error = my_sds.read(&p25, &p10);
   if (!error) 
   {
     Serial.println("PM2.5: " + String(p25) + " (Between 0 and 35.4)");
     Serial.println("PM10:  " + String(p10) + " (Between 0 and 50)");
     Serial.println("=======================================");
     
     //uncomment this call to start pushing... need to check condition if the arduino is deployed by mobile app...
     if(startSending)
        sendHttpPost(String(p10),String(p25));
     else
      {
        String mac=generateMac();
//        String mac="553087f2-36d8-11ea-aec2-2e728ce88222";/
        mqtt_client.publish("test_uid", mac);
        mqtt_client.subscribe(mac);
        Serial.println("Can't send yet!");
        delay(5000);
      }
   }
   delay(5000);
}
byte mac[6];  
String generateMac(){
  String mac_address = "";
  if(WiFi.status() == WL_CONNECTED){
    WiFi.macAddress(mac);
    
    mac_address+=String(mac[5],HEX);
    mac_address+=":";
    mac_address+=String(mac[4],HEX);
    mac_address+=":";
    mac_address+=String(mac[3],HEX);
    mac_address+=":";
    mac_address+=String(mac[2],HEX);
    mac_address+=":";
    mac_address+=String(mac[1],HEX);
    mac_address+=":";
    mac_address+=String(mac[0],HEX);
  }else{
    Serial.println("not connected to WIFI");
  }
  return mac_address;
}
void sendHttpPost(String pm10,String pm25)
{
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
   
      WiFiClientSecure client;
      Serial.print("connecting to ");
      Serial.println(host);
  
  //  Serial.printf("Using fingerprint '%s'\n", fingerprint);
  //  client.setFingerprint(fingerprint);
    client.setInsecure();   //solves the finger print issue .. 
    
    String msg = "{\"data\":{\"station_id\":\""+generateMac()+"\",\"temperature\":0,\"pressure\":0,\"pm10\":"+pm10+",\"pm25\":"+pm25+"}}";
    String url = "/applications/air-quality-control/station-info";
    Serial.print("requesting URL: ");
    Serial.println(url);
    Serial.print("payload: ");
    Serial.println(msg);
  
  
    if(client.connect(host, httpsPort)){
   
     
      client.println("POST /applications/air-quality-control/sensor-value HTTP/1.1");
    client.println("Host: territoire.emse.fr");                          
     client.println("Connection: close");
     client.println("Content-Type: application/json");
     client.println("Content-Length: "+String(msg.length())+"\r\n");
     client.print(msg);             
     
     Serial.println("request sent");
     // print result. ...
     
     /* while (client.connected()) {
           String line = client.readStringUntil('\r');
            Serial.print(line);
        }*/
        
    }else{
      Serial.println("Cannot connect to server...");
    }
                
  }
}

void connect() {

    Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  
  mqtt_client.begin(mqtt_host, mqtt_port, wifi_client) ;
  mqtt_client.onMessage(callback) ;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  while ( !mqtt_client.connect(ID.c_str()) ) {
    digitalWrite(LED_BUILTIN, HIGH) ;
    delay(500);
    digitalWrite(LED_BUILTIN, LOW) ;
    Serial.print("-");
    delay(500);
  }
  Serial.println("MQTT: connected") ;
  String clientId = "ESP8266Client-";
  clientId += String(random(0xffff), HEX);

}
void callback(String &intopic, String &payload)
{
  startSending=true;
  Serial.println("incoming: " + intopic + " - " + payload);
}
