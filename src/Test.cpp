///*-------------------------------------------------------
// | CS 372: Software Construction                        |
// | Project 2: C++ To PostScript Library                 |
// | Date: 3/20/18                                        |
// | File: test.cpp                                       |
// | Written By: Collin Lasley & Tristan Van Cise         |
// | Description: Unit Tests For Library, Using Catch     |
// ------------------------------------------------------*/

#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <vector>

#include "Shape.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Spacer.h"
#include "Polygon.h"
#include "Triangle.h"
#include "Square.h"
#include "Layered.h"
#include "Vertical.h"
#include "Horizontal.h"
#include "Rotated.h"
#include "ScaleShape.h"
#include "fan.h"

static std::string psCommands;


using namespace PostLib;

#define OUTPUT_FILE 1

//Helpter function for making PS files in tests
std::string PSHeader(const std::vector<std::function<std::string()>> & functionCallList)
{
	std::string header = "%!PS-Adobe-3.0\n%%Pages: 1\n%%EndComments\n\n\n\n \
						 /inch {72 mul} def\n\n";

	for (const auto & PSSHapeFunction : functionCallList)
	{
		header += PSSHapeFunction();
		header += "\n\n\n";
	}

	header += "%%Page: 1 1\n\n";

	return header;
}

TEST_CASE("Circle Construction", "[CIRCLE]")
{
    PostLib::Circle             aCircle;
    PostLib::PostScriptPoint    aPoint;
    
    aPoint = {500, 500};
    
    aCircle = Circle(aPoint, 12);
    
    REQUIRE(aCircle.bounds().origin.x == aPoint.x - 12);
    REQUIRE(aCircle.bounds().origin.y == aPoint.y - 12);

	const double bRADIUS = 42;
	PostScriptPoint bPoint = { 10, 10 };

	Circle bCircle = { bPoint, bRADIUS };

	REQUIRE(bCircle.bounds().origin.x == bPoint.x - bRADIUS);
	REQUIRE(bCircle.bounds().origin.y == bPoint.y - bRADIUS);
}

TEST_CASE("Circle Bounding Box Origin", "[CIRCLE]")
{
	const double RADIUS = 42;
	PostScriptPoint aPoint = { 20, 20 };

	Circle aCircle = { aPoint, RADIUS };

	REQUIRE(aCircle.bounds().origin.x == -22);
	REQUIRE(aCircle.bounds().origin.y == aPoint.y - RADIUS);
}

TEST_CASE("Circle Bounding Box Size", "[CIRCLE]")
{
	const double RADIUS = 42;
	PostScriptPoint aPoint = { 10, 10 };

	Circle aCircle = { aPoint, RADIUS };

	REQUIRE(aCircle.bounds().size.width == RADIUS*2);
	REQUIRE(aCircle.bounds().size.height == RADIUS*2);
}

TEST_CASE("Circle PostScript Conversion", "[CIRCLE]")
{
    PostLib::Circle             aCircle;
    PostLib::PostScriptPoint    aPoint;
    
    aPoint = {72, 72};
    
    aCircle = Circle(aPoint, 12);
    
	std::ofstream outFile("circleTest.txt", std::ofstream::trunc);

	REQUIRE(outFile);

	outFile << PSHeader({std::bind(&Circle::PostScriptRepresentation, aCircle)});

	REQUIRE(aCircle.PostScriptRepresentation() == "/renderCircle { %Parameter order: x, y, radius\n\
		\n\
		/radius   exch def\n\
		/drawPosY exch def\n\
		/drawPosX exch def\n\
		\n\
		drawPosX drawPosY radius 0 360 arc\n\
		\n\
	} def");

	outFile << "gsave" << std::endl;
	outFile << aCircle.postScript() << std::endl;
	outFile << "stroke" << std::endl;
	outFile << "grestore" << std::endl;
	outFile << "showpage" << std::endl;
}

