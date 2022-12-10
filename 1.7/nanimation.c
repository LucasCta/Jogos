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

void desenhaBoneco(int v[100][2], SDL_Renderer* ren){
	SDL_SetRenderDrawColor(ren, 0x20,0x20,0x50,0x00); 
	SDL_RenderClear(ren);
	int c1 = filledCircleColor(ren, 50, 20, 10, 0xFFBBBBBB);
	int c2 = filledCircleColor(ren, 50, 40, 20, 0xFFBBBBBB);
	int c3 = filledCircleColor(ren, 50, 60, 30, 0xFFBBBBBB);
	int b1 = filledCircleColor(ren, 50, 45, 2, 0xFF000000);
	int b2 = filledCircleColor(ren, 50, 60, 2, 0xFF000000);
	int b3 = filledCircleColor(ren, 50, 75, 2, 0xFF000000);
	int o1 = filledCircleColor(ren, 45, 20, 1, 0xFF000000);
	int o2 = filledCircleColor(ren, 55, 20, 1, 0xFF000000);
	Sint16 v1[] = {50,58,50}; Sint16 v2[] = {24,26,28};
	int cen = filledPolygonRGBA(ren, v1, v2, 3, 0xFF, 0x57, 0x33, 255);
	SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
	/*int i = 0; for (i; i<100; i++){
		SDL_RenderDrawPoint(ren, v[i][0],v[i][1]);
	} */ SDL_RenderPresent(ren); 
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
	
    while (running) {
    
    	/* RENDER */
    	//desenhaBoneco(v, ren);
        SDL_Rect snowman = (SDL_Rect){1,1,100,100};
		SDL_RenderCopy(ren, img, &snowman, &snowman);
		SDL_RenderPresent(ren);
		
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
			} espera = 400; 
		}
		
	}

	/* FINALIZACAO */
    SDL_DestroyTexture(img);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();

}

/*
	else{   
	
		switch(isup){
			case 1:
				c = (SDL_Rect) { 0, 64, 30,32 };
			break;
			case 2:
				c = (SDL_Rect) { 125,64, 30,32 };
			break;
			case 3:
				c = (SDL_Rect) { 158,64, 30,32 };
			break;
			case 4:
				c = (SDL_Rect) { 125,64, 30,32 };
			break;
		} isup++;
	
		
        SDL_Rect r = { x,50, 100,80 };
        SDL_Rect c;
        
		SDL_RenderPresent(ren);
		espera = 250;
		x = (x + 10) % 400;
		if(isup > 4){
			isup = 1;
		}
*/
