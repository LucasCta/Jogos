#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
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
    
    enum tela {menu=0,telaInicial,fim};
    enum states {idle=0,walking,pushing,talking,interacting};
    
    SDL_Rect player = {40,20,100,100};
    int pState = idle;
    int pSpeed = 5;
    
    int screen = menu;
    int espera = 100;
    
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("zk.ttf",100);
    
    /* EVT LOOP */
    while (screen < fim) {
    
        while (screen == menu){
        
            SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
            SDL_RenderClear(ren);
        
            SDL_Rect recPlay = {500,500,200,200};
            SDL_Color grey = {125,125,125,125};
            struct SDL_Surface * play = TTF_RenderText_Solid(font,"Play",grey);    
            struct SDL_Texture * playBut = SDL_CreateTextureFromSurface(ren,play);
            SDL_RenderCopy(ren,playBut,NULL,&recPlay);
	
		    SDL_RenderPresent(ren);
		    
		    SDL_Event evt;
            int isevt = AUX_WaitEventTimeoutCount(&evt, &espera);
            if (isevt){
                if (evt.type == SDL_WINDOWEVENT){
                	if (SDL_WINDOWEVENT_CLOSE == evt.window.event)
                	    screen = fim;
                } 
            } else espera = 100;
            
        }
        
        while (screen == telaInicial){
            SDL_Rect npc = {400,400,100,100};
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
					    screen = fim;
                	}
                } 
            } else espera = 20;
        }
        
    }

	/* FINALIZACAO */
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();

}




