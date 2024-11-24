#include "grid.h"
#include "sudoku.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

/*
 * 	IOANNIS CHATZIANTONIOU CSD5193
 * 	ASSIGNMENT 4
 * 	sudoku.c FILE
 */


/* Read a sudoku puzzle from stdin and return an object Grid_T*/
Grid_T sudoku_read(){
	int i;int j;int n;
	Grid_T g;

	int v[9][9];
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			v[i][j]=0;
		}
	}
	
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			scanf("%d", &n);
			if(n==32 || n==10 || n==EOF){
				continue;
			}else
				v[i][j]=n;
		}
	}

	g=grid_init(g,v);

	return g;
}

/* Print g to stream s in the same format as expected by sudoku_read(). */
void sudoku_print(FILE *s, Grid_T g){
	int i, j;

    	for (i = 0; i < 9; i++) {
        	for (j = 0; j < 9; j++) {
      
                	fprintf(s, "%d", g.cell[i][j].choices[0]);
            		
            		if (j < 8) {
                		fprintf(s, " ");
            		}
        	}
        	fprintf(s, "\n");
    	}

}

/*  Returns:
 *   0  if sudoku is correct
 *  -1  if duplication
 *   1  if zero value 
 *   */
int sudoku_is_correct(Grid_T g){
	
	int i, j , x , y;
    	Choice_T choice;
	int count[10];
    
    	/* Check rows */
    	for (i = 0; i < 9; i++) {
        	for(x=0;x<10;x++) count[x]=0; /* Array to count occurrences of each number */
        
        	for (j = 0; j < 9; j++) {
            		choice.i = i;
            		choice.j = j;
            		choice = grid_read_value(g, choice);
            
            		if (choice.n != 0) {
                		if (count[choice.n] == 1) {
                    			return -1; /* Duplicate number found in row */
                		}
                		count[choice.n]++;
            		}else
				return 1;	/* it has empty element*/
        	}
    	}
    
    	/* Check columns */
    	for (j = 0; j < 9; j++) {
        	for(x=0;x<10;x++) count[x]=0;
        
        	for (i = 0; i < 9; i++) {
            		choice.i = i;
            		choice.j = j;
            		choice = grid_read_value(g, choice);
            
            		if (choice.n != 0) {
		    		if (count[choice.n] == 1) {
                    			return -1; /* Duplicate number found in colum */
		    		}
		    		count[choice.n]++;
            		}else
				return 1;	/* it has zero in one cell*/
        	}
    	}
    
    	/* Check subgrids */
    	for (i = 0; i < 9; i += 3) {
        	for (j = 0; j < 9; j += 3) {
            		for(x=0;x<10;x++) count[x]=0;
            
            		for (x = i; x < i + 3; x++) {
                		for (y = j; y < j + 3; y++) {
                    			choice.i = x;
                    			choice.j = y;
                    			choice = grid_read_value(g, choice);
                    
                    			if (choice.n != 0) {
                        			if (count[choice.n] == 1) {
                            				return -1; /* Duplicate number found in subgrid */
                       	 			}
                        			count[choice.n]++;
                    			}else
						return 1;	/* it has zero in one cell */
                		}
            		}
        	}
    	}

	return 0; /* the sudoku is correct */
}

/* Generate and return a sudoku puzzle with "approximately" nelts 
 * elements having non-0 value. The smaller nelts the harder may be 
 * to generate/solve the puzzle. For instance, nelts=81 should return 
 * a completed and correct puzzle. If unique=1 the puzzle must have a
 * unique choice at each step of finding the solution.
 */
