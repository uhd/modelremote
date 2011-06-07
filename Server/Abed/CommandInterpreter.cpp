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
    
    XRRScreenSize *xrrs = XRRSizes(display, 0, &numberSizes);
    
    XRRScreenConfiguration *configuration = XRRGetScreenInfo(display, RootWindow(display, 0));
    SizeID originalSize = XRRConfigCurrentConfiguration(configuration, &originalRotation);
    
    int width=xrrs[originalSize].width;
    int height=xrrs[originalSize].height;
    
    xOrigin = (int)width / 4;
    yOrigin = (int)height / 4;
		
	memset(&event, 0x00, sizeof(event));
}

void CommandInterpreter::handleCommand(TACommand command)
{
    printf("COMMAND: %i, %i, %i, %i\n", command.type, command.touch, command.xDifference, command.yDifference);
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
}

void CommandInterpreter::click(TACommand command)
{	
	cout<<"Attempting to click."<<endl;
	event.xbutton.button = Button1;
	event.type = ButtonPress;
	event.xbutton.state = 0x100;

	XGrabPointer(display, RootWindow(display, 0), True, ButtonPressMask, GrabModeAsync, GrabModeAsync, RootWindow(display, 0), True, CurrentTime);
	
	XSelectInput(display, RootWindow(display, 0), Button1);
	XSendEvent(display, RootWindow(display, 0), True, ButtonPressMask, &event);
		
	XFlush(display);
	usleep(100);
}

void CommandInterpreter::releaseMouse(TACommand command)
{	
	cout<<"Attempting to release."<<endl;
	event.xbutton.button = Button1;
	event.type = ButtonRelease;
	event.xbutton.state = 0x0;
	
	XGrabPointer(display, RootWindow(display, 0), True, ButtonReleaseMask, GrabModeAsync, GrabModeAsync, RootWindow(display, 0), True, CurrentTime);
	
	XSelectInput(display, RootWindow(display, 0), Button1);
	XSendEvent(display, RootWindow(display, 0), True, ButtonReleaseMask, &event);
	
	XUngrabPointer(display, CurrentTime);
				
	XFlush(display);
	usleep(100);
	
}

void CommandInterpreter::moveMouse(TACommand command)
{
	cout<<"Attempting to move the mouse."<<endl;
    int absX = xOrigin + command.xDifference;
    int absY = yOrigin + command.yDifference;
    
    XWarpPointer (display, None, RootWindow(display, 0), 0, 0, 0, 0, absX, absY);
    XFlush (display);
	usleep(100);
}