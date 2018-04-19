/*-------------------------------------------------------
 | CS 372: Software Construction                        |
 | Project 2: C++ To PostScript Library                 |
 | Date: 3/20/18                                        |
 | File: polygon.h                                      |
 | Written By: Collin Lasley & Tristan Van Cise         |
 | Description: Header Of Polygon Class                 |
 ------------------------------------------------------*/

#include <string>
#include <cmath>
#include "shape.h"

#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif

#ifndef POLYGON_H
#define POLYGON_H

namespace PostLib {

	class Polygon : public PostLib::Shape
	{
	public:
		Polygon();
		Polygon(PostLib::PostScriptPoint centerPoint, unsigned int numSides, double sideLength);

		virtual std::string		   PostScriptRepresentation() override;
		std::string				   postScript(void) override;

		int                        getNumSides() const;
		double                     getSideLength() const;

	private:
		int                        _numSides;
		double                     _sideLength;

		PrimitiveRectangle		   calculatePrimitiveRectangle(int numSides, double sideLength, PostLib::PostScriptPoint centerPoint) const;
	};

}

#endif // !POLYGON_H
