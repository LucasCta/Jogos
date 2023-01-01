#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#define MAX(x,y) (((x) > (y)) ? (x) : (y))
#define MIN(x,y) (((x) < (y)) ? (x) : (y))

typedef struct {
    char * text;
    TTF_Font * font;
    SDL_Color color;
    SDL_Rect rect;
} screenTex;

enum states {idle=0,walking,pushing,talking,interacting};
enum tela {menu=0,telaInicial,fim};

int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32* ms){
    Uint32 antes = SDL_GetTicks();
    if (SDL_WaitEventTimeout(evt, *ms)) {
    	int temp = *ms - (SDL_GetTicks() - antes);
		*ms = MAX(0, temp);
		return 1;
    } return 0;
}

void menuRen (SDL_Renderer* ren, int * screen, int * espera) {

    int x, y;
    
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("zk.ttf",100);
    
    SDL_Color orange = {0xF6,0x6A,0x03,0xFF}; 
    SDL_Color black = {0x00,0x00,0x00,0xFF};
    SDL_Color darkGrey = {125,125,125,255}; 
    SDL_Color grey = {125,125,125,125};
    
    screenTex * menuTex = malloc(sizeof(*menuTex) * 3);
    
    menuTex[0].text = malloc(sizeof("Detalhes"));
    menuTex[0].text = "Detalhes";
    menuTex[0].font = font;
    menuTex[0].color = orange;
    menuTex[0].rect = (SDL_Rect) {340,100,600,200};
    
    menuTex[1].text = malloc(sizeof("Jogar"));
    menuTex[1].text = "Jogar";
    menuTex[1].font = font;
    menuTex[1].color = grey;
    menuTex[1].rect = (SDL_Rect) {540,300,200,200};    
    
    menuTex[2].text = malloc(sizeof("Sair"));
    menuTex[2].text = "Sair";
    menuTex[2].font = font;
    menuTex[2].color = grey;
    menuTex[2].rect = (SDL_Rect) {540,500,200,200};

    while (*screen == menu){
    
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);   
        
        int i;
        for (i = 0; i < 3; i++){
            struct SDL_Surface * tempSur = TTF_RenderText_Solid(menuTex[i].font,menuTex[i].text,menuTex[i].color);
            struct SDL_Texture * tempTex = SDL_CreateTextureFromSurface(ren,tempSur);
            SDL_RenderCopy(ren,tempTex,NULL,&(menuTex[i].rect));
            SDL_FreeSurface(tempSur); SDL_DestroyTexture(tempTex);
        }
        
	    SDL_RenderPresent(ren);
	    
	    SDL_Event evt;
        if (AUX_WaitEventTimeoutCount(&evt, espera)){
            switch (evt.type) {
                case SDL_WINDOWEVENT:
                	if (SDL_WINDOWEVENT_CLOSE == evt.window.event)
                	    *screen = fim;
                	break;
                case SDL_MOUSEMOTION:
                    SDL_GetMouseState(&x,&y);
                    menuTex[1].color = grey;
                    menuTex[2].color = grey;
				    if (menuTex[1].rect.x < x && menuTex[1].rect.x + 200 > x && 
				    menuTex[1].rect.y < y && menuTex[1].rect.y + 200 > y)
                        menuTex[1].color = black;
                    else if (menuTex[2].rect.x < x && menuTex[2].rect.x + 200 > x && 
                    menuTex[2].rect.y < y && menuTex[2].rect.y + 200 > y)
                        menuTex[2].color = black;
				    break;
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&x,&y);
                    if (menuTex[1].rect.x < x && menuTex[1].rect.x + 200 > x && 
                    menuTex[1].rect.y < y && menuTex[1].rect.y + 200 > y)
                        *screen = telaInicial;
                    else if (menuTex[2].rect.x < x && menuTex[2].rect.x + 200 > x && 
                    menuTex[2].rect.y < y && menuTex[2].rect.y + 200 > y)
                        *screen = fim;
                    break;
            }
        } else *espera = 100;
        
    }
    
	TTF_CloseFont(font);
	free(menuTex);
	
}

void telaInicialRen(SDL_Renderer* ren, SDL_Window* win, int * screen, int * espera) {

    int w, h; SDL_GetWindowSize(win, &w, &h);
    
    SDL_Rect player = {40,20,100,100};
    int pState = idle;
    int pSpeed = 5;
    
    while (*screen == telaInicial){
    
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &player);
        SDL_RenderPresent(ren);
        
        SDL_Event evt;
        if (AUX_WaitEventTimeoutCount(&evt, espera)){
            if (evt.type == SDL_KEYDOWN){
                switch (evt.key.keysym.sym){
                     case SDLK_w:
                        player.y = MAX(player.y - pSpeed, 0);
                        break;
                    case SDLK_s:
                        player.y = MIN(player.y + pSpeed, h - player.h);
                        break;
                    case SDLK_a:
                        player.x = MAX(player.x - pSpeed, 0);
                        break;
                    case SDLK_d:
                        player.x = MIN(player.x + pSpeed, w - player.w);
                        break;
                    case SDLK_LSHIFT:
                        pSpeed = 10;
                        break;
                   case SDLK_ESCAPE:
                        *screen = menu;
                        break;
                }
            } else if (evt.type == SDL_KEYUP){
               if (evt.key.keysym.sym == SDLK_LSHIFT)
                   pSpeed = 5;
            } else if (evt.type == SDL_WINDOWEVENT){
            	if (SDL_WINDOWEVENT_CLOSE == evt.window.event)
				    *screen = fim;
            } 
        } else *espera = 20;
        
    }
    
}

int main (int argc, char* args[]){

    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Detalhes",SDL_WINDOWPOS_UNDEFINED
                                                 ,SDL_WINDOWPOS_UNDEFINED
                                                                ,1280,720
                                                  ,SDL_WINDOW_FULLSCREEN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    
    int screen = menu;
    int espera = 100;
    
    /* EVT LOOP */
    while (screen < fim) {
        switch (screen) {
            case menu:
                menuRen(ren,&screen,&espera);
            case telaInicial:  
                telaInicialRen(ren,win,&screen,&espera);
        } 
    }

	/* FINALIZACAO */
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();

}




