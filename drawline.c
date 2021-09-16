#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "SDL2//SDL.h"
#include "drawline.h"


/* 
 * Set pixel (x, y) on the surface to the given color
 */
void set_pixel(SDL_Surface *surface, int x, int y, unsigned int color)
{
    Uint32 *pixels = surface->pixels,
           idx = x + y*surface->w;

    /* Verify that pixel is inside of surface */
    if (x >= surface->w || x < 0 ||
        y >= surface->h || y < 0) {
         fprintf(stderr, "Plotting pixel outside of surface, check translation or scale\n");
         return;
    }

    /* Set pixel */
    pixels[idx] = color;
}

/*
 * Draw a line on the surface from point (x1, y1) to point (x2, y2) using color
 */
void draw_line(SDL_Surface *surface, int x1, int y1, int x2, int y2, unsigned int color)
{
    // Draws a horizonbtal line from left to right
    if(x1 < x2 && y1 == y2) 
    { 
        for(x1; x1<x2; x1++)  
        {
            set_pixel(surface, x1, y1, SDL_MapRGB(surface->format, 0, 0xff, 0));
        }
    
    }
    // Draws a horizonbtal line from right to left 
    else if(x2 < x1 && y1 == y2) 
    { 
        for(x1; x2<x1; x1--) 
        {
            set_pixel(surface, x1, y1, SDL_MapRGB(surface->format, 0, 0xff, 0));
        }
    }  

    // Draws a vertical line from top to bottom    
    else if(y1 < y2 && x1 == x2)
    {         
        for(y1; y1<y2; y1++) 
        {
            set_pixel(surface, x1, y1, SDL_MapRGB(surface->format, 0, 0xff, 0)); 
        }
    }
    
    // Draws a vertical line from bottom to top
    else if(y2 < y1 && x1 == x2) 
    { 
        for(y1; y2<y1; y1--) 
        {
            set_pixel(surface, x1, y1, SDL_MapRGB(surface->format, 0, 0xff, 0));
        }
    }  

    // Draws a diogonally line from top left to bottom right
    else if( x1 < x2 && y1 < y2)
    {
        for(x1; x1<x2; x1++)  
        {
            for(y1; y1<x1; y1++) 
            {
                set_pixel(surface, x1, y1, SDL_MapRGB(surface->format, 0, 0xff, 0));
            }
        }

    }
    
    // Draws a diogonally line from bottom right to top left
    else if(x2 < x1 && y2 < y1)
    {
        for(x1; x1>x2; x1--)  
        {
            for(y1; y1>x1; y1--) 
            {
                set_pixel(surface, x1, y1, SDL_MapRGB(surface->format, 0, 0xff, 0)); 
            }
        }

    }
    
    

    





    


} 


int main(void)
{
    const size_t bufsize = 100;
    
    /* Change the screen width and height to your own liking */
    const int screen_w = 1024;
    const int screen_h = 768;

    char errmsg[bufsize];
    int done;
    SDL_Surface *surface;
    SDL_Window *window;
    SDL_Event event;
    
    /* Initialize SDL */
    if (SDL_Init(SDL_INIT_VIDEO) < -1) {
        snprintf(errmsg, bufsize, "Unable to initialize SDL.");
        goto error;
    }
    
    /* Create a 1600x900 window */
    window = SDL_CreateWindow("The Amazing Line",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              screen_w, screen_h,
                              0);
    if(!window) {
        snprintf(errmsg, bufsize, "Unable to get video surface.");
        goto error;
    }

    /* Create the suface in RAM that we manipulate the pixels of */
    surface = SDL_GetWindowSurface(window);
    if(!surface) {
        snprintf(errmsg, bufsize, "Unable to create surface.");
        goto error;
    }

    // Example call (horizontal line). Remember to pass surface as first parameter.
    // The SDL_MapRGB function converts a RGB value tSo
    // a 32-bit value (each color is 8 bit)
    //draw_line(surface, 10, 10, 100, 10, SDL_MapRGB(surface->format, 0, 0xff, 0)); // horizonbtal line from left to right
    //draw_line(surface, 300, 10, 200, 10, SDL_MapRGB(surface->format, 0, 0xff, 0)); // horizonbtal line from right to left
    

    
    
    // Example Diagonal line, uncomment to draw
    //draw_line(surface, 10, 10, 100, 100, SDL_MapRGB(surface->format, 0, 0xff, 0)); // diogonally line from top left to bottom right
    //draw_line(surface, 100, 100, 10, 10, SDL_MapRGB(surface->format, 0, 0xff, 0)); // diogonally line from bottom right to top left
    draw_line(surface, 10, 100, 100, 10, SDL_MapRGB(surface->format, 0, 0xff, 0)); // diagonally line bottom left top dop right

    // Example vertical line, uncomment to draw
    //draw_line(surface, 10, 10, 10, 100, SDL_MapRGB(surface->format, 0, 0, 0xff)); // vertical line from top to bottom
    //draw_line(surface, 10, 300, 10, 200, SDL_MapRGB(surface->format, 0, 0, 0xff)); //vertical line from bottom to top
    
    
    /* Wait for the user to exit the application */
    done = 0;
    while (!done) {
        
        /* Update the window surface */
        SDL_UpdateWindowSurface(window);
        
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    done = 1;
                    break;
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_SHOWN)
                        SDL_SetWindowPosition(window, 50, 50);
                    break;
            }        
        }
    }   
    
    SDL_Quit();

    return 0;

    /* Upon an error, print message and quit properly */
error:
    fprintf(stderr, "%s Error returned: %s\n", errmsg, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}