Grid_T sudoku_generate(int nelts, int unique){
	
	FILE *s;

	/* this sudoku has only one solution*/
	/*	1 2 3 4 5 6 7 8 9
		4 5 6 7 8 9 1 2 3
		7 8 9 1 2 3 4 5 6
		2 3 4 5 6 7 8 9 1
		5 6 7 8 9 1 2 3 4
		8 9 1 2 3 4 5 6 7
		3 4 5 6 7 8 9 1 2
		6 7 8 9 1 2 3 4 5
		9 1 2 3 4 5 6 7 8
		*/
	int v1[9][9] = {
    		{1, 2, 3, 4, 5, 6, 7, 8, 9},
    		{4, 0, 6, 7, 8, 9, 1, 2, 3},
    		{7, 8, 9, 1, 2, 3, 4, 5, 6},
		{2, 3, 4, 5, 6, 7, 8, 9, 1},
    		{5, 6, 7, 8, 9, 1, 2, 0, 4},
    		{8, 9, 1, 2, 3, 4, 5, 6, 7},
    		{3, 4, 5, 6, 7, 8, 9, 1, 2},
    		{6, 7, 8, 9, 1, 2, 3, 4, 5},
    		{9, 1, 2, 3, 0, 5, 6, 7, 8}
	};

	/* this sudoku has more than one solution*/
	int v2[9][9] = {
    		{0, 3, 0, 0, 7, 0, 0, 0, 0},
    		{6, 0, 0, 1, 0, 5, 0, 0, 0},
    		{0, 9, 0, 0, 0, 0, 0, 6, 0},
    		{8, 0, 0, 0, 6, 0, 0, 0, 3},
    		{0, 0, 0, 8, 0, 3, 0, 0, 0},
    		{7, 0, 0, 0, 2, 0, 0, 0, 6},
    		{0, 6, 0, 0, 0, 0, 2, 8, 0},
    		{0, 0, 0, 0, 1, 9, 0, 0, 5},
    		{0, 0, 0, 0, 8, 0, 0, 7, 9}
	};

	
	/* empty array*/
	int v[9][9] = {
    		{0, 0, 0, 0, 0, 0, 0, 0, 0},
   	 	{0, 0, 0, 0, 0, 0, 0, 0, 0},
 		{0, 0, 0, 0, 0, 0, 0, 0, 0},
    		{0, 0, 0, 0, 0, 0, 0, 0, 0},
    		{0, 0, 0, 0, 0, 0, 0, 0, 0},
    		{0, 0, 0, 0, 0, 0, 0, 0, 0},
    		{0, 0, 0, 0, 0, 0, 0, 0, 0},
    		{0, 0, 0, 0, 0, 0, 0, 0, 0},
    		{0, 0, 0, 0, 0, 0, 0, 0, 0}
	};
	
	Grid_T g;
	Choice_T c;
	int i;int j;int x;int y;
	int zeron=81-nelts;
	srand(time(NULL));
	s=fopen("example.txt","w");

	g=grid_init(g,v);
	
	for(i=0;i<10;i++){
		c.i=0;
		c.j=0;
		c=grid_iterate(g,c);

		g=sudoku_solve(g,c);

		if(sudoku_is_correct(g)==0){
			for(j=0;j<zeron;j++){
				
				x=rand()%9;
				y=rand()%9;
				while(g.cell[x][y].choices[0]==0){

					
					x=rand()%9;
					y=rand()%9;
				}

				g.cell[x][y].choices[0]=0;
				
			}
	
			return g;
		}
	}

	sudoku_print(s,g);

	if(unique==1){
		g=grid_init(g,v1);
		return g;
	}else if(unique==0){
		g=grid_init(g,v2);
		return g;
	}
	return g;
}

/* Sovle g and return the solution; if g has multiple solutions, return one of them. 
 * c can help you iterate over all cells in g */
Grid_T sudoku_solve(Grid_T g, Choice_T c){
	

	if((c.i==0 && c.j==0 && c.n==0)){
		return g;
	}

	/* checks for unique option */
	while(g.cell[c.i][c.j].count==1){
		g=grid_update(g,c);
		c=grid_iterate(g,c);
	}
	
	
	

	return g;
}


