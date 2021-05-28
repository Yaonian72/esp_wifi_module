
//#include "Pages.h"
#include <Arduino.h>
#include <Pages.h>


ESPweb pidweb(mySerial,Serial);


void resetCb() {
  Serial.println("EL-Client (re-)starting!");
  bool ok = false;
  do {
    ok = pidweb.esp_Sync(100);      // sync up with esp-link, blocks for up to 2 seconds
    if (!ok) Serial.println("EL-Client sync failed!");
  } while(!ok);
  Serial.println("EL-Client synced!");

  pidweb.webserver_setup();
}

void Web_ButtonCb(char * btnId){
  pidweb.ButtonPressCb(btnId);
}

void Web_FieldCb(const char * field){
  pidweb.userSetFieldCb(field);
}
void Web_LoadCb(const char * url){
  pidweb.userLoadCb(url);
}


void webinit(){
  URLHandler *pidPageHandler = pidweb.createURLH();
  pidPageHandler->buttonCb.attach(&Web_ButtonCb);
  pidPageHandler->setFieldCb.attach(&Web_FieldCb);
  pidPageHandler->loadCb.attach(&Web_LoadCb);
  pidPageHandler->refreshCb.attach(&Web_FieldCb);
}


void setup() {
  // put your setup code here, to run once:
  mySerial.begin(115200);
  Serial.begin(115200);
  webinit();
  pidweb.begin(resetCb);
}

void loop() {
  // put your main code here, to run repeatedly:
  pidweb.process_esp();
  pidweb.printloop();
  delay(50);
}