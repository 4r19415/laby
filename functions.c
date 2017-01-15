#include<stdio.h>
#include<stdlib.h>
#include"labyrinthAPI.h"
#include"functions.h"				//test de commentaire


#ifndef functions_c
#define functions_c

#define DEBUG
#undef DEBUG

#define DEBUG_RANDOM
#undef DEBUG_RANDOM

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




t_move playRandom (Lab *lab, int player)
{
	int a=0, randn;
	
	t_move move;
	move.value=0;

	while(a==0)
	{
		
		randn = rand()%9;
		
		if (randn == 1) move.type = MOVE_UP;
		else if (randn == 2) move.type = MOVE_DOWN;
		else if (randn == 3) move.type = MOVE_LEFT;		
		else if (randn == 4) move.type = MOVE_RIGHT;
		
		else if (randn == 5) { 
			move.type =  ROTATE_LINE_LEFT;
			move.value = rand()%lab->sizeY; 
		}
		else if (randn == 6) { 
			move.type =  ROTATE_LINE_RIGHT;
			move.value = rand()%lab->sizeY; 
		}
		else if (randn == 7) { 
			move.type =  ROTATE_COLUMN_UP;
			move.value = rand()%lab->sizeX; 
		}
		else if (randn == 8) { 
			move.type =  ROTATE_COLUMN_DOWN;
			move.value = rand()%lab->sizeX; 
		}
		
		a=possible(lab, move, player);
	}
	#ifdef DEBUG
		printf("===== move = %d,%d\n",move.type,move.value);
	#endif
	return (move);
}


int possible(Lab *lab, t_move move, int player)
{
	int a = 0;
	
	
	switch(move.type)
	{
		case ROTATE_COLUMN_DOWN: 
		case ROTATE_COLUMN_UP:
		case ROTATE_LINE_RIGHT:
		case ROTATE_LINE_LEFT :
		
			if (player == 0) // add prev move
			{
				if (lab -> j1_energy >=5 && lab->last_move.value != move.value)
					a = 1;
			}
			else
			{
				if (lab -> j2_energy >=5 && lab->last_move.value != move.value)
					a = 1;
			}
					
		break;
		
		
		case MOVE_DOWN:
			if (player == 0)
			{
				if (lab->j1_posY == lab->sizeY-1)
				{
					if (lab->plateau[0][lab->j1_posX] != '|' ) a = 1;
				}
				else if (lab->plateau[lab->j1_posY+1][lab->j1_posX] != '|' ) a = 1;
			}
			else
			{
				if (lab->j2_posY == lab->sizeY-1)
				{
					if (lab->plateau[0][lab->j2_posX] != '|' ) a = 1;
				}
				else if (lab->plateau[lab->j2_posY+1][lab->j2_posX] != '|' ) a = 1;
			}
			
			#ifdef DEBUG_RANDOM
				if(a==1)
					printf(" ==== move down asked by %d ",player );
				if (player == 0)
				{
					if (lab->j1_posY == lab->sizeY-1)
					{
						printf(" jump, %c\n",lab->plateau[0][lab->j1_posX] );
						lab->plateau[0][lab->j1_posX] = 'M';
						show_plateau( *lab );
						lab->plateau[0][lab->j1_posX] = ' ';
					}
					else 
					{
						printf(" no jump, '%c' \n",lab->plateau[lab->j1_posY+1][lab->j1_posX]);
						lab->plateau[lab->j1_posY+1][lab->j1_posX] = 'M';
						show_plateau( *lab );
						lab->plateau[lab->j1_posY+1][lab->j1_posX] = ' ';
					}
				}
				else
				{
					if (lab->j1_posY == lab->sizeY-1)
					{
						printf(" jump, %c\n",lab->plateau[0][lab->j2_posX] );
						lab->plateau[0][lab->j2_posX] = 'M';
						show_plateau( *lab );
						lab->plateau[0][lab->j2_posX] = ' ';
					}
					else 
					{
						printf(" no jump, '%c' \n",lab->plateau[lab->j1_posY+1][lab->j2_posX]);
						lab->plateau[lab->j1_posY+1][lab->j2_posX] = 'M';
						show_plateau( *lab );
						lab->plateau[lab->j1_posY+1][lab->j2_posX] = ' ';
					}
				}
				
			#endif
			
		break;
		
		
		case MOVE_UP:
			if (player == 0)
			{
				if (lab->j1_posY == 0)
				{
					if (lab->plateau[lab->sizeY-1][lab->j1_posX] != '|' ) a = 1;
				}
				else if (lab->plateau[lab->j1_posY-1][lab->j1_posX] != '|' ) a = 1;
			}
			else
			{
				if (lab->j2_posY == 0)
				{
					if (lab->plateau[lab->sizeY-1][lab->j2_posX] != '|' ) a = 1;
				}
				else if (lab->plateau[lab->j2_posY-1][lab->j2_posX] != '|' ) a = 1;
			}
		break;
		
		case MOVE_LEFT:
			if (player == 0)
			{
				if (lab->j1_posX == 0)
				{
					if (lab->plateau[lab->j1_posY][lab->sizeX-1] != '|' ) a = 1;
				}
				else if (lab->plateau[lab->j1_posY][lab->j1_posX-1] != '|' ) a = 1;
			}
			else
			{
				if (lab->j2_posX == 0)
				{
					if (lab->plateau[lab->j2_posY][lab->sizeX-1] != '|' ) a = 1;
				}
				else if (lab->plateau[lab->j2_posY][lab->j2_posX-1] != '|' ) a = 1;
			}
		break;
		
		case MOVE_RIGHT:
			if (player == 0)
			{
				if (lab->j1_posX == lab->sizeX-1)
				{
					if (lab->plateau[lab->j1_posY][0] != '|' ) a = 1;
				}
				else if (lab->plateau[lab->j1_posY][lab->j1_posX+1] != '|' ) a = 1;
			}
			else
			{
				if (lab->j2_posY == lab->sizeY-1)
				{
					if (lab->plateau[0][lab->j2_posX] != '|' ) a = 1;
				}
				else if (lab->plateau[lab->j2_posY][lab->j2_posX+1] != '|' ) a = 1;
			}
		break;
		
		default:
			a=0;
		break;
		
	}
	#ifdef DEBUG
		printf("===== move asked by player %d : %d, rep = %d\n",player ,move.type,a);
	#endif
	return(a);
	
}


