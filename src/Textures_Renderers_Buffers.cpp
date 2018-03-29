//============================================================================
// Name        : Textures_Renderers_Buffers.cpp
/*
 * 		Textures: like a bmp that we can draw directly to
 *
 * 		RENDERER: what we use in SDL to write/draw on a window
 *
 *		Buffer: set aside area of memory that will get and set info
 *
 *
 *	creat render, use buffer to write to texture, pass texture to the renderer, tell renderer to display in window
 *
 * */
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <SDL.h>
#include <string.h>
using namespace std;

int main(int argc, char *argv[])
    {

    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
	cout << "SDL init failed." << endl;
	return 1;
	}
    //SDL object
    SDL_Window *window = SDL_CreateWindow("Particle Fire Explosion",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
	    SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL) //if window doesn't load, run the quit function
	{
	SDL_Quit();
	return 2; // return a number so you can look at where things went wrong in error codes/0 if runs good
	}

    //create the renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
	    SDL_RENDERER_PRESENTVSYNC);

    //create texter
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
	    SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

    //check if renderer was created successfully
    if (renderer == NULL) //NULL is returned if something went wrong
	{
	cout << "Could not create renderer" << endl;
	SDL_DestroyWindow(window); //if we could create window but not renderer
	SDL_Quit();
	return 3;
	}

    //check if texture was created successfully
    if (texture == NULL) //NULL is returned if something went wrong
	{
	cout << "Could not create texture" << endl;
	SDL_DestroyWindow(window); //if we could create window but not renderer
	SDL_DestroyRenderer(renderer); //if we could create the renderer but not the texture
	SDL_Quit();
	return 4;
	}

    //create the buffer area
    Uint32 *buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT]; //Uint32 is SDL's version of 'int'

    //memset=set a block of memory with a perticular value
    memset(buffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

    //set one pixel a different color
    //buffer[30000] = 0xFFFFFF;

    //for loop that basically does what the memset function does
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
	{
	buffer[i] = 0x87014DFF;
	}	   // R|G|B|Alpha|

    //update the texture with info being held in the buffer
    SDL_UpdateTexture(texture, NULL, buffer, SCREEN_WIDTH * sizeof(Uint32));

    //tell renderer to draw the texture
    SDL_RenderClear(renderer); //clear out the renderer
    SDL_RenderCopy(renderer, texture, NULL, NULL); //copy new info into renderer
    SDL_RenderPresent(renderer); //draw on the screen

    bool quit = false;

    SDL_Event event;

    while (!quit)	//game loop
	{
	//update particles
	//draw particles
	//check for messages/events

	while (SDL_PollEvent(&event))
	    {
	    if (event.type == SDL_QUIT)
		{
		quit = true;
		}
	    }
	}
    delete[] buffer;	// b/c we used 'new' we must free or delete this info
    SDL_DestroyTexture(texture); //destroy resources used for the texture
    SDL_DestroyRenderer(renderer); //destroy resources used for the renderer
    SDL_DestroyWindow(window); //kills the anything to do with the window

    SDL_Quit(); //quit SDL stuff

    return 0; //return 0 b/c all ran well
    }
