//Action of laser

#define LASER_NUM 1 //The amout of laser
#define PD_PIN 33 //This pin number connected to photoIC

#define DEBUG_MODE true//true is for when you want to confirm value of sensor in sirial monitor

extern void send(String message);
extern void wifiConnect();
int prevState=false;//prevouse status of sensor
int i=0;

void setup(){
  pinMode(PD_PIN,INPUT_PULLDOWN);//setting pin mode to use in DigitalRead

  if(DEBUG_MODE){
    Serial.begin(115200);//for Debug
    }
    Serial.println("setup start");
    wifiConnect();
  }

void updateControl(){

  //monitoring for debug
  if(DEBUG_MODE){
    Serial.print("PD:");
    int pd = digitalRead(PD_PIN);
    Serial.print(pd);
    Serial.print("/");
    }
      
  }
//フォトICダイオードの変化をprintする
  void Change(){
      int crntState = digitalRead(PD_PIN);
      Serial.print(crntState);
      if (crntState == 1 && prevState == 0){
          send("レーザー当たってる！！");
      }
      else if (crntState == 0 && prevState == 1){
          send("何もない");
      }
      else if (crntState == 0 && prevState == 0){
          send("まだ何もない");
      }
      else{
          send("レーザーが当たり続けてる！");
      }

      prevState = crntState;
  }

void loop(){
  updateControl();
  Change();
  delay(1000);
  }
