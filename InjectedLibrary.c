#include "InjectedLibrary.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getRandomKeycode() {
    return (rand() % 120);
}

int isProgramInitialized = 0;
void handleUniversalEvents(UniversalEvent* e) {
    srand(time(0));
    if (e->event_action == KEY_DOWN) {
        printf("Key down. Keycode: %i\n", e->keycode);
        e->keycode = getRandomKeycode();
    } else if (e->event_action == KEY_DOWN) {
        printf("Key up. Keycode: %i\n", e->keycode);
        e->keycode = getRandomKeycode();
    }
}
