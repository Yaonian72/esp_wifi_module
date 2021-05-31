#ifndef ELC_PAGES_H
#define ELC_PAGES_H


#include <ELClient.h>
#include <ELClientWebServer.h>

// extern SoftwareSerial mySerial;
typedef void (*r_cb)();

// extern ELClient esp;
// // Initialize the Web-Server client
// extern ELClientWebServer webServer;

struct AppConfig{
    uint8_t airspeed = 80;
    uint8_t fragspeed = 80;
};

class ESPweb {

    public:
        ESPweb(Stream *comm_ser, Stream *debug_ser);
        // void PIDInit();
        void begin(r_cb cb);
        void process_esp();
        void userSetFieldCb();
        void userLoadCb();
        void printloop();
        void Byteprint(float f);
        void ButtonPressCb(char * btnId);
        void userLoadCb(const char * url);
        void userSetFieldCb(const char * field);
        boolean esp_Sync(uint32_t timeout = 100);
        void webserver_setup();
        URLHandler * createURLH();

    private:
        float a_kp=0.01;
        float a_ki=0.01;
        float a_kd=0.01;
        float f_kp=0.02;
        float f_ki=0.02;
        float f_kd=0.02;
        bool v_status=0; //1 on 0 off
        AppConfig p_speed ={30, 30};
        ELClient esp;
        Stream * _dbg_ser;
        Stream * _comm_ser;
        ELClientWebServer webServer;// Initialize the Web-Server client
};






#endif /* ELC_PAGES_H */