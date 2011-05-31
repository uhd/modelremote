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
        case TACommandTouchStart:
            click(command);
            break;
        case TACommandTouchMove:
            moveMouse(command);
            break;
        case TACommandTouchEnd:
            releaseMouse(command);
            break;
        default:
            break;
    }
}

void CommandInterpreter::click(TACommand command)
{
	XEvent event;
	memset (&event, 0, sizeof(event));
	
	//Establishes this function to only do clicking.
	event.type = ButtonPress;
	event.xbutton.button = Button2;
	event.xbutton.same_screen = True;
	
	//Grabs first pointer window.
	XQueryPointer (display, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);	
	event.xbutton.subwindow = event.xbutton.window;
	
	//Repeats and updates the event window.
	while (event.xbutton.subwindow)
    {
        event.xbutton.window = event.xbutton.subwindow;
		XQueryPointer (display, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);	
    }
	
	event.
	
	XFlush(display);
	usleep(10);
}

void CommandInterpreter::releaseMouse(TACommand command)
{
	XEvent event;
	memset (&event, 0, sizeof(event));

	//Establishes this function to only do releasing.
	event.type = ButtonRelease;
	event.xbutton.button = Button2;
	event.xbutton.same_screen = True;
	
	//Grabs first pointer window.
	XQueryPointer (display, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);	
	event.xbutton.subwindow = event.xbutton.window;
	
	//Repeats and updates the event window.
	while (event.xbutton.subwindow)
    {
        event.xbutton.window = event.xbutton.subwindow;
		XQueryPointer (display, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);	
    }
	
	XFlush(display);
	usleep(10);}

void CommandInterpreter::moveMouse(TACommand command)
{
    
    int absX = xOrigin + command.xDifference;
    int absY = yOrigin + command.yDifference;
    
    XWarpPointer (display, None, rootWindow, 0, 0, 0, 0, absX, absY);
    XFlush (display);
    usleep (10);
}