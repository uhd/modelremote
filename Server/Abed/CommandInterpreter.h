//
//  CommandInterpreter.h
//  Abed
//
//  Created by Max Goedjen on 4/10/11.
//  UHD
//

#include "TACommand.h"
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>
#include <X11/Xutil.h>

using namespace std;

class CommandInterpreter
{
public:
    CommandInterpreter();
    void handleCommand(TACommand command);
    void click(TACommand command);
    void moveMouse(TACommand command);
    void releaseMouse(TACommand command);
	void grabWindowID(char* inputWindowID);
    
private:
    Display *display;
    Window rootWindow;
	long inputWindow;
	XEvent event;
    int xOrigin;
    int yOrigin;
};