#include "RLEList.h"

RLEList asciiArtRead(FILE* in_stream){
    if(in_stream==NULL){
        return NULL;
    }
    RLEList list =RLEListCreate();
    char letter ;
    while(fscanf(in_stream, "%c",&letter)){
        RLEListAppend(list,letter);
    }
    return list;
}

