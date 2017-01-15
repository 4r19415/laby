#include "a_star.h"
#include<stdio.h>
#include<stdlib.h>

#define DEBUG_NEIGHBOUR
#undef DEBUG_NEIGHBOUR

#define DEBUG_A_STAR



t_move a_star(Lab * lab, int player) //TOWORK
{

	#ifdef DEBUG_A_STAR
		printf("===== enter in A* for player %d\n",player+1);
	#endif
	
	Case * open_list = (Case *) malloc(sizeof(Case)*lab->sizeX*lab->sizeY);
	int n_open_list = 0;
	
	Case * close_list = (Case *) malloc(sizeof(Case)*lab->sizeX*lab->sizeY);
	int n_close_list = 0;
	
	Case first_case;
	
	if (player == 0)
	{
		first_case.x = (lab->j1_posX);
		first_case.y = (lab->j1_posY);
	}
	else
	{
		first_case.x = (lab->j2_posX);
		first_case.y = (lab->j2_posY);
	}

	first_case.heuristique = heuristique(lab, first_case.x, first_case.y);
	first_case.cost = 0;
	first_case.p_case = NULL;
	
	open_list[0] = first_case;
	
	int i=0;
	
	Case * neighbour;
	neighbour = search_for_neighbour(lab, first_case);  
	
	
	for (i=0 ; i<9 ; i++ )
		if (neighbour[i].cost != -1)  
		{
			open_list[n_open_list] = neighbour[i];
			n_open_list ++;
		}
		
	
}


Case * search_for_neighbour(Lab * lab, Case watched_case) //TODO
{

	#ifdef DEBUG_NEIGHBOUR
		printf("===== enter in search_for_neighbour of %d; %d \n", watched_case.y, watched_case.x);
	#endif
	
	Case * neighbour = (Case *) malloc(sizeof(Case)*8);
	
	int left_side = watched_case.x - 1 , right_side = watched_case.x + 1 , 
			up_side = watched_case.y - 1, down_side = watched_case.y + 1;
	
	if (watched_case.x == lab-> sizeX -1) right_side = 0;
	else if (watched_case.x == 0 ) left_side = lab-> sizeX -1;
	
	if (watched_case.y == lab-> sizeY -1) down_side = 0;
	else if (watched_case.y == 0 ) up_side = lab-> sizeY -1;
	
	int to_append[8][2]= {{watched_case.y, right_side},
												{watched_case.y, left_side},
												{up_side, right_side},
												{up_side, watched_case.x},
												{up_side, left_side},
												{down_side, right_side},
												{down_side, watched_case.x},
												{down_side, left_side}};
												
	int i;
	
	for (i=0; i<8 ;i++)
	{
		
		neighbour[i].x = to_append[i][1];
		neighbour[i].y = to_append[i][0];
		
		neighbour[i].heuristique = heuristique(lab, neighbour[i].x, neighbour[i].y);
		
		if(lab->plateau[to_append[i][0]][to_append[i][1]] == '|') 
			neighbour[i].cost = -1;
		else neighbour[i].cost = watched_case.cost+1;
		
		neighbour[i].p_case = & watched_case;
		neighbour[i].xp = watched_case.x;
		neighbour[i].yp = watched_case.y;
		
		
		#ifdef DEBUG_NEIGHBOUR
			printf ("neighbour = '%d' , '%d' , cost = %d \n ", to_append[i][0], to_append[i][1],neighbour[i].cost);
		#endif
		
		
	}
	
	return(neighbour);

}

int heuristique(Lab *lab, int x, int y)
{
	return(abs(x-lab->t_posX)+abs(y-lab->t_posY));
}
