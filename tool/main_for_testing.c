#include "../RLEList.h"

int main(){
    RLEList list = RLEListCreate();
    char * str=  "B2\nb2\n-9\n\n3\n";


    for (int i = 0; i < 123; ++i) {
        RLEListAppend(list,'^');
    }

    int result[1];
    char * out = RLEListExportToString(list,result);
    printf("%s",out);


}