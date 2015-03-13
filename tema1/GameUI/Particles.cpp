// Despa Diana Alexandra 331CA

#include "Particles.h"


Particles::Particles(Visual2D *v2d)
{
	this->v2d = v2d;
}

Particles::~Particles()
{
}

void Particles::draw(double x, double y)
{
	double size, amp, cycle;
	Rectangle2D *square;
	for (int i = 0; i < 2; ++i) {
		size = 4;
		square = new Rectangle2D(Point2D(0, 0), size, size, Color(0.168, 0.168, 0.431), true);
		DrawingWindow::addObject2D_to_Visual2D(square, v2d);
		parts.push_back(square);
		amp = (double)rand() / (RAND_MAX);
		amp = 3 + amp * 11;
		amplitudes.push_back(amp);
		cycle = (double)rand() / (RAND_MAX);
		cycle = 0.5 + cycle * 1.5;
		cycles.push_back(cycle);
		coords.push_back(new Point2D(x, y));
		scales.push_back(1);
		displacement.push_back(0);
	}
	move();
}

void Particles::move()
{
	int i, y;
	for (i = 0; i < parts.size(); ++i) {
		Transform2D::loadIdentityMatrix();
		y = amplitudes[i] * (1 + sin(cycles[i] * displacement[i]));
		Transform2D::translateMatrix(-2, -2);
		Transform2D::scaleMatrix(scales[i], scales[i]);
		Transform2D::translateMatrix(coords[i]->x + displacement[i] + 7, coords[i]->y + y + 2);
		Transform2D::applyTransform(parts[i]);
		amplitudes[i] -= 0.4;
		scales[i] -= 0.01;
		displacement[i] -= 1;
	}
	// Daca amplitudinile particulelor ajung sub valoare 0.5, ele sunt sterse.
	while (!parts.empty() && amplitudes[0] <= 0.5) {
		DrawingWindow::removeObject2D_from_Visual2D(parts[0], v2d);
		parts.erase(parts.begin());
		coords.erase(coords.begin());
		scales.erase(scales.begin());
		amplitudes.erase(amplitudes.begin());
		cycles.erase(cycles.begin());
		displacement.erase(displacement.begin());
	}
}

void Particles::clear()
{
	for (int i = 0; i < parts.size(); ++i) {
		DrawingWindow::removeObject2D_from_Visual2D(parts[i], v2d);
	}
	parts.clear();
	coords.clear();
	scales.clear();
	amplitudes.clear();
	cycles.clear();
	displacement.clear();
}