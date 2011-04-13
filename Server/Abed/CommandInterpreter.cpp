//
//  CommandInterpreter.cpp
//  Abed
//
//  Created by Max Goedjen on 4/10/11.
//  UHD
//

#import "CommandInterpreter.h"

void CommandInterpreter::initialize()
{
    Display *display = XOpenDisplay(NULL);
    
    int num_sizes;
    Rotation original_rotation;
    
    Window root = RootWindow(display, 0);
    XRRScreenSize *xrrs = XRRSizes(display, 0, &num_sizes);
    
    XRRScreenConfiguration *conf = XRRGetScreenInfo(display, root);
    short original_rate          = XRRConfigCurrentRate(conf);
    SizeID original_size_id       = XRRConfigCurrentConfiguration(conf, &original_rotation);
    
    int width=xrrs[original_size_id].width;
    int height=xrrs[original_size_id].height;
    
    cout<<width<<endl<<height;
    
    XCloseDisplay(display);

}

void CommandInterpreter::handleCommand(TACommand command)
{
    
    printf("COMMAND: %i, %i, %i, %i\n", command.type, command.touch, command.xDifference, command.yDifference);
    

}

void CommandInterpreter::click(TACommand command)
{
    /*XEvent event;
    memset (&event, 0, sizeof (event));
    event.xbutton.button = command.;
    event.xbutton.same_screen = True;
    event.xbutton.subwindow = DefaultRootWindow (display);
    while (event.xbutton.subwindow)
    {
        event.xbutton.window = event.xbutton.subwindow;
        XQueryPointer (display, event.xbutton.window,
                       &event.xbutton.root, &event.xbutton.subwindow,
                       &event.xbutton.x_root, &event.xbutton.y_root,
                       &event.xbutton.x, &event.xbutton.y,
                       &event.xbutton.state);
    }
    // Press
    event.type = ButtonPress;
    if (XSendEvent (display, PointerWindow, True, ButtonPressMask, &event) == 0)
        fprintf (stderr, "Error to send the event!\n");
    XFlush (display);
    usleep (1);
    // Release
    event.type = ButtonRelease;
    if (XSendEvent (display, PointerWindow, True, ButtonReleaseMask, &event) == 0)
        fprintf (stderr, "Error to send the event!\n");
    XFlush (display);
    usleep (1);*/
}

void CommandInterpreter::releaseMouse(TACommand command)
{
    
}

void CommandInterpreter::moveMouse(TACommand command)
{
    
}