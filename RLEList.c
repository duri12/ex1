#include "RLEList.h"

struct RLEList_t
{
    int count;
    char letter;
    struct RLEList_t* node;
};
//TODO: fix count not letter
//implement the functions here
RLEList RLEListCreate()
{
    RLEList newList = malloc(sizeof(RLEList));
    if (newList == NULL){
        return NULL;
    }
    newList->count = 0 ;
    newList->letter = '\0';
    newList->node = NULL;
    return newList;
}


void RLEListDestroy(RLEList list)
{
    if (list == NULL){
        return;
    }
    RLEListDestroy(list->node);
    free(list);
}

//hi i
RLEListResult RLEListAppend(RLEList list, char value)
{
    if (list == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(list->node == NULL){
        RLEList newNode = RLEListCreate();
        if(newNode == NULL){
            return RLE_LIST_OUT_OF_MEMORY;
        }
        newNode->letter = value;
        newNode->count = 1;
        list->node = newNode;
        return RLE_LIST_SUCCESS
    }
    return RLEListAppend(list->node, value);
}


int RLEListSize(RLEList list)
{
    if(list == NULL){
        return -1;
    }
    if (list->node == NULL){
        return list->count;
    }
    return list->count + RLEListSize(list->node);
}

RLEListResult RLEListRemove(RLEList list, int index){
    if(list == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(index < list->count){
        list->count --;
        return RLE_LIST_SUCCESS;
    }
    if(list->node == NULL){
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    return RLEListRemove(list->node,index-list->count);
}

char RLEListGet(RLEList list, int index, RLEListResult *result){
    if(list == NULL){
        if (result != NULL){
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return 0 ;
    }
    if (list->letter=='\0'){
        return RLEListGet(list->node,index,result);
    }
    if(index < list->count){
        if(result != NULL){
            *result = RLE_LIST_SUCCESS;
        }
        return list->letter;
    }
    if(list->node == NULL){
        if (result != NULL){
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        return 0 ;
    }
    return RLEListGet(list->node,index-list->count , result );
}

char* RLEListExportToString(RLEList list, RLEListResult* result){ // TODO:!!!!!!!!!!!
    if (list == NULL){
        if (result != NULL){
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return NULL;
    }
    if(list->letter == '\0'){
        return  RLEListExportToString(list->node , result);
    }
    for (int i = 0; i < list->count; i++) {

    }
    if(list->node == NULL){

    }
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if (list == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(list->letter == '\0'){
        return RLEListMap(list->node , map_function);
    }
    list->letter = map_function(list->letter);
    if(list->node == NULL){
        return RLE_LIST_SUCCESS;
    }
    return  RLEListMap(list->node , map_function);
}
int countNodes(RLEList list) {
    int count=0;
    while(list!=null) {
        if(list->count!=0) {
            count++;
        }
        list = list->node;
    }
    return count;
}
int countSpaceForNumbers(RLEList list) {
    int copyNum;
    int count=0;
    while(list!=null) {
        count += countSpaceForSpecificNumber(list);
        list = list->node;
    }
    return count;
}
int countSpaceForSpecificNumber(RLEList list) {
    int count=0;
    int copyNum = list->count;
    while(copynum!=0) {
        copyNum = copyNum/10;
        count++;
    }
    return count;
}
char* RLEListExportToString(RLEList list, RLEListResult* result) {
    if(list==NULL) {
        if(result != NULL){
            *result =  RLE_LIST_NULL_ARGUMENT;
        }
        return NULL;
    }
    char* str = (char*)(malloc(sizeof(char)* countNodes(list)*2+countSpaceForNumers(list)+1));
    if(str == null){
        *result = RLE_LIST_OUT_OF_MEMORY;
    }
    char* savePtrStr = str;
    while(list!=null) {
        if(list->count!=0) {
            *str = list->letter;
            str++;
            itoa(list->count,str,10);
            str += countSpaceForSpecificNumber(list);
            *str = '\n';
            str++;
        }
        list = list->node;
    }
    *str = '\0';
    *result = RLE_LIST_SUCCESS;
    return savePtrStr;
}