#ifdef ESP32
#error ESP32 does not work with SoftSerial, use HardwareSerial example instead
#endif


#include <SDS011.h>
#include <Arduino.h>
#include <string>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

using namespace std;
float p10, p25;
int error;
ESP8266WiFiMulti WiFiMulti;
SDS011 my_sds;

void setup() {
  my_sds.begin(5, 4); //RX, TXd
  Serial.begin(9600);
  Serial.println("Hello");
//  connect();
}

void loop() {
  error = my_sds.read(&p25, &p10);
  if (!error) {
    Serial.println("PM2.5: " + String(p25) + " (Between 0 and 35.4)");
    Serial.println("PM10:  " + String(p10) + " (Between 0 and 50)");
    Serial.println("=======================================");
//    httpRequest(p25,p10);
  }
  delay(100);
}
//void httpRequest(double pm25,double pm10) {
//  // wait for WiFi connection
//  if ((WiFiMulti.run() == WL_CONNECTED)) {
//
//    WiFiClient client;
//    HTTPClient http; //must be declared after WiFiClient for correct destruction order, because used by http.begin(client,...)
//
//    Serial.print("Connected!");
//
//    String urlTripleStore = "http://192.168.43.132/air-quality-control/DustSensor/sendDustTripleStore.php?pm25=";
////    String url="http://www.google.com/";
//    urlTripleStore+=pm25;
//    urlTripleStore+="&pm10=";
//    urlTripleStore+=pm10;
//    Serial.println(urlTripleStore);
//    http.begin(client, urlTripleStore);
//
//    String urlInflux= "http://192.168.43.132/air-quality-control/DustSensor/sendDustInflux.php?pm25=";
//    urlInflux+=pm25;
//    urlInflux+="&pm10=";
//    urlInflux+=pm10;
//    Serial.println(urlInflux);
//    http.begin(client, urlInflux);
//
//    
//  
//    Serial.print("[HTTP] GET...\n");
//    // start connection and send HTTP header
//    int httpCode = http.GET();
//    if (httpCode > 0) {
//      // HTTP header has been send and Server response header has been handled
//      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
//
//      // file found at server
//      if (httpCode == HTTP_CODE_OK) {
//
//        // get lenght of document (is -1 when Server sends no Content-Length header)
//        int len = http.getSize();
//
//        // create buffer for read
//        uint8_t buff[128] = { 0 };
//
//#if 0
//        // with API
//        Serial.println(http.getString());
//#else
//        // or "by hand"
//
//        // get tcp stream
//        WiFiClient * stream = &client;
//
//        // read all data from server
////        while (http.connected() && (len > 0 || len == -1)) {
////          // read up to 128 byte
////          int c = stream->readBytes(buff, std::min((size_t)len, sizeof(buff)));
////          Serial.printf("readBytes: %d\n", c);
////          if (!c) {
////            Serial.println("read timeout");
////          }
////
////          // write it to Serial
////          Serial.write(buff, c);
////
////          if (len > 0) {
////            len -= c;
////          }
////        }
//#endif
//
//        Serial.println();
//        Serial.print("[HTTP] connection closed or file end.\n");
//      }
//    } else {
//      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
//    }
//
//    http.end();
//  }
//  else 
//  {
//    Serial.printf("Not connected");
//  }
//
//  delay(5000);
//}
//void connect() {
//
//  Serial.println();
//  Serial.println();
//  Serial.println();
//
//  for (uint8_t t = 4; t > 0; t--) {
//    Serial.printf("[SETUP] WAIT %d...\n", t);
//    Serial.flush();
//    delay(1000);
//  }
//
//  WiFi.mode(WIFI_STA);
//  WiFiMulti.addAP("Ahmad'sPhone", "12345678");
//
//}
