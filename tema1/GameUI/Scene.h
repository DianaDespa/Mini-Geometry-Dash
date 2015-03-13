// Despa Diana Alexandra 331CA

#pragma once
#include "../Framework/Rectangle2d.h"
#include "../Framework/Polygon2D.h"
#include "../Framework/Circle2D.h"
#include "../Framework/DrawingWindow.h"
#include "../Framework/Transform2D.h"

#define PERIOADA 25 

// Simboluri care codifica obiectele de pe scena in matricea scenei.
enum SceneObject {
	FREE,	// Loc liber.
	BLOCK,	// Platforma.
	CONE,	// Obstacol.
	JUMP,	// JUMP automat. 
	BOOST,	// Booster pentru JUMP.
	BONUS,	// Viata bonus.
	FLAG	// Punct/checkpoint.
};

class Scene
{
private:
	Visual2D *v2d, *v2d_dynam;		// Contexte vizuale.
	int width, height,				// Dimensiuni.
		frames;						// Numar de cadre.
	std::vector < std::vector<SceneObject> > world;			// Matricea scenei.
	std::vector <Object2D *> dynamic_objects;				// Toate obiectele dinamice de pe scena.
	std::vector < std::pair<int, int> > dynam_locations;	// Coordonatele in matrice ale obiectelor dinamice.

	// Deseneaza o platforma formata din times_x * times_y blocuri, in pozitia start_x, start_y.
	void draw_basic_square(int times_x, int times_y, int start_x, int start_y);

	// Deseneaza o platforma dinamica din times_x * times_y blocuri, in pozitia start_x, start_y.
	void draw_dynam_platform(int times_x, int times_y, int start_x, int start_y);

	// Deseneaza con/triunghi dinamic in pozitia x, y, de times ori.
	void draw_dynam_cone(int x, int y, int times);

	// Deseneaza con/triunghi in pozitia x, y, de times ori.
	void draw_cone(int x, int y, int times);

	// Deseneaza con/triunghi intors in pozitia x, y, de times ori.
	void draw_reverse_cone(int x, int y, int times);

	// Deseneaza steag/checkpoint in pozitia x, y.
	void draw_flag(int x, int y);

	// Deseneaza cerc pentru JUMP automat in pozitia x, y.
	void draw_jump(int x, int y);

	// Deseneaza booster pentru JUMP in pozitia x, y.
	void draw_boost(int x, int y);

	// Deseneaza simbol pentru viata bonus in pozitia x, y.
	void draw_bonus(int x, int y);

	// Sterge toate obiectele dinamice.
	void clear_dynamic_objects();

public:
	static const int SS = 50; //square size

	Scene();
	Scene(int width, int height);
	~Scene();
	
	// Deseneaza scena.
	void draw(Visual2D *v2d, Visual2D *v2d_dynam);

	// Intoarce simbolul de la pozitia [i][j] din matricea scenei.
	SceneObject get(int i, int j);

	// Intoarce latimea scenei.
	int get_width();

	// Intoarce inaltimea scenei.
	int get_height();

	// Misca obiectele dinamice.
	void move();
};

