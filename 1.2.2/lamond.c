#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

int main (int argc, char* args[])
{
    //INICIALIZACAO 
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("lamond",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         500, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);    
    
    //EXECUÇÃO 
    SDL_SetRenderDrawColor(ren, 40, 40, 100, 0x00);
    SDL_RenderClear(ren);
    
    int lua = filledCircleColor(ren, 200, 310, 300, 0xFFEEEEEE);
    int lua2 = filledCircleRGBA(ren, 300, 260, 250, 40, 40, 100, 0xFF);
    
    int galho = roundedBoxRGBA(ren, 0, 540, 500, 580, 10, 139, 69, 19, 0xFF);
    int i = 0; 
    for (i; i<2; i++){
    	int asas = filledEllipseRGBA(ren, 200+(i*200), 300, 60, 180, 220, 210, 120, 0xFF);
    	int pernas = roundedBoxRGBA(ren, 235+(i*75), 460, 275+(i*75), 540, 10, 220, 210, 120, 0xFF);
    } 
    int corpo = filledEllipseRGBA(ren, 300, 300, 140, 200, 240, 230, 140, 0xFF);
    int cabeca = filledCircleRGBA(ren, 300, 150, 100,  220, 210, 120, 0xFF);    
    for (i = 0; i<2; i++){
      	int bochechas = filledCircleRGBA(ren, 250+(i*100), 200, 50, 220, 210, 120, 0xFF);  	
      	int olhos = filledCircleColor(ren, 250+(i*100), 150, 20, 0xFF000000);
    }
    Sint16 v1[] = {300,270,330}; Sint16 v2[] = {230,180,180};
    int bico = filledPolygonRGBA(ren, v1, v2, 3, 200, 200, 0, 255);
    Sint16 va[] = {280,315,335}; Sint16 vb[] = {580,520,530};
    int pe1 = filledPolygonRGBA(ren, va, vb, 3, 220, 210, 120, 0xFF);
    Sint16 vc[] = {325,350,365}; Sint16 vd[] = {530,530,575};
    int pe2 = filledPolygonRGBA(ren, vc, vd, 3, 220, 210, 120, 0xFF);
    Sint16 ve[] = {205,240,260}; Sint16 vf[] = {580,520,530};
    int pe3 = filledPolygonRGBA(ren, ve, vf, 3, 220, 210, 120, 0xFF);
    Sint16 vg[] = {250,275,290}; Sint16 vh[] = {530,530,575};
    int pe4 = filledPolygonRGBA(ren, vg, vh, 3, 220, 210, 120, 0xFF);

    SDL_RenderPresent(ren);
    SDL_Delay(5000);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
