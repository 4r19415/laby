/*############################################################################
  #                                                                          #
  #  lab_type.h                                                              #
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


#ifndef lab_type_h
#define lab_type_h

typedef struct {
/** 
	structure of all the labyrinth
	contain data of : the lab
			  the players
			  the treasure
*/

	char ** plateau; // the matrix of the lab, contain ' ' ou '|'
	int sizeX; // the number of columns
	int sizeY; // the number of lines
	
	int j1_posX; // x of player1
	int j1_posY; // y of player1
	int j1_energy; // energy of player1
	
	int j2_posX; // X of player2
	int j2_posY; // y of player2
	int j2_energy; // energy of player2
	
	int t_posX; // x of the treasure
	int t_posY; // y of the treasure
	
	t_move last_move; // the last move done in the lab, not used ^^
	
	int lab_has_change; // if there is a rotation noot viewed 

}Lab;

typedef struct prev{
/** 
	structure of a case of the lab
	contain data of : the position
			  the distance between this case and the treasure
			  the case before this case in the A* (cf a_star.c)
			  if the case contain the treasure
*/

	int x,y; // the x and y of this case
	int cost; // the distance between this case 
		  // and the player who launch the A*
	int heuristique; // the distance between this case and the tresure
	int xp, yp; // coordonate of the previous case
	
	struct prev * p_case; // pointer on the previous case
	
	int treasure; // thi case contain the treasure ? if yes = 1


}Case;


#endif
