//
//  CommandInterpreter.cpp
//  Abed
//
//  Created by Max Goedjen on 4/10/11.
//  UHD
//

#include "CommandInterpreter.h"
#define CLICK XK_Pointer_Button1
#define DRAG XK_Pointer_Drag1

CommandInterpreter::CommandInterpreter()
{
    display = XOpenDisplay(NULL);
	
	rootDisplayWindow = XDefaultRootWindow(display);
}

void CommandInterpreter::queryResolution()
{
	int numberSizes;
    Rotation originalRotation;
    
    XRRScreenSize *xrrs = XRRSizes(display, 0, &numberSizes);
    
    XRRScreenConfiguration *configuration = XRRGetScreenInfo(display, RootWindow(display, 0));
    SizeID originalSize = XRRConfigCurrentConfiguration(configuration, &originalRotation);
    
    int width = xrrs[originalSize].width;
    int height = xrrs[originalSize].height;
    
    xOrigin = (int)width / 2;
    yOrigin = (int)height / 2;
}

void CommandInterpreter::createPointer(XButtonEvent &event, string type)
{
	if (type == "click")
		event.type = ButtonPress;
	if (type == "release")
		event.type = ButtonRelease;
		
	event.display = display;
	event.window = currentWindow;
	event.root = rootDisplayWindow;
	event.time = CurrentTime;
	event.same_screen = True;
	event.button = Button1;
	event.state = Button1Mask;
}

void CommandInterpreter::handleCommand(TACommand command)
{
    //printf("COMMAND: %i, %i, %i, %i\n", command.type, command.touch, command.xDifference, command.yDifference);
    switch (command.touch) 
	{
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
	XFlush(display);
	usleep(100);
}

void CommandInterpreter::click(TACommand command)
{	
	XButtonEvent event;
	XGetInputFocus(display, &currentWindow, RevertToNone);
	createPointer(event, "click");
	
	XSendEvent(display, event.window, True, ButtonPressMask,(XEvent *) &event);
}

void CommandInterpreter::releaseMouse(TACommand command)
{
	XButtonEvent event;
	XGetInputFocus(display, &currentWindow, RevertToNone);
	createPointer(event, "release");
	
	XSendEvent(display, event.window, True, ButtonPressMask,(XEvent *) &event);
}

void CommandInterpreter::moveMouse(TACommand command)
{
    int absX = xOrigin + command.xDifference;
    int absY = yOrigin + command.yDifference;
    
	printf("Sending move command.\n");
    XWarpPointer (display, None, RootWindow(display, 0), 0, 0, 0, 0, absX, absY);
}