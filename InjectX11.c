#include <X11/Xlib.h>

typedef int (*XNextEvent_t)(Display *display, XEvent *event_return);
int XNextEvent(Display *display, XEvent *event_return) {
    //cause a segfault for the BT
    event_return = 0;
    int i = event_return->type;
    return 0;
}
