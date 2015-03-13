// Despa Diana Alexandra 331CA

#include "Framework/DrawingWindow.h"
#include "Framework/Visual2D.h"
#include "Framework/Transform2D.h"
#include "Framework/Line2D.h"
#include "Framework/Circle2D.h"
#include "Framework/Polygon2D.h"
#include "GameUI/Icon.h"
#include "GameUI/Background.h"
#include "GameUI/Scene.h"
#include "GameUI/Stats.h"
#include <iostream>
#include <windows.h>

#define SCENE_FACTOR 20

using namespace std;

Visual2D *v2d_game, *v2d_stats, *v2d_particles;
Icon *icon;
Background *bg;
Scene *scene;
Stats *stats;
Particles *particles;
Text *lives_text, *points_text;
int stop = 0, pas = 0;;

//functia care permite adaugarea de obiecte
void DrawingWindow::init()
{
	// Creeaza contextul pentru text.
	v2d_stats = new Visual2D(0.0f, 0.0f, (float)DrawingWindow::width, 50.0f, 0, 0, DrawingWindow::width, 50);
	v2d_stats->tipTran(true);
	addVisual2D(v2d_stats);

	// Creeezza contextul pentru particule.
	v2d_particles = new Visual2D(0.0f, 0.0f, (float)DrawingWindow::width, (float)DrawingWindow::height + 100,
		0, 0, DrawingWindow::width, DrawingWindow::height);
	v2d_particles->tipTran(true);
	addVisual2D(v2d_particles);

	// Creeaza contextul pentru restul jocului.
	v2d_game = new Visual2D(0.0f, 0.0f, (float)DrawingWindow::width, (float)DrawingWindow::height + 100,
		0, 0, DrawingWindow::width, DrawingWindow::height);
	v2d_game->tipTran(true);
	addVisual2D(v2d_game);


	// Initializeaza si deseneaza fundalul, scena, iconita si efectul de particule.
	bg = new Background();
	scene = new Scene(DrawingWindow::width * SCENE_FACTOR, DrawingWindow::height + 100);
	stats = new Stats();
	particles = new Particles(v2d_particles);
	icon = new Icon(v2d_game, scene, stats, particles);
	icon->draw();
	scene->draw(v2d_game, v2d_particles);
	bg->draw(v2d_game, DrawingWindow::width * SCENE_FACTOR, DrawingWindow::height);

	// Initializeaza si adauga textul la contextul corespunzator.
	std::string lives, points;
	points = "Points " + std::to_string((_Longlong)stats->get_flags()) + " / 5";
	points_text = new Text(points, Point2D(DrawingWindow::width / 2 - 25, 25), Color(0, 0, 0), BITMAP_HELVETICA_18);
	addText_to_Visual2D(points_text, v2d_stats);

	lives = "Lives " + std::to_string((_Longlong)stats->get_lives());
	lives_text = new Text(lives, Point2D(DrawingWindow::width - 75, 25), Color(0, 0, 0), BITMAP_HELVETICA_18);
	addText_to_Visual2D(lives_text, v2d_stats);

}

//functia care permite animatia
void DrawingWindow::onIdle()
{
	if (stop == 1)
		return;
	pas = icon->get_x();
	v2d_game->fereastra(pas, 0, DrawingWindow::width + pas, DrawingWindow::height);
	v2d_particles->fereastra(pas, 0, DrawingWindow::width + pas, DrawingWindow::height);

	// Animez obiectele dinamice de pe scena.
	scene->move();

	switch(icon->move()) {
	case DEAD:
	case EXTRA_LIFE: // Actualizeaza text despre vieti.
		removeText_from_Visual2D(lives_text, v2d_stats);
		lives_text->text = "Lives " + std::to_string((_Longlong)stats->get_lives());
		addText_to_Visual2D(lives_text, v2d_stats);
		break;
	case EXTRA_POINT: // Actualizeaza text despre puncte.
		removeText_from_Visual2D(points_text, v2d_stats);
		points_text->text = "Points " + std::to_string((_Longlong)stats->get_flags()) + " / 5";
		addText_to_Visual2D(points_text, v2d_stats);
		break;
	}
	if (stats->get_lives() == 0 || stats->get_flags() == 5) {
		removeText_from_Visual2D(points_text, v2d_stats);
		removeText_from_Visual2D(lives_text, v2d_stats);
		std::string message;
		if (stats->get_lives() == 0)
			message = "GAME OVER!";
		else
			message = "CONGRATS! YOU WON!";
		points_text = new Text(message, Point2D(DrawingWindow::width / 2 - 25, 25), Color(0, 0, 0), BITMAP_TIMES_ROMAN_24);
		addText_to_Visual2D(points_text, v2d_stats);
		stop = 1;
	}
}

//functia care se apeleaza la redimensionarea ferestrei
void DrawingWindow::onReshape(int width,int height)
{
	v2d_game->poarta(0, 0, width, height);
}

//functia care defineste ce se intampla cand se apasa pe tastatura
void DrawingWindow::onKey(unsigned char key)
{
	switch(key)
	{
		case 32 : // Tasta SPACE.
			icon->jump();
			break;
	}
}

//functia care defineste ce se intampla cand se da click pe mouse
void DrawingWindow::onMouse(int button,int state,int x, int y)
{
}

int main(int argc, char** argv)
{
	//creare fereastra
	DrawingWindow dw(argc, argv, 1000, 600, 100, 50, "Tema 1 - Geometry Dash");
	//se apeleaza functia init() - in care s-au adaugat obiecte
	dw.init();
	//se intra in bucla principala de desenare - care face posibila desenarea, animatia si procesarea evenimentelor
	dw.run();
	return 0;
}