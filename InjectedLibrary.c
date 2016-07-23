#include "InjectedLibrary.h"
#include <stdio.h>

void handleUniversalEvents(UniversalKeyboardEvent* e) {
    if (e == 0) {
    } else {
        printf("Got nonzero event\n");
    }
}
