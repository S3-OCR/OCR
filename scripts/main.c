#include "Tools.h"

int main()
{
	struct Matrix mat2 = CreateMatrix(5, 5);
       	ChangeMatrix(mat2, 4, 4, 76);
	PrintMatrix(mat2);
}
