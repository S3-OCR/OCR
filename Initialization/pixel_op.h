#ifndef PIXEL_OP_H
#define PIXEL_OP_H

#include "image.h"

Uint32 get_pixel(SDL_Surface *surface, unsigned x, unsigned y);
void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);

#endif
