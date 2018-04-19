#include "fan.h"

PostLib::Fan::Fan(unsigned int fanOut, PostLib::PostScriptPoint center) : Polygon(center, 3, 1),_fanOut(fanOut)
{}

std::string PostLib::Fan::PostScriptRepresentation(void)
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

std::string PostLib::Fan::postScript(int color)
{
	if (color == PURPLE)
	{
		return std::to_string(_fanOut) + " -1 3 { \n\
		gsave\n\
		/vertices exch def\n\
		vertices 10 div vertices 15 div vertices cos setrgbcolor\n" +
				std::to_string(center().x) + " inch " + std::to_string(center().y)
				+ " inch vertices 1 inch ngon\n\
		fill\n\
		grestore\n\
		} for\n";
	}

	if (color == YELLOW)
	{
		return std::to_string(_fanOut) + " -1 3 { \n\
		gsave\n\
		/vertices exch def\n\
		vertices 10 div vertices 15 div vertices cos sin setrgbcolor\n" +
				std::to_string(center().x) + " inch " + std::to_string(center().y)
				+ " inch vertices 1 inch ngon\n\
		fill\n\
		grestore\n\
		} for\n";
	}
    
    return "Visual C++'s compiler is terrible\n";
}
