#include "robot.h"
#define ROBOT_SPEED  100

void setup(){
  Serial.begin(38400);
  Serial.println("Boot");
  rbt_init();  
  delay(5000);
}

uint16_t lleft,lmid,lright;
boolean wleft,wmid,wright;

void loop(){
  rbt_sns(&lleft,&lmid,&lright,&wleft,&wmid,&wright);
  Serial.print("Left: ");
  Serial.print(lleft);
  Serial.print("Mid: ");
  Serial.print(lmid);
  Serial.print("Right: ");
  Serial.println(lright);

  //off the line
  if(lleft == 1000 && lmid == 1000 && lright == 1000){
    rbt_move(BRAKE,0);
  }
  
  //follow track
  else{
    if(lleft > lmid && lleft > lright){
      rbt_move(LEFT,ROBOT_SPEED);
    }
    if(lmid > lleft && lmid > lright){
      rbt_move(FWD,ROBOT_SPEED);
    }
    if(lright > lmid && lright > lleft){
      rbt_move(RIGHT,ROBOT_SPEED);
    }
  }
}
