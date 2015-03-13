// Despa Diana Alexandra 331CA

#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

Scene::Scene(int width, int height)
{
	this->width = width;
	this->height = height;
	frames = 0;
	world = std::vector< std::vector<SceneObject> >(height / SS, std::vector<SceneObject>(width / SS, FREE));
}

void Scene::draw(Visual2D *v2d, Visual2D *v2d_dynam)
{
	this->v2d = v2d;
	this->v2d_dynam = v2d_dynam;
	draw_basic_square(10, 2, 0, 0);
	draw_basic_square(35, 2, 600, 0);
	draw_cone(850, 100, 1);
	draw_basic_square(25, 1, 1100, 100);
	draw_basic_square(20, 2, 1350, 150);
	draw_basic_square(9, 2, 1600, 250);
	draw_basic_square(9, 1, 1600, 550);
	draw_reverse_cone(1650, 500, 7);
	draw_flag(1800, 350);
	draw_cone(2050, 250, 6);
	draw_jump(2250, 350);
	draw_basic_square(2, 1, 2550, 100);
	draw_jump(2800, 200);
	draw_basic_square(2, 1, 2950, 300);
	draw_jump(3200, 400);
	draw_basic_square(2, 7, 3450, 0);
	draw_basic_square(2, 5, 3550, 0);
	draw_cone(3650, 0, 1);
	draw_basic_square(5, 1, 3700, 0);
	draw_boost(3800, 50);
	draw_basic_square(7, 1, 3950, 150);
	draw_cone(3950, 200, 1);
	draw_boost(4150, 200);
	draw_basic_square(10, 1, 4350, 350);
	draw_cone(4550, 400, 2);
	draw_cone(4850, 0, 6);
	draw_basic_square(7, 3, 5150, 0);
	draw_flag(5300, 150);
	draw_jump(5550, 100);
	draw_jump(5700, 200);
	draw_jump(5900, 300);
	draw_basic_square(6, 1, 6100, 350);
	draw_reverse_cone(6100, 550, 6);
	draw_basic_square(8, 2, 6550, 0);
	draw_boost(6600, 100);
	draw_basic_square(3, 1, 6650, 300);
	draw_bonus(6700, 350);
	draw_cone(6950, 0, 4);
	draw_basic_square(5, 2, 7150, 0);
	draw_basic_square(3, 1, 6800, 400);
	draw_jump(7150, 400);
	draw_bonus(7200, 100);
	draw_basic_square(7, 1, 7450, 150);
	draw_flag(7550, 200);
	draw_cone(7750, 200, 1);
	draw_basic_square(4, 3, 7950, 0);
	draw_basic_square(3, 1, 8150, 200);
	draw_basic_square(3, 1, 8300, 300);
	draw_basic_square(3, 1, 8300, 550);
	draw_reverse_cone(8300, 500, 3);
	draw_cone(8150, 0, 17);
	draw_jump(8700, 250);
	draw_basic_square(21, 1, 9000, 0);
	draw_basic_square(13, 2, 9400, 50);
	draw_cone(9600, 150, 2);
	draw_boost(9800, 150);
	draw_basic_square(1, 4, 10000, 150);
	draw_jump(10100, 150);
	draw_basic_square(18, 2, 10300, 50);
	draw_flag(10600, 150);
	draw_jump(11200, 250);
	draw_basic_square(25, 1, 11400, 350);
	draw_bonus(12250, 400);
	draw_basic_square(3, 1, 12650, 250);
	draw_basic_square(3, 1, 12800, 150);
	draw_basic_square(7, 1, 12950, 50);
	draw_basic_square(3, 1, 13450, 0);
	draw_basic_square(24, 1, 13750, 0);
	draw_boost(13850, 50);
	draw_boost(14300, 50);
	draw_basic_square(5, 4, 14900, 0);
	draw_basic_square(3, 6, 15150, 0);
	draw_basic_square(3, 8, 15300, 0);
	draw_basic_square(5, 10, 15450, 0);
	draw_basic_square(2, 9, 15700, 0);
	draw_cone(15700, 450, 2);
	draw_basic_square(4, 10, 15800, 0);
	draw_basic_square(2, 9, 16000, 0);
	draw_cone(16000, 450, 2);
	draw_basic_square(4, 10, 16100, 0);
	draw_cone(16300, 0, 50);
	draw_jump(16450, 200);
	draw_jump(16750, 100);
	draw_jump(16850, 250);
	draw_jump(17100, 250);
	draw_jump(17350, 350);
	draw_jump(17650, 250);
	draw_basic_square(3, 3, 17900, 150);
	draw_flag(17950, 300);
	draw_basic_square(2, 2, 18200, 400);
	draw_basic_square(2, 2, 18500, 400);
	draw_basic_square(8, 1, 18200, 250);
	draw_basic_square(1, 1, 18250, 200);
	draw_basic_square(1, 1, 18500, 200);
	draw_basic_square(4, 1, 18300, 150);
}

