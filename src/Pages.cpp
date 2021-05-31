#include <Pages.h>

ESPweb::ESPweb(Stream *comm_ser, Stream *debug_ser):esp(comm_ser),webServer(&esp),_dbg_ser(debug_ser),_comm_ser(comm_ser){}

void ESPweb::begin(r_cb cb){
  esp.resetCb = cb;
  esp.resetCb();
}


void ESPweb::userSetFieldCb(const char * field)
{
  String fld = field;
  _dbg_ser->println(fld);
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
    // _dbg_ser->print("024420");
    // _dbg_ser->println();
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
    // _dbg_ser->print("4343420"); 
    _dbg_ser->println("4343420");
}

// void ButtonPressCb(char * btnId)
// {
//         String fld = btnId;
//   _dbg_ser->println(fld);
//   _dbg_ser->println("Botton pressed!");
// }

void ESPweb::ButtonPressCb(char * btnId)
{
  String id = btnId;
//   _comm_ser->print(id);
  if( id == F("Valve_on") )
    v_status = 1;
  else if( id == F("Valve_off") )
    v_status = 0;
//   _comm_ser->print(v_status);
//   _comm_ser->println();
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
      _comm_ser->print(p[i]);
  }
}

void ESPweb::printloop(){

    _dbg_ser->print(a_ki);
    _dbg_ser->print(",");
    _dbg_ser->print(a_kp);
    _dbg_ser->print(",");
    _dbg_ser->print(a_kd);
    _dbg_ser->print(",");
    _dbg_ser->println();
    
    _comm_ser->print(a_ki);
    _comm_ser->print(",");
    _comm_ser->print(a_kp);
    _comm_ser->print(",");
    _comm_ser->print(a_kd);
    _comm_ser->print(",");
    _comm_ser->print(f_ki);
    _comm_ser->print(",");
    _comm_ser->print(f_kp);
    _comm_ser->print(",");
    _comm_ser->print(f_kd);
    _comm_ser->print(",");
    _comm_ser->print(p_speed.airspeed);
    _comm_ser->print(",");
    _comm_ser->print(p_speed.fragspeed);
    _comm_ser->print(",");
    _comm_ser->print(v_status);
    // Byteprint(ki);
    // // _comm_ser->print(",");
    // Byteprint(a_kp);
    // // _comm_ser->print(",");
    // Byteprint(a_kd);
    _comm_ser->println();
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