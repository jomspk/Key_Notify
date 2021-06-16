#include <WiFi.h>
#include "WiFiClientSecure.h"

//WiFi設定
const char* ssid = "Buffalo-G-8278";//ここにWiFiのssidを入れるipconfigで確認できるかも
const char* password = "bu6i586reh8kd";//put wifi password
void wifiConnect(){
  Serial.println("Connecting to " + String(ssid));//print ssid to connect

  //Start connecting to WiFi
  WiFi.begin(ssid, password);
  Serial.println(WiFi.status());

  //Wait until connect status
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
    }

    //Success to connect. Print IP address again
    Serial.print("Connected! IP address: ");
    Serial.println(WiFi.localIP());
  }


  //Line inform
  void sendLineNotify(String mes){
    const char* host = "notify-api.line.me";
    const char* token = "dzqGeo7KcN34ZUQ9rQNsMSDSUVgG4aMkQlT5nYdJlWO";//put your line token here
    const char* message = "YOU MISS TO LOCK";//put the message here
    WiFiClientSecure client;
    Serial.println("Try");
    //Connect to Line API server
    //"!" means that client.connect is NOT
    //May be "443" means port number
    if (!client.connect(host,443)){
      Serial.println("Connection failed");
      return;
    }
    Serial.println("Connected");
    //Send request
    String query = mes;
    String request = String("") +
                 "POST /api/notify HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Authorization: Bearer " + token + "\r\n" +
                 "Content-Length: " + String(query.length()) + "\r\n" +
                 "Content-Type: application/x-www-form-urlencoded\r\n\r\n" +
                 query + "\r\n";
    client.print(request);
    

    //Wait until finish receiving returned information
    while (client.connected()){
      String line = client.readStringUntil('\n');
      if (line == "\r"){
        break;
      }
    }

    String line = client.readStringUntil('\n');
    Serial.println(line);
  }

  // I want to send the information when the LockStatus changes.
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("---Started---");
  wifiConnect();
}

void loop() {
  // put your main code here, to run repeatedly:
  sendLineNotify("Hello");
  delay(1000);
}
