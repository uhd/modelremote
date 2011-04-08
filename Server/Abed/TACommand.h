//
//  TACommand.h
//  Abed
//
//  Created by Max Goedjen on 4/8/11.
//  UHD
//

#include <iostream>
#include <string>

using namespace std;

typedef enum {
    
    TACommandTypeRotate = 0,
    TACommandTypePan,
    TACommandTypeZoom,
    
} TACommandType;

typedef struct TACommand {
    
    TACommandType type;
    int xCoordinate;
    int yCoordinate;
    
} TACommand;

TACommand TACommandMake(TACommandType commandType, int x, int y);
string StringFromTACommand(TACommand command);