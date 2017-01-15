//
// TEMPLATE 
//
//
// Permet de jouer un seul tour (en ne faisant rien s'il commence ou en 
// réceptionnant le coup de l'adversaire s'il ne commence pas) 
// et termine le jeu.
// Ce programme vous sert de base pour construire votre propre programme


#define DEBUG
#undef DEBUG

#include <stdio.h>
#include <stdlib.h>
#include "labyrinthAPI.h"
#include "functions.h"
#include <unistd.h>


extern int debug;	/* hack to enable debug messages */


int main()
{
	char labName[50];					/* name of the labyrinth */
	char* labData;						/* data of the labyrinth */
	t_return_code ret = MOVE_OK;		/* indicates the status of the previous move */
	t_move move;						/* a move */
	int player;
	int sizeX,sizeY;

	/* connection to the server */
	connectToServer( "pc4023.polytech.upmc.fr", 1234, "the_plague");
	
	
	/* wait for a game, and retrieve informations about it */
	//waitForLabyrinth( "DO_NOTHING timeout=10", labName, &sizeX, &sizeY);
	waitForLabyrinth( "PLAY_RANDOM timeout=60", labName, &sizeX, &sizeY);
	labData = (char*) malloc( sizeX * sizeY );
	player = getLabyrinth( labData);
	
	
	
	Lab lab =  make_lab(labData, sizeX, sizeY, player);
	
	lab.j2_energy = 2;
	lab.j1_energy = 0;
	
	 
	//return(0);
	 
	while(1)
	{
	
	        /* display the labyrinth */
	        printLabyrinth();
	
                #ifdef DEBUG
                        printf("player = %d\n",player);
                #endif
	
	        if (player==1)	/* The opponent plays */
	          {
	            #ifdef DEBUG
	                printf("getMove\n");
	            #endif
	            ret = getMove( &move);
	            
	            update(&lab, move, player);
	            
	            lab.j2_energy++;
	            
	            //show_plateau( lab );
	            //playMove( &lab, move);
	            
	            
	            player = 0;
	          }
	        else
	          {
	            move = playRandom (&lab, player);
	            
	      	    #ifdef DEBUG
	                printf("sendMove\n");
	            #endif
	            ret = sendMove(move);
	            
	            update(&lab, move, player);
	            
	            lab.j1_energy++;
	            
	            //show_plateau( lab );
	            
	            a_star(&lab, player);
	            
	            
	            player = 1;
	          }
	
	        if ((player ==1 && ret == MOVE_WIN) || (player==0 && ret == MOVE_LOSE))
	          printf("I lose the game\n");
	        
	        #ifdef DEBUG  
	                char trash;
	                scanf("%c", &trash); // just for waiting.
                #endif
                
                
	  }
	
	/* we do not forget to free the allocated array */
	free(labData);
	
	
	/* end the connection, because we are polite */
	closeConnection();
	
	return EXIT_SUCCESS;
}

