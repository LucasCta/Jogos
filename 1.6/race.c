#include <assert.h>
#include <SDL2/SDL.h>
#define MAX(x,y) (((x) > (y)) ? (x) : (y))

typedef struct {
  SDL_Rect r;
  int rgb[3];
  int pos;
} Player;

int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32* ms){
    Uint32 antes = SDL_GetTicks();
    if (SDL_WaitEventTimeout(evt, *ms)) {
    	int temp = *ms - (SDL_GetTicks() - antes);
		*ms = MAX(0, temp);
		return 1;
    } else return 0;
}

void desenhaCorrida(Player p[], SDL_Renderer* ren){
    SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
    SDL_RenderClear(ren);
	SDL_Rect line = {180,0,5,100};
	SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0x00,0x00);
    SDL_RenderFillRect(ren, &line);
	int i; for (i = 0; i < 3; i++){
		SDL_SetRenderDrawColor(ren, p[i].rgb[0],p[i].rgb[1],p[i].rgb[2],0x00);
    	SDL_RenderFillRect(ren, &p[i].r);
	} SDL_RenderPresent(ren);
	return;
}

void desenhaFinal(Player p[], SDL_Renderer* ren){
	SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
    SDL_RenderClear(ren);
	int i; for (i = 0; i < 3; i++){
		SDL_SetRenderDrawColor(ren, p[i].rgb[0],p[i].rgb[1],p[i].rgb[2],0x00);
    	SDL_Rect pillar = {70+(i*20),30+((p[i].pos-1)*10),20,50-(p[i].pos*10)};
		SDL_RenderFillRect(ren, &pillar);
	} SDL_RenderPresent(ren);
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
	int x, y;
	int tela = 0;
    int final = 0;
    int espera = 100;
	int position = 0;
	Player p[3]; int i;
	for (i = 0; i < 3; i++) {
		SDL_Rect temp = {40,20+(i*20),10,10};
		p[i].r = temp;
		p[i].rgb[0] = 0x00;
		p[i].rgb[1] = 0x00;
		p[i].rgb[2] = 0x00;
		p[i].rgb[i] = 0xFF;
		p[i].pos = 0;
	} int running = 1;

    while (running) {
		
		switch (tela){
			case 0:
        		desenhaCorrida(p,ren);
				break;
			case 1:
				desenhaFinal(p,ren);
				break;		
		}

        SDL_Event evt;
        if (AUX_WaitEventTimeoutCount(&evt, &espera)){
            switch (evt.type){
                case SDL_KEYDOWN:
                    switch (evt.key.keysym.sym) {
                        case SDLK_LEFT:
                            p[0].r.x -= 2;
                            break;
                        case SDLK_RIGHT:
                            p[0].r.x += 2;
                            break;
                    } break;
                case SDL_WINDOWEVENT:
                    if (SDL_WINDOWEVENT_CLOSE == evt.window.event) running = 0;
                    break;
				case SDL_MOUSEMOTION:
					SDL_GetMouseState(&x, &y);
					if (p[1].r.x < x && p[1].r.x+10 > x && p[1].r.y < y && p[1].r.y+10 > y)
		        		p[1].r.x = x-5;
					break;
            }
        } else {
			p[2].r.x += 3;
            espera = 100; 
        }
		
		for (i = 0; i < 3; i++){
			if (p[i].pos == 0){
				if (p[i].r.x >= 185)
					p[i].pos = ++position;
			} else { 
				if (++final == 3)
					tela = 1;
			}
		} final = 0;
		
    }

	/* FINALIZACAO */
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();

}