void Scene::draw_basic_square(int times_x, int times_y, int start_x, int start_y)
{
	Rectangle2D *square, *outline;
	int i = start_y / SS,
		j = start_x / SS,
		x, y;
	for (int l = 0; l < times_y; ++l) {
		y = start_y + l * SS;
		for (int k = 0; k < times_x; ++k) {
			x = start_x + k * SS;
			square = new Rectangle2D(Point2D(x + 3, y + 3), SS - 6, SS - 6, Color(0.274, 0.101, 0.439), true);
			outline = new Rectangle2D(Point2D(x, y), SS, SS, Color(0.337, 0.337, 0.658), true);
			DrawingWindow::addObject2D_to_Visual2D(square, v2d);
			DrawingWindow::addObject2D_to_Visual2D(outline, v2d);
			world[i + l][j + k] = BLOCK;
		}
	}
}

void Scene::draw_dynam_platform(int times_x, int times_y, int start_x, int start_y)
{
	int i = start_y / SS,
		j = start_x / SS,
		x, y;
	Rectangle2D *outline = new Rectangle2D(Point2D(start_x, start_y), times_x * SS, times_y * SS, Color(0.274, 0.101, 0.439), true);
	DrawingWindow::addObject2D_to_Visual2D(outline, v2d_dynam);
	for (int l = 0; l < times_y; ++l) {
		y = start_y + l * SS;
		for (int k = 0; k < times_x; ++k) {
			x = start_x + k * SS;
			world[i + l][j + k] = BLOCK;
			dynam_locations.push_back(std::make_pair(i + l, j + k));
		}
	}
	dynamic_objects.push_back(outline);
}

void Scene::draw_dynam_cone(int x, int y, int times)
{
	Polygon2D *cone;

	int aux;
	for (int i = 0; i < times; ++i) {
		aux = x + i * SS;
		cone = new Polygon2D(Color(0.4, 0.1, 0), true);
		cone->addPoint(Point2D(aux, y));
		cone->addPoint(Point2D(aux + SS , y));
		cone->addPoint(Point2D(aux + SS / 2, y + SS));
		DrawingWindow::addObject2D_to_Visual2D(cone, v2d_dynam);
		dynamic_objects.push_back(cone);
		world[(int)(y / SS)][(int)(x / SS) + i] = CONE;
		dynam_locations.push_back(std::make_pair((int)(y / SS), (int)(x / SS) + i));
	}
}

void Scene::draw_cone(int x, int y, int times)
{
	Polygon2D *cone, *outline;

	int aux;
	for (int i = 0; i < times; ++i) {
		aux = x + i * SS;
		cone = new Polygon2D(Color(0.4, 0.1, 0), true);
		cone->addPoint(Point2D(aux + 6, y + 3));
		cone->addPoint(Point2D(aux + SS - 6, y + 3));
		cone->addPoint(Point2D(aux + SS / 2, y + SS - 9));
		outline = new Polygon2D(Color(1, 0, 0), true);
		outline->addPoint(Point2D(aux, y));
		outline->addPoint(Point2D(aux + SS, y));
		outline->addPoint(Point2D(aux + SS / 2, y + SS));
		DrawingWindow::addObject2D_to_Visual2D(cone, v2d);
		DrawingWindow::addObject2D_to_Visual2D(outline, v2d);
		world[(int)(y / SS)][(int)(x / SS) + i] = CONE;
	}
}

void Scene::draw_reverse_cone(int x, int y, int times)
{
	Polygon2D *cone, *outline;

	int aux;
	for (int i = 0; i < times; ++i) {
		aux = x + i * SS;
		cone = new Polygon2D(Color(0.4, 0.1, 0), true);
		cone->addPoint(Point2D(aux + 6, y + SS - 3));
		cone->addPoint(Point2D(aux + SS - 6, y + SS - 3));
		cone->addPoint(Point2D(aux + SS / 2, y + 8));
		outline = new Polygon2D(Color(1, 0, 0), true);
		outline->addPoint(Point2D(aux, y + SS));
		outline->addPoint(Point2D(aux + SS, y + SS));
		outline->addPoint(Point2D(aux + SS / 2, y));
		DrawingWindow::addObject2D_to_Visual2D(cone, v2d);
		DrawingWindow::addObject2D_to_Visual2D(outline, v2d);
		world[(int)(y / SS)][(int)(x / SS) + i] = CONE;
	}
}

void Scene::draw_flag(int x, int y)
{
	Rectangle2D *pole = new Rectangle2D(Point2D(x + SS / 2, y), 4, 2 * SS, Color(0, 0, 0), true);
	Polygon2D *flag, *outline;

	flag = new Polygon2D(Color(1, 1, 1), true);
	flag->addPoint(Point2D(x + SS / 2 - 2, y + SS + 8));
	flag->addPoint(Point2D(x + SS / 2 - 2, y + 2 * SS - 8));
	flag->addPoint(Point2D(x + 6, y + 3 * SS / 2));
	outline = new Polygon2D(Color(0, 0, 0), true);
	outline->addPoint(Point2D(x + SS / 2, y + SS));
	outline->addPoint(Point2D(x + SS / 2, y + 2 * SS));
	outline->addPoint(Point2D(x, y + 3 * SS / 2));
	DrawingWindow::addObject2D_to_Visual2D(pole, v2d);
	DrawingWindow::addObject2D_to_Visual2D(flag, v2d);
	DrawingWindow::addObject2D_to_Visual2D(outline, v2d);
	int i = (int)(y / SS);
	while (i < height / SS && world[i][(int)(x / SS)] == 0)
		world[i++][(int)(x / SS)] = FLAG;
}

