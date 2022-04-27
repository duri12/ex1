#include "RLEList.h"
#include <stdlib.h>


RLEList asciiArtRead(FILE* in_stream){
    if(in_stream==NULL)
    {
        return NULL;
    }
    RLEList list =RLEListCreate();
    if(list==NULL)
    {
        return list;
    }
    char letter ;
    while(fscanf(in_stream, "%c",&letter)!= EOF)
    {
        if(RLEListAppend(list,letter) != RLE_LIST_SUCCESS)
        {
            return NULL;
        }
    }
    return list;
}

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream) {
    if(out_stream==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult* result = malloc(sizeof(RLEListResult));
    if(result==NULL)
    {
        return RLE_LIST_OUT_OF_MEMORY;
    }
    int length = RLEListSize(list);
    if(length==0)
    {
        free(result);
        return RLE_LIST_NULL_ARGUMENT;
    }
    for(int i=0; i< length ; i++)
    {
        if(fprintf(out_stream, "%c" ,RLEListGet(list, i, result))<0)
        {

            free(result);
            return RLE_LIST_ERROR;
        }
        if(*result != RLE_LIST_SUCCESS)
        {

            RLEListResult resultValue = *result;
            free(result);
            return resultValue;
        }
    }
    RLEListResult resultValue = *result;
    free(result);

    return resultValue;
}
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream) {
    if(out_stream==NULL || list==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult* result = malloc(sizeof(RLEListResult));
    if(result==NULL)
    {
        return RLE_LIST_OUT_OF_MEMORY;
    }
    char* str = RLEListExportToString(list, result);
    if(fprintf(out_stream, "%s" , str)<0)
    {
        free(result);
        free(str);
        return RLE_LIST_ERROR;
    }
    RLEListResult resultValue = *result;
    free(result);
    free(str);
    return resultValue;
}
