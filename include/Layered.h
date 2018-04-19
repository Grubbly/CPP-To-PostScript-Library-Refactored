#/*-------------------------------------------------------
| CS 372: Software Construction                        |
| Project 2: C++ To PostScript Library                 |
| Date: 3/20/18                                        |
| File: Layered.h                                     |
| Written By: Collin Lasley & Tristan Van Cise         |
| Description: Header Of Layered Class                |
------------------------------------------------------*/

#include <string>
#include <vector>
#include "Polygon.h"
#include <memory>

#ifndef Layered_H
#define Layered_H

namespace PostLib {

	class Layered : public PostLib::Shape
	{
	public:
		Layered();
		Layered(const PostLib::PostScriptPoint & centerPoint, const std::initializer_list<std::unique_ptr<Shape>> & shapeList);

		virtual std::string PostScriptRepresentation(void) override;
		std::string         postScript(void) override;
	
	private:
		std::initializer_list<std::unique_ptr<Shape>> _shapeList;
	};
}

#endif // !Layered_H
