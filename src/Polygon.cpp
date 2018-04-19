/*-------------------------------------------------------
 | CS 372: Software Construction                        |
 | Project 2: C++ To PostScript Library                 |
 | Date: 3/20/18                                        |
 | File: polygon.cpp                                    |
 | Written By: Collin Lasley & Tristan Van Cise         |
 | Description: Implementation Of Polygon Class         |
 ------------------------------------------------------*/


#include "Polygon.h"

PostLib::Polygon::Polygon() : Shape({ 5, 4 }, { { 5,4 } ,{ 4,4 } }), _numSides(3), _sideLength(1)
{
}

//TODO BOUNDING BOX
PostLib::Polygon::Polygon(PostLib::PostScriptPoint centerPoint, unsigned int numSides, double sideLength) : Shape(centerPoint, { { 5,4 } ,{ 4,4 } }), _numSides((int)numSides), _sideLength(sideLength)
{
	setBounds(calculatePrimitiveRectangle(numSides, sideLength, centerPoint));
	setPostScript(postScript());
}

std::string PostLib::Polygon::PostScriptRepresentation()
{
	this->PostScriptCode = "/ngon { %Parameter order: xPosOrigin, yPosOrigin, sides, sideLen\n\
		newpath\n\n\
		/sideLen 				exch def\n\
		/sides 					exch def\n\
		/yPosOrigin 			exch def\n\
		/xPosOrigin 			exch def\n\
		/regularAngle 360 sides div def\n\n\
		xPosOrigin yPosOrigin 	moveto\n\
		sideLen sideLen 	  	scale\n\
		1 sideLen inch		  	div setlinewidth % Counterbalances the scaling to prevent fat lines\n\n\
		1 1 sides{\n\
		/vertex exch def\n\
		/theta vertex regularAngle mul def\n\
		theta cos theta sin rlineto\n\
		} for\n\
		closepath\n\n\
	} def";

	return this->PostScriptCode;
}
//TODO SQUARE TRIANGLE AND POLY ORIGIN POINT IN POSTSCRIPT
std::string PostLib::Polygon::postScript(void)
{
	/*return std::to_string(bounds().origin.x) + " inch " + std::to_string(bounds().origin.y)
		+ " inch " + std::to_string(getNumSides()) + " " + std::to_string(getSideLength()) + " inch ngon\n";*/
	setPostScript(std::to_string(center().x) + " inch " + std::to_string(center().y)
		+ " inch " + std::to_string(getNumSides()) + " " + std::to_string(getSideLength()) + " inch ngon\n");
	return this->PostScriptCode;
}

int PostLib::Polygon::getNumSides() const
{
	return _numSides;
}

double PostLib::Polygon::getSideLength() const
{
	return _sideLength;
}

PostLib::PrimitiveRectangle PostLib::Polygon::calculatePrimitiveRectangle(int numSides, double sideLength, PostLib::PostScriptPoint centerPoint) const
{
	double height = 0;
	double width = 0;

	if (numSides % 2 == 1)
	{
		height = sideLength*(1 + std::cos(M_PI / numSides)) / (2 * std::sin(M_PI / numSides));
		width = sideLength * (1 / std::sin(M_PI / numSides));
		//width = (sideLength * std::sin(M_PI * (numSides - 1) / (2*numSides))) / (std::sin(M_PI / numSides));
	}
	else if (numSides % 4 == 0)
	{
		height = sideLength * (std::cos(M_PI / numSides)) / (std::sin(M_PI / numSides));
		//width = (sideLength * std::cos(M_PI / numSides)) / (std::sin(M_PI / numSides));
		width = sideLength * (1 / std::sin(M_PI / numSides));
	}
	else
	{
		height = sideLength * ((std::cos(M_PI / numSides)) / (std::sin(M_PI / numSides)));
		//width = sideLength / (std::sin(M_PI / numSides));
		//width = sideLength * (1 / std::sin(M_PI / numSides));
		width = sideLength * (1 / std::sin(M_PI / numSides));
	}

	return { { (centerPoint.x - (width / 2)), (centerPoint.y - (height / 2)) } , { width, height } };
};
