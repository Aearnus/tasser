#pragma once

typedef enum {
    XCB
} EventSource;

typedef enum {
    KEY_UP,
    KEY_DOWN,
    UNKNOWN
} EventAction;

typedef struct UniversalEvent {
    EventAction event_action;
    unsigned int keycode;
} UniversalEvent;
