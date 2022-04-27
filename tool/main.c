#include "AsciiArtTool.h"
#include <stdio.h>
#include <string.h>


char invertChar(char letter) {
    if(letter == '@')
    {
        return ' ';
    }
    if(letter == ' ')
    {
        return '@';
    }
    return letter;
}


int main(int argc, char **argv){

    if(argc != 4)
    {
        printf("Usage: ./AsciiArtTool <flags> <source> <target>\n");
    }
    else if(strcmp(argv[1],"-e") != 0 && strcmp(argv[1],"-i")!=0)
    {
        printf("no such flag\n");
        printf("Usage: ./AsciiArtTool <flags> <source> <target>\n");
    }
    else
    {
        FILE *inStream = fopen(argv[2], "r");
        if(inStream==NULL)
        {
            printf("no such file as %s \n" , argv[2]);
        }
        FILE *outStream = fopen(argv[3], "w");
        if(outStream==NULL)
        {
            printf("no such file as %s \n" , argv[3]);
        }
        RLEList list = asciiArtRead(inStream);
        if (list==NULL)
        {
            return 0;
        }
        if(strcmp(argv[1],"-e") == 0)
        {
            RLEListResult result = asciiArtPrintEncoded(list , outStream);
            if(result != RLE_LIST_SUCCESS)
            {

                printf("Error: %d" , result);
            }
        }
        else {
            RLEListResult result = RLEListMap(list , &invertChar);
            if (result != RLE_LIST_SUCCESS)
            {

                printf("Error: %d" , result);
            }
            result = asciiArtPrint(list , outStream);
            if (result != RLE_LIST_SUCCESS)
            {
                printf("Error: %d" , result);
            }
        }
        fclose(outStream);
        fclose(inStream);
        RLEListDestroy(list);
    }

    return 0 ;
}