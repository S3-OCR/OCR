#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <err.h>

void image_load(char* path)
{
    SDL_Window* fenetre;

    if(SDL_VideoInit(NULL) < 0) // Initialise SDL
    {
        printf("Error of initializing SDL : %s",SDL_GetError());
    }

    // Create window
    fenetre = SDL_CreateWindow("Une interface" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , 1000 , 600 , SDL_WINDOW_RESIZABLE);
    if(fenetre == NULL) // if problem return error
    {
        printf("Error of creating window : %s",SDL_GetError());
    }

    SDL_Surface* image = IMG_Load(path); // Load bmp with the path
    if(!image)
    { 
	// error if path not found
        errx(3, "can't load %s: %s", path, IMG_GetError());
    }


    SDL_BlitSurface(image, NULL, SDL_GetWindowSurface(fenetre),0);
    SDL_UpdateWindowSurface(fenetre);
    SDL_Delay(5000);//pause de 5 -secondes


    SDL_FreeSurface(image); // free memory
}
