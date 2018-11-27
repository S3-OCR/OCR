# include <string.h>
# include "Initialization/image.h"
# include "Initialization/Binarize.h"
# include "Detection/segmentation.h"
# include "scripts/NeuralNetwork_XOR.h"

int main(int argc, char** argv)
{
    SDL_Surface* img;// the bmp
    SDL_Window* screen;

    if(argc > 1)// at least must have one minimum argument
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
            img = load_image(argv[1]);//argv[1] = path of bmp
            screen = display_img(img);
            wait_for_keypressed();

            Binarize(img);
            SDL_BlitSurface(img, NULL, SDL_GetWindowSurface(screen),0);
            SDL_UpdateWindowSurface(screen);
            wait_for_keypressed();

            lines(img);
            SDL_BlitSurface(img, NULL, SDL_GetWindowSurface(screen),0);
            SDL_UpdateWindowSurface(screen);
            wait_for_keypressed();

            SDL_FreeSurface(img);

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
