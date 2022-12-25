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
    } return 0;
}

int main (int argc, char* args[]){

    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Detalhes",SDL_WINDOWPOS_UNDEFINED
                                                 ,SDL_WINDOWPOS_UNDEFINED
                                                                ,1280,720
                                                  ,SDL_WINDOW_FULLSCREEN);
    int w, h; SDL_GetWindowSize(win, &w, &h);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    SDL_Rect player = {40,20,100,100};
    int pSpeed = 5;
    int running = 1;
    int espera = 20;
    
    /* EVT LOOP */
    while (running) {
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &player);
        SDL_RenderPresent(ren);
        SDL_Event evt;
        int isevt = AUX_WaitEventTimeoutCount(&evt, &espera);
        if (isevt){
            if (evt.type == SDL_KEYDOWN){
                switch (evt.key.keysym.sym){
                     case SDLK_UP:
                        player.y = MAX(player.y - pSpeed, 0);
                        break;
                    case SDLK_DOWN:
                        player.y = MIN(player.y + pSpeed, h - player.h);
                        break;
                    case SDLK_LEFT:
                        player.x = MAX(player.x - pSpeed, 0);
                        break;
                    case SDLK_RIGHT:
                        player.x = MIN(player.x + pSpeed, w - player.w);
                        break;
                }
            } else if (evt.type == SDL_WINDOWEVENT){
            	if (SDL_WINDOWEVENT_CLOSE == evt.window.event){
					running = 0;
            	}
            } 
        } else espera = 20;
    }

	/* FINALIZACAO */
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();

}




