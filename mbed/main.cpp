#include "mbed.h"
#include "ATCmdParser.h"
#include "UARTSerial.h"
#include "location.h"
//#include "debugLocation.h"
#include "stringOperations.h"

#define VERSION "v1.0"
#define ESP8266_DEFAULT_BAUD_RATE   115200
UARTSerial *_serial;
ATCmdParser *_parser;

//chipselect WIFI module
//DigitalOut wifi_enable(D9);

StringOperations so;

int main()
{   
    printf("Device location version %s\n\r",VERSION);
    printf("List of known AP's\n\r");
    
    for (int i = 0; i < NUMBER_OF_MACS; ++i)
    {
        printf("location: %s => MAC: %s.\n\r", location[i], macs[i]);
    }

    _serial = new UARTSerial(D1, D0, ESP8266_DEFAULT_BAUD_RATE);
    _parser = new ATCmdParser(_serial);
    _parser->debug_on( 0 );
    _parser->set_delimiter( "\r\n" );
    
    char** tokens;
    
    while(1)
    {
        //Get a List of available AP's
        _parser->send("AT+CWLAP=\"campusroam\"");    
        //_parser->send("AT+CWLAP=\"telenet-C32F3A2\""); // request
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
        //split the buffer
        int size = 0;
        tokens = so.split(buffer, ',', &size);
        if(tokens != NULL)
        {
            
            //find the best AP
            int max = -1000;
            int AP = 0;
            for (int k = 0; k < (size-1)/6; k++)
            {
                int tempSignal = so.ConvertToInt(tokens[2 + (6*k)]);
                if(max < tempSignal)
                {
                    max = tempSignal;
                    AP = k;
                }
            }
            
            if(max != -1000)
            {
                so.removeChar(tokens[3 + (6*AP)],'"');
                printf("=> %d mdB, MAC: %s\n\r", max,tokens[3 + (6*AP)]);
                for(int device = 0; device < NUMBER_OF_MACS; device++)
                {
                    //printf("macs[%d](%s) == %s.\n\r",device,macs[device],tokens[3 + (6*AP)]);
                    //find the location of the AP
                    if(strcmp(macs[device],tokens[3 + (6*AP)]) == 0)
                    {
                        printf("Location ID: %s\n\r",location[device]);
                        break;
                    }
                }
            }  
            
            //importent => free() tokens!
            // first free each row
            for(int x = 0; x < size; x++)
            {
                free(tokens[x]);
            }
            // second free the top
            free(tokens);
        }
        else
        {
            printf("split returned a NULL\n\r");
        }
    }
    
    return 0; //OKE
}
