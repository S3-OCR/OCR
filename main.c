#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <err.h>

int main(int argc, char** argv)
{

	if  (argc > 1)
	{
		image_load(argv[1]); //argv[1] = path of bmp
		return 0;
	}			
	else
		return 1;
}
