/*
  Button

 Turns on and off a light emitting diode(LED) connected to digital
 pin 13, when pressing a pushbutton attached to pin 2.


 The circuit:
 * LED attached from pin 13 to ground
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground

 * Note: on most Arduinos there is already an LED on the board
 attached to pin 13.


 created 2005
 by DojoDave <http://www.0j0.org>
 modified 30 Aug 2011
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Button
 */

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>

//const char* ssid = "shapeways-guest";
//const char* password = "sh@p3way5!";

const char* ssid = "shapeways-staff";
const char* password = "j@R04f1i35!";

// constants won't change. They're used here to
// set pin numbers:
const int tiltPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int tiltState;            // current reading from tilt sensor
int lastTiltState = LOW;   // last reading from tilt sensor

// the following variables are unsigned long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 200;    // the debounce time; increase if the output flickers
int wasPushed = 0;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(tiltPin, INPUT);

  Serial.begin(115200);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  Serial.println(password);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // read the state of the tilt sensor
  tiltState = digitalRead(tiltPin);  

  if (tiltState != lastTiltState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) 
  {
    if (tiltState == HIGH) {
      if (wasPushed == 0) 
      {
        // turn LED on, play music:
        HTTPClient http;
        digitalWrite(ledPin, HIGH);
        http.begin("http://10.1.6.151:5000/play"); //HTTP
    
        Serial.println("Play that funky music\n");
        // start connection and send HTTP header
        int httpCode = http.GET();
      }
      wasPushed = 1;
    } 
    else 
    {
      // turn LED off:
      digitalWrite(ledPin, LOW);
      if (wasPushed == 1) 
      {
        Serial.println("Enjoy your coffee.\n");
        wasPushed = 0;
      }
      
      
    }
  }
  
  lastTiltState = tiltState;
}
