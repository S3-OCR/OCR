# include "image.h"

SDL_Surface *image;

    SDL_Surface *load_image(char *path)
{
    // Load an image using SDL_image with format detection.
    // If it fails, die with an error message.
    image = IMG_Load(path);
    if (!image)
        errx(3, "can't load %s: %s", path, IMG_GetError());

    return image;
}

void wait_for_keypressed()
{
    SDL_Event event;

    // Wait for a key to be down.
    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYDOWN);

    // Wait for a key to be up.
    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYUP);
}


    SDL_Window* display_img(SDL_Surface* image)
{
	if(SDL_VideoInit(NULL) < 0) // Initialise SDL
	{	
		printf("Error of initializing SDL : %s",SDL_GetError());
	}

    	// Create window
    	SDL_Window* fenetre;
	fenetre = SDL_CreateWindow("OCR" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , 1000 , 600 , SDL_WINDOW_RESIZABLE);
    	
	if(fenetre == NULL) // if problem return error
	{
	printf("Error of creating window : %s",SDL_GetError());
	}


    	SDL_BlitSurface(image, NULL, SDL_GetWindowSurface(fenetre),0);
    	SDL_UpdateWindowSurface(fenetre);

	//wait_for_keypressed(); // wait for a key pressed before leaving

	//SDL_FreeSurface(image); // free memory
	
	return fenetre;
}

void SDL_FreeSurface(SDL_Surface *surface); // close window and free memory

