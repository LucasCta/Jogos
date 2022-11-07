#include <SDL2/SDL.h>

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
    SDL_Rect r = { 40,20, 10,10 };
    SDL_Event evt;
    
    while (1) {
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &r);
        SDL_RenderPresent(ren);
        SDL_WaitEvent(&evt);
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if (evt.type == SDL_KEYDOWN) {
            if (state[SDL_SCANCODE_LALT] && state[SDL_SCANCODE_F4]) {
				SDL_DestroyRenderer(ren);
				SDL_DestroyWindow(win);
				SDL_Quit();
			} switch (evt.key.keysym.sym) {
                case SDLK_UP:
                    r.y -= 5;
                    break;
                case SDLK_DOWN:
                    r.y += 5;
                    break;
                case SDLK_LEFT:
                    r.x -= 5;
                    break;
                case SDLK_RIGHT:
                    r.x += 5;
                    break;
            } 
        } else if (evt.type == SDL_WINDOWEVENT) {
            switch (evt.window.event){
            	case SDL_WINDOWEVENT_CLOSE:
            		SDL_DestroyRenderer(ren);
					SDL_DestroyWindow(win);
					SDL_Quit();
			}
        } else if (evt.type == SDL_MOUSEBUTTONDOWN){
        	if (SDL_BUTTON_LEFT){
        		SDL_Rect r = {40,20,10,10};
			}
        }
    }
    
}

