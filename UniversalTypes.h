#pragma once

typedef enum {
    XCB
} EventSource;

typedef enum {
    KEY_UP,
    KEY_DOWN
} EventAction;

typedef struct UniversalKeyboardEvent {
    EventAction event_action;
    unsigned int keycode;
} UniversalKeyboardEvent;
