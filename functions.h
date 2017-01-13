#include "labyrinthAPI.h"

#ifndef functions_h
#define functions_h

typedef struct {

	char ** plateau;
	int sizeX;
	int sizeY;
	
	int j1_posX;
	int j1_posY;
	int j1_energy;
	
	int j2_posX;
	int j2_posY;
	int j2_energy;
	
	int t_posX;
	int t_posY;
	
	t_move last_move;
	
	int lab_has_change;

}Lab;

t_move playRandom (Lab *lab, int player);

int possible(Lab *lab, t_move move, int player);

void show_lab( char* labData, int sizeX, int sizeY);
void show_plateau( Lab lab );

Lab make_lab(char * lab, int sizeX, int sizeY, int player);

void update(Lab *lab, t_move move, int player);

void rotation(Lab *lab, t_move move, int player);


#endif