#include <WiFi.h>
#include <WiFiMulti.h>
#include <ssl_client.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

const char* ssid = "UBIC-3D-G";
const char* password = "UbiC$mar29-";

const char* line_notify_ca= \
"-----BEGIN CERTIFICATE-----/n" \
"MIIGvTCCBaWgAwIBAgIMA5+Eduqn8JC9rUTPMA0GCSqGSIb3DQEBCwUAMFAxCzAJ/n" \
"BgNVBAYTAkJFMRkwFwYDVQQKExBHbG9iYWxTaWduIG52LXNhMSYwJAYDVQQDEx1H/n" \
"bG9iYWxTaWduIFJTQSBPViBTU0wgQ0EgMjAxODAeFw0yMDA2MTcwNjAxNThaFw0y/n" \
"MjA5MDUxMjAwMDBaMGUxCzAJBgNVBAYTAkpQMREwDwYDVQQIEwhUb2t5by10bzEU/n" \
"MBIGA1UEBxMLU2hpbmp1a3Uta3UxGTAXBgNVBAoTEExJTkUgQ29ycG9yYXRpb24x/n" \
"EjAQBgNVBAMMCSoubGluZS5tZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoC/n" \
"ggEBAMLkCXzXU8mAQajoVb8J80eYBE/qejymyJW2jqEunJIKakFt/fX4mqILUHsi/n" \
"1auGnoZxXu5tJCfYTbfchibZZ/PiLqSRldJURgIXxub3njrpIcplAc26P1n4y62q/n" \
"A38XeKiIF80fTols1LNBNXhV2cKj1lRv2SwUTXZcke3noWye1oZ47QFtEuAzEFkp/n" \
"F9k9r2YdEqjWwuLBicrQEXVbrsRQer8YVJFvt3tpfeWSgQIOB35WReZi1M876+Yq/n" \
"GHBAW0/ty1Bjg+yR9hNSdrcbzOnzhnsBWantZishoJp/P5o+WhsYn8z1Oxgs7KwW/n" \
"Htuf59nbQgMkdAwjxugem5b2h48CAwEAAaOCA4AwggN8MA4GA1UdDwEB/wQEAwIF/n" \
"oDCBjgYIKwYBBQUHAQEEgYEwfzBEBggrBgEFBQcwAoY4aHR0cDovL3NlY3VyZS5n/n" \
"bG9iYWxzaWduLmNvbS9jYWNlcnQvZ3Nyc2FvdnNzbGNhMjAxOC5jcnQwNwYIKwYB/n" \
"BQUHMAGGK2h0dHA6Ly9vY3NwLmdsb2JhbHNpZ24uY29tL2dzcnNhb3Zzc2xjYTIw/n" \
"MTgwVgYDVR0gBE8wTTBBBgkrBgEEAaAyARQwNDAyBggrBgEFBQcCARYmaHR0cHM6/n" \
"Ly93d3cuZ2xvYmFsc2lnbi5jb20vcmVwb3NpdG9yeS8wCAYGZ4EMAQICMAkGA1Ud/n" \
"EwQCMAAwHQYDVR0RBBYwFIIJKi5saW5lLm1lggdsaW5lLm1lMB0GA1UdJQQWMBQG/n" \
"CCsGAQUFBwMBBggrBgEFBQcDAjAfBgNVHSMEGDAWgBT473/yzXhnqN5vjySNiPGH/n" \
"AwKz6zAdBgNVHQ4EFgQUlMcjP5HQIbB0fruuvxoWlNUpg6QwggH2BgorBgEEAdZ5/n" \
"AgQCBIIB5gSCAeIB4AB2ACJFRQdZVSRWlj+hL/H3bYbgIyZjrcBLf13Gg1xu4g8C/n" \
"AAABcsDevRsAAAQDAEcwRQIgKO4iNHwKctJ6i23CcusiS/eRybD7OgmyK6DtVJkZ/n" \
"nskCIQDMzwX1NU3ySt2E7a3dq6tCbgBzSGpHd56300ntq06/6QB2ACl5vvCeOTkh/n" \
"8FZzn2Old+W+V32cYAr4+U1dJlwlXceEAAABcsDevcQAAAQDAEcwRQIhAONwL/C8/n" \
"/sz+UxaLfwfyt+RuQNpK5TO/opHyPK2WcPIkAiAVTLmQL0LT0vIyUX0sJjPZjJ22/n" \
"l3aC6FG6x803fHxQ/wB3AFWB1MIWkDYBSuoLm1c8U/DA5Dh4cCUIFy+jqh0HE9MM/n" \
"AAABcsDevckAAAQDAEgwRgIhANwqyszHCK1h0Y19oKD8coAROyUkVm/fcKuDqQqq/n" \
"5dGJAiEA6MlqAolv+RNuiRhVBA0LNrtHE5HAdHwkRqwecNxirFgAdQBRo7D1/QF5/n" \
"nFZtuDd4jwykeswbJ8v3nohCmg3+1IsF5QAAAXLA3r3dAAAEAwBGMEQCIGaE5uuM/n" \
"9iv0U+i7S5+V+Hum1bMquroZ3T427DAJsi5MAiBEXZxZjFab994Ca4xhyqYKEvKP/n" \
"cHnXBjNqpBdCgpQB8zANBgkqhkiG9w0BAQsFAAOCAQEAfyFH/m+uOMS6zOMp8iag/n" \
"JTMq6d4UtFMasAEHFbbtyUS8u59gcrsDEPDRfcJbVNDPe+knIc7H8FjTrVVdWz17/n" \
"Ii+ZaA5R5QWdABfejl82n8qGYuTrJk5UuZN6FTSTsoDbMxBZzcBED+ghD2vB2G6G/n" \
"w32Ltwail16LsDWNnwLAvd5idS2svU8BlA+O0rhBvIsBX7kFuP4TJbZ3yGjPAYXk/n" \
"ztj5SGLUenuTj0Yy5CWa6U67Er53x98ezOKkzaO9C0sAiv1M9ux8yK/zA1ggUpSl/n" \
"7WmRjBf1LoGWFHB66olsSxYd0YwZcBgRTyzmG2S+6zURZPIipFy5OqyOaiAEtWYm/n" \
"wQ==/n" \
"-----END CERTIFICATE-----/n";

