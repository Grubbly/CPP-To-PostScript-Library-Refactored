#include "Layered.h"

//TODO BOUNDING BOX
PostLib::Layered::Layered(const PostLib::PostScriptPoint & centerPoint, const std::initializer_list<std::unique_ptr<Shape>> & shapeList) : CompositeShape(centerPoint, shapeList)
{
	formatShapes();
}

void PostLib::Layered::formatShapes()
{
	for (auto & item : getShapeList())
	{
		if (item->bounds().size.width > bounds().size.width)
			setBounds({ { bounds().origin.x, bounds().origin.y },{ item->bounds().size.width, bounds().size.height } });
		if (item->bounds().size.height > bounds().size.height)
			setBounds({ { bounds().origin.x, bounds().origin.y } ,{ bounds().size.width, item->bounds().size.height } });

		item->setCenter(centerPoint);
		item->setBounds({ centerPoint,{ item->bounds().size.width, item->bounds().size.height } });
	}

	double centerDifferenceY;

	for (auto & item : getShapeList())
	{
		centerDifferenceY = (bounds().size.height / 2) - (item->bounds().size.height / 2);
		if (centerDifferenceY > 0)
			item->setCenter({ item->center().x , (item->center().y + centerDifferenceY) });
	}
}

