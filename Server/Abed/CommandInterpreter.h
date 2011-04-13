//
//  CommandInterpreter.h
//  Abed
//
//  Created by Max Goedjen on 4/10/11.
//  UHD
//

#import <X11/Xlib.h>
#import <X11/extensions/Xrandr.h>
#import "TACommand.h"

using namespace std;

class CommandInterpreter
{
public:
    void initialize();
    void handleCommand(TACommand command);
    void click(TACommand command);
    void moveMouse(TACommand command);
    void releaseMouse(TACommand command);
    
private:
    
};