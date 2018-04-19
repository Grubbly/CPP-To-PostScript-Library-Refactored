/*-------------------------------------------------------
| CS 372: Software Construction                        |
| Project 2: C++ To PostScript Library                 |
| Date: 3/20/18                                        |
| File: Square.h									   |
| Written By: Collin Lasley & Tristan Van Cise         |
| Description: Header Of Square Class                  |
------------------------------------------------------*/

#include <string>

#include "Polygon.h"

#ifndef SQUARE_H
#define SQUARE_H

namespace PostLib {

	class Square : public PostLib::Polygon
	{
	public:
		Square();
		Square(PostLib::PostScriptPoint centerPoint, double sideLength);

		virtual std::string PostScriptRepresentation(void) override;
		std::string         postScript(void) override;
	};

}

#endif // !SQUARE_H
