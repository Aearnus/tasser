#include "InjectedLibrary.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void handleUniversalEvents(UniversalEvent* e) {
    if (e->event_action == KEY_DOWN) {
        printf("Key down. Keycode: %i\n", e->keycode);
    } else if (e->event_action == KEY_DOWN) {
        printf("Key up. Keycode: %i\n", e->keycode);
    }
}
