// Despa Diana Alexandra 331CA

#pragma once
#include "../Framework/Visual2D.h"
#include "../Framework/Rectangle2d.h"
#include "../Framework/DrawingWindow.h"
#include "../Framework/Transform2D.h"

class Background
{
public:
	Background();
	~Background();

	// Metoda care deseneaza fundalul.
	void draw(Visual2D *v2d, int width, int height);
};

