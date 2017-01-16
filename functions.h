/*############################################################################
  #                                                                          #
  #  Functions.h                                                             #
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
  
#include "labyrinthAPI.h"
#include "lab_type.h"

#ifndef functions_h
#define functions_h



t_move playRandom (Lab *lab, int player);
/**
    Function:    playRandom
                 send a move randomly but a possible move

    @params:    Lab * lab (cf lab_type.h)

    @returns:  t_move move (cf ret_type.c) the random posible move
    
*/

int possible(Lab *lab, t_move move, int player);
/**
    Function:    posible
                 say if  a player can do a move in the rules

    @params:    Lab * lab (cf lab_type.h) the lab 
    						t_move move (cf ret_type.c) the move in question
    						int player (0 or 1) the player digit

    @returns:  	int 1 if the move is OK
    								0 if the move is not OK
    
*/

void show_lab( char* labData, int sizeX, int sizeY);
/**
    Function:    show_lab
                 show the plateau of a Lab in the herdest way 
                 depreciated, use show_plateau 

    @params:    char * array of char '0' or '1'
    						int sizeX, the number of columns
    						int sizeY, thne number of lines    					

    @returns:  	
    
*/

void show_plateau( Lab lab );
/**
    Function:    show_plateau
                 show the plateau of a Lab

    @params:    Lab * lab (cf lab_type.h) the lab 
    					

    @returns:  	
    
*/

Lab make_lab(char * lab, int sizeX, int sizeY, int player);
/**
    Function:    make lab
                 creat a Lab object from a 1d array of char

    @params:    char* labdata with '0' for a corridor
    															 '1' for a wall
    						int sizeX, the number of column
    						int sizeY, the number of lines
    						int player the digit of the first player who play

    @returns:  	Lab the lab (cf lab_type.h)
    
*/

void update(Lab *lab, t_move move, int player);
/**
    Function:    update
                 change the lab when a player make a move
                 if its a rotation, it will call rotation

    @params:    Lab * lab (cf lab_type.h) the lab 
    						t_move move (cf ret_type.c) the move in question
    						int player (0 or 1)

    @returns:  
    
*/

void rotation(Lab *lab, t_move move, int player);
/**
    Function:    rotation
                 change the lab if one player make a rotation

    @params:    Lab * lab (cf lab_type.h) the lab 
    						t_move move (cf ret_type.c) the move in question 
    									(it should be a rotation)
    						int player (0 or 1) who make a rotation

    @returns:  	    
*/


#endif
