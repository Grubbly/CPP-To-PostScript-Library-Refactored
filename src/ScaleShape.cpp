/*-------------------------------------------------------
 | CS 372: Software Construction                        |
 | Project 2: C++ To PostScript Library                 |
 | Date: 3/20/18                                        |
 | File: ScaleShape.h                                   |
 | Written By: Collin Lasley & Tristan Van Cise         |
 | Description: Implementation For Scaled Shapes Class  |
 ------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#include "ScaleShape.h"

PostLib::Scaled::Scaled(PostLib::Shape *passedShape, double xScale, double yScale)
{
    this->theShape = passedShape;
    xScaleFactor   = xScale;
    yScaleFactor   = yScale;
    PostScriptCode = "";
}

std::string PostLib::Scaled::PostScriptRepresentation(void)
{
    std::string   workingCodeStr;
    std::string   plainShapePS;
    std::string   plainFunctionName;
    const char *aStr = "\n\ngsave\n\
    %lf %lf scale\n\
    %s\n\
    stroke\n\
    grestore\n";
    char *replacedStr = (char*)malloc(strlen(aStr)*2);
    
    plainShapePS = theShape->PostScriptRepresentation();
    plainFunctionName = plainShapePS.substr(1, plainShapePS.find("{")-2);
    
    workingCodeStr.append(plainShapePS);
    workingCodeStr.append("\n\n");
    sprintf(replacedStr, aStr, this->xScaleFactor, this->yScaleFactor, plainFunctionName.c_str());
    
    workingCodeStr.append(replacedStr);
    this->PostScriptCode = workingCodeStr;
    //free(replacedStr);
    
    return workingCodeStr;
}


std::string PostLib::Scaled::postScript(void)
{
    if (this->PostScriptCode == "")
        this->PostScriptRepresentation();
    
    return this->PostScriptCode;
}


