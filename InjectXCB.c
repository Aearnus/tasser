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

//keep polling for events until you get a keyboard event
//once you do, return control to application for a frame
xcb_generic_event_t* mainHookLoop(xcb_poll_for_event_t f, xcb_connection_t* c) {
    for (;;) {
        xcb_generic_event_t* returnEvent = f(c);
        //if an event is returned
        if (returnEvent != 0) {
            //if the event is a key press
            if (returnEvent->response_type == XCB_KEY_PRESS) {
                //close the loop, we done here
                return returnEvent;
            }
        }
    }
}

xcb_generic_event_t* xcb_poll_for_event(xcb_connection_t* c) {
    xcb_poll_for_event_t xcb_poll_for_event_o;
    xcb_poll_for_event_o = (xcb_poll_for_event_t)dlsym(RTLD_NEXT,"xcb_poll_for_event");
    //begin the loop waiting for the application to ready
    if (!xcbApplicationIsReady) {
        return preInitLoop(xcb_poll_for_event_o, c);
    } else {
        //once the application is ready, begin normal processing
        //this call BLOCKS until input is recieved
        xcb_generic_event_t* returnEvent = mainHookLoop(xcb_poll_for_event_o, c);
        //create myEvent for population with XCB event data
        UniversalEvent* myEvent = (UniversalEvent*)malloc(sizeof(UniversalEvent));
        //https://xcb.freedesktop.org/tutorial/events/
        if (returnEvent->response_type == XCB_KEY_PRESS) {
            myEvent->event_action = KEY_DOWN;
            myEvent->keycode = ((xcb_key_press_event_t*)returnEvent)->detail;
            //modify my universal event
            handleUniversalEvents(myEvent);
            //repopulate the XCB event
            ((xcb_key_release_event_t*)returnEvent)->detail = myEvent->keycode;
        } else if (returnEvent->response_type == XCB_KEY_RELEASE) {
            //all same as above
            myEvent->event_action = KEY_UP;
            myEvent->keycode = ((xcb_key_release_event_t*)returnEvent)->detail;
            handleUniversalEvents(myEvent);
            ((xcb_key_release_event_t*)returnEvent)->detail = myEvent->keycode;
        } else {
            myEvent->event_action = UNKNOWN;
        }
        free(myEvent);
        return returnEvent;
    }
}
