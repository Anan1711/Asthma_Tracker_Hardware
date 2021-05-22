#include <Wire.h>
#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>

// Set these to run example.
#define FIREBASE_HOST "asthma-tracker-fa7ac.firebaseio.com"
#define FIREBASE_AUTH "ktQCiMyQdICFbhhCnOni1delSI3MaT2Fg20NwreA"
#define WIFI_SSID "SAFAYAT"
#define WIFI_PASSWORD "anan_7272#"

FirebaseData firebaseData;


void setup() 
{
// initialize the serial communication:
Serial.begin(9600);
pinMode(14, INPUT); // Setup for leads off detection LO +
pinMode(12, INPUT); // Setup for leads off detection LO -

  // connect to wifi.
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
  Firebase.reconnectWiFi(true);
 
}
 
void loop() {
 
if((digitalRead(10) == 1)||(digitalRead(11) == 1)){
Serial.println('!');
}
else{
// send the value of analog input 0:
Serial.print("ECG value : ");
Serial.println(analogRead(A0));
String ecg = String(analogRead(A0));
Firebase.setString(firebaseData, "ECG", ecg);
}
//Wait for a bit to keep serial data from saturating
delay(10);
}
