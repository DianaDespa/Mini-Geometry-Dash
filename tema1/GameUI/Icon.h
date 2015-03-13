// Despa Diana Alexandra 331CAs

#pragma once
#include "../Framework/Visual2D.h"
#include "../Framework/Rectangle2d.h"
#include "../Framework/Polygon2D.h"
#include "../Framework/DrawingWindow.h"
#include "../Framework/Transform2D.h"
#include "Particles.h"
#include "Scene.h"
#include "Stats.h"
#include <math.h>
#include <random>

#define PI 3.14159265358979323846
#define G 9.8
#define COEF_A 0.0008
#define COEF_B 2
#define EPS 23

// Valori posibile intoarse de metoda move().
enum ReturnValues {
	OK,				// Miscare normala.
	DEAD,			// S-a pierdut o viata.
	EXTRA_POINT,	// S-a castigat un punct.
	EXTRA_LIFE		// S-a castigat o viata bonus.
};

class Icon
{
private:
	Visual2D *v2d;			// Contextul vizual
	Scene *scene;			// Scena
	Stats *stats;			// Starea jocului (vieti ramase, steaguri acumulate, etc.)
	Particles *particles;	// Starea particulelor

	// Obiectele care compun iconita
	Rectangle2D *shape,
		*right_eye,
		*left_eye,
		*face,
		*nose,
		*right_twinkle,
		*left_twinkle;
	Polygon2D *mouth, *teeth;
	Point2D *center;
	std::vector<Object2D *> objects; 

	double v,					// Viteza generala
		p_x, p_y,				// Deplasamentul la un moment dat
		initial_x, initial_y,	// Doordonatele initiale
		prev_x, prev_y;			// Deplasamente anterioare unei sarituri
	double angle;				// Unghiul cu care este rotita figura la un anumit moment
	int jumping,				// 1 - se afla in aer dupa o saritura, 0 - altfel
		auto_jump,				// 1 - face un JUMP automat, 0 - altfel
		falling,				// 1 - se afla in cadere, 0 - altfel
		super_jump;				// Numarul de JUMP-uri cu bonus ramase 
	
	// Verifica daca se afla pe o platforma.
	int is_on_platform();
	// Initializeaza campurile care au legatura cu miscarea.
	void initialize_move();
	// Aplica transformarile necesare asupra figurii.
	void apply_move();
	// Reseteaza figura la ultimul checkpoint.
	void reset();
	// Calculeaza coordonata Y pentru un X dat, dupa formula unei parabole(functie de gradul 2).
	double formula(double x);

	// Intoarce un punct cu coordonatele din matricea scenei 
	Point2D *adjust(Point2D *point);

	// Intoarce cel mai din dreapta punct al figurii.
	Point2D *right_point();
	// Intoarce cel mai din stanga punct al figurii.
	Point2D *left_point();
	// Intoarce cel mai de sus punct al figurii.
	Point2D *up_point();
	// Intoarce cel mai de jos punct al figurii.
	Point2D *down_point();

public:
	Icon(Visual2D *v2d, Scene *scene, Stats *stats, Particles *particles);
	~Icon();

	// Deseneaza iconita.
	void draw();
	// Intoarce deplasamentul pe axa OX a iconitei.
	int get_x();
	// Actualizeaza pozitia iconitei.
	ReturnValues move();
	// Verifica daca se poate face JUMP si seteaza jumping pe 1 in caz afirmativ.
	void jump();
};
