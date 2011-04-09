//
//  TACommand.h
//  Troy
//
//  Created by Max Goedjen on 4/8/11.
//  UHD
//

#import <Foundation/Foundation.h>

typedef enum {
    
    TACommandTypeRotate = 0,
    TACommandTypePan,
    TACommandTypeZoom,
    
} TACommandType;

typedef struct TACommand {
    
    TACommandType type;
    int xDifference;
    int yDifference;
    
} TACommand;

TACommand TACommandMake(TACommandType commandType, int x, int y);
NSString *NSStringFromTACommand(TACommand command);