// Despa Diana Alexandra 331CA

#include "Stats.h"


Stats::Stats()
{
	flags = 0;
	lives = 3;
	checkpoint = new Point2D(0, 0);
	booster = 0;
	bonus = 0;
}


Stats::~Stats()
{
}

void Stats::inc_flags()
{
	flags++;
}

int Stats::get_flags()
{
	return flags;
}

void Stats::inc_lives()
{
	lives++;
}

void Stats::dec_lives()
{
	lives--;
}

int Stats::get_lives()
{
	return lives;
}

void Stats::set_checkpoint(Point2D *checkpoint)
{
	this->checkpoint = checkpoint;
}

Point2D * Stats::get_checkpoint()
{
	return checkpoint;
}

void Stats::set_booster(int booster)
{
	this->booster = booster;
}

int Stats::get_booster()
{
	return booster;
}

void Stats::set_bonus(int bonus)
{
	this->bonus = bonus;
}

int Stats::get_bonus()
{
	return bonus;
}