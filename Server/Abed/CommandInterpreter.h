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
    void click(TACommand command);
    void moveMouse(TACommand command);
    void releaseMouse(TACommand command);
	void zoom(TACommand command);
    
private:
    Display *display;
	Window rootDisplayWindow;
	Window currentWindow;
	bool clicked;
	bool zooming;
    int xOrigin;
    int yOrigin;
};