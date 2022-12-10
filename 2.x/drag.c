#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
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
    SDL_Window* win = SDL_CreateWindow("drag",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         200, 100, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    
	int x, y, newX, newY;
	
	int clicked = 0;
	int dragged = 0;
	
    char* texto[] = {"Ready!","Cancelled!","Clicked!","Dropped!","Dragging...","Selected","Unselected"};
    enum states {ready=0,cancelled,click,dropped,dragging,selected,unselected}; 
	int cur_state;

	SDL_Rect cube = {75,25,50,50};
	int oPos[2] = {75,25};
	
    int espera = 30;
    int contEspera = 0;
	int running = 1;
	
	
    while (running) {
    
		SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
	    SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0x00,0x00);
        SDL_RenderFillRect(ren, &cube);
        stringRGBA(ren, 5, 5, texto[cur_state], 0x00,0x00,0x00,0xFF);
        SDL_RenderPresent(ren);
        
        SDL_Event evt;	
	    if (AUX_WaitEventTimeoutCount(&evt, &espera)){
	        contEspera = 0;
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
                        cur_state = cancelled;  
                    } break;
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&x,&y);
                    oPos[0] = cube.x; oPos[1] = cube.y;
                    clicked = 0;
                    if (cube.x < x && cube.x + 50 > x && cube.y < y && cube.y + 50 > y)
                        clicked = 1;
                    dragged = 0;
				    break;
				case SDL_MOUSEBUTTONUP:
				    if (!dragged && clicked && cur_state == selected)
				        cur_state = unselected;
				    else if (!dragged && clicked) 
				        cur_state = click;
				    else if (dragged && clicked)
				        cur_state = dropped;
				    clicked = 0;
				    dragged = 0;
				    break;
			    case SDL_MOUSEMOTION:
			        if (SDL_GetMouseFocus()){
			            SDL_GetMouseState(&newX, &newY);
				        if (clicked){
				            cur_state = dragging;
	                    	cube.x = MAX(0, MIN(cube.x + (newX - x), 150));
	                        cube.y = MAX(0, MIN(cube.y + (newY - y), 50));
	                        dragged = 1;
				        } x = newX; y = newY; 
				    } else {
				        clicked = 0;
				        if (dragged) cur_state = dropped;
				        dragged = 0;
				    } break;
            }
        } else {
            espera = 30; 
            if (clicked && !dragged){
                if (contEspera++ == 10)
                    cur_state = selected;
            } else contEspera = 0;
        }   
	   
    }

	/* FINALIZACAO */
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();

}




