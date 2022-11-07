#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Globo de Neve",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         100, 100, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
	 
   
    /* EXECUÇÃO */
    		
   
    					
	int vx[]={51,23,31,92,35,98,43,24,4,29,89,45,72,27,59,61,77,6,69,90,47,42,57,60,5,96,14,93,53,25,15,88,10,82,54,71,85,75,86,55,11,20,73,41,76,64,100,40,81,44,97,83,46,33,12,50,56,18,67,84,68,0,7,13,8,1,94,21,48,80,91,38,70,9,19,78,16,66,39,30,62,74,34,3,87,79,22,63,99,32,26,2};
	int vy[]={23,67,78,86,63,12,2,95,37,64,17,51,89,11,52,85,59,27,7,25,0,68,77,87,83,34,98,16,65,36,13,90,94,5,69,47,82,30,19,61,31,46,6,71,3,40,9,96,53,97,92,35,14,44,88,29,39,66,33,76,1,10,18,21,58,20,56,91,24,72,42,84,38,75,80,43,73,41,55,54,60,32,49,26,22,4,93,57,48,45,79,8,100,28,50,81,99,15,74,62};
    int i = 0;
    for (i; i<30; i++) {
    
        SDL_SetRenderDrawColor(ren, 0x20,0x20,0x50,0x00);
        SDL_RenderClear(ren);
        
        int c1 = filledCircleColor(ren, 50, 20, 10, 0xFFBBBBBB);
    	int c2 = filledCircleColor(ren, 50, 40, 20, 0xFFBBBBBB);
    	int c3 = filledCircleColor(ren, 50, 60, 30, 0xFFBBBBBB);
    	int b1 = filledCircleColor(ren, 50, 45, 2, 0xFF000000);
    	int b2 = filledCircleColor(ren, 50, 60, 2, 0xFF000000);
    	int b3 = filledCircleColor(ren, 50, 75, 2, 0xFF000000);
    	int o1 = filledCircleColor(ren, 45, 20, 1, 0xFF000000);
    	int o2 = filledCircleColor(ren, 55, 20, 1, 0xFF000000);
    	Sint16 v1[] = {50,58,50}; Sint16 v2[] = {24,26,28};
    	int cenoura = filledPolygonRGBA(ren, v1, v2, 3, 0xFF, 0x57, 0x33, 255);
    	
    	SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        int j = 0; for (j; j<100; j++){
           vx[j] += 1; vy[j] += 3;
           if (vx[j] >= 100) vx[j] -= 100;
           if (vy[j] >= 100) vy[j] -= 100;
           SDL_RenderDrawPoint(ren, vx[j], vy[j]);	
		} 
	
    	SDL_RenderPresent(ren); 
		
        SDL_Delay(400);
    }

	
    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
