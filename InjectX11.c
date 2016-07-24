#include <X11/Xlib.h>
//THIS IS UNUSED FOR NOW
typedef int (*XNextEvent_t)(Display *display, XEvent *event_return);
int XNextEvent(Display *display, XEvent *event_return) {
    return 0;
}
