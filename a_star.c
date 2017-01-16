/*############################################################################
  #                                                                          #
  #  a_star.c                                                                #
  #                                                                          #
  #  For project ROB3 labyrrinth                                             #
  #                                                                          #
  #  Authors: <Bezieau justin>      justin.bezieau@gmx.com                   #
  #           <Ge Jiaxun>           jx_g@hotmail.fr                          #
  #                                                                          #
  #  Verion of the 16/01/2017                                                #
  #                                                                          #
  #  This program is free software: you can redistribute it and/or modify    #
  #  it under the terms of the GNU General Public License as published by    #
  #  the Free Software Foundation, either version 3 of the License, or       #
  #  (at your option) any later version.                                     #
  #                                                                          #
  #  This program is distributed in the hope that it will be useful,         #
  #  but WITHOUT ANY WARRANTY; without even the implied warranty of          #
  #  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           #
  #  GNU General Public License for more details.                            #
  #                                                                          #
  #  You should have received a copy of the GNU General Public License       #
  #  along with this program.  If not, see <http://www.gnu.org/licenses/>.   #
  #                                                                          #
  #                                                                          #
  ############################################################################*/
  
  
#include "a_star.h"
#include "lab_type.h"
#include "labyrinthAPI.h"
#include<stdio.h>
#include<stdlib.h>

#define DEBUG_NEIGHBOUR
#undef DEBUG_NEIGHBOUR

#define DEBUG_A_STAR
//#undef DEBUG_A_STAR

#define DEBUG_A_STAR_1
#undef DEBUG_A_STAR_1

int compare_case(const void * a, const void * b)
/**
    Function:   copare_case 
                compare to Case with their cost

    @params:    Case *a , Case *b

    @returns:   int 0 if a.cost == b.cost
                    cost.b - cost.a
                    
    Case : cf lab_type.h  
    
*/
{

	Case * a_ = (Case * )a;
	Case * b_ = (Case * )b;
	
	return ( b_->cost - a_->cost );

}


void show_list(Case * list, int n)
/**
    Function:   show_list 
                show a list of Case of size n
                

    @params:    Case * List, int n 

    @returns:  
    
*/
{
	int i;
	for (i=0; i<n; i++)
	{
		printf("case %d on %d  : x= %d y= %d cost= %d \n",i,n,list[i].x,list[i].y,list[i].cost);
	}
}

int is_in(Case * list, int n, Case c)
/**
    Function:   is_in
                say if a Case is in a Case (c) list (*list) of size n
                

    @params:    Case * List, int n , Case c

    @returns:   (int)   1 if the Cass is in the list
                        0 if the Case in not in the list
    
*/
{
	int i;
	for (i=0; i<n; i++)
		if (list[i].x == c.x && list[i].y == c.y)
			return (1);
			
	return(0);

}


