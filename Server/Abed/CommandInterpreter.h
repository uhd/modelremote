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
    
private:
    Display *display;
    int xOrigin;
    int yOrigin;
};