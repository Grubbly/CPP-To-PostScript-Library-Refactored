#include "..\include\CompositeShape.h"
///*-----------------------------------------------------------------
// | CS 372: Software Construction									|
// | Project 2: C++ To PostScript Library							|
// | Date: 3/20/18													|
// | File: CompositeShape.cpp										|
// | Written By: Collin Lasley & Tristan Van Cise					|
// | Description: Description: Source for template design pattern	|
// ------------------------------------------------------------------*/

PostLib::CompositeShape::CompositeShape(const PostLib::PostScriptPoint & centerPoint, const std::initializer_list<std::unique_ptr<Shape>>& shapeList) : Shape(centerPoint, { { 0,0 } ,{ 0,0 } }), _shapeList(shapeList)
{
}

std::string PostLib::CompositeShape::makePSFile()
{
	std::string header = "%!PS-Adobe-3.0\n%%Pages: 1\n%%EndComments\n\n\n\n \
						 /inch {72 mul} def\n\n";

	header += PostScriptRepresentation() + "\n\n\n";
	header += "%%Page: 1 1\n\n";

	std::string body = postScript();

	return header + body;
}

std::initializer_list<std::unique_ptr<PostLib::Shape>> PostLib::CompositeShape::getShapeList()
{
	return _shapeList;
}

std::string PostLib::CompositeShape::PostScriptRepresentation(void)
{
	return "/ngon { %Parameter order: xPosOrigin, yPosOrigin, sides, sideLen\n\
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
}

std::string PostLib::CompositeShape::postScript(void)
{
	std::string ngonCalls = "";

	for (const auto & item : _shapeList) {
		ngonCalls += "gsave\n";
		ngonCalls += item->postScript();
		ngonCalls += "stroke\ngrestore\n";
	}
	ngonCalls += "\nshowpage\n";

	return ngonCalls;
}
