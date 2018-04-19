/*-------------------------------------------------------
 | CS 372: Software Construction                        |
 | Project 2: C++ To PostScript Library                 |
 | Date: 3/20/18                                        |
 | File: ScaleShape.h                                   |
 | Written By: Collin Lasley & Tristan Van Cise         |
 | Description: Header For Scaled Shapes Class          |
 ------------------------------------------------------*/

#ifndef ScaleShape_h
#define ScaleShape_h

#include "Shape.h"

#include <memory.h>

namespace PostLib{
    
    class Scaled : public PostLib::Shape {
        
    public:
        Scaled()  = default;
        Scaled(PostLib::Shape *passedShape, double xScale, double yScale);
        ~Scaled() = default;
        
        std::string PostScriptRepresentation(void) override;
        std::string postScript(void) override;
        
    protected:
        PostLib::Shape                  *theShape;
        double                          xScaleFactor;
        double                          yScaleFactor;
    };
    
}

#endif /* ScaleShape_h */
