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
    
    xOrigin = (int)width / 4;
    yOrigin = (int)height / 4;
}

void CommandInterpreter::handleCommand(TACommand command)
{
    
    printf("COMMAND: %i, %i, %i, %i\n", command.type, command.touch, command.xDifference, command.yDifference);
    switch (command.touch) {
        case 0:
            click(command);
            break;
        case 1:
            moveMouse(command);
            break;
        case 2:
            releaseMouse(command);
            break;
        default:
            break;
    }
}

void CommandInterpreter::click(TACommand command)
{	
	memset(&event, 0x00, sizeof(event));
	event.xbutton.button = Button1;
	event.xbutton.same_screen = True;	
	XSelectInput(display, PointerWindow, ButtonPressMask | ButtonReleaseMask);

	event.type = ButtonPress;
	
	XQueryPointer(display, RootWindow(display, DefaultScreen(display)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
	event.xbutton.subwindow = event.xbutton.window;
	
	XSelectInput(display, PointerWindow, ButtonPressMask | ButtonReleaseMask);
	
	XSendEvent(display, PointerWindow, True, 0xfff, &event); 
	
	XFlush(display);
	usleep(1);
}

void CommandInterpreter::releaseMouse(TACommand command)
{	
	memset(&event, 0x00, sizeof(event));
	event.xbutton.button = Button1;
	event.xbutton.same_screen = True;
	XSelectInput(display, PointerWindow, ButtonPressMask | ButtonReleaseMask);

	event.type = ButtonRelease;
	
	XQueryPointer(display, RootWindow(display, DefaultScreen(display)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
	event.xbutton.subwindow = event.xbutton.window;	
	
	
	XSendEvent(display, PointerWindow, True, 0xfff, &event); 	
	
	XFlush(display);
	usleep(1);
}

void CommandInterpreter::moveMouse(TACommand command)
{
    
    int absX = xOrigin + command.xDifference;
    int absY = yOrigin + command.yDifference;
    
    XWarpPointer (display, None, rootWindow, 0, 0, 0, 0, absX, absY);
    XFlush (display);
    usleep (1);
}