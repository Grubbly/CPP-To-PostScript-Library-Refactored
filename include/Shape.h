/*-------------------------------------------------------
 | CS 372: Software Construction                        |
 | Project 2: C++ To PostScript Library                 |
 | Date: 3/20/18                                        |
 | File: shape.h                                        |
 | Written By: Collin Lasley & Tristan Van Cise         |
 | Description: Header Of Shape Class                   |
 ------------------------------------------------------*/

#include <string>

#ifndef SHAPE_H
#define SHAPE_H

namespace PostLib {
    
    typedef struct{
        double x;
        double y;
    }PostScriptPoint;
    
    typedef struct{
        double width;
        double height;
    }Size;
    
    typedef struct{
        PostLib::PostScriptPoint origin;
        PostLib::Size            size;
    }PrimitiveRectangle;
    
    
    class Shape {
        friend class RotatedShape;
        
    public:
        Shape();
        Shape(PostLib::PostScriptPoint aCenter, PostLib::PrimitiveRectangle aBoundingBox);
		virtual ~Shape();
        
        PostScriptPoint            center(void) const;
        PrimitiveRectangle         bounds(void) const;
        void                       setCenter(const PostScriptPoint& newCenter);
        void                       setBounds(const PrimitiveRectangle &newBounds);
		void                       setPostScript(const std::string & postScript);
        
		virtual std::string		   PostScriptRepresentation(void)=0;
		virtual std::string		   postScript(void)=0;
        
    protected:
        PostScriptPoint            centerPoint;
        PrimitiveRectangle         boundingBox;
        std::string                PostScriptCode;
        
    };
    
}

#endif // !SHAPE_H
