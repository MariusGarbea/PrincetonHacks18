#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "whiteboard-21f79.firebaseio.com"
#define FIREBASE_AUTH "7bIW9m9lfu8VQHoUn2zz7mMAHrRLJeymjrvWZ9PK"
#define WIFI_SSID "NODEMCU"
#define WIFI_PASSWORD "12345678"


SoftwareSerial mySerial(12, 14);
String holdS = "";
boolean checkVal = false;

void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  while(mySerial.available()) {
    char holdC = mySerial.read();
    holdS.concat(holdC);
    if(holdS.length() == 2) {
      holdS.replace("\n","");
      if(holdS.length() == 2) {
        String holdArray = "0000000000000000";
        Serial.println(holdS);
        holdArray.setCharAt(holdS.toInt() - 20, '1');
        Serial.println(holdArray);
        Firebase.setString("droneSec/data/value", holdArray);
        checkVal = true;
      }
      holdS = "";
    }
  }
  
  if(Firebase.getString("droneSec/data/value") == "0000000000000000" && checkVal == true) {
    mySerial.print("Z");
    checkVal = false;
  }
}
