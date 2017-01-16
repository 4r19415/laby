#include "labyrinthAPI.h"
#include "lab_type.h"

#ifndef A_STAR_H
#define A_STAR_H


int heuristique(Lab *lab, int x, int y);
/**
    Function:   heuristique
                compute the distance between the point (x,y) to the treasure 
                

    @params:    Lab *lab (cf lab_type.h) ,int x, int y

    @returns:  int the the distance.
    
*/

Case * search_for_neighbour(Lab * lab, Case * watched_case); 
/**
    Function:   search_for_neighbour 
                search the reachables neighbour of a Case
                

    @params:    Lab* lab (cf lyb_type.h),Case * watched_case,

    @returns:  list (Case *) (size 4) of reachable case
    
*/

int compare_case(const void * a, const void * b);
/**
    Function:   copare_case 
                compare to Case with their cost

    @params:    Case *a , Case *b

    @returns:   int 0 if a.cost == b.cost
                    cost.b - cost.a
                    
    Case : cf lab_type.h  
    
*/

void show_list(Case * list, int n);
/**
    Function:   show_list 
                show a list of Case of size n
                

    @params:    Case * List, int n 

    @returns:  
    
*/

int is_in(Case * list, int n, Case c);
/**
    Function:   is_in
                say if a Case is in a Case (c) list (*list) of size n
                

    @params:    Case * List, int n , Case c

    @returns:   (int)   1 if the Cass is in the list
                        0 if the Case in not in the list
    
*/

t_move a_star(Lab * lab, int player);
/**
    Function:   a_star
                find the shortest path betwin a player ant the 
                treasure in the lab,
                

    @params:    Lab * lab (cf lab_type.h), int player (0 or 1) 

    @returns:  t_move (cf ret_type.h) the first move of the path to the treasure
    
*/




#endif
