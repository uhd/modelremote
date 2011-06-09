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
	
	rootDisplayWindow = XDefaultRootWindow(display);\
	
	queryResolution();
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
	
	printf("Server Dimensions: %i x %i.\n", xrrs[originalSize].width, xrrs[originalSize].height);
	printf("Adjusted Dimensions: %i x %i.\n", xOrigin, yOrigin);
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
	XSync(display, 0);
	usleep(1);
}

void CommandInterpreter::click(TACommand command)
{	
	if (released == true)
	{
		printf("Attempting to release.\n");
		XTestFakeButtonEvent(display, 1, False, CurrentTime);
		return;
	}
	printf("Attempting to click.\n");
	XTestGrabControl(display, True);
	XEvent event;
	XQueryPointer(display, RootWindow(display, DefaultScreen(display)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
	XTestFakeButtonEvent(display, 1, True, CurrentTime);
}

void CommandInterpreter::releaseMouse(TACommand command)
{
	released = true;
}

void CommandInterpreter::moveMouse(TACommand command)
{
    int absX = xOrigin + command.xDifference;
    int absY = yOrigin + command.yDifference;
	
	printf("Sending move command.\n");
	XTestFakeMotionEvent(display, 0, absX, absY, CurrentTime);
}