#include "grid.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 *	IOANNIS CHATZIANTONIOU CSD5193
 *	ASSIGNMENT 4
 *	grid.c FILE
 */


/* initialization of grind for sudoku */
Grid_T grid_init(Grid_T g , int v[9][9]){
	int i=0;int j=0;int k=0;int x=0;int y=0;
	int subgrid_j=0;int subgrid_i=0;

	/* putting elements of v array to our cell.choices[0]*/
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			g.cell[i][j].choices[0]=v[i][j];
			g.cell[i][j].count=0;
		}
	}

	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			
			if(g.cell[i][j].choices[0]==0){
				
				for(k=1;k<10;k++)
					g.cell[i][j].choices[k]=1;

				
				/* checks rows*/
				for (k = 0; k < 9; k++) {
                			if (k != j && g.cell[i][k].choices[0] != 0) {
                    				g.cell[i][j].choices[g.cell[i][k].choices[0]] = 0;
                			}
            			}
            			/* checks columns*/
            			for (k = 0; k < 9; k++) {
                			if (k != i && g.cell[k][j].choices[0] != 0) {
                    				g.cell[i][j].choices[g.cell[k][j].choices[0]] = 0;
                			}
            			}

				/* checks sub-grid*/
            			subgrid_i = (i / 3) * 3; 
            			subgrid_j = (j / 3) * 3;
            			for (x = subgrid_i; x < subgrid_i + 3; x++) {
                			for (y = subgrid_j; y < subgrid_j + 3; y++) {
                    				if (x != i && y != j && g.cell[x][y].choices[0] != 0) {
                        				g.cell[i][j].choices[g.cell[x][y].choices[0]] = 0;
                    				}
                			}
            			}	

			}else{

				for(k=1;k<10;k++)
					g.cell[i][j].choices[k]=0;
				
			}
		}
	}

	
	/* calculating the counts */
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			if(g.cell[i][j].choices[0]==0){
				k=1;
				while(k<10){
					if(g.cell[i][j].choices[k]==1)
						g.cell[i][j].count++;

					k++;
				}
			}else
				g.cell[i][j].count=0;
		}
	}


	return g;
}

/* for the first empty box it encounters, it returns one of 
 * the available choices of numbers that can be
 * entered based on the rules of the game */
Choice_T grid_iterate(Grid_T g, Choice_T t){
	
	int i ; int j; int k;int p;
	Choice_T finished;

	srand(time(NULL));
	k= rand() % 9 + 1;
	
	/* It finds the first cell thats contains zero and it has
	 * only 1 possible choice and return the value that can be
	 * fit inside the cell and it's potision*/
	for(i=t.i;i<9;i++){
		for(j=t.j;j<9;j++){
			if(g.cell[i][j].choices[0]==0){
				if(g.cell[i][j].count==1){
					finished.i=i;
					finished.j=j;
					for(p=1;p<10;p++){
						if(g.cell[i][j].choices[p]==1)
							finished.n=p;
					}
				}
			}
		}
	}

	/* now it checking the zero cells that have more than
	 * 1 possible choice and pick one of the values that 
	 * can be fit in the cell randomly. */
    	for (i = t.i; i < 9; i++) {
        	for (j=t.j;j<9; j++) {
			if(g.cell[i][j].choices[0]==0){
				
				if(g.cell[i][j].count==0){	/* if an empty cell has valid choices*/
					finished.i=0;
					finished.j=0;
					finished.n=0;
					return finished;
				}
				
				while(g.cell[i][j].choices[k]==0){
					k=rand()%9 +1;
				}	
            			finished.i=i;
				finished.j=j;
				finished.n=k;
				return finished;
			}	
		}
	}

	finished.i=0;
	finished.j=0;
	finished.n=0;


	return finished;	
}

/* changes it to apply to cell c.i, c.j the selection c.n
 * and subtract it from the remainder g, returning the new g.*/
Grid_T grid_update(Grid_T g, Choice_T c){
	int i;int j;int k;
	int subgrid_i;int subgrid_j;

	g.cell[c.i][c.j].choices[0]=c.n;
	
	/* we put null to the other choices cause
	 * we already but a value to choice[0]*/
	for(k=1;k<10;k++){
		g.cell[c.i][c.j].choices[k]=0;
		g.cell[c.i][c.j].count=0;
	}
	
	/* for every column i delete this choice for the other cells*/
	for(j=0;j<9;j++){
	
		if(g.cell[c.i][j].choices[c.n]!=0)
			g.cell[c.i][j].count--;
		
		g.cell[c.i][j].choices[c.n]=0;
	}

	/* for every row i delete this choice for the other cells*/
	for(i=0;i<9;i++){
		
		if(g.cell[i][c.i].choices[c.n]!=0)
			g.cell[i][c.i].count--;

		g.cell[i][c.i].choices[c.n]=0;
	}

	/* we found the subgrid and we delete this option for the subgrid*/
	subgrid_i=(c.i/3) * 3;
	subgrid_j=(c.j/3) * 3;

	for (i = subgrid_i; i < subgrid_i + 3; i++) {
            for (j = subgrid_j; j < subgrid_j + 3; j++) {
		    if(g.cell[i][j].choices[c.n]!=0)
			    g.cell[i][j].count--;
		    
		    g.cell[i][j].choices[c.n] = 0;
            }
        }
	return g;
}

/* return unique flag for g */
int grid_unique(Grid_T g){
	return g.unique;
}

/* clear unique flag */
Grid_T grid_clear_unique(Grid_T g){
	g.unique = 0;
    	return g;
}

/* finds the unique options we have to put in the empty box
 *  (count=1) and returns its coordinates and the element
 *  that can be inserted*/
Choice_T grid_exist_unique(Grid_T g){
	int i;int j;int k;
	Choice_T choice;

	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			if(g.cell[i][j].count==1){
				k=1;
				while(k<10){
					if(g.cell[i][j].choices[k]==1){
						choice.i=i;
						choice.j=j;
						choice.n=k;
						return choice;
					}
					k++;
				}
			}
		}
	}

	choice.i=0;
	choice.j=0;
	choice.n=0;

	return choice;
}

/* return value of i,j */
Choice_T grid_read_value(Grid_T g, Choice_T c){

	Choice_T choice;
    	choice.i = c.i;
    	choice.j = c.j;
    	choice.n = g.cell[c.i][c.j].choices[0];
    	return choice;
}



