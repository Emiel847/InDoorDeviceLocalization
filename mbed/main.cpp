#include "mbed.h"
#include "ATCmdParser.h"
#include "UARTSerial.h"
#include "location.h"

#define   ESP8266_DEFAULT_BAUD_RATE   115200
UARTSerial *_serial;
ATCmdParser *_parser;

//chipselect WIFI module
//DigitalOut wifi_enable(D9);

int main()
{   

    printf("List of AP's\n\r");
    
    for (int i = 0; i < NUMBER_OF_MACS; ++i)
    {
        printf("location: %s => MAC: %s.\n\r", location[i], macs[i]);
    }

    _serial = new UARTSerial(D1, D0, ESP8266_DEFAULT_BAUD_RATE);
    _parser = new ATCmdParser(_serial);
    _parser->debug_on( 1 );
    _parser->set_delimiter( "\r\n" );
    
    
    _parser->send("AT+GMR");
    int version;
    _parser->recv("SDK version:%d", &version);
    _parser->recv("OK");
    
    
    //Now get the FW version number of ESP8266 by sending an AT command 
    _parser->send("AT+CWLAP=\"campusroam\"");
    int i = 0;
    char buffer[3000];
    bool isOk = false;
    while(!isOk)
    {
        buffer[i] = (char)_parser->getc();
        if(buffer[i] == 'K')
        {
            isOk = true; 
        }
        i++;
    }
    
    printf("=> %s\n\r",buffer);
    //_parser->recv("+CWLAP:%s)", buffer);
    
    printf("Done\n");
    
    return 0; //OKE
}