#include "Square.h"

PostLib::Square::Square()
{
}

PostLib::Square::Square(PostLib::PostScriptPoint centerPoint, double sideLength) : Polygon(centerPoint, 4, sideLength)
{
	setPostScript(PostScriptRepresentation());
}

std::string PostLib::Square::PostScriptRepresentation(void)
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

std::string PostLib::Square::postScript(void)
{
	return std::to_string(center().x) + " inch " + std::to_string(center().y)
		+ " inch 4 " + std::to_string(getSideLength()) + " inch ngon\n";
}
