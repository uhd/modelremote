//
//  CommandInterpreter.cpp
//  Abed
//
//  Created by Max Goedjen on 4/10/11.
//  UHD
//

#include "CommandInterpreter.h"

CommandInterpreter::CommandInterpreter(char* inputWindowID)
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
		
	memset(&event, 0x00, sizeof(event));
	event.xbutton.button = Button1;
	event.xbutton.same_screen = True;
	
	unsigned long inputWindow;
	inputWindow =  strtoul(inputWindowID, NULL, 16);	
	CGLXWindow = inputWindow;
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
	event.type = ButtonPress;
	//event.xbutton.state = 0x100;
	
	XQueryPointer(display, CGLXWindow, &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
	event.xbutton.subwindow = event.xbutton.window;
	
	XSendEvent(display, CGLXWindow, True, 0xfff, &event);
		
	XFlush(display);
	usleep(100);
}

void CommandInterpreter::releaseMouse(TACommand command)
{	
	cout<<"Attempting to release."<<endl;
	event.type = ButtonRelease;
	//event.xbutton.state = 0x0;
	
	XQueryPointer(display, CGLXWindow, &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
	event.xbutton.subwindow = event.xbutton.window;
		
	XSendEvent(display, CGLXWindow, True, 0xfff, &event);
		
	XFlush(display);
	usleep(100);
}

void CommandInterpreter::moveMouse(TACommand command)
{
	cout<<"Attempting to move the mouse."<<endl;
    int absX = xOrigin + command.xDifference;
    int absY = yOrigin + command.yDifference;
    
    XWarpPointer (display, None, CGLXWindow, 0, 0, 0, 0, absX, absY);
    XFlush (display);
	usleep(100);
}