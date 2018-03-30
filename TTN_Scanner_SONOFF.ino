/*
    This sketch demonstrates how to scan WiFi networks.
    The API is almost the same as with the WiFi Shield library,
    the most obvious difference being the different file you need to include:
*/
#define my_SSID  "PUT YOUR SSID HERE"
#define my_TTN   "PUT YOUR THINGS GATEWAY SSID HERE"
#include "ESP8266WiFi.h"
#define LED_PIN_GRN 13
#define LED_PIN_RELAY 12
#define LED_PIN_BUTTON 15
#define maxCount 5
#define stepDelay 300
#define my_SSID  "ASUS_TECH"

int x;
int status_count;
int rssi;
bool found;
bool reboot;
void setup() {
  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  pinMode(LED_PIN_GRN,    OUTPUT);
  pinMode(LED_PIN_RELAY,  OUTPUT);
  pinMode(LED_PIN_BUTTON, INPUT);
  digitalWrite(LED_PIN_GRN, HIGH);
  digitalWrite(LED_PIN_RELAY, LOW);
  found = false;
  status_count = 0;
  Serial.println("Setup done - power is OFF");
  Serial.print("Searching for ");
  Serial.println(my_SSID);
}

void loop() {

  while (digitalRead(LED_PIN_BUTTON) == HIGH) {
    digitalWrite(LED_PIN_GRN,   HIGH);    
    digitalWrite(LED_PIN_RELAY, LOW);
    status_count = 0;
  };
      
  //  Serial.println("scan start");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  //  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    //    Serial.println(" ");
    //    Serial.print(n);
    //    Serial.println(" networks found");

    found  = false;
    reboot = false;
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      //      Serial.print(i + 1);
      //      Serial.print(": ");
      //      Serial.print(WiFi.SSID(i));
      //      Serial.print(" (");
      //      Serial.print(WiFi.RSSI(i));
      //      Serial.println(")");
      //      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
      if (WiFi.SSID(i) == my_SSID) {
        rssi = WiFi.RSSI(i);
        found = true;
      };
      if (WiFi.SSID(i) == my_TTN) {
        rssi = WiFi.RSSI(i);
        reboot = true;
      };
      
      delay(10);
    };

    if (reboot == true) {
      reboot = false;
      found  = false;
      digitalWrite(LED_PIN_GRN, HIGH);
      digitalWrite(LED_PIN_RELAY, LOW);
      Serial.print("\"");
      Serial.print(my_TTN);
      Serial.print("\"(");
      Serial.print(rssi);
      Serial.print(")");
      Serial.println(" has been found - power turned off - Will re-start again soon");
    }else{   

      if (found == true) {
        reboot = false;
        found  = false;
        if (status_count == maxCount) {
          Serial.print("\"");
          Serial.print(my_SSID);
          Serial.print("\"(");
          Serial.print(rssi);
          Serial.print(")");
          Serial.print(" still available - power stays ON   - \"alive\" counter stays at ");
          Serial.println(status_count);
        } else {
          status_count = maxCount;
          if (digitalRead(LED_PIN_RELAY) == HIGH) {
            Serial.print("\"");
            Serial.print(my_SSID);
            Serial.print("\"(");
            Serial.print(rssi);
            Serial.print(")");
            Serial.print(" rediscovered    - power stays ON   - \"alive\" counter reset to ");
            Serial.println(status_count);
            digitalWrite(LED_PIN_RELAY, HIGH);
          } else {
            Serial.print("\"");
            Serial.print(my_SSID);
            Serial.print("\"(");
            Serial.print(rssi);
            Serial.print(")");
            Serial.print(" found           - power turned ON  - \"alive\" counter set to ");
            Serial.println(status_count);
            digitalWrite(LED_PIN_RELAY, HIGH);
          };
        };
      } else {
        if (status_count > 1) {
          status_count--;
          Serial.print("\"");
          Serial.print(my_SSID);
          Serial.print("\" missing              - power stays ON   - \"alive\" counter decremented to ");
          Serial.println(status_count);
        } else {
          if (status_count == 1) {
            status_count--;
            Serial.print("\"");
            Serial.print(my_SSID);
            Serial.println("\" missing              - power turned OFF - \"alive\" counter has sunk to ZERO");
          } else {
            Serial.print("\"");
            Serial.print(my_SSID);
            Serial.println("\" not found            - power is OFF");
          };
        };
      };
      // Switch on!!
      if ( status_count == maxCount ) {
        //      Serial.println("Power is ON");
        digitalWrite(LED_PIN_RELAY, HIGH);
        digitalWrite(LED_PIN_GRN,   LOW);
      } else {
        digitalWrite(LED_PIN_GRN,   HIGH);
      }; 
      // Switch off!!
      if ( status_count <= 0) {
        //      Serial.println("Power is OFF");
        digitalWrite(LED_PIN_RELAY, LOW);
      };
    };
  };

  // Wait a bit before scanning again
  x = 0;
  do 
    {
      if (digitalRead(LED_PIN_BUTTON) == HIGH) {
        x = stepDelay;
      }else{
        x++;
      };
      delay(1000);
    } while ( x <= stepDelay );

  };
