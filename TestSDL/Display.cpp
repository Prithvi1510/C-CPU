/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "CPU.h"
#include "MemoryFile.h"



//Screen dimension constants
const int SCREEN_WIDTH = 256;
const int SCREEN_HEIGHT = 224;

unsigned char buffer[32][28]; 

void paint_buffer(unsigned char* buffer,int rows , int columns  , unsigned int fill)
{
	memset(buffer, fill, rows * columns); 
	
}

void paint_column(int colno, int no_blocks) {

}



void paint_pixel_block(int colno, int blockno, int pixel_block , SDL_Renderer* renderer)
{
	if (pixel_block & 0x80) SDL_RenderDrawPoint(renderer, colno, 0 + blockno * 8);
	if (pixel_block & 0x40)SDL_RenderDrawPoint(renderer, colno, 1 + blockno * 8); 
	if (pixel_block & 0x20)SDL_RenderDrawPoint(renderer, colno, 2 + blockno * 8);
	if (pixel_block & 0x10)SDL_RenderDrawPoint(renderer, colno, 3 + blockno * 8);
	if (pixel_block & 0x08)SDL_RenderDrawPoint(renderer, colno, 4 + blockno * 8);
	if (pixel_block & 0x04)SDL_RenderDrawPoint(renderer, colno, 5 + blockno * 8);
	if (pixel_block & 0x02)SDL_RenderDrawPoint(renderer, colno, 6 + blockno * 8);
	if (pixel_block & 0x01)SDL_RenderDrawPoint(renderer, colno, 7 + blockno * 8);
}

int main(int argc, char* args[])
{
	//The window we'll be rendering to
	SDL_Window* window = NULL;
	SDL_Renderer* rend = NULL;  
	Uint32 render_flags = SDL_RENDERER_SOFTWARE; 
	//SDL_CreateRenderer(, -1, render_flags);

	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		paint_buffer(&buffer [0][0] , 32, 28, 0x56);
		//Create window
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get window surface
			screenSurface = SDL_GetWindowSurface(window);
			rend = SDL_CreateRenderer(window, -1, render_flags);
			//Fill the surface white
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

			//Update the surface
			SDL_UpdateWindowSurface(window);

			//Wait two seconds
			SDL_Delay(2000);
		}
	}
	
	     
	    int8_t  temp;
		MemoryFile  memory_map(0x00);
		CPU cpu1(&memory_map, 0x00);
		temp = memory_map.LoadROMData((const char*)"invaders");
		uint16_t program_counter = cpu1.Get_PC();

		do {
			
			uint8_t instruction = cpu1.GetByteAt( program_counter);
			cpu1.Execute(instruction); 
			program_counter = cpu1.Get_PC();
			//program_counter++; 

		} while (1);
		
		
		
	//Destroy window
	SDL_DestroyWindow(window); 

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}