TEST_CASE("Rectangle PostScript Conversion", "[RECT]")
{
    PostLib::Rectangle             objRect;
    PostLib::PostScriptPoint       aPoint;
    
    aPoint = {120, 120};
    
    objRect = PostLib::Rectangle(aPoint, 100, 100);
    
    objRect.PostScriptRepresentation();
    psCommands.append(objRect.postScript());
}

TEST_CASE("Spacer PostScript Conversion", "[RECT: SPACE]")
{
	std::ofstream outFile("spaceTest.txt", std::ofstream::trunc);

	REQUIRE(outFile);

	PostLib::Spacer                objRect;
	PostLib::PostScriptPoint       aPoint;

	aPoint = { 120, 120 };

	objRect = Spacer(aPoint, 150, 150);

	objRect.PostScriptRepresentation();
	
	outFile << (objRect.postScript()) << "\n\naSpace\nshowpage";
}

TEST_CASE("File Output - Circle", "[Circle I/O]")
{
    std::ofstream outFile;
    
#if OUTPUT_FILE
    outFile.open("/file.txt");
    outFile << "%!\n";
    outFile << psCommands << "\n" << "renderCircle\n\naRect\n\naSpace\n\n";

    
    outFile << "showpage\n\n";
    outFile.close();
#else
    
#endif
}

TEST_CASE("Polygon Side Lengths and Number of Sides (Default Ctor)", "[POLYGON]")
{
	PostLib::Polygon aPoly;

	REQUIRE(aPoly.getNumSides() == 3);
	REQUIRE(aPoly.getSideLength() == 1.0);
}

TEST_CASE("Polygon Side Lengths and Number of Sides (2 param Ctor)", "[POLYGON]")
{
	const unsigned int SIDES = 5;
	const double SIDE_LENGTH = 3;
	PostLib::PostScriptPoint aPoint = { 5, 4 };

	PostLib::Polygon aPoly(aPoint, SIDES, SIDE_LENGTH);

	REQUIRE(aPoly.getNumSides() == SIDES);
	REQUIRE(aPoly.getSideLength() == SIDE_LENGTH);
}

TEST_CASE("Polygon Side Bounding Box Lengths", "[POLYGON]")
{
	const unsigned int SIDES = 8;
	const double SIDE_LENGTH = 4;
	PostLib::PostScriptPoint aPoint = { 5, 4 };

	PostLib::Polygon aPoly(aPoint, SIDES, SIDE_LENGTH);

	REQUIRE(aPoly.bounds().size.width != 4);
	REQUIRE(aPoly.bounds().size.height != 4);
}

TEST_CASE("File Output - Polygon", "[Polygon I/O]")
{
	const unsigned int SIDES = 5;
	const double SIDE_LENGTH = 1;
	PostLib::PostScriptPoint aPoint = { 5, 4 };

	PostLib::Polygon aPoly(aPoint, SIDES, SIDE_LENGTH);

	//if i do polyTest.txt the file does not open or get written to...
	std::ofstream outFile("polyTest.txt", std::ofstream::trunc);

	REQUIRE(outFile);

	outFile << PSHeader({std::bind(&Polygon::PostScriptRepresentation, aPoly)});

	REQUIRE(aPoly.PostScriptRepresentation() == "/ngon { %Parameter order: xPosOrigin, yPosOrigin, sides, sideLen\n\
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
	} def");

	outFile << "gsave" << std::endl;
	outFile << aPoly.postScript();
	outFile << "fill" << std::endl;
	outFile << "grestore" << std::endl;
	outFile << "showpage" << std::endl;
}

TEST_CASE("File Output - Triangle", "[Triangle I/O]")
{
	const double SIDE_LENGTH = 1;
	PostLib::PostScriptPoint aPoint = { 5, 4 };

	PostLib::Triangle aTri(aPoint, SIDE_LENGTH);

	std::ofstream outFile("triangleTest.txt", std::ofstream::trunc);

	REQUIRE(outFile);

	outFile << PSHeader({ std::bind(&Triangle::PostScriptRepresentation, aTri) });

	REQUIRE(aTri.PostScriptRepresentation() == "/ngon { %Parameter order: xPosOrigin, yPosOrigin, sides, sideLen\n\
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
	} def");

	outFile << "gsave" << std::endl;
	outFile << aTri.postScript();
	outFile << "fill" << std::endl;
	outFile << "grestore" << std::endl;
	outFile << "showpage" << std::endl;
}

