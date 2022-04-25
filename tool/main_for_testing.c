#include "../RLEList.h"

int main(){
    RLEList list = RLEListCreate();
    RLEListAppend(list,'0');
    for (int i = 0; i < 12; ++i) {
        RLEListAppend(list,'_');
    }
    RLEListAppend(list,'1');
    int result[1];
    char* test = RLEListExportToString(list,result);
    RLEListDestroy(list);
}