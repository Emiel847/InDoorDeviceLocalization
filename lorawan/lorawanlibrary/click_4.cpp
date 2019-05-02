#include "mbed.h"
#include "click_4.h"

/*
*constructor 
*
*@param indicate    indicate pin      
*@param wake        wake pin
*@param tx          tx pin      
*@param rx          rx pin
*@param baudrate    baudrate to set
*@param reset       reset pin
*/
click_4::click_4(PinName Indicate, PinName wake, PinName tx, PinName rx, int baudRate, PinName reset ):NDATA_INDICATE(Indicate),NWAKE(wake),myuart(tx,rx,baudRate),NRESET(reset){ 
    NWAKE.write(1);
    j=0;
}

/*
*deconstructor
*/
click_4::~click_4(){}

/*
* method to reset the device
*/
void click_4::reset(){
     //set NRST to o to reset 
    NRESET.write(0);
    wait(0.5);
    //set reset back to 1
    NRESET.write(1);
    wait(2);
     //while(!NDATA_INDICATE);   test this
     
     
    //this is normally not needed unless you want to reset the module and it's eeprom
    //reset_cmd();
    //factory_reset_cmd();
    printf("\r\nDevice has been reset.\r\n");
   
    }
    
/*
* method to set the baud rate 
*/
void click_4:: init(){
    //call method to set the baud rate
    myuart.baud(115200);
    printf("BaudRate has been set.\r\n");
}

/*
* method to perform a module reset
*/
void click_4::reset_cmd(){
    printf("r\nReset Device.\r\n");
    
    //declare local variables
    uint8_t bufferToSend[4];
    
    //reset buffer and j
    j = 0;  
    memset(buff, 0x00, sizeof(buff));
    
    bufferToSend[0]=0xAA;
    bufferToSend[1]=0x30;
    bufferToSend[2]=0x00;
    bufferToSend[3]=0x26;
    
    send(bufferToSend,sizeof(bufferToSend)); 
    receive();
}

/*
* method to reset the eeprom of the device
*/    
void click_4::factory_reset_cmd(){
    printf("\r\nFactory reset.\r\n");
     //declare local variables
    uint8_t bufferToSend[4];
    
    //reset buffer and j
    j = 0;  
    memset(buff, 0x00, sizeof(buff));
    
    bufferToSend[0]=0xAA;
    bufferToSend[1]=0x31;
    bufferToSend[2]=0x00;
    bufferToSend[3]=0x25;
    
    send(bufferToSend,sizeof(bufferToSend)) ;
    receive();
 
}

/*
*method to get the EUI of the device: (needed for the loraWan communication)
*/
void click_4::getDevEui(){
    printf("\r\nDevEUI:\r\n"); 
    //declare local variables
    uint8_t bufferToSend[4];
    
    //reset buffer and j
    j = 0;  
    memset(buff, 0x00, sizeof(buff));
 
    bufferToSend[0]=0xAA;
    bufferToSend[1]=0x36;
    bufferToSend[2]=0x00;
    bufferToSend[3]=0x20;
   
    send(bufferToSend,sizeof(bufferToSend));
    receive();
}

/*
* method to write to eeprom
*
*@param ptrToData       pointer to the first element of the data to write to the eeprom
*@param startAdress     address of the eeprom to start writing
*@param dataSize        size in bytes of the data to write to the eeprom
*/
void click_4::eeprom_write_cmd(const uint8_t* ptrToData ,uint8_t startAdress, int dataSize){
    printf("\r\nwrite to eeprom:\r\n"); 
    //declare local variables
    uint8_t bufferToSend[5+dataSize];
    
    //reset buffer and j
    j = 0;  
    memset(buff, 0x00, sizeof(buff));
    
    bufferToSend[0]=0xAA;
    bufferToSend[1]=0x32;
    bufferToSend[2]=sizeof(bufferToSend);
    bufferToSend[3]=0x08;
    for (int i=4; i<4+dataSize; i++){
            bufferToSend[i]= (uint8_t) *(ptrToData+i-4);
        }
    bufferToSend[4+dataSize]=calculateCks(bufferToSend,sizeof(bufferToSend));

    send(bufferToSend,sizeof(bufferToSend));
    receive();
}

/*
* method to read from the eeprom
*
*@param startAddress        address o the eeprom to start the reading
*@param numberOfBytes       number of bytes to be read
*/
void click_4::eeprom_read_cmd(uint8_t startAddress, uint8_t numberOfBytes){
    printf("\r\nread from eeprom\r\n");
    //declare local variables
    uint8_t bufferToSend[6];
    
    //reset buffer and j
    j = 0;  
    memset(buff, 0x00, sizeof(buff));
    
    bufferToSend[0]=0xAA;
    bufferToSend[1]=0x33;
    bufferToSend[2]=0x02;
    bufferToSend[3]=startAddress;
    bufferToSend[4]=numberOfBytes;
    bufferToSend[5]=calculateCks(bufferToSend,sizeof(bufferToSend));
    
    
    send(bufferToSend,sizeof(bufferToSend));
    receive();
}



