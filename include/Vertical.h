#/*-------------------------------------------------------
| CS 372: Software Construction                        |
| Project 2: C++ To PostScript Library                 |
| Date: 3/20/18                                        |
| File: Vertical.h                                     |
| Written By: Collin Lasley & Tristan Van Cise         |
| Description: Header Of Vertical Class                |
------------------------------------------------------*/

#include <string>
#include <vector>
#include "Shape.h"
#include <memory>
#include "CompositeShape.h"

#ifndef Vertical_H
#define Vertical_H

namespace PostLib {

	class Vertical : public PostLib::CompositeShape
	{
	public:
		Vertical(const PostLib::PostScriptPoint & centerPoint, const std::initializer_list<std::unique_ptr<Shape>> & shapeList);
		virtual void formatShapes() override;
	};
}

#endif // !Vertical_H
