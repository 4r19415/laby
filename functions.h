#include "labyrinthAPI.h"
#include "lab_type.h"

#ifndef functions_h
#define functions_h



t_move playRandom (Lab *lab, int player);

int possible(Lab *lab, t_move move, int player);

void show_lab( char* labData, int sizeX, int sizeY);
void show_plateau( Lab lab );

Lab make_lab(char * lab, int sizeX, int sizeY, int player);

void update(Lab *lab, t_move move, int player);

void rotation(Lab *lab, t_move move, int player);


#endif
