#define _GNU_SOURCE
#include <xcb/xcb.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include "UniversalTypes.h"
#include "InjectedLibrary.h"

typedef xcb_generic_event_t* (*xcb_poll_for_event_t)(xcb_connection_t* c);
int xcbApplicationIsReady = 0;
xcb_generic_event_t* preInitLoop(xcb_poll_for_event_t f, xcb_connection_t* c) {
    xcb_generic_event_t* returnEvent = f(c);
    //if "r" is pressed,
    //begin normal processing of events
    if (returnEvent != 0) {
        if (returnEvent->response_type == XCB_KEY_PRESS) {
            if (((xcb_key_press_event_t*)returnEvent)->detail == 27) {
                xcbApplicationIsReady = 1;
            }
        }
    }
    return 0;
}

xcb_generic_event_t* xcb_poll_for_event(xcb_connection_t* c) {
    //cause a segfault
    xcb_generic_event_t* e = 0;
    int i = e->response_type;
    //end the segfault
    xcb_poll_for_event_t xcb_poll_for_event_o;
    xcb_poll_for_event_o = (xcb_poll_for_event_t)dlsym(RTLD_NEXT,"xcb_poll_for_event");
    //begin the loop waiting for the application to ready
    if (!xcbApplicationIsReady) {
        return preInitLoop(xcb_poll_for_event_o, c);
    } else {
        //once the application is ready, begin normal processing
        xcb_generic_event_t* returnEvent = xcb_poll_for_event_o(c);
        //decode XCB's event into my universal event
        UniversalEvent* myEvent = (UniversalEvent*)malloc(sizeof(UniversalEvent));
        if (returnEvent != 0) {
            //https://xcb.freedesktop.org/tutorial/events/
            if (returnEvent->response_type == XCB_KEY_PRESS) {
                myEvent->event_action = KEY_DOWN;
                myEvent->keycode = ((xcb_key_press_event_t*)returnEvent)->detail;
                //modify my universal event
                handleUniversalEvents(myEvent);
                //repopulate the XCB event
                ((xcb_key_release_event_t*)returnEvent)->detail = myEvent->keycode;
            } else if (returnEvent->response_type == XCB_KEY_RELEASE){
                myEvent->event_action = KEY_UP;
                myEvent->keycode = ((xcb_key_release_event_t*)returnEvent)->detail;
                //modify my universal event
                handleUniversalEvents(myEvent);
                //repopulate the XCB event
                ((xcb_key_release_event_t*)returnEvent)->detail = myEvent->keycode;
            } else {
                myEvent->event_action = UNKNOWN;
            }
        }
        free(myEvent);
        return returnEvent;
    }
}
