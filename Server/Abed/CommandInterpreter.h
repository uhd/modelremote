//
//  CommandInterpreter.h
//  Abed
//
//  Created by Max Goedjen on 4/10/11.
//  UHD
//

#include "TACommand.h"

using namespace std;

class CommandInterpreter
{
public:
    void initialize();
    void handleCommand(TACommand command);
    
private:
    
};