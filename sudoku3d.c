#include <stdio.h>
#include <stdlib.h>

// Declare printSudoku function
void printSudoku(int***arr);
// Declare solveSudoku function
int solveSudoku(int***blocks);
int FindUnassignedLocation(int ***arr);
int checkSquare(int ***blocks, int num, int block_index);
int checkRow(int ***blocks, int num, int block_index, int row_index);
int checkColumn(int ***blocks, int num, int block_index, int column_index);

//Helper functions. You can define any functions that can help your solve the problem
int FindUnassignedLocation(int ***arr) {
	for (int k = 0; k < 9; k++) {
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 3; i++) {
				if (*(*(*(arr + k) + j) + i) == 0){
					return 1;
					}
			}
		}
	}
	return 0;
}

int checkSquare(int ***blocks, int num, int block_index) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if ((*(*(*(blocks + block_index) + j) + i)) == num) {
				return 1;
			}
		}
	}
	return 0;
}

int checkRow(int ***blocks, int num, int block_index, int row_index) {
	if (block_index == 0 || block_index == 1 || block_index == 2) {
		block_index = 0;
		for (int k = block_index; k < block_index + 3; k++) {
			for (int i = 0; i < 3; i++) {
				if (*(*(*(blocks + block_index) + row_index) + i) == num) {
					return 1;
				}
			}
		}
		return 0;
	}
	else if (block_index == 3 || block_index == 4 || block_index == 5) {
		block_index = 3;
		for (int k = block_index; k < block_index + 3; k++) {
			for (int i = 0; i < 3; i++) {
				if (*(*(*(blocks + block_index) + row_index) + i) == num) {
					return 1;
				}
			}
		}
		return 0;
	}
	else if (block_index == 6 || block_index == 7 || block_index == 8) {
		block_index = 6;
		for (int k = block_index; k < block_index + 3; k++) {
			for (int i = 0; i < 3; i++) {
				if (*(*(*(blocks + block_index) + row_index) + i) == num) {
					return 1;
				}
			}
		}
		return 0;
	}
}

int checkColumn(int ***blocks, int num, int block_index, int column_index) {
	if (block_index == 0 || block_index == 3 || block_index == 6) {
		block_index = 0;
		for (int k = block_index; k < block_index + 9; k = k + 3) {
			for (int j = 0; j < 3; j++) {
				if (*(*(*(blocks + block_index) + j) + column_index) == num) {
					return 1;
				}
			}
		}
		return 0;
	}
	else if (block_index == 1 || block_index == 4 || block_index == 7) {
		block_index = 1;
		for (int k = block_index; k < block_index + 9; k = k + 3) {
			for (int j = 0; j < 3; j++) {
				if (*(*(*(blocks + block_index) + j) + column_index) == num) {
					return 1;
				}
			}
		}
		return 0;
	}
	else if (block_index == 2 || block_index == 5 || block_index == 8) {
		block_index = 2;
		for (int k = block_index; k < block_index + 9; k = k + 3) {
			for (int j = 0; j < 3; j++) {
				if (*(*(*(blocks + block_index) + j) + column_index) == num) {
					return 1;
				}
			}
		}
		return 0;
	}
}



/*The main program reads a text file containing the block values of the Sudoku grid.
It then saves each 3x3 block into a 2D array. The Sudoku grid is composed of 9 3x3 blocks.
DO NOT MODIFY THE MAIN FUNTION!!!*/

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <file name>\n", argv[0]);
		return 2;
	}
	int i, j;
	FILE *fptr;
	int ***blocks = (int***)malloc(9 * sizeof(int**));

	// Open file for reading
	fptr = fopen(argv[1], "r");
	if (fptr == NULL) {
		printf("Cannot Open File!\n");
		return 0;
	}

	// Read 9x9 blocks into 2D arrays
	for (i = 0; i < 9; i++)
	{
		*(blocks + i) = (int**)malloc(3 * sizeof(int*));
		printf("Reading numbers in block %d... \n", i + 1);
		for (j = 0; j < 3; j++)
		{
			*(*(blocks + i) + j) = (int*)malloc(3 * sizeof(int));

			fscanf(fptr, "%d %d %d", *(*(blocks + i) + j), *(*(blocks + i) + j) + 1, *(*(blocks + i) + j) + 2);
			printf("%d %d %d\n", *(*(*(blocks + i) + j)), *(*(*(blocks + i) + j) + 1), *(*(*(blocks + i) + j) + 2));
		}
	}

	// Print out original Sudoku grid
	printf("Printing Sudoku before being solved:\n");
	printSudoku(blocks);

	// Call solveSudoku and print out result
	printf("\nSolving Sudoku...\n\n");
	if (solveSudoku(blocks)) {
		printf("Sudoku solved!\n");
		printSudoku(blocks);
	}
	else
		printf("This Sudoku cannot be solved!\n");

	return 0;
}


void printSudoku(int*** arr) {
	// This function will print out the complete Sudoku grid (arr). It must produce the output in the SAME format as the samples in the instructions. 	
	
	for (int j = 0; j < 3; j++) {
		for (int k = 0; k < 3; k++) {
			for (int i = 0; i < 3; i++) {
				printf("%d ", *(*(*(arr + k) + j) + i));
			}
			printf("|");
		}
		printf("\n");
	}
	printf("---------------------\n");
	for (int j = 0; j < 3; j++) {
		for (int k = 3; k < 6; k++) {
			for (int i = 0; i < 3; i++) {
				printf("%d ", *(*(*(arr + k) + j) + i));
			}
			printf("|");
		}
		printf("\n");
	}
	printf("---------------------\n");
	for (int j = 0; j < 3; j++) {
		for (int k = 6; k < 9; k++) {
			for (int i = 0; i < 3; i++) {
				printf("%d ", *(*(*(arr + k) + j) + i));
			}
			printf("|");
		}
		printf("\n");
	}
	}
	// Your implementation here


int solveSudoku(int*** blocks) {
	// This is the function to solve the Sudoku (blocks). Feel free to use any helper functions.
	// YOU MUST NOT USE ANY ARRAY NOTATION ([])!
	//printf("print this first");
	int num;
	if (!FindUnassignedLocation(blocks)) {
		return 1;

		for (int k = 0; k < 9; k++) {
			for (int j = 0; j < 3; j++) {
				for (int i = 0; i < 3; i++) {
					if (*(*(*(blocks + k) + j) + i) == 0)       /*((*(*(*(blocks + k) + j) + i)) == 0)*/ {
						printf("%d, %d, %d\n", k, j, i);
						for (num = 1; num <= 9; num++) {
							printf("num is %d", num);
							if (!checkRow(blocks, num, k, j) && !checkColumn(blocks, num, k, i) && !checkSquare(blocks, num, k)) {
								*(*(*(blocks + k) + j) + i) = num;
								if (solveSudoku(blocks)) {
									return 1;
								}
								*(*(*(blocks + k) + j) + i) = 0;
							}

						}
						return 0;
					}

					//Your implementation here		
				}

			}

		}
		return 1;
	}
}
