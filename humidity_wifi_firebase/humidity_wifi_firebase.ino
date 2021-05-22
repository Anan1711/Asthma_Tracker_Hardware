/* Sending Sensor Data to Firebase Database by CircuitDigest(www.circuitdigest.com) */
#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>                                             // firebase library
#include <DHT.h>                                                            // dht11 temperature and humidity sensor library

#define FIREBASE_HOST "asthma-tracker-fa7ac.firebaseio.com"
#define FIREBASE_AUTH "ktQCiMyQdICFbhhCnOni1delSI3MaT2Fg20NwreA"
#define WIFI_SSID "SAFAYAT"
#define WIFI_PASSWORD "anan_7272#"                                 //password of wifi ssid
 
#define DHTPIN D4                                                           // what digital pin we're connected to
#define DHTTYPE DHT11                                                       // select dht type as DHT 11 or DHT22
DHT dht(DHTPIN, DHTTYPE); 

FirebaseData firebaseData;
                                                 

void setup() {
  Serial.begin(9600);
  delay(1000);                
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
  dht.begin();                                                               //Start reading dht sensor
}

void loop() { 
  float h = dht.readHumidity();                                              // Reading temperature or humidity takes about 250 milliseconds!
  float t = dht.readTemperature();                                           // Read temperature as Celsius (the default)
    
  if (isnan(h) || isnan(t)) {                                                // Check if any reads failed and exit early (to try again).
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  
  Serial.print("Humidity: ");  Serial.print(h);
  String fireHumid = String(h) + String("%");                                         //convert integer humidity to string humidity 
  Serial.print("  Temperature: ");  Serial.print(t);  Serial.println("°C ");
  String fireTemp = String(t) + String("°C");                                                     //convert integer temperature to string temperature
  delay(1800);
  
  Firebase.setString(firebaseData,"Humidity", fireHumid);                                  //setup path and send readings
  Firebase.setString(firebaseData,"roomtemp", fireTemp);                                //setup path and send readings
   
}
