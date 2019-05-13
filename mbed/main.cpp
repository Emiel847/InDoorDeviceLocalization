#include "mbed.h"
#include "ATCmdParser.h"
#include "UARTSerial.h"
#include "location.h"
//#include "debugLocation.h"
#include "stringOperations.h"
#include "click_4.h"

#define VERSION "v2.2"
#define ESP8266_DEFAULT_BAUD_RATE   115200
#define BUFFER_SIZE 3000
#define ENABLE true
#define DISABLE false
#define delay_time 1
Serial *_serial;
ATCmdParser *_parser;
click_4 *c4;

//chipselect WIFI module
DigitalOut cs_WIFI(D10);
//DigitalOut cs_LORA(D9);
DigitalOut cs_WIFI_RST(A3);

StringOperations so;

int init(void);
void WIFI_module(bool isEnable);

//reset ticker
bool needReset = true;
Ticker rst_ticker;
void rst_func() {
  //reset module
    if(needReset == true)
    {
        NVIC_SystemReset();
    }
}

int main()
{  
    printf("Device location version %s\n\r",VERSION);
    
    if(init() < 0)
    {
        printf("Error: something whent rong in init function.\n\r");
        return -1;
    }
        
    char** tokens;
    
    
    while(1)
    {   ////////
        // -> Get a List of available AP's
        ////////
        
        //disable wifi module 
        WIFI_module(ENABLE);
        
        //sent AT request
        printf("Send AT command...\n\r");
        _parser->send("AT+CWLAP=\"campusroam-2.4\""); 
        
        
        char buffer[BUFFER_SIZE];
        int i = 0;
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
        WIFI_module(DISABLE);
        
        //remove bad chars from begin of ths string
        int i_find = 0;
        bool ready = false;
        char *p = buffer;
        while (ready == false)
        {
            //find start of string...
            if (buffer[i_find] == '+' && buffer[i_find+1] == 'C' && buffer[i_find+2] == 'W')
            {
                ready = true;
                i = i - i_find;
                strcpy(buffer, p + i_find);
            }
            else if(i_find >= BUFFER_SIZE)
            {
                //nothing found, continue code... nothing happend...
                ready = true; 
            }
            else
            {
                i_find++;
            }
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
                        
                       /*  -------------------------------------------------------------------------  */                                                             
                       //      ____  _____ _   _ ____    _____ ___    _     ___  ____     _           //
                       //     / ___|| ____| \ | |  _ \  |_   _/ _ \  | |   / _ \|  _ \   / \          //
                       //     \___ \|  _| |  \| | | | |   | || | | | | |  | | | | |_) | / _ \         //
                       //      ___) | |___| |\  | |_| |   | || |_| | | |__| |_| |  _ < / ___ \        //
                       //     |____/|_____|_| \_|____/    |_| \___/  |_____\___/|_| \_/_/   \_\       //
                       //                                                                             //
                       /*  -------------------------------------------------------------------------  */
                        
                        uint8_t message[2];
                        message[0]=location[device][0] - 48;
                        message[1]=(location[device][2] - 48) + (10 * (location[device][1] - 48));
                        
                        needReset = false;
                        
                        //call method to initialize the click4 module and the uart
                        //this method also lets the device join the lorawan network using OTAA
                        c4->initialize(AppEUI, sizeof(AppEUI), AppKey, sizeof(AppKey));
                        //call method to send a message to the TTN 
                        c4->sendData(message, sizeof(message));
                        //call method to reset lorawan module uart
                        c4->close();
                        
                        //reset the module :/ ...
                        NVIC_SystemReset();
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
    //start reset ticker
    rst_ticker.attach(&rst_func, 10.0);
    
    //enable Reset pin
    cs_WIFI_RST = 1;
    
    //activate UART and AT paser
    _serial = new Serial(D1, D0, ESP8266_DEFAULT_BAUD_RATE);
    c4 = new click_4(D3, D9, A2, _serial);
    
    if( c4 == NULL)
    {
        printf("ERROR: Could not link click_4.\n\r");
        return -1;
    } 
    
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
    
     //lora...
    
    return 0; //OKE

}


void WIFI_module(bool isEnable)
{
    if(isEnable)
    {
        cs_WIFI = 1;
        //cs_LORA = 0; //prevent lora be enable!
        wait(delay_time);
    }
    else
    {
        cs_WIFI = 0;
    } 
}