/* my test main function */
int main(int argc,char * argv[]) {
    
	int correct; int nelts;int unique;int i;
	Grid_T grid;Choice_T choice;Grid_T solution;

	if (argc == 1) {
        	/* No command line arguments */
        	grid = sudoku_read();

		fprintf(stderr,"\n");

		sudoku_print(stderr,grid);        	

        	/* Solve the puzzle */
        	choice.i=0;
		choice.j=0;
		choice.n=0;

		solution = sudoku_solve(grid,choice);
		
		fprintf(stderr,"\n");

		sudoku_print(stderr,solution);

		fprintf(stderr,"\n");

		if(sudoku_is_correct(solution)!=0){
			fprintf(stderr,"There is no solution\n");
		}else{
			if(solution.unique==1)
				fprintf(stderr,"There is a unique solution\n");
			else
				fprintf(stderr,"It has more than 1 solution\n");
		}

        	return 0;
    	
	}else if (argc == 2 && argv[1][0] == '-' && argv[1][1] == 'c') {

		grid=sudoku_read();
		
		fprintf(stderr, "\n" );
		
		sudoku_print(stderr,grid);
		
		correct=sudoku_is_correct(grid);

		fprintf(stderr,"\n");

    		if(correct==0)
	    		fprintf(stderr,"This sudoku is right\n");
    		else if(correct==1)
	    		fprintf(stderr,"It contains zero value\n");
    		else
	    		fprintf(stderr,"Sudoku is wrong for duplication element\n");

		return 0;

	}else if (argv[1][0] == '-' && argv[1][1] == 'g' && (argc==3 || argc==4)) {

		for (i = 0; argv[2][i] != '\0'; i++) {
            		if (!isdigit(argv[2][i])) {
                		fprintf(stderr, "Error: nelts must be a number.\n");
                		return 1;
            		}
        	}

		nelts = atoi(argv[2]);
        	unique = 0;
        	if (argc == 4 && argv[3][0] == '-' && argv[3][1] == 'u')
            		unique = 1;

		grid=sudoku_generate(nelts,unique);
		
        	sudoku_print(stdout,grid);

		return 0;
	}
/*	
	int i;int j;int k;

	int v[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    Grid_T grid;
    FILE *s;
    Choice_T choice1={0,0,0};
    Choice_T choice={0,0,0};
    Choice_T value; 
    s=fopen("example.txt" , "w");
    grid = grid_init(grid, v);

    
    printf("Initialized Grid:\n");
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            printf("%d ", grid.cell[i][j].choices[0]);
        }
        printf("\n");
    }

    printf("\n");

    for(i=0;i<9;i++){
	    for(j=0;j<9;j++){
		    for(k=1;k<10;k++){
		    	printf("%d ",grid.cell[i][j].choices[k]);
			}
		    printf("\t %d \n",grid.cell[i][j].count);
		}
	    printf("\n");
    }


    
  
    choice = grid_iterate(grid, choice);
    printf("Next choice: (%d, %d, %d)\n\n", choice.i, choice.j, choice.n);

    
   
    printf("Updating the grid...\n\n");
    grid = grid_update(grid, choice);

    
    printf("Updated Sudoku Puzzle:\n");
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            printf("%d ", grid.cell[i][j].choices[0]);
        }
        printf("\n");
    }


    printf("\n");

    for(i=0;i<9;i++){
	    for(j=0;j<9;j++){
		    for(k=1;k<10;k++){
		    	printf("%d ",grid.cell[i][j].choices[k]);
			}
		    printf("\t %d \n",grid.cell[i][j].count);
		}
	    printf("\n");
    }

    value=grid_read_value(grid,choice1);
    printf("Value at position (%d, %d): %d\n", value.i,value.j,value.n);

    grid=sudoku_read();
    
    sudoku_print(s,grid); 
    
    if(sudoku_is_correct(grid)==0)
	    printf("This sudoku is right\n");
    else if(sudoku_is_correct(grid)==1)
	    printf("It contains zero value\n");
    else
	    printf("Sudoku is wrong\n");


    grid=sudoku_generate(74,8);
    sudoku_print(s,grid);

*/
    return 0;
}

