// Despa Diana Alexandra 331CA

#include "Icon.h"

Icon::Icon(Visual2D *v2d, Scene *scene, Stats *stats, Particles *particles)
{
	this->v2d = v2d;
	this->scene = scene;
	this->stats = stats;
	this->particles = particles;

	v = 5;
	initial_x = 300;
	initial_y = 100;
	center = new Point2D(Scene::SS / 2, Scene::SS / 2);
	stats->set_checkpoint(new Point2D(initial_x, initial_y));
	initialize_move();
}

Icon::~Icon()
{
}

void Icon::initialize_move()
{
	p_x = 0;
	p_y = 0;
	prev_x = 0;
	prev_y = 0;
	jumping = 0;
	auto_jump = 0;
	falling = 0;
	super_jump = 0;
	angle = 2 * PI;
	initial_x = stats->get_checkpoint()->x;
	initial_y = stats->get_checkpoint()->y;
	stats->set_bonus(0);
	stats->set_booster(0);
	particles->clear();
}

int Icon::is_on_platform()
{
	Point2D *p = adjust(this->down_point());
	if (angle * 2 / PI -  floor(angle * 2 / PI) == 0 && // angle este multiplu de PI/2
		scene->get(p->y - 1, p->x) == BLOCK) {
		return 1;
	}
	return 0;
}

void Icon::jump()
{
	if (is_on_platform() == 1) {
		jumping = 1;
		prev_x = p_x;
		prev_y = p_y;
	}
}

int Icon::get_x()
{
	return p_x + initial_x - 300;
}

void Icon::draw()
{
	face = new Rectangle2D(Point2D(3, 3), Scene::SS - 6, Scene::SS - 6, Color(0.9, 0.658, 0.811), true);
	left_eye = new Rectangle2D(Point2D(10, 30), 10, 10, Color(0.168, 0.168, 0.431), true);
	left_twinkle = new Rectangle2D(Point2D(12, 36), 2, 2, Color(1, 1, 1), true);
	right_eye = new Rectangle2D(Point2D(30, 30), 10, 10, Color(0.168, 0.168, 0.431), true);
	right_twinkle = new Rectangle2D(Point2D(32, 36), 2, 2, Color(1, 1, 1), true);
	nose = new Rectangle2D(Point2D(20, 20), 10, 3, Color(0.168, 0.168, 0.431), true);
	mouth = new Polygon2D(Color(0.168, 0.168, 0.431), true);
	mouth->addPoint(Point2D(10, 15));
	mouth->addPoint(Point2D(20, 5));
	mouth->addPoint(Point2D(30, 5));
	mouth->addPoint(Point2D(40, 15));
	teeth = new Polygon2D(Color(1, 1, 1), true);
	teeth->addPoint(Point2D(15, 13));
	teeth->addPoint(Point2D(22, 7));
	teeth->addPoint(Point2D(28, 7));
	teeth->addPoint(Point2D(35, 13));
	shape = new Rectangle2D(Point2D(0, 0), Scene::SS, Scene::SS, Color(0.168, 0.168, 0.431), true);

	objects.push_back(face);
	objects.push_back(left_eye);
	objects.push_back(left_twinkle);
	objects.push_back(right_eye);
	objects.push_back(right_twinkle);
	objects.push_back(nose);
	objects.push_back(mouth);
	objects.push_back(teeth);
	objects.push_back(shape);

	DrawingWindow::addObject2D_to_Visual2D(left_twinkle, v2d);
	DrawingWindow::addObject2D_to_Visual2D(left_eye, v2d);
	DrawingWindow::addObject2D_to_Visual2D(right_twinkle, v2d);
	DrawingWindow::addObject2D_to_Visual2D(right_eye, v2d);
	DrawingWindow::addObject2D_to_Visual2D(nose, v2d);
	DrawingWindow::addObject2D_to_Visual2D(teeth, v2d);
	DrawingWindow::addObject2D_to_Visual2D(mouth, v2d);
	DrawingWindow::addObject2D_to_Visual2D(face, v2d);
	DrawingWindow::addObject2D_to_Visual2D(shape, v2d);

	apply_move();
}

void Icon::reset()
{
	stats->dec_lives();
	initialize_move();
	apply_move();
}

double Icon::formula(double x)
{
	return x * COEF_B - COEF_A * G * x * x;
}

Point2D * Icon::adjust(Point2D *point)
{
	// verific daca e intreg si cum e fata de centru
	Point2D *result = new Point2D(point->x / Scene::SS, point->y / Scene::SS);
	if (result->y - floor(result->y) == 0.0 && point->y > center->y) {
		result->y--;
	}
	if (result->x - floor(result->x) == 0.0 && point->x > center->x)
		result->x--;
	return result;
}

