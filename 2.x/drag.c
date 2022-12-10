#include <assert.h>
#include <SDL2/SDL.h>
#define MAX(x,y) (((x) > (y)) ? (x) : (y))
#define MIN(x,y) (((x) < (y)) ? (x) : (y))

int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32* ms){
    Uint32 antes = SDL_GetTicks();
    if (SDL_WaitEventTimeout(evt, *ms)) {
    	int temp = *ms - (SDL_GetTicks() - antes);
		*ms = MAX(0, temp);
		return 1;
    } else return 0;
}

int main (int argc, char* args[]){

    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("race",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         200, 100, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    
	int x, y, newX, newY;
	
	int clicked = 0;
	int dragged = 0;
	int reset = 0;
	
	SDL_Rect cube = {75,25,50,50};
	int oPos[2] = {75,25};
	
    int espera = 100;
	int running = 1;
	
    while (running) {
    
		SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
	    SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0x00,0x00);
        SDL_RenderFillRect(ren, &cube);
        SDL_RenderPresent(ren);
        
        SDL_Event evt;	
	    if (AUX_WaitEventTimeoutCount(&evt, &espera)){
            switch (evt.type){
                case SDL_WINDOWEVENT:
                    if (SDL_WINDOWEVENT_CLOSE == evt.window.event)
                        running = 0;
                    break;
                case SDL_KEYDOWN:
                    if (evt.key.keysym.sym == SDLK_ESCAPE && dragged){
                        cube.x = oPos[0]; cube.y = oPos[1] ;
                        clicked = 0;
                        dragged = 0;
                        reset = 1;   
                    } break;
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&x,&y);
                    oPos[0] = cube.x; oPos[1] = cube.y;
                    clicked = 1;
                    dragged = 0;
				    reset = 0;
				    break;
				case SDL_MOUSEBUTTONUP:
				    if (!dragged && !reset) 
				        printf("Clicked");
				    clicked = 0;
				    dragged = 0;
				    reset = 0;
				    break;
			    case SDL_MOUSEMOTION:
			        if (SDL_GetMouseFocus()){
			            SDL_GetMouseState(&newX, &newY);
				        if (clicked){
				            if (cube.x < x && cube.x + 50 > x && cube.y < y && cube.y + 50 > y){
	                    		cube.x = MAX(0, MIN(cube.x + (newX - x), 150));
	                    		cube.y = MAX(0, MIN(cube.y + (newY - y), 50));
	                    	} dragged = 1;
				        } x = newX; y = newY; 
				    } else clicked = 0;
				    break;
            }
        } else {
            espera = 100; 
        }   
	   
    }

	/* FINALIZACAO */
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();

}




