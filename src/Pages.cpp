#include <Pages.h>

SoftwareSerial mySerial(5, 6); // RX, TX


void ESPweb::begin(r_cb cb){
  esp.resetCb = cb;
  esp.resetCb();
}


void ESPweb::userSetFieldCb(const char * field)
{
  String fld = field;
  Serial.println(fld);
  if( fld == F("a_kp")){
    a_kp = (float)webServer.getArgFloat();}
  else if( fld == F("a_ki")){
    a_ki = (float)webServer.getArgFloat();}
  else if( fld == F("a_kd")){
    a_kd = (float)webServer.getArgFloat();}
  else if( fld == F("airspeed")){
    p_speed.airspeed = (float)webServer.getArgInt();}
  else if( fld == F("f_kp")){
    f_kp = (float)webServer.getArgFloat();} 
  else if( fld == F("f_ki")){
    f_ki = (float)webServer.getArgFloat();}
  else if( fld == F("f_kd")){
    f_kd = (float)webServer.getArgFloat();}
  else if( fld == F("fragspeed")){
    p_speed.fragspeed = (float)webServer.getArgInt();}

}

void ESPweb::userLoadCb(const char * url)
{
    // Serial.print("024420");
    // Serial.println();
    // char buf[MAX_STR_LEN];
    webServer.setArgFloat(F("a_kp"), a_kp);
    webServer.setArgFloat(F("a_ki"), a_ki);
    webServer.setArgFloat(F("a_kd"), a_kd);
    webServer.setArgInt(F("airspeed"), p_speed.airspeed);
    webServer.setArgFloat(F("f_kp"), f_kp);
    webServer.setArgFloat(F("f_ki"), f_ki);
    webServer.setArgFloat(F("f_kd"), f_kd);
    webServer.setArgInt(F("fragspeed"), p_speed.fragspeed);
    // webServer.setArgString(F("Valve Status"), (v_status == 0) ?  F("on") : F("off"));
    // Serial.print("4343420"); 
    Serial.println("4343420");
}

// void ButtonPressCb(char * btnId)
// {
//         String fld = btnId;
//   Serial.println(fld);
//   Serial.println("Botton pressed!");
// }

void ESPweb::ButtonPressCb(char * btnId)
{
  String id = btnId;
//   mySerial.print(id);
  if( id == F("Valve_on") )
    v_status = 1;
  else if( id == F("Valve_off") )
    v_status = 0;
//   mySerial.print(v_status);
//   mySerial.println();
}

URLHandler *ESPweb::createURLH(){
  URLHandler *pidPageHandler = webServer.createURLHandler(F("/pid.html.json"));
  return pidPageHandler;
}

// void ESPweb::PIDInit()
// {
//   URLHandler *pidPageHandler = webServer.createURLHandler(F("/pid.html.json"));
//   pidPageHandler->buttonCb.attach(&ButtonPressCb);
//   pidPageHandler->setFieldCb.attach(&userSetFieldCb);
//   pidPageHandler->loadCb.attach(&userLoadCb);
//   pidPageHandler->refreshCb.attach(&userSetFieldCb);
  
// }

void ESPweb::Byteprint(float f){

  unsigned char const * p = reinterpret_cast<unsigned char const *>(&f);

  for (std::size_t i = 0; i != sizeof(float); ++i)
  {
      mySerial.print(p[i]);
  }
}

void ESPweb::printloop(){

    Serial.print(a_ki);
    Serial.print(",");
    Serial.print(a_kp);
    Serial.print(",");
    Serial.print(a_kd);
    Serial.print(",");
    Serial.println();
    
    mySerial.print(a_ki);
    mySerial.print(",");
    mySerial.print(a_kp);
    mySerial.print(",");
    mySerial.print(a_kd);
    mySerial.print(",");
    mySerial.print(f_ki);
    mySerial.print(",");
    mySerial.print(f_kp);
    mySerial.print(",");
    mySerial.print(f_kd);
    mySerial.print(",");
    mySerial.print(p_speed.airspeed);
    mySerial.print(",");
    mySerial.print(p_speed.fragspeed);
    mySerial.print(",");
    mySerial.print(v_status);
    // Byteprint(ki);
    // // mySerial.print(",");
    // Byteprint(a_kp);
    // // mySerial.print(",");
    // Byteprint(a_kd);
    mySerial.println();
    delay(400);
}



void ESPweb::process_esp(void){
  esp.Process();
}

boolean ESPweb::esp_Sync(uint32_t timeout){
  return esp.Sync(timeout);
}

void ESPweb::webserver_setup(){
  webServer.setup();
}