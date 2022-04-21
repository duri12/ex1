#include "RLEList.h"

struct RLEList_t
{
    int count;
    char letter;
    struct RLEList_t* next;
};

RLEList RLEListCreate()
{
    RLEList newList = malloc(sizeof(RLEList));
    if (newList == NULL){
        return NULL;
    }
    newList->count = 0 ;
    newList->letter = '\0';
    newList->next = NULL;
    return newList;
}


void RLEListDestroy(RLEList list)
{
    if (list == NULL){
        return;
    }
    RLEListDestroy(list->next);
    free(list);
}


RLEListResult RLEListAppend(RLEList list, char value)
{
    if (list == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(list->next == NULL){
        if(list->count == 0 && list->letter=='\0'){
            list->letter =value;
            list->count = 1;
            return RLE_LIST_SUCCESS;
        }
        if(list->letter == value){
            list->count ++ ;
            return RLE_LIST_SUCCESS;
        }
        RLEList newNode = RLEListCreate();
        if(newNode == NULL){
            return RLE_LIST_OUT_OF_MEMORY;
        }
        newNode->letter = value;
        newNode->count = 1;
        list->next = newNode;
        return RLE_LIST_SUCCESS;
    }
    return RLEListAppend(list->next, value);
}


int RLEListSize(RLEList list)
{
    if(list == NULL){
        return -1;
    }
    if (list->next == NULL){
        return list->count;
    }
    return list->count + RLEListSize(list->next);
}

static RLEList RLEListFindPrevious(RLEList current, RLEList target)
{
    if(current->next == NULL){
        return NULL;
    }
    if(current->next == target){
        return current;
    }
    return RLEListFindPrevious(current->next , target);
}

static RLEListResult RLEListRemoveWithHeadPointer(RLEList head , RLEList currentNode ,int index )
{
    if(index < currentNode->count){
        currentNode->count --;
        if(currentNode->count == 0){
            if(currentNode == head){
                currentNode->letter = '\0';
                return RLE_LIST_SUCCESS;
            }
            RLEList previous = RLEListFindPrevious(head , currentNode);
            if(previous!= NULL &&previous->letter == currentNode->next->letter){
                previous->count += currentNode->next->count;
                previous->next = currentNode->next->next;
                free(currentNode->next);
                free(currentNode);
            }
            else if (previous!=NULL)
            {
                previous->next = currentNode->next;
                free(currentNode);
            }
        }
        return RLE_LIST_SUCCESS;
    }
    if(currentNode->next == NULL){
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    return RLEListRemoveWithHeadPointer(head,currentNode->next,index-currentNode->count);
}

RLEListResult RLEListRemove(RLEList list, int index){
    if(list == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(index < 0){
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    return RLEListRemoveWithHeadPointer(list , list , index);
}

char RLEListGet(RLEList list, int index, RLEListResult *result){
    if(list == NULL){
        if (result != NULL){
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return 0 ;
    }

    if (list->count == 0 ){
        return RLEListGet(list->next,index,result);
    }
    if(index < list->count){
        if(result != NULL){
            *result = RLE_LIST_SUCCESS;
        }
        return list->letter;
    }
    if(list->next == NULL){
        if (result != NULL){
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        return 0 ;
    }

    return RLEListGet(list->next,index-list->count , result );
}


RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if (list == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(list->count==0){
        return RLEListMap(list->next , map_function);
    }
    list->letter = map_function(list->letter);
    if(list->next == NULL){
        return RLE_LIST_SUCCESS;
    }
    return  RLEListMap(list->next , map_function);
}
static int countNodes(RLEList list) {
    int count=0;
    while(list!=NULL) {
        if(list->count!=0) {
            count++;
        }
        list = list->next;
    }
    return count;
}

static int countSpaceForSpecificNumber(RLEList list) {
    int count=0;
    int copyNum = list->count;
    while(copyNum!=0) {
        copyNum = copyNum/10;
        count++;
    }
    return count;
}

static void intToString(int number , char* buffer){
    if(number <9){
        number +=(int)'0';
        buffer[0] = (char)number;
    }
    else{
        int firstDigit = number ;
        while(firstDigit > 9){
            firstDigit /=10;
        }
        firstDigit +=(int)'0';
        buffer[0] = (char)firstDigit;
        intToString(number/10, buffer ++);
    }
}


static int countSpaceForNumbers(RLEList list) {
    int count=0;
    while(list!=NULL) {
        count += countSpaceForSpecificNumber(list);
        list = list->next;
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
    int sizeOfMemory = sizeof(char)* countNodes(list)*2+countSpaceForNumbers(list)+1;
    char* str = (char*)(malloc(sizeOfMemory));
    if(str == NULL){
        *result = RLE_LIST_OUT_OF_MEMORY;
    }
    char* savePtrStr = str;
    while(list!=NULL) {
        if(list->count!=0) {
            *str = list->letter;
            str++;
            intToString(list->count,str);
            str += countSpaceForSpecificNumber(list);
            *str = '\n';
            str++;
        }
        list = list->next;
    }
    *str = '\0';
    *result = RLE_LIST_SUCCESS;
    return savePtrStr;
}