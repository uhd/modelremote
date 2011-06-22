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
	queryResolution();
}

void CommandInterpreter::queryResolution()
{
	int numberSizes;
    Rotation originalRotation;
    
    XRRScreenSize *xrrs = XRRSizes(display, 0, &numberSizes);
    
    XRRScreenConfiguration *configuration = XRRGetScreenInfo(display, RootWindow(display, 0));
    SizeID originalSize = XRRConfigCurrentConfiguration(configuration, &originalRotation);
    
    displayXResolution = xrrs[originalSize].width;
    displayYResolution = xrrs[originalSize].height;
    
    xOrigin = displayXResolution / 2;
    yOrigin = displayYResolution / 2;
	
	printf("Server Dimensions: %i x %i.\n", displayXResolution, displayYResolution);
	printf("Origin of Screen %i: (%i, %i).\n", DefaultScreen(display), xOrigin, yOrigin);
}


void CommandInterpreter::handleCommand(TACommand command)
{
	XTestGrabControl(display, True);

    printf("COMMAND: %i, %i, %i, %i, %f\n", command.type, command.touch, command.xDifference, command.yDifference, command.zoomValue);
	switch(command.type)
	{		
		case TACommandTypeZoom:
			zoom(command);
			break;
		case TACommandTypePan:
			pan(command);
			break;
		case TACommandTypeRotate:
			rotate(command);
			break;
		default:
		break;
	}
	
	XSync(display, 0);
	
	XTestGrabControl(display, False);
	usleep(100);
}

void CommandInterpreter::moveMouse(TACommand command)
{
    int scale = 1;
    
	int absX = (xOrigin + command.xDifference) / scale;
    int absY = (yOrigin + command.yDifference) / scale;
    
	XTestFakeMotionEvent(display, 0, absX, absY, CurrentTime);
}

void CommandInterpreter::rotate(TACommand command)
{	
	if (lastEvent != TACommandTypeRotate)		
		cancel(lastEvent, command.type);
    
    if (checkBounds() == false)
    {
        cancel(lastEvent, command.type);
        printf("Went past bounds.\n");
        return;
    }
	    
	switch (command.touch)
	{
		case TACommandTouchStart:
			lastEvent = TACommandTypeRotate;
			XTestFakeButtonEvent(display, 1, True, CurrentTime);
		break;
		case TACommandTouchMove:
			moveMouse(command);
		break;
		case TACommandTouchEnd:
			XTestFakeButtonEvent(display, 1, False, CurrentTime);
			lastEvent = NULL;
		break;
		default:
		break;
	}
}

void CommandInterpreter::zoom(TACommand command)
{
	int threshold = 20;
	
	if (lastEvent != TACommandTypeZoom)
		cancel(lastEvent, command.type);
    
    if (checkBounds() == false)
    {
        cancel(lastEvent, command.type);
        printf("Went past bounds.\n");
        return;
    }
    
	switch (command.touch)
	{
		case TACommandTouchStart:
			lastEvent = TACommandTypeZoom;
			XTestFakeButtonEvent(display, 3, True, CurrentTime);
            XTestFakeMotionEvent(display, 0, xOrigin, yOrigin, CurrentTime);
		break;
		case TACommandTouchMove:
		{
			if (command.zoomValue > 1.0)
				XTestFakeRelativeMotionEvent(display, 0, threshold, CurrentTime);
			if (command.zoomValue < 1.0)
				XTestFakeRelativeMotionEvent(display, 0, (-1 * threshold), CurrentTime);
		}
		break;
		case TACommandTouchEnd:
		{
			XTestFakeButtonEvent(display, 3, False, CurrentTime);
            XTestFakeMotionEvent(display, 0, xOrigin, yOrigin, CurrentTime);
			lastEvent = NULL;
		}
		break;
		default:
		break;
	}
}

void CommandInterpreter::pan(TACommand command)
{
	if (lastEvent != TACommandTypePan)
		cancel(lastEvent, command.type);
    
    
    if (checkBounds() == false)
    {
        cancel(lastEvent, command.type);
        printf("Went past bounds.\n");
        return;
    }
		    
	switch (command.touch)
	{
		case TACommandTouchStart:
			lastEvent = TACommandTypePan;
			XTestFakeButtonEvent(display, 2, True, CurrentTime);
            XTestFakeMotionEvent(display, 0, xOrigin, yOrigin, CurrentTime);
        break;
		case TACommandTouchMove:
			moveMouse(command);
		break;
		case TACommandTouchEnd:
			XTestFakeButtonEvent(display, 2, False, CurrentTime);
            XTestFakeMotionEvent(display, 0, xOrigin, yOrigin, CurrentTime);
			lastEvent = NULL;
		break;
		default:
		break;
	}
}

void CommandInterpreter::cancel(int command, int currentCommand)
{
	switch (command)
	{
		case TACommandTypeRotate:
			XTestFakeButtonEvent(display, 1, False, CurrentTime);
		break;
		case TACommandTypeZoom:
			XTestFakeButtonEvent(display, 3, False, CurrentTime);
		break;
		case TACommandTypePan:
			XTestFakeButtonEvent(display, 2, False, CurrentTime);
		break;
		default:
		break;
	}
	lastEvent = currentCommand;
}

bool CommandInterpreter::checkBounds()
{
    int vertiBound = 70;

    int upBound = vertiBound;
    int downBound = displayYResolution - vertiBound;
    
    XQueryPointer(display, RootWindow(display, DefaultScreen(display)), &event.xbutton.window, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
    
    printf("Checking for bounds: (%i, %i)\n", event.xbutton.x, event.xbutton.y);
    
    if ((event.xbutton.y > downBound) || (event.xbutton.y < upBound))
        return false;
    else
        return true;
}