#include <SDL2/SDL.h>
#include <stdio.h>

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Falgas",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         500, 500, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    
    
    SDL_SetRenderDrawColor(ren, 125,255,000,0x00);
    SDL_RenderClear(ren);

    SDL_SetRenderDrawColor(ren, 200,000,000,0x00);
    int i = 0; for (i = 0; i<50; i++){
    	int j = 0; for (j = 0; j<50; j++){ 
	   		SDL_RenderDrawPoint(ren, i*10, j*10);
		}
    }
    
    SDL_SetRenderDrawColor(ren, 200, 70, 70, 0x00);
    SDL_Rect cabecote = { 220, 85, 60, 65};
    SDL_RenderFillRect(ren, &cabecote);
    SDL_SetRenderDrawColor(ren, 139, 0, 139, 0x00);
    SDL_Rect corpitcho = { 200, 150, 100, 150};
    SDL_RenderFillRect(ren, &corpitcho);
    SDL_SetRenderDrawColor(ren, 55, 135, 254, 0x00);
    SDL_Rect faixa = { 200, 230, 100, 40};
    SDL_RenderFillRect(ren, &faixa);

    SDL_SetRenderDrawColor(ren, 255, 255, 255, 0x00);
    SDL_Rect rosto = { 230, 105, 40, 40};
    SDL_RenderFillRect(ren, &rosto);

    SDL_SetRenderDrawColor(ren, 254, 254, 000, 0x00);
    SDL_Rect podio = { 180, 320, 140, 40};
    SDL_RenderFillRect(ren, &podio);
    SDL_SetRenderDrawColor(ren, 255, 215, 000, 0x00);
    SDL_Rect sombra = { 180, 360, 140, 20};
    SDL_RenderFillRect(ren, &sombra);
    SDL_SetRenderDrawColor(ren, 235, 205, 000, 0x00);
    SDL_Rect pilar = { 200, 380, 100, 120};
    SDL_RenderFillRect(ren, &pilar);
    
    SDL_SetRenderDrawColor(ren, 200, 70, 70, 0x00);  
    for (i = 0; i < 2; i++){
       SDL_Rect bracos = { 170+(i*130), 150, 30, 100};
       SDL_RenderFillRect(ren, &bracos);
       SDL_Rect pernos = { 200+(i*70), 300, 30, 40};
       SDL_RenderFillRect(ren, &pernos);
       SDL_RenderDrawLine(ren, 240+(i*20), 125, 240+(i*20), 140);
    } 
    

    SDL_RenderPresent(ren);
    SDL_Delay(5000);

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
