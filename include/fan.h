#/*-------------------------------------------------------
| CS 372: Software Construction                          |
| Project 2: C++ To PostScript Library                   |
| Date: 3/20/18                                          |
| File: Fan.h										     |
| Written By: Collin Lasley & Tristan Van Cise           |
| Description: Header Of Fan Class                       |
------------------------------------------------------*/

#include <string>
#include <vector>
#include "Shape.h"
#include "Polygon.h"
#include <memory>

#ifndef Fan_H
#define Fan_H

#define PURPLE 1
#define YELLOW 2

namespace PostLib {

	class Fan : public PostLib::Polygon
	{
	public:
		Fan(unsigned int fanOut = 1, PostLib::PostScriptPoint center = { 5, 4 });

		virtual std::string PostScriptRepresentation(void) override;
		std::string         postScript(int color = PURPLE);

	private:
		unsigned int _fanOut;
	};
}

#endif // !Fan_H