#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Servo.h>
Servo myservoLeft;
Servo myservoRight;

#define FIREBASE_HOST "whiteboard-21f79.firebaseio.com"
#define FIREBASE_AUTH "7bIW9m9lfu8VQHoUn2zz7mMAHrRLJeymjrvWZ9PK"
#define WIFI_SSID "NODEMCU"
#define WIFI_PASSWORD "12345678"

int gridMap[16][2] = {
  {1, 4},
  {2, 4},
  {3, 4},
  {4, 4},
  {1, 3},
  {2, 3},
  {3, 3},
  {4, 3},
  {1, 2},
  {2, 2},
  {3, 2},
  {4, 2},
  {1, 1},
  {2, 1},
  {3, 1},
  {4, 1}
};

void setup() {
  
  myservoRight.attach(14);
  myservoLeft.attach(12);  
  Serial.begin(9600);
  
  Stop();
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

void Forwardn(int n){
  int i;
  for (i = 0; i < n; i++){
    
    myservoRight.write(75.5);//0 - 95
    myservoLeft.write(135);//180?  - 93
    delay(30);
    myservoRight.write(66.5);
    delay(1640);
  }
}

void uTurn(){
    myservoRight.write(130);//0 - 95
    myservoLeft.write(130);//180?  - 93
    delay(2020);
    myservoLeft.write(57.5);//180?  - 93
    myservoRight.write(130);
    delay(810);
}

void RightTurn(){
    myservoLeft.write(57.5);//180?  - 93
    myservoRight.write(130);
    delay(200);
    myservoRight.write(95.5);//0 - 95
    myservoLeft.write(130);//180?  - 93
    delay(2035);
    myservoLeft.write(57.5);//180?  - 93
    myservoRight.write(130);
    delay(1000);
}

void LeftTurn(){
    myservoLeft.write(57.5);//180?  - 93
    myservoRight.write(130);
    delay(200);
    myservoRight.write(55.5);//0 - 95
    myservoLeft.write(93);//180?  - 93
    delay(1950);
    myservoLeft.write(57.5);//180?  - 93
    myservoRight.write(130);
    delay(1000);
}

void Stop(){
    myservoRight.write(95.5);//0 - 95
    myservoLeft.write(93);//180?  - 93
}

void MoveGrid(int x, int y){
  Forwardn(y);
  delay(50);
  if(x>1){
    RightTurn();
    delay(50);
    Forwardn(x-1);
    delay(50);
  }
  uTurn();
  Stop();
  delay(3000);
  if(x>1){
    Forwardn(x-1);
    delay(50);
    LeftTurn();
    delay(50);
  }
  Forwardn(y);
  delay(50);
}

void loop() {
  if(Firebase.getString("droneSec/robot/coor") != "NONE") {
    int hold = Firebase.getString("droneSec/robot/coor").toInt();
    MoveGrid(gridMap[hold - 1][0],gridMap[hold - 1][1]);
    Firebase.setString("droneSec/robot/coor", "NONE");
  } else {
    Stop();
  }
}