TEST_CASE("File Output - Square", "[Square I/O]")
{
	const double SIDE_LENGTH = 1;
	PostLib::PostScriptPoint aPoint = { 5, 4 };

	PostLib::Square aSquare(aPoint, SIDE_LENGTH);

	std::ofstream outFile("squareTest.txt", std::ofstream::trunc);

	REQUIRE(outFile);

	outFile << PSHeader({ { std::bind(&Square::PostScriptRepresentation, aSquare) } });

	REQUIRE(aSquare.PostScriptRepresentation() == "/ngon { %Parameter order: xPosOrigin, yPosOrigin, sides, sideLen\n\
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
	} def");

	outFile << "gsave" << std::endl;
	outFile << aSquare.postScript();
	outFile << "fill" << std::endl;
	outFile << "grestore" << std::endl;
	outFile << "showpage" << std::endl;
}

TEST_CASE("File Output - Layered", "[Layered I/O]")
{
	const double SIDE_LENGTH = 1;
	PostLib::PostScriptPoint aPoint = { 5, 4 };

	std::initializer_list<std::unique_ptr<Shape>> testPoly = { std::make_unique<PostLib::Polygon>(PostLib::Polygon(aPoint, 3, 1)),
															   std::make_unique<PostLib::Polygon>(PostLib::Polygon(aPoint, 4, 1)),
															   std::make_unique<PostLib::Polygon>(PostLib::Polygon(aPoint, 5, 1)),
															   std::make_unique<PostLib::Polygon>(PostLib::Polygon(aPoint, 7, 1)) };

	PostLib::Layered aLayered(aPoint, testPoly);

	std::ofstream outFile("layeredTest.txt", std::ofstream::trunc);

	REQUIRE(outFile);

	outFile << PSHeader({ std::bind(&Layered::PostScriptRepresentation, aLayered) });

	REQUIRE(aLayered.PostScriptRepresentation() == "/ngon { %Parameter order: xPosOrigin, yPosOrigin, sides, sideLen\n\
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
	} def");

	outFile << aLayered.postScript();
}

TEST_CASE("File Output - Layered2", "[Layered I/O]")
{
	const double SIDE_LENGTH = 1;
	PostLib::PostScriptPoint aPoint = { 5, 4 };
	PostLib::PostScriptPoint bPoint = { 1, 1 };
	PostLib::PostScriptPoint cPoint = { 9, 7 };

	std::initializer_list<std::unique_ptr<Shape>> testPoly = { std::make_unique<PostLib::Square>(PostLib::Square(aPoint, 1)),
		std::make_unique<PostLib::Triangle>(PostLib::Triangle(bPoint, 0.30)),
		std::make_unique<PostLib::Triangle>(PostLib::Triangle(cPoint, 0.51)),
		std::make_unique<PostLib::Square>(PostLib::Square(cPoint, 1.2)),
		std::make_unique<PostLib::Polygon>(PostLib::Polygon(bPoint, 8, 0.5)) };

	PostLib::Layered aLayered(aPoint, testPoly);

	std::ofstream outFile("layeredTest2.txt", std::ofstream::trunc);

	REQUIRE(outFile);

	outFile << PSHeader({ std::bind(&Layered::PostScriptRepresentation, aLayered) });

	REQUIRE(aLayered.PostScriptRepresentation() == "/ngon { %Parameter order: xPosOrigin, yPosOrigin, sides, sideLen\n\
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
	} def");

	outFile << aLayered.postScript();
}

