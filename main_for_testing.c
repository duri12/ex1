#include "RLEList.h"

int main(){
    RLEList list = RLEListCreate();
    char * str=  "B2\nb2\n-9\n\n3\n";
    RLEListAppend(list,'B');
    RLEListAppend(list,'B');
    RLEListAppend(list,'b');
    RLEListAppend(list,'b');
    for (int i = 0; i < 12; ++i) {
        RLEListAppend(list,'-');
    }
    for (int i = 0; i < 3; ++i) {
        RLEListAppend(list,'\n');
    }


    /*
    for (int i = 0; i < 123; ++i) {
        RLEListAppend(list,'^');
    }
    */
    int result[1];
    char * out = RLEListExportToString(list,result);
    printf("%s",out);


}
