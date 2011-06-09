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

typedef enum {
    
    TACommandTouchStart = 0,
    TACommandTouchMove,
    TACommandTouchEnd,
    
} TACommandTouch;

typedef struct TACommand {
    
    TACommandType type;
    TACommandTouch touch;
    int xDifference;
    int yDifference;
	float zoomValue;
    
} TACommand;

TACommand TACommandMake(TACommandType commandType, TACommandTouch touchType, int x, int y, float scale, float zoomValue);
NSString *NSStringFromTACommand(TACommand command);