void Scene::draw_jump(int x, int y)
{
	Circle2D *circle = new Circle2D(Point2D(x + SS / 2, y + 2 * SS / 3), SS / 3, Color(1,1,0.8), true);
	DrawingWindow::addObject2D_to_Visual2D(circle, v2d);
	circle = new Circle2D(Point2D(x + SS / 2, y + 2 * SS / 3), SS / 3 + 4, Color(1, 1, 0.8), false);
	DrawingWindow::addObject2D_to_Visual2D(circle, v2d);
	world[(int)(y / SS)][(int)(x / SS)] = JUMP;
}

void Scene::draw_boost(int x, int y)
{
	Rectangle2D *vertical = new Rectangle2D(Point2D(x + SS / 2 - 5, y), 10, SS - 30, Color(0, 0.5, 0), true);
	Polygon2D *head = new Polygon2D(Color(0, 0.5, 0), true);
	head->addPoint(Point2D(x + SS / 2, y + SS));
	head->addPoint(Point2D(x + 10, y + SS - 30));
	head->addPoint(Point2D(x + SS - 10, y + SS - 30));
	DrawingWindow::addObject2D_to_Visual2D(vertical, v2d);
	DrawingWindow::addObject2D_to_Visual2D(head, v2d);
	world[(int)(y / SS)][(int)(x / SS)] = BOOST;
}

void Scene::draw_bonus(int x, int y)
{
	Rectangle2D *vertical = new Rectangle2D(Point2D(x + SS / 2 - 5, y), 10, SS, Color(1, 0, 0), true),
		*horizontal = new Rectangle2D(Point2D(x, y + SS / 2 - 5), SS, 10, Color(1, 0, 0), true);
	DrawingWindow::addObject2D_to_Visual2D(vertical, v2d);
	DrawingWindow::addObject2D_to_Visual2D(horizontal, v2d);
	world[(int)(y / SS)][(int)(x / SS)] = BONUS;
}

SceneObject Scene::get(int i, int j)
{
	return world[i][j];
}

int Scene::get_width()
{
	return width;
}

int Scene::get_height()
{
	return height;
}

void Scene::move()
{
	if (frames % PERIOADA == 0) {
		clear_dynamic_objects();
		switch (frames / PERIOADA) {
		case 0:
			draw_dynam_platform(8, 1, 8400, 150);
			draw_dynam_platform(2, 1, 9200, 150);
			draw_dynam_platform(3, 1, 9950, 400);
			draw_dynam_cone(10850, 150, 1);
			draw_dynam_cone(12000, 400, 1);
			draw_dynam_cone(12500, 400, 1);
			draw_dynam_platform(1, 2, 14000, 50);
			draw_dynam_platform(1, 2, 14600, 200);
			break;
		case 1:
		case 5: 
			draw_dynam_platform(8, 1, 8450, 150);
			draw_dynam_platform(2, 1, 9150, 150);
			draw_dynam_platform(3, 1, 9950, 450);
			draw_dynam_cone(10900, 150, 1);
			draw_dynam_cone(12050, 400, 1);
			draw_dynam_cone(12450, 400, 1);
			draw_dynam_platform(1, 2, 14000, 100);
			draw_dynam_platform(1, 2, 14600, 150);
			break;
		case 2:
		case 4:
			draw_dynam_platform(8, 1, 8500, 150);
			draw_dynam_platform(2, 1, 9100, 150);
			draw_dynam_platform(3, 1, 9950, 500);
			draw_dynam_cone(10950, 150, 1);
			draw_dynam_cone(12100, 400, 1);
			draw_dynam_cone(12400, 400, 1);
			draw_dynam_platform(1, 2, 14000, 150);
			draw_dynam_platform(1, 2, 14600, 100);
			break;
		case 3:
			draw_dynam_platform(8, 1, 8550, 150);
			draw_dynam_platform(2, 1, 9050, 150);
			draw_dynam_platform(3, 1, 9950, 550);
			draw_dynam_cone(10950, 150, 1);
			draw_dynam_cone(12100, 400, 1);
			draw_dynam_cone(12400, 400, 1);
			draw_dynam_platform(1, 2, 14000, 200);
			draw_dynam_platform(1, 2, 14600, 50);
			break;
		}
	}
	frames++;
	if (frames > 5 * PERIOADA)
		frames = 0;
}

void Scene::clear_dynamic_objects()
{
	int i;
	for (i = 0; i < dynamic_objects.size(); ++i) {
		DrawingWindow::removeObject2D_from_Visual2D(dynamic_objects[i], v2d_dynam);
	}
	for (i = 0; i < dynam_locations.size(); ++i) {
		world[dynam_locations[i].first][dynam_locations[i].second] = FREE;
	}
	dynamic_objects.clear();
	dynam_locations.clear();
}