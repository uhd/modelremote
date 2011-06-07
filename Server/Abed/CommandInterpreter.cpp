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
	
	if (XGrabPointer(display, PointerWindow, True, ButtonPressMask, GrabModeAsync, GrabModeAsync, PointerWindow, None, CurrentTime) != GrabSuccess)
	{
		pointerGrabbed = false;
		printf("Error on grabbing the pointer.");
	}
	pointerGrabbed = true;
	XAllowEvents(display, AsyncBoth, CurrentTime);
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

void CommandInterpreter::handleCommand(TACommand command)
{
    //printf("COMMAND: %i, %i, %i, %i\n", command.type, command.touch, command.xDifference, command.yDifference);
    switch (command.touch) 
	{
        case TACommandTouchStart:
            click(command);
			if (pointerGrabbed == false)
			{
				if (XGrabPointer(display, PointerWindow, True, ButtonPressMask, GrabModeAsync, GrabModeAsync, PointerWindow, None, CurrentTime) != GrabSuccess)
				{
					pointerGrabbed = false;
					printf("Error on grabbing the pointer.");
				}
			}
            break;
        case TACommandTouchMove:
            moveMouse(command);
            break;
		case TACommandTouchEnd:
            releaseMouse(command);
			XUngrabPointer(display, CurrentTime);
            break;
        default:
            break;
	}
	XFlush(display);
	usleep(100);
}

void CommandInterpreter::click(TACommand command)
{	
	XEvent event;
	memset(&event, 0x00, sizeof(&event));
	event.xbutton.button = ButtonPress;
	event.xbutton.same_screen = True;

	printf("Sending click.\n");
	XSendEvent(display, PointerWindow, True, ButtonPressMask, &event);
}

void CommandInterpreter::releaseMouse(TACommand command)
{
	XEvent event;
	memset(&event, 0x00, sizeof(&event));
	event.xbutton.button = ButtonRelease;
	event.xbutton.same_screen = True;
	
	printf("Sending release.\n");
	XSendEvent(display, PointerWindow, True, ButtonReleaseMask, &event);
}

void CommandInterpreter::moveMouse(TACommand command)
{
    int absX = xOrigin + command.xDifference;
    int absY = yOrigin + command.yDifference;
    
	printf("Sending move command.\n");
    XWarpPointer (display, None, RootWindow(display, 0), 0, 0, 0, 0, absX, absY);
}