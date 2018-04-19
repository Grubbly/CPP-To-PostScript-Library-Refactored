//
//  Rectangle.cpp
//  PostScriptXcode
//
//  Created by Collin Lasley on 3/28/18.
//  Copyright © 2018 clasley. All rights reserved.
//

#include "Rectangle.h"

#include <stdlib.h>


PostLib::Rectangle::Rectangle()
{
    
}

PostLib::Rectangle::Rectangle(PostLib::PostScriptPoint centerPoint, unsigned int width, unsigned int height)
{
    this->boundingBox.size.width  = width;
    this->boundingBox.size.height = height;
    this->boundingBox.origin.x    = centerPoint.x - (width/2);
    this->boundingBox.origin.y    = centerPoint.y - (height/2);
    this->centerPoint             = centerPoint;
}

std::string PostLib::Rectangle::PostScriptRepresentation(void)
{
    char* replacedRectPSCode;
    const char* blankRectPSCode = "/aRect {\n\
    newpath\n\
    0 0 0 setrgbcolor\n\
    /lowerLeftX %lf def\n\
    /lowerLeftY %lf def\n\
    /width %lf def\n\
    /height %lf def\n\
    lowerLeftX lowerLeftY moveto\n\
    0 height rlineto\n\
    width 0 rlineto\n\
    0 -1 height mul rlineto\n\
    closepath\n\
    stroke\n\
} def\n\n";
    
    replacedRectPSCode = (char *)malloc(2*strlen(blankRectPSCode));
    sprintf(replacedRectPSCode, blankRectPSCode, this->boundingBox.origin.x, this->boundingBox.origin.y, this->boundingBox.size.width, this->boundingBox.size.height);
    this->PostScriptCode = std::string(replacedRectPSCode);
    
    free(replacedRectPSCode);
    
    return this->PostScriptCode;
}

std::string PostLib::Rectangle::postScript(void)
{
    return this->PostScriptCode;
}
