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
	
	clicked = false;
	clickTimeout = 0;
    
    xOrigin = (int)width / 4;
    yOrigin = (int)height / 4;
    
}

void CommandInterpreter::handleCommand(TACommand command)
{
    
    printf("COMMAND: %i, %i, %i, %i, ClickTimeout = %i\n", command.type, command.touch, command.xDifference, command.yDifference, clickTimeout);
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
    memset (&event, 0, sizeof (event));
    event.xbutton.button = Button1;
    event.xbutton.same_screen = True;
    event.xbutton.subwindow = DefaultRootWindow (display);
	
    // Press
    event.type = ButtonPress;
	
	// If the touch is held, this allows clicking within the window.
	if ((clicked == true) && (clickTimeout < 15))
	{
		event.type = ButtonPress;
	}
	clicked = true;
    XFlush (display);
    usleep (10);
}

void CommandInterpreter::releaseMouse(TACommand command)
{
 
    XEvent event;
    memset (&event, 0, sizeof (event));
    event.xbutton.button = Button1;
    event.xbutton.same_screen = True;
    event.xbutton.subwindow = DefaultRootWindow (display);
	
    // Release
    event.type = ButtonRelease;
	clicked = false;
    XFlush (display);
    usleep (10);

}

void CommandInterpreter::moveMouse(TACommand command)
{
    
    int absX = xOrigin + command.xDifference;
    int absY = yOrigin + command.yDifference;
	
	if (clicked == true)
		clickTimeout++;
    
    XWarpPointer (display, None, rootWindow, 0, 0, 0, 0, absX, absY);
    XFlush (display);
    usleep (10);
}