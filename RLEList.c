#include "RLEList.h"

struct RLEList_t
{
    int count;
    char letter;
    struct RLEList_t* node;
};

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

RLEListResult RLEListAppend(RLEList list, char value)
{
    RLEList newNode = RLEListCreate();
    newNode->letter = value;
    newNode->count = 1;
    list->node = newNode;
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
            *result = RLE_LIST_NULL_ARGUMENT
        }
        return 0 ;
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

char* RLEListExportToString(RLEList list, RLEListResult* result){

}

RLEListResult RLEListMap(RLEList list, MapFunction map_function){

}