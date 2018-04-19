/*-------------------------------------------------------
 | CS 372: Software Construction                        |
 | Project 2: C++ To PostScript Library                 |
 | Date: 3/20/18                                        |
 | File: circle.cpp                                     |
 | Written By: Collin Lasley & Tristan Van Cise         |
 | Description: Implementation Of Circle Class          |
 ------------------------------------------------------*/


#include "circle.h"
#include <iostream>
#include <cstring>

PostLib::Circle::Circle() : Shape({ 50,50 }, { {5,4} , {4,4} }), radius(2)
{
    /*PrimitiveRectangle newBoundBox;
    PostScriptPoint    centerPoint;
    
    centerPoint.x     = 50;
    centerPoint.y     = 50;
    this->radius            = 2;
    newBoundBox.origin.x    = (int)(centerPoint.x - radius);
    newBoundBox.origin.y    = (int)(centerPoint.y - radius);
    newBoundBox.size.width  = 2*radius;
    newBoundBox.size.height = 2*radius;
    
    Shape(centerPoint, newBoundBox);*/
}

PostLib::Circle::Circle(PostLib::PostScriptPoint centerPoint, double radius) : Shape(centerPoint, { {(centerPoint.x - radius), (centerPoint.y - radius)}, {2* radius, 2* radius} }), radius(radius)
{
    /*PrimitiveRectangle newBoundBox;
    
    this->radius            = radius;
    newBoundBox.origin.x    = (int)(centerPoint.x - radius);
    newBoundBox.origin.y    = (int)(centerPoint.y - radius);
    newBoundBox.size.width  = 2*radius;
    newBoundBox.size.height = 2*radius;
    
    this->boundingBox = newBoundBox;
    this->centerPoint = centerPoint;*/
}

std::string PostLib::Circle::PostScriptRepresentation(void)
{
	this->PostScriptCode = 
	"/renderCircle { %Parameter order: x, y, radius\n\
		\n\
		/radius   exch def\n\
		/drawPosY exch def\n\
		/drawPosX exch def\n\
		\n\
		drawPosX drawPosY radius 0 360 arc\n\
		\n\
	} def";
	
	return this->PostScriptCode;
}

double PostLib::Circle::getRadius() const
{
	return radius;
}

std::string PostLib::Circle::postScript()
{
	return std::to_string(center().x) + " " + std::to_string(center().y) + " " + std::to_string(getRadius()) + " renderCircle\n";
}
