#include "FirebaseArduino.h"
#include <CircularBuffer.h>
#include <MAX30100.h>
#include <MAX30100_BeatDetector.h>
#include <MAX30100_Filters.h>
#include <MAX30100_PulseOximeter.h>
#include <MAX30100_Registers.h>
#include <MAX30100_SpO2Calculator.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "ESP8266WebServer.h"
#include <Wire.h>
#define REPORTING_PERIOD_MS 2000  

#define FIREBASE_HOST "asthma-tracker-fa7ac.firebaseio.com"
#define FIREBASE_AUTH "ktQCiMyQdICFbhhCnOni1delSI3MaT2Fg20NwreA"
#define WIFI_SSID "SAFAYAT"
#define WIFI_PASSWORD "anan_7272#"

PulseOximeter pox;

uint32_t tsLastReport = 0;

void onBeatDetected()
{
    Serial.println("Beat!");
}

void setup()
{
    Serial.begin(115200);
    pinMode(2, OUTPUT);
    Serial.print("Initializing Pulse Oximeter..");
    pinMode(16, OUTPUT);
    if (!pox.begin())
    {
      Serial.println("FAILED");
      for(;;);
    }
    else
    {
      Serial.println("SUCCESS");
      digitalWrite(2, HIGH);   //Turn off in-built LED
    }
    // Connect to wifi.
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());

    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);


   if (Firebase.failed()) {
        Serial.print("setting /message failed:");
        Serial.println(Firebase.error());
    }

    pox.begin();
    pox.setOnBeatDetectedCallback(onBeatDetected);
    pox.setIRLedCurrent(MAX30100_LED_CURR_24MA);

}

void loop()
{
    pox.update();
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {

        float bpm = pox.getHeartRate();
        float spO2 = pox.getSpO2();
        String BPM = String(bpm) + String(" BPM");
        String SpO2 = String(spO2) + String("%");
    
        
        Serial.print("Heart rate:");
        Serial.print(bpm);
        Serial.print("bpm / SpO2:");
        Serial.print(spO2);
        Serial.println("%");                                          

        tsLastReport = millis();

        if (bpm != 0 && spO2 != 0) {
            Firebase.setString("HeartRate", BPM);
            Firebase.setString("SpO2", SpO2);
        }
    }
}
