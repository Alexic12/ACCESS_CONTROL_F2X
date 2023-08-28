#include <Arduino.h>
#include "fsm.h"

fsm F;

// put function declarations here:

CONFIG_ERROR();
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //Serial.print("FIELD CONTROL ACCESS UNIT.....INIT");
  fsm::initFSM();

}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.print("FIELD CONTROL ACCESS UNIT.....INIT");
  fsm::runFSM();
  //delay(1000);
}

