#include <assert.h>
#include <SDL2/SDL.h>
#define MAX(x,y) (((x) > (y)) ? (x) : (y))

int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32* ms){
    Uint32 antes = SDL_GetTicks();
    if (SDL_WaitEventTimeout(evt, *ms)) {
    	int temp = *ms - (SDL_GetTicks() - antes);
		*ms = MAX(0, temp);
		return 1;
    } else {
    	return 0;
    }
}

int main (int argc, char* args[]){
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Contando o Tempo",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         200, 100, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    SDL_Rect k = { 40,20, 10,10 };
    int running = 1;
    int espera = 500;
    while (running) {
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &k);
        SDL_RenderPresent(ren);

        SDL_Event evt;
        int isevt = AUX_WaitEventTimeoutCount(&evt, &espera);
        if (isevt){
            if (evt.type == SDL_KEYDOWN) {
                switch (evt.key.keysym.sym) {
                    case SDLK_UP:
                        k.y -= 5;
                        if (k.y < 0) k.y = 0;
                        break;
                    case SDLK_DOWN:
                        k.y += 5;
                        if (k.y > 90) k.y = 90;
                        break;
                    case SDLK_LEFT:
                        k.x -= 5;
                        if (k.x < 0) k.x = 0;
                        break;
                    case SDLK_RIGHT:
                        k.x += 5;
                        if (k.x > 190) k.x = 190;
                        break;
                }
            } else if (evt.type == SDL_WINDOWEVENT){
            	if (SDL_WINDOWEVENT_CLOSE == evt.window.event){
					running = 0;
			    }
            }
        } else {
            if (k.x < 190) k.x += 2;
            if (k.y < 90) k.y += 2;
			espera = 500; 
        }
    }
	
	/* FINALIZACAO */
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}
