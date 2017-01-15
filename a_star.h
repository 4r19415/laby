#include "labyrinthAPI.h"
#include "lab_type.h"

#ifndef A_STAR_H
#define A_STAR_H


int heuristique(Lab *lab, int x, int y);

t_move a_star(Lab * lab, int player);

Case * search_for_neighbour(Lab * lab, Case watched_case);



#endif
