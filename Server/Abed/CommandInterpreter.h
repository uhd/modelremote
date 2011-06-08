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
#include <X11/keysymdef.h>
#include <X11/keysym.h>

using namespace std;

class CommandInterpreter
{
public:
    CommandInterpreter();
    void handleCommand(TACommand command);
	void queryResolution();
	void createPointer(XButtonEvent &event, string type);
    void click(TACommand command);
    void moveMouse(TACommand command);
    void releaseMouse(TACommand command);
    
private:
    Display *display;
	Window rootDisplayWindow;
	Window currentWindow;
    int xOrigin;
    int yOrigin;
};