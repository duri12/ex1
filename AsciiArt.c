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

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream) {
    if(out_stream==NULL) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult* result = malloc(sizeof(RLEListResult));
    char* str = RLEListExportToString(list, result);
    for(int i=0; i< RLEListSize(list); i++) {
        fprintf(out_stream, RLEListGet(list, i, result));
    }
    return result;
}
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream) {
    RLEListResult* result = malloc(sizeof(RLEListResult));
    char* str = RLEListExportToString(list, result);
    if(result==NULL) {
        return result;
    }
    fprintf(out_stream, str);
    return result;
}
