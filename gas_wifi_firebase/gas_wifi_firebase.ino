#include <FirebaseESP8266.h>  // Install Firebase ESP8266 library
#include <ESP8266WiFi.h>
int gas = A0;

#define FIREBASE_HOST "asthma-tracker-fa7ac.firebaseio.com"
#define FIREBASE_AUTH "ktQCiMyQdICFbhhCnOni1delSI3MaT2Fg20NwreA"
#define WIFI_SSID "SAFAYAT"
#define WIFI_PASSWORD "anan_7272#"     

FirebaseData firebaseData;
void setup() {
  pinMode(gas, INPUT);
  Serial.begin(9600);

 WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                            //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                              // connect to firebase

}


void loop() {
 
  int analogSensor = analogRead(gas);
  String airquality = String(analogSensor) + String(" PPM");
  Firebase.setString(firebaseData, "Air Quality",airquality);
  Serial.print("Air Quality: "); 
  Serial.print(analogSensor);
  Serial.println(" PPM");
  
  delay(4000);
}
