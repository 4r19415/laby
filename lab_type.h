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

typedef struct prev{

	int x,y;
	int cost;
	int heuristique;
	int xp, yp;
	
	struct prev * p_case;
	
	int treasure;


}Case;


#endif
