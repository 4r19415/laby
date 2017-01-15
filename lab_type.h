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
