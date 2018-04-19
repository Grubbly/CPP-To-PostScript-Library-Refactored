/*-------------------------------------------------------
 | CS 372: Software Construction                        |
 | Project 2: C++ To PostScript Library                 |
 | Date: 3/20/18                                        |
 | File: Spacer.h                                       |
 | Written By: Collin Lasley & Tristan Van Cise         |
 | Description: Header for Spacer Class                 |
 ------------------------------------------------------*/

#include <string>

#include "Rectangle.h"

#ifndef SPACER_H
#define SPACER_H

namespace PostLib {
    
    class Spacer : public PostLib::Rectangle
    {
    public:
        Spacer();
        Spacer(PostLib::PostScriptPoint centerPoint, unsigned int width, unsigned int height);
        
        virtual std::string PostScriptRepresentation(void) override;
        std::string         postScript(void) override;
        
    protected:
    };
    
}

#endif // !SPACER_H
