#include<stdio.h>
#include<stdlib.h>
#include"labyrinthAPI.h"
#include"functions.h"


#ifndef functions_c
#define functions_c

#define DEBUG
//#undef DEBUG

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
				else if (lab->plateau[lab->j1_posY-1][lab->j1_posX] != '|' ) a = 1;
			}
			else
			{
				if (lab->j2_posY == lab->sizeY-1)
				{
					if (lab->plateau[0][lab->j2_posX] != '|' ) a = 1;
				}
				else if (lab->plateau[lab->j2_posY-1][lab->j2_posX] != '|' ) a = 1;
			}
			
			#ifdef DEBUG
				if(a==1)
					printf(" ==== move down asked by %d ",player );
				if (player == 0)
				{
					if (lab->j1_posY == lab->sizeY-1)
					{
						printf(" jump, %c\n",lab->plateau[0][lab->j1_posX] );
					}
					else printf(" no jump, '%c' \n",lab->plateau[lab->j1_posY-1][lab->j1_posX]);
				}
				else
				{
					if (lab->j1_posY == lab->sizeY-1)
					{
						printf(" jump, %c\n",lab->plateau[0][lab->j2_posX] );
					}
					else printf(" no jump, '%c' \n",lab->plateau[lab->j1_posY-1][lab->j2_posX]);
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
				else if (lab->plateau[lab->j1_posY+1][lab->j1_posX] != '|' ) a = 1;
			}
			else
			{
				if (lab->j2_posY == 0)
				{
					if (lab->plateau[lab->sizeY-1][lab->j2_posX] != '|' ) a = 1;
				}
				else if (lab->plateau[lab->j2_posY+1][lab->j2_posX] != '|' ) a = 1;
			}
		break;
		
		case MOVE_LEFT:
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
				if (lab->j2_posX == lab->sizeX-1)
				{
					if (lab->plateau[lab->j2_posY][0] != '|' ) a = 1;
				}
				else if (lab->plateau[lab->j2_posY][lab->j2_posX+1] != '|' ) a = 1;
			}
		break;
		
		case MOVE_RIGHT:
			if (player == 0)
			{
				if (lab->j1_posX == lab->sizeX-1)
				{
					if (lab->plateau[lab->j1_posY][0] != '|' ) a = 1;
				}
				else if (lab->plateau[lab->j1_posY][lab->j1_posX-1] != '|' ) a = 1;
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
			a=1;
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

	if (player == 0) lab->j1_energy-=5;
	else lab->j2_energy-=5;

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
