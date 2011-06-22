//
//  CommandInterpreter.h
//  Abed
//
//  Created by Max Goedjen on 4/10/11.
//  UHD
//

#include "TACommand.h"
#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>
#include <X11/extensions/XTest.h>


using namespace std;

class CommandInterpreter
{
public:
    CommandInterpreter();
    void handleCommand(TACommand command);
	void queryResolution();
	void moveMouse(TACommand command);
    void rotate(TACommand command);
	void zoom(TACommand command);
	void pan(TACommand command);
	void cancel(int command, int currentCommand);
    
private:
    Display *display;
	XEvent event;
	int lastEvent;
    int xOrigin;
    int yOrigin;
    int displayXResolution;
    int displayYResolution;
    int upBound;
    int downBound;
};