// Despa Diana Alexandra 331CA

#include "Background.h"


Background::Background()
{
}


Background::~Background()
{
}

void Background::draw(Visual2D *v2d, int width, int height)
{
	Color darker = Color(0.741, 0.709, 0.901),
		lighter = Color(0.843, 0.827, 0.929);
	Rectangle2D *rect = new Rectangle2D(Point2D(0, 0), width, height, lighter, true);
	Rectangle2D *lower, *middle, *upper;
	int h1, h2;
	for (int i = 0; i < width; i += 200) {
		h1 = rand() % (height / 2);
		h2 = rand() % (height / 2);
		lower = new Rectangle2D(Point2D(i + 5, 0), 185, h1, darker, true);
		middle = new Rectangle2D(Point2D(i + 5, h1 + 10), 185, h2, darker, true);
		upper = new Rectangle2D(Point2D(i + 5, h1 + h2 + 20), 185, height - h1 - h2 - 20, darker, true);
		DrawingWindow::addObject2D_to_Visual2D(lower, v2d);
		DrawingWindow::addObject2D_to_Visual2D(middle, v2d);
		DrawingWindow::addObject2D_to_Visual2D(upper, v2d);
	}
	DrawingWindow::addObject2D_to_Visual2D(rect, v2d);
}