#include "RLEList.h"

struct RLEList_t
{
    int count;
    char letter;
    struct RLEList_t* next;
};

RLEList RLEListCreate()
{
    RLEList newList = malloc(sizeof(*newList));
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

static RLEListResult RLEListRemoveWithHeadPointer(RLEList head , RLEList currentNode , RLEList previous ,int index )
{
    if(index < 0 || index >=RLEListSize(head)){
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    if(index == 0 && head->count == 0){
        if(head->next != NULL){
            return RLEListRemoveWithHeadPointer(head->next, head->next,head->next,index);
        }
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    if(index < currentNode->count){
        currentNode->count --;
        if(currentNode->count == 0){
            if(currentNode == head){
                if(currentNode->next != NULL){

                    RLEList temp = currentNode->next;
                    currentNode->letter = currentNode->next->letter;
                    currentNode->count = currentNode->next->count ;
                    currentNode->next = currentNode->next->next;
                    free(temp);
                }
                else{
                    currentNode->letter = '\0';
                }
                return RLE_LIST_SUCCESS;
            }
            if(previous!= NULL && currentNode->next !=NULL&&previous->letter == currentNode->next->letter){
                previous->count += currentNode->next->count;
                previous->next = currentNode->next->next;
                if(currentNode->next != NULL){
                    free(currentNode->next);
                }
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
    if((void *)currentNode == (void *)previous){
        return RLEListRemoveWithHeadPointer(head,currentNode->next,previous , index-currentNode->count);
    }
    return RLEListRemoveWithHeadPointer(head,currentNode->next , previous->next,index-currentNode->count);
}

RLEListResult RLEListRemove(RLEList list, int index){
    if(list == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(index < 0 || index >= RLEListSize(list)){
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    return RLEListRemoveWithHeadPointer(list , list, list , index);
    /*
    int i = 0 ;
    int inNode = 0;
    RLEList temp = list ;
    RLEList before = NULL;
    while(inNode!= index &&  temp != NULL){
        i++;
        inNode++;
        if(inNode == temp->count){
            before = temp;
            temp = temp->next;
            inNode = 0 ;
        }
    }
    temp->count -- ;
    if(temp->count != 0){
        return RLE_LIST_SUCCESS;
    }
    if(before == NULL){
        RLEList nextNode = temp->next;
        if(nextNode == NULL){
            temp->letter = '\0';
        }
        else{
            temp->letter = temp->next->letter;
            temp->count = temp->next->count;
            temp->next = temp->next->next;
            free(nextNode);
        }
    }
    else{
        RLEList tempNext = temp->next ;
        before->next = tempNext;
        free(temp);
        if(tempNext !=NULL && before->letter == tempNext->letter){
            before->count += tempNext->count ;
            before->next = tempNext->next ;
            free(tempNext);
        }
    }
    return RLE_LIST_SUCCESS;
     */

}


char RLEListGet(RLEList list, int index, RLEListResult *result){

    if(list == NULL){
        if (result != NULL){
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return 0 ;
    }
    if(index < 0 || index >= RLEListSize(list)){
        if (result != NULL){
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        return 0 ;
    }

    while(list != NULL && list->count <= index){
        index -=  list->count;
        list = list->next;

    }
    if(index < list->count){
        if(result != NULL){
            *result = RLE_LIST_SUCCESS;
        }
        return list->letter;
    }
    if (result != NULL){
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    return 0 ;

}


RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if (list == NULL || map_function == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(list->count == 0 && list->next ==NULL && list->letter == '\0'){
        return RLE_LIST_SUCCESS;
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
    while(copyNum != 0) {
        copyNum /=10;
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
        int countPower = 0;
        while(firstDigit > 9){
            countPower++;
            firstDigit /=10;
        }
        firstDigit +=(int)'0';
        buffer[0] = (char)firstDigit;
        int power = 1;
        for (int i = 0; i < countPower; ++i) {
            power *= 10;
        }
        intToString(number%power , buffer+1);
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
            str[0] = list->letter;
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