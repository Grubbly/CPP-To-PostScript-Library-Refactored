///*-------------------------------------------------------
// | CS 372: Software Construction                        |
// | Project 2: C++ To PostScript Library                 |
// | Date: 3/20/18                                        |
// | File: CompositeShape.h                               |
// | Written By: Collin Lasley & Tristan Van Cise         |
// | Description: Header for template design pattern      |
// ------------------------------------------------------*/


#ifndef FILE_COMPOSITESHAPE_H
#define FILE_COMPOSITESHAPE_H

#include "Shape.h"
#include <string>
#include <vector>
#include <memory>

namespace PostLib {

	class CompositeShape : public PostLib::Shape
	{
	public:
		CompositeShape(const PostLib::PostScriptPoint & centerPoint, const std::initializer_list<std::unique_ptr<Shape>>& shapeList);

	public:
		std::string makePSFile();
		std::initializer_list<std::unique_ptr<PostLib::Shape>> getShapeList();

	private:
		virtual std::string PostScriptRepresentation(void) override;
		std::string         postScript(void) override;

	private:
		virtual void formatShapes() = 0;
		std::initializer_list<std::unique_ptr<PostLib::Shape>> _shapeList;
	};

}
#endif // !FILE_COMPOSITESHAPE_H