#include "Layered.h"

PostLib::Layered::Layered()
{
}

//TODO BOUNDING BOX
PostLib::Layered::Layered(const PostLib::PostScriptPoint & centerPoint, const std::initializer_list<std::unique_ptr<Shape>> & shapeList) : Shape(centerPoint, { { 0,0 } ,{ 0,0 } }), _shapeList(shapeList)
{
	for (auto & item : _shapeList)
	{
		if (item->bounds().size.width > bounds().size.width)
			setBounds({ { bounds().origin.x, bounds().origin.y }, { item->bounds().size.width, bounds().size.height } });
		if (item->bounds().size.height > bounds().size.height)
			setBounds({ { bounds().origin.x, bounds().origin.y } , { bounds().size.width, item->bounds().size.height } });

		item->setCenter(centerPoint);
		item->setBounds({ centerPoint, {item->bounds().size.width, item->bounds().size.height} });
	}

//	double centerDifferenceX;
	double centerDifferenceY;

	//TODO HORIZONTAL SHIFT
	for (auto & item : _shapeList)
	{
		centerDifferenceY = (bounds().size.height/2) - (item->bounds().size.height/2);
		if (centerDifferenceY > 0)
			item->setCenter({ item->center().x , (item->center().y + centerDifferenceY) });
		/*
		centerDifferenceX = (bounds().origin.x) - (item->bounds().origin.y);
		if (centerDifferenceX > 0)
			item->setCenter({ (item->center().x + centerDifferenceX), item->center().y });*/
	}
}

//TODO Fix polygon so only the call is printed instead of entire function
//	   Currently only works with square and triangle.
std::string PostLib::Layered::PostScriptRepresentation(void)
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

std::string PostLib::Layered::postScript(void)
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
