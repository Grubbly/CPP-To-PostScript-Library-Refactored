/*-------------------------------------------------------
| CS 372: Software Construction                        |
| Project 2: C++ To PostScript Library                 |
| Date: 3/20/18                                        |
| File: triangle.h                                     |
| Written By: Collin Lasley & Tristan Van Cise         |
| Description: Header Of Triangle Class                |
------------------------------------------------------*/

#include <string>

#include "Polygon.h"

#ifndef TRIANGLE_H
#define TRIANGLE_H

namespace PostLib {

	class Triangle : public PostLib::Polygon
	{
	public:
		Triangle();
		Triangle(PostLib::PostScriptPoint centerPoint, double sideLength);

		virtual std::string PostScriptRepresentation(void) override;
		std::string         postScript(void) override;
	};

}

#endif // !TRIANGLE_H
