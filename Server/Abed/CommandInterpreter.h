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
#include <X11/extensions/XTest.h>


using namespace std;

class CommandInterpreter
{
public:
    CommandInterpreter();
    void handleCommand(TACommand command);
	void queryResolution();
	void moveMouse(TACommand command);
    void click(TACommand command);
	void zoom(TACommand command);
	void pan(TACommand command);
    
private:
    Display *display;
	Window rootDisplayWindow;
	Window currentWindow;
	bool clicked;
    int xOrigin;
    int yOrigin;
};