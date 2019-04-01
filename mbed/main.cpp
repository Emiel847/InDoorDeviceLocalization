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
//DigitalOut cs_WIFI(D9);
//DigitalOut cs_WIFI_RST(A2); TODO: chipselect does not work when declearing pins :O

StringOperations so;

enum chips{
    OFF = 0,
    WIFI,
    LORA
};

int init(void);

int main()
{  
    printf("Device location version %s\n\r",VERSION);
    printf("List of known AP's\n\r");
    
    for (int i = 0; i < NUMBER_OF_MACS; ++i)
    {
        printf("location: %s => MAC: %s.\n\r", location[i], macs[i]);
    }
    
    if(init() < 0)
    {
        printf("Error: something whent rong in init function.\n\r");
        return -1;
    }
        
    char** tokens;
    
    while(1)
    {
        //Get a List of available AP's
        //disable wifi module 
        //chipSelect(WIFI);  
        //_parser->send("AT+CWLAP=\"telenet-C32F3A2\""); // request
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
        
        //disable wifi module
        //chipSelect(OFF);  
        
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
                        
                       /*  -------------------------------------------------------------------------  */                                                             
                       //      ____  _____ _   _ ____    _____ ___    _     ___  ____     _           //
                       //     / ___|| ____| \ | |  _ \  |_   _/ _ \  | |   / _ \|  _ \   / \          //
                       //     \___ \|  _| |  \| | | | |   | || | | | | |  | | | | |_) | / _ \         //
                       //      ___) | |___| |\  | |_| |   | || |_| | | |__| |_| |  _ < / ___ \        //
                       //     |____/|_____|_| \_|____/    |_| \___/  |_____\___/|_| \_/_/   \_\       //
                       //                                                                             //
                       /*  -------------------------------------------------------------------------  */
                        
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

int init(void)
{
    //activate module
    //cs_WIFI = 1;
    //wait(5);
    //cs_WIFI_RST = 1;
    
    //activate UART and AT paser
    _serial = new UARTSerial(D1, D0, ESP8266_DEFAULT_BAUD_RATE);
    if( _serial != NULL)
    {
        _parser = new ATCmdParser(_serial);
        
        if(_parser != NULL)
        {
            _parser->debug_on( 0 );
            _parser->set_delimiter( "\r\n" );
        }
        else
        {
            printf("Error (init): Can not link ATcmd.\n\r");
            return -1;
        }
    }
    else
    {
        printf("Error (init): Can not link UART.\n\r");
        return -1;
    }
    
    return 0; //OKE

}
