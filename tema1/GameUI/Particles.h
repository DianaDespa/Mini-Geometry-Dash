// Despa Diana Alexandra 331CA

#pragma once
#include "../Framework/Visual2D.h"
#include "../Framework/Rectangle2d.h"
#include "../Framework/DrawingWindow.h"
#include "../Framework/Transform2D.h"
#include <random>

#define PI 3.14159265358979323846

class Particles
{
private:
	Visual2D *v2d;						// Context vizual.
	std::vector<Rectangle2D *> parts;	// Multimea de dreptunghiuri-particule.
	std::vector<Point2D *> coords;		// Coordonatele de inceput pentru toate particulele.
	std::vector<double> scales;			// Gradele de scalare ale particulelor.
	std::vector<double> amplitudes;		// Amplitudinile oscilatiilor particulelor.
	std::vector<double> cycles;			// Pulsatiile oscilatiilor particulelor.
	std::vector<int> displacement;		// Deplasamentul particulelor fata de coltul iconitei.

public:
	Particles(Visual2D *v2d);
	~Particles();

	// Deseanaza noi particule.
	void draw(double x, double y);

	// Misca particulele deja existente.
	void move();

	// Sterge toate particulele.
	void clear();
};

