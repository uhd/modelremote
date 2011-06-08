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

/*XKeyEvent CommandInterpreter::createPointer(Display *display, Window &currentWindow, Window &rootDisplayWindow, bool press, int keycode, int modifiers)
{
	XKeyEvent event;
	
	if (press)
		event.type = KeyPress;
	else
		event.type = KeyRelease;
		
	event.display = display;
	event.window = currentWindow;
	event.subwindow = None;
	event.root = rootDisplayWindow;
	event.time = CurrentTime;
	event.same_screen = True;
	event.keycode = XKeysymToKeycode(display, keycode);
	event.state = modifiers;
	
	return event;
}*/

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
	printf("Clicking.\n");
	XTestGrabControl(display, True);
	XTestFakeKeyEvent(display, XK_Pointer_Button1, True, 0);
}

void CommandInterpreter::releaseMouse(TACommand command)
{
	printf("Releasing.\n");
	XTestFakeKeyEvent(display, XK_Pointer_Button1, False, 0);
	XSync(display, False);
	XTestGrabControl(display, False);
}

void CommandInterpreter::moveMouse(TACommand command)
{
    int absX = xOrigin + command.xDifference;
    int absY = yOrigin + command.yDifference;
    
	printf("Sending move command.\n");
    XWarpPointer (display, None, RootWindow(display, 0), 0, 0, 0, 0, absX, absY);
}