/*
* method to set the application key
*
*@param ptrToData   pointer to the first element/byte of the application key
*@param dataSize    size in bytes of the application key
*/
void click_4::set_app_key(const uint8_t* ptrToData , int dataSize){
    printf("\r\nset app key\r\n");
    //declare local variables
    uint8_t bufferToSend[4+dataSize];
    
    //reset buffer and j
    j = 0;  
    memset(buff, 0x00, sizeof(buff));

    //set dataToSend to module
    bufferToSend[0]=0xAA;
    bufferToSend[1]=0x43;
    bufferToSend[2]=0x10;
    for (int i=3; i<3+dataSize; i++){
            bufferToSend[i]= (uint8_t) *(ptrToData+i-3);
        }
    bufferToSend[3+dataSize]= calculateCks(bufferToSend,sizeof(bufferToSend));
    
    send(bufferToSend,sizeof(bufferToSend));
    receive();
}

/*
* method to set the dataRate for the next transmission
*
*@param dataRate    int to set the dataRate (specified in the datasheet )
*/
void click_4::set_next_dr_cmd(uint8_t dataRate){
    printf("\r\nset next data rate\r\n");
     //declare local variables
    uint8_t bufferToSend[5];
    
    //reset buffer and j
    j = 0;  
    memset(buff, 0x00, sizeof(buff));
    
    bufferToSend[0]=0xAA;
    bufferToSend[1]=0x4B;
    bufferToSend[2]=0x01;
    bufferToSend[3]=dataRate;
    bufferToSend[4]= calculateCks(bufferToSend, sizeof(bufferToSend));
    
    send(bufferToSend,sizeof(bufferToSend));
    receive();   
}

/*
* method to perfom the network join command 
* mode 0 for ABP: activation by personalization
* mode 1 for OTAA: activation over the air
*
*@param mode used to define whether OTAA or ABP will be used as activation mode
*/
void click_4::join_cmd(uint8_t mode){
    printf("\r\njoin cmd\r\n");
    //declare local variables
    uint8_t bufferToSend[5];
    
    //reset buffer and j
    j = 0;  
    memset(buff, 0x00, sizeof(buff));
    
    bufferToSend[0]=0xAA;
    bufferToSend[1]=0x40;
    bufferToSend[2]=0x01;
    bufferToSend[3]=mode;
    bufferToSend[4]=calculateCks(bufferToSend,sizeof(bufferToSend));
    
    send(bufferToSend,sizeof(bufferToSend));
    receive();
}

/*
* method to transmit a radio frame
*
* reliability: 
*   0x00 for unreliable data transmission
*   0x01 for reliable data transmission
*
*@param msgPayload          pointer to first element/byte of the payload
*@param lengthOfPayLoad     lenght in bytes of the payload
*@param reliability         defines whether reliable or unreliable data transmission will be done
*@param port                port to send to (1-223)
*/
void click_4::tx_msg_cmd(uint8_t* msgPayload, uint8_t lengthOfPayload, uint8_t reliability, uint8_t port){
    printf("\r\nsend message\r\n");
    //declare local variables
    uint8_t bufferToSend[6+lengthOfPayload];
    
    //reset buffer and j
    j = 0;  
    memset(buff, 0x00, sizeof(buff));  
    
    bufferToSend[0]=0xAA;
    bufferToSend[1]=0x46;
    bufferToSend[2]=(uint8_t)sizeof(bufferToSend);
    bufferToSend[3]=reliability;
    bufferToSend[4]=port;
    for(int i=5; i<5+lengthOfPayload;i++){
        bufferToSend[i]=*(msgPayload+i-5);
    }
    bufferToSend[5+lengthOfPayload]=calculateCks(bufferToSend,sizeof(bufferToSend));
    
    send(bufferToSend,sizeof(bufferToSend));
    receive();
}

/*
* method to send to module
*
*@param ptrToData           pointer to the first element/byte to send to the module
*@param numberOfElements    number of elements/bytes to send to the module
*/
void click_4::send(uint8_t* ptrToData, int numberOfElements){
     NWAKE.write(0);
     printf("Data to send to module: \r\n");
     for(int i=0; i<=numberOfElements-1; i++){
         printf("%x\r\n",*(ptrToData+i));
     }
     for(int i=0; i<=numberOfElements-1; i++){
         myuart.putc(*(ptrToData+i));
     }
}

/*
* Method to receive an answer from the module
*/
void click_4::receive(){
     while(NDATA_INDICATE.read());
     while(!NDATA_INDICATE.read()){
         buff[j++] = myuart.getc();
     }
    NWAKE.write(1);
    int temp = j;
    printf("\r\nReceived answer:\r\n");
    while(j){
        printf("%x\r\n",buff[temp-(j--)]);
    }
    printf("\r\n");
}
    
/*
* method to calculate a checksum
*
*@param ptrToData           pointer to the first element/byte to calculate the checksum on
*@param numberOfElements    the number of elements/bytes to calculate the checksum on
*/
uint8_t click_4::calculateCks(uint8_t* ptrToData, int numberOfElements){
    int sum=0;
    printf("\r\nCalculateCks:\r\n");
    for(int k=0; k<numberOfElements-1; k++){
        sum=sum+ *(ptrToData+k);
        printf("%2x  sum: %x\r\n",*(ptrToData+k),sum);
        }
    printf("\r\n");
    return (uint8_t)-sum;
}

/*
* method to end a session
*/
void click_4::close(){
    NWAKE.write(1);
    printf("End of session, NWAKE is set to 1\r\n");
}