//
//  CommandInterpreter.cpp
//  Abed
//
//  Created by Max Goedjen on 4/10/11.
//  UHD
//

#include "CommandInterpreter.h"

CommandInterpreter::CommandInterpreter()
{
    display = XOpenDisplay(NULL);
    
    int numberSizes;
    Rotation originalRotation;
    
    rootWindow = RootWindow(display, 0);
    XRRScreenSize *xrrs = XRRSizes(display, 0, &numberSizes);
    
    XRRScreenConfiguration *configuration = XRRGetScreenInfo(display, rootWindow);
    SizeID originalSize = XRRConfigCurrentConfiguration(configuration, &originalRotation);
    
    int width=xrrs[originalSize].width;
    int height=xrrs[originalSize].height;
    
    xOrigin = (int)width / 2;
    yOrigin = (int)height / 2;
    
}

void CommandInterpreter::handleCommand(TACommand command)
{
    
    //printf("COMMAND: %i, %i, %i, %i\n", command.type, command.touch, command.xDifference, command.yDifference);
    switch (command.touch) {
        case TACommandTouchStart:
            click(command);
            break;
        case TACommandTouchMove:
            moveMouse(command);
            break;
        default:
            break;
    }
}

void CommandInterpreter::click(TACommand command)
{
    XEvent event;
    memset (&event, 0, sizeof (event));
    event.xbutton.button = Button1;
    event.xbutton.same_screen = True;
    event.xbutton.subwindow = DefaultRootWindow (display);
    while (event.xbutton.subwindow)
    {
        event.xbutton.window = event.xbutton.subwindow;
        XQueryPointer (display, event.xbutton.window,
                       &event.xbutton.root, &event.xbutton.subwindow,
                       &event.xbutton.x_root, &event.xbutton.y_root,
                       &event.xbutton.x, &event.xbutton.y,
                       &event.xbutton.state);
    }
    // Press
    event.type = ButtonPress;
    printf("Click Start");
    if (XSendEvent (display, PointerWindow, True, ButtonPressMask, &event) == 0)
        fprintf (stderr, "Error to send the event!\n");
    XFlush (display);
    usleep (1);
    // Release
    event.type = ButtonRelease;
    if (XSendEvent (display, PointerWindow, True, ButtonReleaseMask, &event) == 0)
        fprintf (stderr, "Error to send the event!\n");
    XFlush (display);
    usleep (1);
}

void CommandInterpreter::releaseMouse(TACommand command)
{
    
}

void CommandInterpreter::moveMouse(TACommand command)
{
    
    int absX = xOrigin + command.xDifference;
    int absY = yOrigin + command.yDifference;
    
    
    XWarpPointer (display, None, rootWindow, 0, 0, 0, 0, absX, absY);
    XFlush (display);
    usleep (1);
}