t_move a_star(Lab * lab, int player)
/**
    Function:   a_star
                find the shortest path betwin a player ant the 
                treasure in the lab,
                

    @params:    Lab * lab (cf lab_type.h), int player (0 or 1) 

    @returns:  t_move (cf ret_type.h) the first move of the path to the treasure
    
*/
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
	n_open_list = 1;
	
	int i=0;
	
	Case * neighbour;
	
	Case * treasure;

	int founded = 0;
	
	while((! founded) && n_open_list)
	{
	
		close_list[n_close_list] = open_list[n_open_list-1];
	
		neighbour = search_for_neighbour(lab, &close_list[n_close_list]);  
		
		n_open_list --;
		n_close_list ++;
	
	
		for (i=0 ; i<4 ; i++ )
			if (neighbour[i].cost != -1)
				if (! is_in(close_list, n_close_list, neighbour[i]))  
				{
					if (neighbour[i].treasure == 1) 
					{
						founded = 1;
						treasure = & neighbour[i];
					}
					open_list[n_open_list] = neighbour[i];
					n_open_list ++;
				}
		
		qsort (open_list, n_open_list-1, sizeof(Case), compare_case);
		
		
		#ifdef DEBUG_A_STAR_1
			printf("\n===== openlist n = %d :\n",n_open_list);
			show_list(open_list,n_open_list);
			printf("\n===== closelist n = %d :\n",n_close_list);
			show_list(close_list,n_close_list);
		#endif
	
	//break;
	}
	
	Case *  previous, * current ;
	
	current = treasure; 
	
	if (founded) // do revers path and take the first move
	{
		#ifdef DEBUG_A_STAR
			printf("===== Path :  treasure %d %d\n", current->x, current->y);
		#endif
		while (current->p_case != NULL)
		{
			
			previous = current;
			current = current->p_case;
			#ifdef DEBUG_A_STAR
				printf("===== Path :           %d %d\n", current->x, current->y);
			#endif
		}
		int dx = current->x - previous->x;
		int dy = current->y - previous->y;
		
		#ifdef DEBUG_A_STAR
			printf("\n===== A star worke !!!! dx = %d dy = %d\n",dx,dy);
		#endif
		
		t_move move;
		move.value = 0;
		
		if (dx>0)	move.type = MOVE_LEFT ;
		else if (dx<0)	move.type = MOVE_RIGHT ;
		else if (dy>0)	move.type = MOVE_UP ;
		else if (dy<0)	move.type = MOVE_DOWN ;
		else exit(143);
		
		printf("===== A * say : %d\n", move.type);
		
		return(move);
	}
	
	else //try to rotate treasure //TODO
	{
		int line = lab -> t_posY;
		int column = lab -> t_posX;
		if (player == 0)
		{
		}
		else
		{
		}
	}
	
}



Case * search_for_neighbour(Lab * lab, Case * watched_case) 
/**
    Function:   search_for_neighbour 
                search the reachables neighbour of a Case
                

    @params:    Lab* lab (cf lyb_type.h),Case * watched_case,

    @returns:  list (Case *) (size 4) of reachable case
    
*/
{

	#ifdef DEBUG_NEIGHBOUR
		printf("===== enter in search_for_neighbour of %d; %d \n", watched_case.y, watched_case.x);
	#endif
	
	Case * neighbour = (Case *) malloc(sizeof(Case)*8);
	
	int left_side = watched_case->x - 1 , right_side = watched_case->x + 1 , 
			up_side = watched_case->y - 1, down_side = watched_case->y + 1;
	
	if (watched_case->x == lab-> sizeX -1) right_side = 0;
	else if (watched_case->x == 0 ) left_side = lab-> sizeX -1;
	
	if (watched_case->y == lab-> sizeY -1) down_side = 0;
	else if (watched_case->y == 0 ) up_side = lab-> sizeY -1;
	
	int to_append[4][2]= {{watched_case->y, right_side},
												{watched_case->y, left_side},
												{up_side, watched_case->x},
												{down_side, watched_case->x}};
												
	int i;
	
	for (i=0; i<4 ;i++)
	{
		
		neighbour[i].x = to_append[i][1];
		neighbour[i].y = to_append[i][0];
		neighbour[i].treasure = 0;
		
		neighbour[i].heuristique = heuristique(lab, neighbour[i].x, neighbour[i].y);
		
		if(lab->plateau[to_append[i][0]][to_append[i][1]] == '|') 
			neighbour[i].cost = -1;
		else if (lab->t_posX == neighbour[i].x && lab->t_posY == neighbour[i].y )
			neighbour[i].treasure = 1;
		else neighbour[i].cost = watched_case->cost+1;
		
		neighbour[i].p_case = watched_case;
		neighbour[i].xp = watched_case->x;
		neighbour[i].yp = watched_case->y;
		
		
		#ifdef DEBUG_NEIGHBOUR
			printf ("neighbour = '%d' , '%d' , cost = %d \n ", to_append[i][0], to_append[i][1],neighbour[i].cost);
		#endif
		
		
	}
	
	return(neighbour);

}

int heuristique(Lab *lab, int x, int y)
/**
    Function:   heuristique
                compute the distance between the point (x,y) to the treasure 
                

    @params:    Lab *lab (cf lab_type.h) ,int x, int y

    @returns:  int the the distance.
    
*/
{
	return(abs(x-lab->t_posX)+abs(y-lab->t_posY));
}

