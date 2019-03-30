#include "stringOperations.h"

// information about StringOperations => stringOperations.h!

StringOperations::StringOperations()
{
}
    
StringOperations::~StringOperations()
{
}

char** StringOperations::split(char* string, char seperator, int *sizeOfSplitStr)
{
    //count the saperators in the stirng
    //and get length of string
    int length = 0;
    int count = 0;
    while (string[length] != '\0')
    {
        if (string[length] == seperator)
            count++;
        length++;
    }

    if(string[0] != seperator)
        count++; // give a extra count sow we can reach the last value, only when seperator is not in the begining!

    // give a refrence to the size
    *sizeOfSplitStr = count;

    // make a string array with malloc
    // add string to array
    char** result;
    result = (char**)malloc(sizeof(char*) * count);
    if(result != NULL)
    {
        int k = 0;
        for (int i = 0; i < count; i++)
        {
            result[i] = (char *)malloc((100) * sizeof(char));
            if(result[i] == NULL)
                break; // stop the operation
            int j = 0;
    
            if (string[k] == seperator)
                k++;
    
            while (string[k] != seperator)
            {
                if (string[k] == '\0') // break when you reach the end of the string!
                    break;
                result[i][j] = string[k];
                k++;
                j++;
            }
            result[i][j] = '\0';
        }
    
        //debug
        /*
        for (int t = 0; t < count; t++)
        {
            printf("=> %s\n\r", result[t]);
        }
        */
    }
    return result;
}
void StringOperations::removeChar(char* str, char trim)
{
    int i = 0;
    int k = 0;
    while(str[i] != '\0')
    {
        if(str[i] == trim)
        {
            k++;
        }
        
        str[i] = str[i+k];
        
        i++;    
    }
    
    str[i-k] = '\0';
}
int StringOperations::ConvertToInt(char* stringNum)
{
    int result = 0;
    int decimal = 1;
    
    //count chars in string
    int length = 0;
    while (stringNum[length] != '\0')
        length++;

    //convert string to int
    for (int i = length-1; i >= 0; i--)
    {
        switch (stringNum[i])
        {
        case '-':
                result = result * -1;
            break;
        default:
            result += decimal * ((int)stringNum[i] - 48);
            decimal = decimal * 10;
            break;
        }
    }

    return result;    
}