void rotation(Lab *lab, t_move move, int player) 
{
	int i,stock;
	
	lab-> lab_has_change =1;
	
	t_move new_move;
	
	switch(move.type)
	{
		case ROTATE_COLUMN_DOWN:
		
			#ifdef DEBUG
				printf(" ===== rotation down\n");
			#endif

			stock = lab->plateau[lab->sizeY-1][move.value];
			
			for(i= lab->sizeY-1; i> 0 ; i--)
				lab->plateau[i][move.value]=lab->plateau[i-1][move.value]; 
			
			lab->plateau[0][move.value]=stock;
			
			new_move.type = MOVE_DOWN;
	    new_move.value = 0;
	            	
	    #ifdef DEBUG
				printf(" ===== move down\n");
			#endif
			
			if (lab->j1_posX == move.value)
				update(lab, new_move, 0);
				
			if (lab->j2_posX == move.value)
				update(lab, new_move, 1);
				
			if (lab->t_posX == move.value)
				update(lab, new_move, 2);
					
		break;
		
		case ROTATE_COLUMN_UP:
		
			#ifdef DEBUG
				printf(" ===== rotation up\n");
			#endif
		
			stock = lab->plateau[0][move.value];
			
			for(i= 0; i< lab->sizeY-1 ; i++)
				lab->plateau[i][move.value]=lab->plateau[i+1][move.value]; 
			
			lab->plateau[lab->sizeY-1][move.value]=stock; 
			
			new_move.type = MOVE_UP;
	    new_move.value = 0;
	            	
	            	
			#ifdef DEBUG
				printf(" ===== move up\n");
			#endif
			
			if (lab->j1_posX == move.value)
				update(lab, new_move, 0);
				
			if (lab->j2_posX == move.value)
				update(lab, new_move, 1);
				
			if (lab->t_posX == move.value)
				update(lab, new_move, 2);
				
		break;
		
		case ROTATE_LINE_RIGHT: 
		
			#ifdef DEBUG
				printf(" ===== rotation right\n");
			#endif
			
		
			stock = lab->plateau[move.value][lab->sizeX-1];
			
			for(i= lab->sizeX-1; i > 0 ; i--)
				lab->plateau[move.value][i]=lab->plateau[move.value][i-1]; 
			
			lab->plateau[move.value][0]=stock;
			
			new_move.type = MOVE_RIGHT;
	    new_move.value = 0;
	            	
	    #ifdef DEBUG
				printf(" ===== move right\n");
			#endif
			
			if (lab->j1_posY == move.value)
				update(lab, new_move, 0);
				
			if (lab->j2_posY == move.value)
				update(lab, new_move, 1);
				
			if (lab->t_posY == move.value)
				update(lab, new_move, 2);
			
			
		break;
		
		case ROTATE_LINE_LEFT:
		
			#ifdef DEBUG
				printf(" ===== rotation left\n");
			#endif
			
		
			stock = lab->plateau[move.value][0];
			
			for(i= 0; i< lab->sizeX-1 ; i++)
				lab->plateau[move.value][i]=lab->plateau[move.value][i+1]; 
			
			lab->plateau[move.value][lab->sizeX-1]=stock; 
			
			new_move.type = MOVE_LEFT;
	    new_move.value = 0;
	            	
	    #ifdef DEBUG
				printf(" ===== move left\n");
			#endif

			if (lab->j1_posY == move.value)
				update(lab, new_move, 0);
				
			if (lab->j2_posY == move.value)
				update(lab, new_move, 1);
				
			if (lab->t_posY == move.value)
				update(lab, new_move, 2);
			
		break;
		
		default:
		break;
	
	}

	if (player == 0) lab->j1_energy-=6;
	else lab->j2_energy-=6;

}

