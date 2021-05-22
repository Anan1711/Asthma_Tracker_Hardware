
#include <Wire.h>
#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
#include <Adafruit_MLX90614.h>

// Set these to run example.
#define FIREBASE_HOST "asthma-tracker-fa7ac.firebaseio.com"
#define FIREBASE_AUTH "ktQCiMyQdICFbhhCnOni1delSI3MaT2Fg20NwreA"
#define WIFI_SSID "SAFAYAT"
#define WIFI_PASSWORD "anan_7272#"

int a = 10;
int b = 5;
FirebaseData firebaseData;

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
void setup() {
  Serial.begin(9600);
  mlx.begin();
  pinMode(D2, INPUT);
  pinMode(D1, OUTPUT);

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
  float f = mlx.readAmbientTempF();
  String fahrenheit = String(f) + String("°F");
  Firebase.setString(firebaseData, "Temperature", fahrenheit);
  Serial.print("Patient's Temperature = "); Serial.print(f); Serial.println("*F");
  Serial.println();
  delay(2000);

}
