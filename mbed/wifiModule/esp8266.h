#include "mbed.h"
#include "stringOperations.h"
#include "location.h"
//#include "debugLocation.h"

#define SSID "AT+CWLAP=\"campusroam-2.4\""  // with AT command...
#define ENABLE true
#define DISABLE false
#define BUFFER_SIZE 3000
#define delay_time 1.5

class esp8266
{
public:
    esp8266(PinName, PinName, Serial*);
    ~esp8266();

    //methods
    int scan(void); // returns index of device id table
    void WIFI_module(bool);

private:
    Serial* _serial;
    ATCmdParser* _parser;
    DigitalOut _rstWifi;
    DigitalOut _enWifi;
    char** tokens;
    StringOperations so;
};