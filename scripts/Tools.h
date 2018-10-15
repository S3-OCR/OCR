#ifndef TOOLS_H_
#define TOOLS_H_

// Matrix object declaration
struct Matrix
{
        // Size of the matrix
        int rows;
        int columns;

        // Pointer to the matrix
        double *mat;
};

void ChangeMatrix(struct Matrix matrix, int x, int y, float val);

double NavMatrix(struct Matrix matrix, int x, int y);

void InitMatrix();

struct Matrix CreateMatrix(int rows, int colums);

void PrintMatrix(struct Matrix matrix);

#endif
