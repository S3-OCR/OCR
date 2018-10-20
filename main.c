# include "Initialization/image.h"
# include "Initialization/Binarize.h"
# include "scripts/NeuralNetwork_XOR.h"
# include <string.h>

int main(int argc, char** argv)
{
	SDL_Surface* img; // the initial bmp
	SDL_Surface* BW_img; // the white and black colored bmp
	SDL_Window* screen;

	if  (argc > 1) // at least must have one minimum argument 
	{ 
		if(argc == 3)
		{
			if(!strcmp(argv[1], "display") && !strcmp(argv[2], "xor"))
			{
				TestForNeuralNetwork();
				return 0;
			}
			else
			{
				printf("Unknown command.\n");
				return 1;
			}
		}
		if(argc == 2)
		{	
			img = load_image(argv[1]); //argv[1] = path of bmp
			screen = display_img(img);
			wait_for_keypressed();

			SDL_BlitSurface(BW_img, NULL, SDL_GetWindowSurface(screen),0);
			SDL_UpdateWindowSurface(screen);
			BW_img = Binarize(img);
			display_img(BW_img);
			wait_for_keypressed();
                	SDL_FreeSurface(BW_img);

			return 0;
		}
		
		printf("Unknown command.\n");
		return 1;
	}			
	else
	{
		printf("'./main' needs at least one argument.\n");
		return 1;
	}
}
