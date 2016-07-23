//http://cs.lmu.edu/~ray/notes/x/
/*****************************************************************************
*
*  This is a sample  X11 program which uses  Xlib calls only (no toolkit!).
*  It just writes to the console the events that the window receives.
*
*****************************************************************************/

#include <X11/Xlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
  Display* display = XOpenDisplay(NULL);
  Window window = XCreateSimpleWindow(
    display, XDefaultRootWindow(display),
    100, 100, 200, 200, 4, 0, 0);
  XEvent event;

  XMapWindow(display, window);
  XSelectInput(display, window, KeyPressMask | ButtonPressMask | ExposureMask);

  while (True) {
    XNextEvent(display, &event);
    printf("%d\n", event.type);
  }

  return 0;
}
