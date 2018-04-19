/*-------------------------------------------------------
 | CS 372: Software Construction                        |
 | Project 2: C++ To PostScript Library                 |
 | Date: 3/20/18                                        |
 | File: Spacer.cpp                                     |
 | Written By: Collin Lasley & Tristan Van Cise         |
 | Description: Implementation Of Spacer Class          |
 ------------------------------------------------------*/

#include "Spacer.h"

#include <stdlib.h>


PostLib::Spacer::Spacer()
{
    
}

PostLib::Spacer::Spacer(PostLib::PostScriptPoint centerPoint, unsigned int width, unsigned int height)
{
    this->boundingBox.size.width  = width;
    this->boundingBox.size.height = height;
    this->boundingBox.origin.x    = centerPoint.x - (width/2);
    this->boundingBox.origin.y    = centerPoint.y - (height/2);
    this->centerPoint             = centerPoint;
}

std::string PostLib::Spacer::PostScriptRepresentation(void)
{
    char* replacedSpacerPSCode;
    const char* blankSpacerPSCode = "/aSpace {\n\
    newpath\n\
    /lowerLeftX %d def\n\
    /lowerLeftY %d def\n\
    /width %d def\n\
    /height %d def\n\
    width height moveto\n\
    0 height rlineto\n\
    width 0 rlineto\n\
    0 -1 height mul rlineto\n\
    closepath\n\
    } def\n\n";
    
    replacedSpacerPSCode = (char *)malloc(2*strlen(blankSpacerPSCode));
    sprintf(replacedSpacerPSCode, blankSpacerPSCode, this->boundingBox.origin.x, this->boundingBox.origin.y, this->boundingBox.size.width, this->boundingBox.size.height);
    this->PostScriptCode = std::string(replacedSpacerPSCode);
    
    free(replacedSpacerPSCode);
    
    return this->PostScriptCode;
}

std::string PostLib::Spacer::postScript(void)
{
    return this->PostScriptCode;
}
