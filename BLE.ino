//This code is for BLE conection
#include "SimpleBLE.h"
SimpleBLE ble;

void NotifyBLE(){
    if (ble.begin("Start BLE connection")){
      Serial.println("Connected successfully!");
        
    }
    else{
        Serial.println("starting BLE failed!");
    }
}

void setup() {
  Serial.begin(9600);
    delay(10);
    NotifyBLE();
    delay(50);
    ble.end();
}
void loop() {
    NotifyBLE();
    delay(50);
    ble.end();
    delay(3000);
}