ReturnValues Icon::move()
{
	Point2D *right_point = adjust(this->right_point()),
		*down_point = adjust(this->down_point()),
		*up_point = adjust(this->up_point()),
		*left_point = adjust(this->left_point());

	// Verific daca atinge baza scenei sau daca atinge marginea unei alte platforme.
	if (down_point->y <= 0 || scene->get(right_point->y, right_point->x) == BLOCK ||
		scene->get(up_point->y, up_point->x) == BLOCK ||
		scene->get(right_point->y, right_point->x) == CONE ||
		scene->get(up_point->y, up_point->x) == CONE ||
		scene->get(down_point->y, down_point->x) == CONE ||
		scene->get(center->y / Scene::SS - 1, center->x / Scene::SS) == CONE) {
		reset();
		return DEAD;
	}

	// Verific daca este pe platforma pentru a activa efectul de particule.
	if (is_on_platform() == 1)
		particles->draw(center->x - Scene::SS / 2, center->y - Scene::SS / 2);
	else
		particles->move();

	// Verific daca atinge steag
	if (scene->get(right_point->y, right_point->x) == FLAG &&
		floor(right_point->x) * Scene::SS != stats->get_checkpoint()->x) {
		stats->inc_flags();
		// setez checkpoint la cea mai joasa platforma
		int i = right_point->y;
		while (i > 0 && scene->get(i, right_point->x) == FLAG)
			i--;
		stats->set_checkpoint(new Point2D(floor(right_point->x) * Scene::SS, (i + 1) * Scene::SS));
		return EXTRA_POINT;
	}

	// Verific daca atinge jump.
	if ((scene->get(right_point->y, right_point->x) == JUMP ||
		scene->get(down_point->y, down_point->x) == JUMP ||
		scene->get(center->y / Scene::SS - 1, center->x / Scene::SS) == JUMP)) {
		jumping = 1;
		auto_jump = 1;
		prev_x = p_x;
		prev_y = p_y;
	}

	// Verific daca atinge jump booster.
	if (scene->get(center->y / Scene::SS, center->x / Scene::SS) == BOOST &&
		center->x > stats->get_booster()) {
		stats->set_booster(center->x + Scene::SS);
		super_jump++;
	}

	// Verific daca atinge viata bonus.
	if ((scene->get(right_point->y, right_point->x) == BONUS ||
		scene->get(down_point->y, down_point->x) == BONUS) &&
		floor(left_point->x) * Scene::SS > stats->get_bonus()) {
		stats->set_bonus((right_point->x + 1) * Scene::SS);
		stats->inc_lives();
		return EXTRA_LIFE;
	}

	p_x += v;

	// Verific daca trebuie sa aterizeze pe o platforma.
	if (jumping == 1 && falling == 1 &&
		scene->get((center->y - EPS) / Scene::SS - 1, center->x / Scene::SS) == BLOCK) {
		angle = floor(angle * 2 / PI + 0.5) * PI / 2;
		jumping = 0;
		auto_jump = 0;
		falling = 0;
		if (super_jump > 0)
			super_jump--;
		p_y = ceil(p_y / Scene::SS) * Scene::SS;
	}

	if (jumping == 0) {
		// Verific daca se afla in gol.
		if (scene->get(center->y / Scene::SS - 1, center->x / Scene::SS) == FREE) {
			angle -= 0.05;
			p_y -= G;
			falling = 1;
		}
		else if (falling == 1) {
			angle = floor(angle * 2 / PI + 0.5) * PI / 2;
			p_y = floor(p_y / Scene::SS + 0.5) * Scene::SS;
			falling = 0;
		}
	}
	else {
		angle -= 0.05;
		double result = formula(p_x - prev_x),
			y_max = floor(1 / COEF_A / G);
		if (super_jump > 0) { // Dublez inaltimea.
			result += result;
			y_max += y_max;
		}
		p_y = prev_y + result;
		if (result >= y_max) // Trece de cel mai inalt punct al parabolei.
			falling = 1;
	}

	if (angle <= 0)
		angle = 2 * PI;
	apply_move();
	return OK;
}

void Icon::apply_move()
{
	int half = Scene::SS / 2;
	center->x = initial_x + half + p_x,
	center->y = initial_y + half + p_y;
	Transform2D::loadIdentityMatrix();
	Transform2D::translateMatrix(-half, -half);
	Transform2D::rotateMatrix(angle);
	Transform2D::translateMatrix(center->x, center->y);

	for (int i = 0; i < objects.size(); ++i) {
		Transform2D::applyTransform(objects[i]);
	}
}

Point2D * Icon::right_point()
{
	Point2D *chosen_point;
	int max_x = 0;
	Point2D *point;
	for (int i = 0; i < 4; ++i) {
		point = shape->transf_points[i];
		if (point->x > max_x) {
			chosen_point = point;
			max_x = point->x;
		}
	}
	return chosen_point;
}

Point2D * Icon::left_point()
{
	Point2D *chosen_point;
	int min_x = scene->get_width();
	Point2D *point;
	for (int i = 0; i < 4; ++i) {
		point = shape->transf_points[i];
		if (point->x < min_x) {
			chosen_point = point;
			min_x = point->x;
		}
	}
	return chosen_point;
}

Point2D * Icon::up_point()
{
	Point2D *chosen_point;
	int max_y = 0;
	Point2D *point;
	for (int i = 0; i < 4; ++i) {
		point = shape->transf_points[i];
		if (point->y > max_y) {
			chosen_point = point;
			max_y = point->y;
		}
	}
	return chosen_point;
}

Point2D * Icon::down_point()
{
	Point2D *chosen_point;
	int min_y = scene->get_height();
	Point2D *point;
	for (int i = 0; i < 4; ++i) {
		point = shape->transf_points[i];
		if (point->y < min_y) {
			chosen_point = point;
			min_y = point->y;
		}
	}
	return chosen_point;
}