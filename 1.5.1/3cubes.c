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
    	*ms = 100; 
    	return 0;
    }
}

int main (int argc, char* args[]){
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("3cubes",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         200, 100, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
	int v[2] = {2,2};
    SDL_Rect k = {40,20,10,10};
    SDL_Rect t = {40,20,10,10};
    SDL_Rect m = {40,20,10,10};
    int running = 1;
    int espera = 100;
    while (running) {
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &k);
        SDL_SetRenderDrawColor(ren, 0x00,0xFF,0x00,0x00);
        SDL_RenderFillRect(ren, &t);
        SDL_SetRenderDrawColor(ren, 0xFF,0x00,0x00,0x00);
        SDL_RenderFillRect(ren, &m);
        SDL_RenderPresent(ren);

        SDL_Event evt;
        int isevt = AUX_WaitEventTimeoutCount(&evt, &espera);
        if (isevt){
            if (evt.type == SDL_KEYDOWN){
                switch (evt.key.keysym.sym){
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
            } else if (evt.type == SDL_MOUSEMOTION){
            	m.x = evt.button.x;
            	m.y = evt.button.y;
				if (m.y > 90) m.y = 90;
				else if (m.x > 190) m.x = 190;
            }
        } else {
			t.x += v[0]; t.y += v[1];
            if (t.x >= 190) v[0] = -2;
			else if (t.x <= 0) v[0] = 2;
            if (t.y >= 90) v[1] = -2;
			else if (t.y <= 0) v[1] = 2;
        }

    }

	/* FINALIZACAO */
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();

}