void send(String message){
  const char* host = "notify-api.line.me";
  const char* token = "bjaqf6LuNUhNT6BfecZrvmwWvaqnNJDTKUSIVxbBJlU";
  WiFiClientSecure client;
  // client.setCACert(line_notify_ca);//line notifyサイトのルート証明書をセットする
  client.setInsecure();
  Serial.println("Try");
  //LineのAPIサーバに接続
  if (!client.connect(host, 443)){
    Serial.println("Connection failed");
    return;
    }
    Serial.println("Connected");
    //リクエスト送信
    String query = String("message=")+message;
  String request = String("") +
               "POST /api/notify HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Authorization: Bearer " + token + "\r\n" +
               "Content-Length: " + String(query.length()) +  "\r\n" + 
               "Content-Type: application/x-www-form-urlencoded\r\n\r\n" +
                query + "\r\n";
  client.print(request);

  //受信終了までまつ
  while (client.connected()){
    String line = client.readStringUntil('\n');
    Serial.println(line);
    if (line == "\r"){
      break;
      }
    }

    String line = client.readStringUntil('\n');
    Serial.println(line);
  }
void wifiConnect(){
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password); //Wi-Fi接続
  while(WiFi.status() != WL_CONNECTED){ //Wi-Fi 接続待ち
    delay(100);
    Serial.printf(".");
    }
    Serial.println("\nwifi connect ok");
  }
/*void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("setup start");
  wifiConnect();

}

void loop() {
  // put your main code here, to run repeatedly:
  send("aaaaaaaaaaaaaaaaa");
  delay(10000);
}*/
