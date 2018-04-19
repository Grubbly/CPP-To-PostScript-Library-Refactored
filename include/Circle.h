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

#ifndef CIRCLE_H
#define CIRCLE_H

namespace PostLib {
    
    class Circle : public PostLib::Shape
    {
    public:
        Circle();
        Circle(PostLib::PostScriptPoint centerPoint, double radius);

        virtual std::string		PostScriptRepresentation(void) override;
        std::string				postScript(void) override;

		double getRadius() const;
        
    protected:
        double radius;
    };
    
}

#endif // !CIRCLE_H
