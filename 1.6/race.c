#include <assert.h>
#include <SDL2/SDL.h>
#define MAX(x,y) (((x) > (y)) ? (x) : (y))

int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32* ms){
    Uint32 antes = SDL_GetTicks();
    if (SDL_WaitEventTimeout(evt, *ms)) {
    	int temp = *ms - (SDL_GetTicks() - antes);
		*ms = MAX(0, temp);
		return 1;
    } else return 0;
}

void desenhaCorrida(SDL_Rect* k, SDL_Rect* t, SDL_Rect* m, SDL_Rect* l, SDL_Renderer* ren){
    SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
    SDL_RenderClear(ren);
	SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0x00,0x00);
    SDL_RenderFillRect(ren, l);
    SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
    SDL_RenderFillRect(ren, k);
    SDL_SetRenderDrawColor(ren, 0x00,0xFF,0x00,0x00);
    SDL_RenderFillRect(ren, t);
    SDL_SetRenderDrawColor(ren, 0xFF,0x00,0x00,0x00);
    SDL_RenderFillRect(ren, m);
	SDL_RenderPresent(ren);
	return;
}

void desenhaFinal(SDL_Rect* k, SDL_Rect* t, SDL_Rect* m, SDL_Rect* l, SDL_Renderer* ren){
	SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
    SDL_RenderClear(ren);
	SDL_Rect ouro = {20,20,20,50};
	SDL_RenderFillRect(ren, &ouro);
	SDL_Rect prata = {40,30,20,40};
	SDL_RenderFillRect(ren, &prata);
	SDL_Rect bronze = {60,40,20,30};
	SDL_RenderFillRect(ren, &bronze);
	return;
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

	int tela = 0;
    int espera = 100;

	int vencedor = 0;
	int vencedores[] = {0,0,0};
    SDL_Rect k = {40,20,10,10};
    SDL_Rect t = {40,40,10,10};
    SDL_Rect m = {40,60,10,10};
	SDL_Rect l = {180,0,5,100};
	
    int running = 1;
    while (running) {
		
		switch (tela){
			case 0:
        		desenhaCorrida(&k,&t,&m,&l,ren);
				break;
			case 1:
				desenhaFinal(&k,&t,&m,&l,ren);
				break;		
		}


        SDL_Event evt;
        if (AUX_WaitEventTimeoutCount(&evt, &espera)){
            switch (evt.type){
                case SDL_KEYDOWN:
                    switch (evt.key.keysym.sym) {
                        case SDLK_LEFT:
                            k.x -= 2;
                            break;
                        case SDLK_RIGHT:
                            k.x += 2;
                            break;
                    }
                case SDL_WINDOWEVENT:
                    if (SDL_WINDOWEVENT_CLOSE == evt.window.event) running = 0;
                    break;
				case SDL_MOUSEMOTION:
		        	m.x = evt.button.x;
            }
        } else {
			t.x += 2;
            espera = 100; 
        }
		
		if (vencedor != 0) {
		if (k.x >= 195) vencedor = 1;
		else if (m.x >= 195) vencedor = 2;
		else if (t.x >= 195) vencedor = 3;
		} if (k.x >= 195 && m.x >= 195 && t.x >= 195) tela = 1;
		
		printf("%d",tela);
    }

	/* FINALIZACAO */
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();

}




