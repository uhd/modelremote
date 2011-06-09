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
	
	clicked = false;
	zooming = false;
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
	XTestGrabControl(display, True);

    printf("COMMAND: %i, %i, %i, %i, %f\n", command.type, command.touch, command.xDifference, command.yDifference, command.zoomValue);
	switch(command.type)
	{
		case TACommandTypeRotate:
			switch(command.touch) 
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
			break;
		case TACommandTypeZoom:
			zoom(command);
			break;
		case TACommandTypePan:
			//pan();
			break;
	}
	XSync(display, 0);
	XTestGrabControl(display, False);
	usleep(1);
}

void CommandInterpreter::click(TACommand command)
{	
	if (clicked == true)
		return;

	XEvent event;
	XQueryPointer(display, RootWindow(display, DefaultScreen(display)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
	XTestFakeButtonEvent(display, 1, True, CurrentTime);
	
	clicked = true;
}

void CommandInterpreter::releaseMouse(TACommand command)
{
	if (clicked == true)
	{
		XTestFakeButtonEvent(display, 1, False, CurrentTime);
		clicked = false;
	}
}

void CommandInterpreter::moveMouse(TACommand command)
{
	XEvent event;
	XQueryPointer(display, RootWindow(display, DefaultScreen(display)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
    
	int absX = xOrigin + command.xDifference;
    int absY = yOrigin + command.yDifference;
	
	if (command.zoomValue != 0)
	{
		if (command.zoomValue > 1.0)
		{
			XTestFakeMotionEvent(display, 0, absX, (absY + 10), CurrentTime);
		}
	
		if (command.zoomValue < 1.0)
		{
			XTestFakeMotionEvent(display, 0, absX, (absY - 10), CurrentTime);
		}
		return;
	}
	
	XTestFakeMotionEvent(display, 0, absX, absY, CurrentTime);
}

void CommandInterpreter::zoom(TACommand command)
{
	XEvent event;
	XQueryPointer(display, RootWindow(display, DefaultScreen(display)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);

	if ((command.zoomValue == -1.000000) || (zooming == true))
	{
		XTestFakeButtonEvent(display, 3, False, CurrentTime);
		zooming = false;
	}
	
	if (command.zoomValue != 0)
	{
		XTestFakeButtonEvent(display, 3, True, CurrentTime);
		zooming = true;
	}
}