/*-------------------------------------------------------
 | CS 372: Software Construction                        |
 | Project 2: C++ To PostScript Library                 |
 | Date: 3/20/18                                        |
 | File: shape.h                                        |
 | Written By: Collin Lasley & Tristan Van Cise         |
 | Description: Header For Rotated Shapes Class         |
 ------------------------------------------------------*/

#ifndef Rotated_h
#define Rotated_h

#include "Shape.h"

#include <memory.h>

typedef enum : unsigned int {
    ROTATION_ANGLE_90  = 90,
    ROTATION_ANGLE_180 = 180,
    ROTATION_ANGLE_270 = 270,
} RotationAngleType;

namespace PostLib{
    
    class RotatedShape : public PostLib::Shape {
        
    public:
        RotatedShape()  = default;
        RotatedShape(PostLib::Shape *passedShape, RotationAngleType passedAngle);
        ~RotatedShape() = default;
//#warning fix above line!!!
        
        std::string PostScriptRepresentation(void) override;
        std::string postScript(void) override;
        
    protected:
        //std::shared_ptr<PostLib::Shape> theShape;
        PostLib::Shape                  *theShape;
        RotationAngleType               rotationAngle;
    };
    
}
#endif /* Rotated_h */
