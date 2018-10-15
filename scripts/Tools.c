#include "Tools.h"
#include <stdio.h>
#include <stdlib.h>

struct Matrix CreateMatrix(int rows, int columns);
double NavMatrix(struct Matrix matrix, int x, int y);
void ChangeMatrix(struct Matrix matrix, int x, int y, float val);
void PrintMatrix(struct Matrix matrix);
void PrintTest();
void InitMatrix();
int CheckCoord(struct Matrix matrix, int x, int y);

//  Matrix object
struct Matrix
{
        // Size of the matrix
        int rows;
        int columns;

        // Pointer to the matrix
        double *mat;
};

// Function to create a matrix
struct Matrix CreateMatrix(int rows, int columns)
{
	struct Matrix matrix;
       	
	matrix.rows = rows;
	matrix.columns = columns;

	//double T[sizeof(double)*columns*rows];
	matrix.mat = malloc(sizeof(double)*columns*rows);

	return matrix;
}

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
        *(matrix.mat + x * matrix.columns + y) = val;
}

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

void PrintTest()
{
	struct Matrix mat1 = CreateMatrix(10,6);
        InitMatrix(mat1);
	ChangeMatrix(mat1, 2, 0, 7);
	ChangeMatrix(mat1, 0, 0, 2);
	ChangeMatrix(mat1, 1, 4, 4);	
	PrintMatrix(mat1);
}

