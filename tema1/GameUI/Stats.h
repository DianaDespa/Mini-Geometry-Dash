// Despa Diana Alexandra 331CA

#pragma once
#include "../Framework/Point2D.h"

class Stats
{
private:
	int flags,		// Numar de puncte.
		lives,		// Numar de vieti/incercari ramase.
		booster,	// Coordonata X a ultimului JUMP automat. 
		bonus;		// Coordonata X a ultimului bonus de viata.
	Point2D *checkpoint; // Ultimul checkpoint.

public:
	Stats();
	~Stats();

	void inc_flags();							// Creste numarul de puncte.
	int get_flags();							// Intoarce numarul de puncte.
	void inc_lives();							// Creste numarul de vieti.
	void dec_lives();							// Scade numarul de vieti.
	int get_lives();							// Intoarce numarul de vieti.
	void set_checkpoint(Point2D *checkpoint);	// Seteaza checkpoint.
	Point2D *get_checkpoint();					// Intoarce checkpoint.
	void set_booster(int booster);				// Seteaza booster.
	void set_bonus(int bonus);					// Seteaza bonus.
	int get_booster();							// Intoarce booster.
	int get_bonus();							// Intoarce bonus.
};

