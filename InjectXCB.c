#define _GNU_SOURCE
#include <xcb/xcb.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include "UniversalTypes.h"
#include "InjectedLibrary.h"

typedef xcb_generic_event_t* (*xcb_poll_for_event_t)(xcb_connection_t* c);
xcb_generic_event_t* xcb_poll_for_event(xcb_connection_t* c) {
    xcb_poll_for_event_t xcb_poll_for_event_o;
    xcb_poll_for_event_o = (xcb_poll_for_event_t)dlsym(RTLD_NEXT,"xcb_poll_for_event");
    xcb_generic_event_t* returnEvent = xcb_poll_for_event_o(c);
    UniversalKeyboardEvent* myEvent = (UniversalKeyboardEvent*)malloc(sizeof(UniversalKeyboardEvent));
    if (returnEvent != 0) {
        //https://xcb.freedesktop.org/tutorial/events/
        if (returnEvent->response_type == XCB_KEY_PRESS) {
            myEvent->event_action = KEY_DOWN;
            myEvent->keycode = ((xcb_key_press_event_t*)returnEvent)->detail;
        } else if (returnEvent->response_type == XCB_KEY_RELEASE){
            myEvent->event_action = KEY_UP;
            myEvent->keycode = ((xcb_key_release_event_t*)returnEvent)->detail;
        } else {
            myEvent = 0;
        }
    }
    handleUniversalEvents(myEvent);
    free(myEvent);
    return returnEvent;
}
