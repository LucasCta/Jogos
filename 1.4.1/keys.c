#include <SDL2/SDL.h>
#include <stdio.h>

typedef struct {
	SDL_Rect r;
    int colors[3];
} Rcolorido;

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Movendo um Retângulo",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         200, 100, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */

    SDL_Event evt;

    int rCont = 0; 
	Rcolorido rect[10];
    SDL_Rect player = {40,20,10,10};
	
	int running = 1;
    while (running) {

        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);

        int i = 0; 
        for (i; i<rCont; i++){
            SDL_SetRenderDrawColor(ren,rect[i].colors[0],rect[i].colors[1],rect[i].colors[2],0x00);
            SDL_RenderFillRect(ren, &rect[i].r);
        } 
        
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &player);

        SDL_RenderPresent(ren);

        SDL_WaitEvent(&evt);
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        switch (evt.type){
            case SDL_KEYDOWN:
                switch (evt.key.keysym.sym) {
                    case SDLK_UP:
                        player.y -= 5;
                        if (player.y < 0) player.y = 0;
                        break;
                    case SDLK_DOWN:
                        player.y += 5;
                        if (player.y > 90) player.y = 90;
                        break;
                    case SDLK_LEFT:
                        player.x -= 5;
                        if (player.x < 0) player.x = 0;
                        break;
                    case SDLK_RIGHT:
                        player.x += 5;
                        if (player.x > 190) player.x = 190;
                        break;
                }
            case SDL_WINDOWEVENT:
                if (SDL_WINDOWEVENT_CLOSE == evt.window.event){
					running = 0;
                } break;
            case SDL_MOUSEBUTTONDOWN:
                if (SDL_BUTTON_LEFT == evt.button.button && rCont < 10){
                    SDL_Rect temp = {evt.button.x,evt.button.y,rand()%20+10,rand()%20+10};
                    int j = 0; for (j; j<4; j++){
                        rect[rCont].colors[j] = rand()%255;
                    } rect[rCont].r = temp; rCont += 1;             
			    } break;
        }

    }
	
	/* FINALIZACAO */
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
    
}
