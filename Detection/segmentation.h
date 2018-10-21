# ifndef DETECT_H
# define DETECT_H

# include <stdio.h>
# include <err.h>
# include <stdlib.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>

SDL_Surface* lines(SDL_Surface* img);
SDL_Surface* columns(SDL_Surface *img, int b_line, int e_line);

#endif
