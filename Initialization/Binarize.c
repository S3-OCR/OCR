#include "image.h"
#include "Binarize.h"
#include "pixel_op.h"


SDL_Surface* Binarize(SDL_Surface* img)
{
    int w = img -> w;// the width of img
    int h = img -> h;// the height of img

    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            // Rappel : Uint8 = nombre signe allant de 0 a 255 inclus
            Uint32 pixel = get_pixel(img, x, y);
            Uint8 r , g , b;
            // get colors of pixel
            SDL_GetRGB(pixel, img->format, &r, &g, &b);
            // get the average of colors
            Uint32 average = (r + g + b) / 3; 
            if (average > 127) // because 255/2 = 127,5
            {
                // change pixel's color to white
		// if the average was greater than 127
                pixel = SDL_MapRGB(img->format, 255, 255, 255); 
                put_pixel(img, x, y, pixel);
            }
            else
            {
                // same reason as before, but here the color will be black
                pixel = SDL_MapRGB(img->format, 0, 0, 0);
                put_pixel(img, x, y, pixel);
            }
        }
    }

    return img;
}

