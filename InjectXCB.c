#define _GNU_SOURCE
#include <xcb/xcb.h>
#include <dlfcn.h>
#include <stdio.h>

typedef xcb_generic_event_t* (*xcb_poll_for_event_t)(xcb_connection_t* c);
xcb_generic_event_t* xcb_poll_for_event(xcb_connection_t* c) {
    printf("hooked xcb_poll_for_event\n");
    xcb_poll_for_event_t xcb_poll_for_event_o;
    xcb_poll_for_event_o = (xcb_poll_for_event_t)dlsym(RTLD_NEXT,"xcb_poll_for_event");
    return xcb_poll_for_event_o(c);
}
