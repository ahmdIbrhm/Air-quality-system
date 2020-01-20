/* This code is to use with Adafruit BMP280           (Metric)
 * It measures both temperature and pressure and it displays them on the Serial monitor with the altitude
 * It's a modified version of the Adafruit example code
 * Refer to www.surtrtech.com or SurtrTech Youtube channel
 */


#include <Adafruit_BMP280.h>
#include <Arduino.h>
#include <string>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

using namespace std;
ESP8266WiFiMulti WiFiMulti;


const char* ssid = "Ahmad'sPhone";
const char* pass = "12345678";
Adafruit_BMP280 bmp; // I2C Interface

void setup() {
  Serial.begin(9600);
  Serial.println(F("BMP280 test"));
  connect();
  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    //while (1);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void loop() {
    Serial.print(F("Temperature = "));
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");

    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure()/100); //displaying the Pressure in hPa, you can change the unit
    Serial.println(" hPa");

    Serial.print(F("Approx altitude = "));
    Serial.print(bmp.readAltitude(1019.66)); //The "1019.66" is the pressure(hPa) at sea level in day in your region
    Serial.println(" m");                    //If you don't know it, modify it until you get your current altitude

    Serial.println();
//    sendToRelationalDB(bmp.readTemperature(),bmp.readAltitude(1019.66),bmp.readPressure()/100);
//    delay(1000);
//    sendToInfluxDB(bmp.readTemperature(),bmp.readAltitude(1019.66),bmp.readPressure()/100);
    delay(2000);
}


void connect() {

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, pass);

}

void sendToRelationalDB(double temp,double alt,double pressure) {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;
    HTTPClient http; //must be declared after WiFiClient for correct destruction order, because used by http.begin(client,...)

    Serial.print("[HTTP] begin...\n");

    // configure server and url
    String url = "http://haidarali.space/addToBmp.php?sensor_id=1&temp=";
    url = url + temp;
    
    url += "&alt=";
    url += alt;
    url += "&pressure=";
    url += pressure;
    Serial.println(url);
    http.begin(client, url);
  
    Serial.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {

        // get lenght of document (is -1 when Server sends no Content-Length header)
        int len = http.getSize();

        // create buffer for read
        uint8_t buff[128] = { 0 };

#if 0
        // with API
        Serial.println(http.getString());
#else
        // or "by hand"

        // get tcp stream
        WiFiClient * stream = &client;

        // read all data from server
        while (http.connected() && (len > 0 || len == -1)) {
          // read up to 128 byte
          int c = stream->readBytes(buff, std::min((size_t)len, sizeof(buff)));
          Serial.printf("readBytes: %d\n", c);
          if (!c) {
            Serial.println("read timeout");
          }

          // write it to Serial
          Serial.write(buff, c);

          if (len > 0) {
            len -= c;
          }
        }
#endif

        Serial.println();
        Serial.print("[HTTP] connection closed or file end.\n");
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }

  delay(10000);
}

void sendToInfluxDB(double temp,double alt,double pressure) {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;
    HTTPClient http; //must be declared after WiFiClient for correct destruction order, because used by http.begin(client,...)

    Serial.print("[HTTP] begin...\n");

    // configure server and url
    String url = "http://192.168.43.228/air-quality-control/bmp280/sendBMPInflux.php?sensor_id=1&temp=";
    url = url + temp;
    
    url += "&alt=";
    url += alt;
    url += "&pressure=";
    url += pressure;
    Serial.println(url);
    http.begin(client, url);
  
    Serial.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {

        // get lenght of document (is -1 when Server sends no Content-Length header)
        int len = http.getSize();

        // create buffer for read
        uint8_t buff[128] = { 0 };

#if 0
        // with API
        Serial.println(http.getString());
#else
        // or "by hand"

        // get tcp stream
        WiFiClient * stream = &client;

        // read all data from server
        while (http.connected() && (len > 0 || len == -1)) {
          // read up to 128 byte
          int c = stream->readBytes(buff, std::min((size_t)len, sizeof(buff)));
          Serial.printf("readBytes: %d\n", c);
          if (!c) {
            Serial.println("read timeout");
          }

          // write it to Serial
          Serial.write(buff, c);

          if (len > 0) {
            len -= c;
          }
        }
#endif

        Serial.println();
        Serial.print("[HTTP] connection closed or file end.\n");
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }

  //delay(10000);
}