void update(Lab *lab, t_move move, int player)
{

	lab->last_move = move;

	switch(move.type)
	{
		
		case MOVE_UP:
			if (player == 0) {
				lab->j1_posY = lab->j1_posY-1;
				if (lab->j1_posY == -1) lab->j1_posY = lab->sizeY-1;
			}
			else if ( player == 1)  {
				lab->j2_posY = lab->j2_posY-1;
				if (lab->j2_posY == -1) lab->j2_posY = lab->sizeY-1;
			}
			else {
				lab->t_posY = lab->t_posY-1;
				if (lab->t_posY == -1) lab->t_posY = lab->sizeY-1;
			}
		break;
		
		case MOVE_DOWN:
			if (player == 0) {
				lab->j1_posY = lab->j1_posY+1;
				if (lab->j1_posY == lab->sizeY) lab->j1_posY = 0;
			}
			else if ( player == 1){
				lab->j2_posY = lab->j2_posY+1;
				if (lab->j2_posY == lab->sizeY) lab->j2_posY = 0;
			}
			else {
				lab->t_posY = lab->t_posY+1;
				if (lab->t_posY == lab->sizeY) lab->t_posY = 0;
			}
		break;
		
		case MOVE_LEFT:
			if (player == 0) {
				lab->j1_posX = lab->j1_posX-1;
				if (lab->j1_posX == -1) lab->j1_posX = lab->sizeX-1;
			}
			else if ( player == 1){
				lab->j2_posX = lab->j2_posX-1;
				if (lab->j2_posX == -1) lab->j2_posX = lab->sizeX-1;
			}
			else{
				lab->t_posX = lab->t_posX-1;
				if (lab->t_posX == -1) lab->t_posX = lab->sizeX-1;
			}
		break;
		
		case MOVE_RIGHT:
			if (player == 0) {
				lab->j1_posX = lab->j1_posX+1;
				if (lab->j1_posX == lab->sizeX) lab->j1_posX = 0;
			}
			else if ( player == 1){
				lab->j2_posX = lab->j2_posX+1;
				if (lab->j2_posX == lab->sizeX) lab->j2_posX = 0;
			}
			else{
				lab->t_posX = lab->t_posX+1;
				if (lab->t_posX == lab->sizeX) lab->t_posX = 0;
			}
		break;
		
		case DO_NOTHING:
		break;
		 
		default:  // for rotation
			rotation(lab, move, player);
		break;
		
	}
}


Lab make_lab(char * labData, int sizeX, int sizeY, int player)
{
	Lab lab;
	
	int i, j;
	
    lab.plateau = (char**)malloc(sizeY*sizeof(char*));
    for (i = 0; i<sizeY; i++)
        lab.plateau[i]=(char*)malloc(sizeX*sizeof(char));

	lab.sizeX = sizeX;
	lab.sizeY = sizeY;
	
    for(i=0; i<sizeY; i++ )
        for (j=0; j<sizeX; j++)
        {
        	if (labData[i*sizeX+j] == 0) lab.plateau[i][j] = ' ';
            else lab.plateau[i][j] = '|';
        }
   
    lab.t_posX = lab.sizeX/2;
    lab.t_posY = lab.sizeY/2;
     
    if (player == 0)
    {
			lab.j1_posX = 0;
			lab.j1_posY = lab.sizeY/2;
			lab.j1_energy = 0;
		
			lab.j2_posX = lab.sizeX-1;
			lab.j2_posY = lab.sizeY/2;
			lab.j2_energy = 0;
    }
    else
   	{
			lab.j2_posX = 0;
			lab.j2_posY = lab.sizeY/2;
			lab.j2_energy = 0;
		
			lab.j1_posX = lab.sizeX-1;
			lab.j1_posY = lab.sizeY/2;
			lab.j1_energy = 0;
    }
    
    return (lab);
}


void show_plateau( Lab lab )
{    

    int i, j;
    printf(" ");
    for(i=0; i<lab.sizeY; i++ )
    {
    	for (j=0; j<lab.sizeX; j++)
      {
				
				if (i == lab.j2_posY && j == lab.j2_posX)
					printf("2 ");
					
				else if (i == lab.t_posY && j == lab.t_posX)
					printf("T ");
					
				else if (i == lab.j1_posY && j == lab.j1_posX)
					printf("1 ");
					
				else
					printf("%c ",lab.plateau[i][j]);
				
			}
      printf("\n ");
    }
    printf("Energy 1 = %d, energy 2 = %d\n", lab.j1_energy, lab.j2_energy);
}


void show_lab( char* labData, int sizeX, int sizeY)
{    
    int i, j;
    for(i=0; i<sizeY; i++ )
    {
        for (j=0; j<sizeX; j++)
        {
        	if (labData[i*sizeX+j] == 0) printf(" ");
            else printf("|");
        }
        printf("\n");
    }
}

int verif(int move, int value, char* labData, int sizeX, int sizeY)
{
    return(0);
}

#endif
