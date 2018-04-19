/*-------------------------------------------------------
 | CS 372: Software Construction                        |
 | Project 2: C++ To PostScript Library                 |
 | Date: 3/20/18                                        |
 | File: circle.h                                       |
 | Written By: Collin Lasley & Tristan Van Cise         |
 | Description: Header Of Circle Class                  |
 ------------------------------------------------------*/

#include <string>

#include "shape.h"

#ifndef RECTANGLE_H
#define RECTANGLE_H

namespace PostLib {
    
    class Rectangle : public PostLib::Shape
    {
    public:
        Rectangle();
        Rectangle(PostLib::PostScriptPoint centerPoint, unsigned int width, unsigned int height);
        
		virtual std::string PostScriptRepresentation(void) override;
        std::string         postScript(void) override;
        
    protected:
    };
    
}

#endif // !RECTANGLE_H
