#include <SDL2/SDL.h>
#include <stdio.h>

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
    SDL_Rect r[10];
    int colors[10][3];
    SDL_Rect player = {40,20,10,10};

    while (1) {

        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);

        int i = 0; 
        for (i; i<rCont; i++){
            SDL_SetRenderDrawColor(ren,colors[i][0],colors[i][1],colors[i][2],0x00);
            SDL_RenderFillRect(ren, &r[i]);
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
                    default:
                        if (state[SDL_SCANCODE_LALT] && state[SDL_SCANCODE_F4]) {
			                 SDL_DestroyRenderer(ren);
	                         SDL_DestroyWindow(win);
                             SDL_Quit();
		                } break;
                }
            case SDL_WINDOWEVENT:
                if (SDL_WINDOWEVENT_CLOSE == evt.window.event){
            		SDL_DestroyRenderer(ren);
					SDL_DestroyWindow(win);
					SDL_Quit();
                } break;
            case SDL_MOUSEBUTTONDOWN:
                if (SDL_BUTTON_LEFT == evt.button.button && rCont < 10){
                    SDL_Rect temp = {evt.button.x,evt.button.y,rand()%20+10,rand()%20+10};
                    int j = 0; for (j; j<4; j++){
                        colors[rCont][j] = rand()%255;
                    } r[rCont] = temp; rCont += 1;             
			    } break;
        }
    }
    
}
