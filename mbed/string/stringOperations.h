#include "mbed.h"

/*
    simple string operations
*/

class StringOperations
{
    public:
    
    //Ctor
    StringOperations();
    
    //Dtor
    ~StringOperations();
    
    //functions
    char **split(char* string, char seperator, int *sizeOfSplitStr);
    void removeChar(char* str, char trim);
    int ConvertToInt(char* stringNum);
    
    
};