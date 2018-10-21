# include "segmentation.h"
# include "pixel_op.h"
# include "image.h"


SDL_Surface* lines(SDL_Surface* img)
{
	int w = img -> w;// width of img
	int h = img -> h;// height of img
	int x;// variable for loops
	Uint8 r , g , b;// Uint8 = signed number from 0 to 255 included
        Uint32 pixel;
        int line = 0;// mark the presence of line, here it has not
	int black = 0;// mark the presence of black pixel
	int begin;// line of the beginning of black pixel's presence
	int end;// line of end of it
	SDL_Surface* l_img = img;


	for (int y = 0; y < h; y++)// through the lines
	{
		for (x = 0; x < w; x++)// through the columns
		{
			pixel = get_pixel(l_img, x, y);
			// get colors of pixel
			SDL_GetRGB(pixel, l_img->format, &r, &g, &b);

			if (!r)// if pixel is black
			{
				black = 1;// black = true
				break;// exit the loop
			}
		}

		if (black && !line)// if line has black pixels
		{
			line = 1;// line = true
			begin = y;// conserve the index of the line

			for (x = 0; x < w; x++)
			{
                        	pixel = get_pixel(l_img, x, y);
				int pos = y - 1;// previous line
				if (pos >= 0)// verify if the height of previous line is positive
				{
					pixel = SDL_MapRGB(l_img->format, 255, 105, 180);//change color of previous line
	                                put_pixel(l_img, x, pos, pixel);
				}
			}
		}
		if (!black && line)
		// if previous line had black pixels but now it is white
		{
			line = 0;// make back line = false
			end = y;// conserve the index of the end

                        for (x = 0; x < w; x++)
			{
	                        pixel = get_pixel(l_img, x, y);

				int pos = y + 1;// next line
                                if (pos < h)// verify if next line can be reached
                                {
                                        pixel = SDL_MapRGB(l_img->format, 255, 105, 180);
                                        put_pixel(l_img, x, pos, pixel);
                                }
                        }
			// trace the columns there because, if it has an end,
			// it has of course a beginning
			l_img = columns(l_img, begin, end);
		}

		black = 0;// make back black = false
	}

	return l_img;
}


SDL_Surface* columns(SDL_Surface* img, int b_line, int e_line)
{
	int w = img -> w;// the limits of columns
	//variable for loops
	int x;
	int y;
	Uint8 r , g , b;// Uint8 = signed number from 0 to 255 included
        Uint32 pixel;
	// it will necesserly have one black pixel one this line
	// and it marks the begin of encountering a caracter
	int end_c = 0;// mark the end of an encounter with a caracter
	int black = 0;// trace first line of the caracter
	int e_black = 0;// trace last line of the caracter
	int white = 0;// if all this columns is white
	SDL_Surface* c_img = img;
	
	//loop from b_line to e_line
	//in wich there is another loop for all the columns

	for(x = 0; x < w; x++)// through the columns
	{
		white = 1;

		for(y = b_line; y < e_line; y++)// through the lines
		{
			pixel = get_pixel(c_img, x, y);
			// get colors of pixel
                        SDL_GetRGB(pixel, c_img->format, &r, &g, &b);

			if (!r && !end_c)// first encounter with a cararcter
			{
				end_c = 1;// the begin of caracter is here
				black = 1;// must trace first line
				break;
			}
			if(!r)// if the caracter in not finished yet
			{
				white = 0;
				break;
			}
			// had encountered a character but now it's its end with y,
			// also verify if this column has not black pixel with the white satement 
			if (b == 255 && end_c && white && y == e_line - 1)
			{
				end_c = 0;// the end of caracter is here
				e_black = 1;// must trace the last line
				break;
			}
		}

		if (end_c && black)// color the previous column of the caracter
		{
			black = 0;// first line was traced, so make back the statement
			for (y = b_line; y < e_line; y++)
			{
				if (x - 1 > 0)//previous column
                                {
                                        pixel = SDL_MapRGB(c_img->format, 1, 149, 255);//change color of column
                                        put_pixel(c_img, x - 1, y, pixel);
                                }
			}
		}
		if (!end_c && e_black)// color the next column of the caracter
		{
			e_black = 0;// last line was traced, so make back the statement
			for (y = b_line; y < e_line; y++)
			{
                     		pixel = SDL_MapRGB(c_img->format, 1, 149, 255);//change color of column
                                put_pixel(c_img, x, y, pixel);
			}
		}
  	}

	return c_img;
}

