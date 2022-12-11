#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <assert.h>

#define MAX(x,y) (((x) > (y)) ? (x) : (y))

int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32* ms){
    Uint32 antes = SDL_GetTicks();
    if (SDL_WaitEventTimeout(evt, *ms)) {
    	int temp = *ms - (SDL_GetTicks() - antes);
		*ms = MAX(0, temp);
		return 1;
    } else return 0;
}

void desenhaBoneco(int v[100][2], int cut, SDL_Texture* img, SDL_Renderer* ren){
    SDL_SetRenderDrawColor(ren, 0x20,0x20,0x50,0x00); 
    SDL_RenderClear(ren);
    SDL_Rect snowman = (SDL_Rect){1,1,100,100};
    SDL_Rect snowmanStage = (SDL_Rect){cut,1,100,100};
	SDL_RenderCopy(ren, img, &snowmanStage, &snowman);
    SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
	int i = 0; 
	for (i; i<100; i++)
	    SDL_RenderDrawPoint(ren, v[i][0],v[i][1]);
    SDL_RenderPresent(ren); 
}

int main (int argc, char* args[]){

    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Ciclos2",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         100, 100, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
    SDL_Texture* img = IMG_LoadTexture(ren, "snowman.png");
    assert(img != NULL);

    /* EXECUÇÃO */	
			
	int v[100][2];
	int i = 0; 
	for (i; i<100; i++){
		v[i][0] = rand()%100;
		v[i][1] = rand()%100;
	}
	
	int running = 1;
	int espera = 400;
	int cont = 0;
	int cut = 1;
	
    while (running) {
    
    	/* RENDER */
	    desenhaBoneco(v, cut, img, ren);
		
		/* EVENTOS */
		SDL_Event evt;
        int isevt = AUX_WaitEventTimeoutCount(&evt, &espera);
        if (isevt){
        	if (evt.type == SDL_WINDOWEVENT){
            	if (SDL_WINDOWEVENT_CLOSE == evt.window.event){
					running = 0;
            	}
            }
        } else {
			int j = 0;
			for (j; j<100; j++){
			   v[j][0] += 1; v[j][1] += 3;
			   if (v[j][0] >= 100) v[j][0] -= 100;
			   if (v[j][1] >= 100) v[j][1] -= 100;	
			}
			if (cont == 450) {
			    cut = 1;
			    cont = 0;
                espera = 400; 
			} else if (cont >= 390) {
			    cut += 100;
			    cont += 1;
                espera = 10; 
			} else if (cont >= 40) { 
			    cont += 10;
			    espera = 400 - cont;
			} else {
                espera = 400; 
			    if (cont++%10 == 9)
			        cut += 100; 
		    }
		}
		
	}

	/* FINALIZACAO */
    SDL_DestroyTexture(img);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();

}
