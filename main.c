# include "Initialization/image.h"

int main(int argc, char** argv)
{
	SDL_Surface* img;
	
	if  (argc > 0)
	{ 
		img = load_image(argv[1]); //argv[1] = path of bmp
		display_img(img);
		wait_for_keypressed();
		SDL_FreeSurface(img);

		return 0;
	}			
	else
		return 1;
}