TEST_CASE("File Output - Vertical", "[Vertical I/O]")
{
	const double SIDE_LENGTH = 1;
	PostLib::PostScriptPoint aPoint = { 5, 2 };

	std::initializer_list<std::unique_ptr<Shape>> testPoly = { std::make_unique<PostLib::Polygon>(PostLib::Polygon(aPoint, 3, 1)),
		std::make_unique<PostLib::Polygon>(PostLib::Polygon(aPoint, 4, 1)),
		std::make_unique<PostLib::Polygon>(PostLib::Polygon(aPoint, 5, 1)),
		std::make_unique<PostLib::Polygon>(PostLib::Polygon(aPoint, 7, 1)) };

	PostLib::Vertical aVert(aPoint, testPoly);

	std::ofstream outFile("verticalTest.txt", std::ofstream::trunc);

	REQUIRE(outFile);

	outFile << aVert.makePSFile();
}

TEST_CASE("File Output - Horizontal", "[Horizontal I/O]")
{
	const double SIDE_LENGTH = 1;
	PostLib::PostScriptPoint aPoint = { 1, 4 };

	std::initializer_list<std::unique_ptr<Shape>> testPoly = { std::make_unique<PostLib::Polygon>(PostLib::Polygon(aPoint, 3, 1)),
		std::make_unique<PostLib::Polygon>(PostLib::Polygon(aPoint, 4, 1)),
		std::make_unique<PostLib::Polygon>(PostLib::Polygon(aPoint, 5, 1)),
		std::make_unique<PostLib::Polygon>(PostLib::Polygon(aPoint, 7, 1)) };

	PostLib::Horizontal aHor(aPoint, testPoly);

	std::ofstream outFile("horizontalTest.txt", std::ofstream::trunc);

	REQUIRE(outFile);

	outFile << aHor.makePSFile();
}

TEST_CASE("Rotated Shape", "[ROTATION]")
{
	std::ofstream outFile("rotateTest.txt", std::ofstream::trunc);

	REQUIRE(outFile);

	PostLib::PostScriptPoint aPoint = { 144,144 };
	unsigned int w = 20, h = 10;
	PostLib::RotatedShape rotatedShape = RotatedShape(new PostLib::Rectangle(aPoint, w, h), ROTATION_ANGLE_90);
	outFile << rotatedShape.PostScriptRepresentation();
}

TEST_CASE("Scaled Shape", "[SCALE]")
{
	std::ofstream outFile("scaleTest.txt", std::ofstream::trunc);

	REQUIRE(outFile);

	PostLib::PostScriptPoint originalPoint = { 120, 240 };

	PostLib::PostScriptPoint aPoint = { 144, 144 };
	unsigned int w = 20, h = 10;
	PostLib::Scaled scaledShape = PostLib::Scaled(new PostLib::Rectangle(aPoint, w, h), 2.0, 2.0);
	scaledShape.PostScriptRepresentation();
	outFile << scaledShape.PostScriptRepresentation();
}

TEST_CASE("Custom Shape Purple", "[FAN]")
{
	const unsigned int fanOut = 15;
	PostLib::PostScriptPoint aPoint = { 4.5, 1 };

	PostLib::Fan aFan(fanOut, aPoint);

	std::ofstream outFile("customShapePurpleTest.txt", std::ofstream::trunc);

	REQUIRE(outFile);

	outFile << PSHeader({ std::bind(&Fan::PostScriptRepresentation, aFan) });
	
	REQUIRE(aFan.PostScriptRepresentation() == "/ngon { %Parameter order: xPosOrigin, yPosOrigin, sides, sideLen\n\
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
	} def");

	outFile << aFan.postScript(PURPLE);
}

TEST_CASE("Custom Shape Yellow", "[FAN]")
{
	const unsigned int fanOut = 15;
	PostLib::PostScriptPoint aPoint = { 4.5, 1 };

	PostLib::Fan aFan(fanOut, aPoint);

	std::ofstream outFile("customShapeYellowTest.txt", std::ofstream::trunc);

	REQUIRE(outFile);

	outFile << PSHeader({ std::bind(&Fan::PostScriptRepresentation, aFan) });

	REQUIRE(aFan.PostScriptRepresentation() == "/ngon { %Parameter order: xPosOrigin, yPosOrigin, sides, sideLen\n\
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
	} def");

	outFile << aFan.postScript(YELLOW);
}
