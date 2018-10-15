#include <stdio.h>
#include <stdlib.h>
#include "Tools.h"

int CheckCoord(struct Matrix matrix, int x, int y);

// Create a matrix
struct Matrix CreateMatrix(int rows, int columns)
{
	struct Matrix matrix;
       	
	matrix.rows = rows;
	matrix.columns = columns;

	matrix.mat = malloc(sizeof(double)*columns*rows);

	return matrix;
}

// Testing if given coordinates are correct
int CheckCoord(struct Matrix matrix, int x, int y)
{
	return (x < matrix.rows &&  y < matrix.columns); 
}


// Function to navigate in the matrix
double NavMatrix(struct Matrix matrix, int x, int y) 
{
	if (!CheckCoord(matrix, x, y))
		printf("Error in coordinates");
	int index = x * matrix.columns + y;	
	return *(matrix.mat + index);
}

// Function to change a value in a matrix
void ChangeMatrix(struct Matrix matrix, int x, int y, float val)
{
	if (!CheckCoord(matrix, x, y))
                printf("Error in coordinates");
        *(matrix.mat + x * matrix.columns + y) = val;
}

// Print the matrix
void PrintMatrix(struct Matrix matrix)
{
	for (int i = 0; i < matrix.rows; i++)
	{
		for(int j = 0; j < matrix.columns; j++)
		{
			printf("%f ", NavMatrix(matrix, i, j));
		}
		printf("\n");
	}
}

// Initialize the matrix with 0s
void InitMatrix(struct Matrix matrix)
{
	 for (int i = 0; i < matrix.rows; i++)
        {
                for(int j = 0; j < matrix.columns; j++)
                {
                        ChangeMatrix(matrix, i, j, 0);
                }
        }    
}
