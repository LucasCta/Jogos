#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#define MAX(x,y) (((x) > (y)) ? (x) : (y))
#define MIN(x,y) (((x) < (y)) ? (x) : (y))

typedef struct {
    char * text;
    TTF_Font * font;
    SDL_Color color;
    SDL_Rect rect;
} screenTex;

typedef struct {
    SDL_Rect rect;
    SDL_Texture * sprite;
    SDL_Rect sprite_cut;
    screenTex * dialog;
    int state;
    int speed;
} character;

typedef struct {
    SDL_Rect tile;
    SDL_Texture * tileset;
    SDL_Rect sprite_cuts[18][32];
} background;

enum states {idle=0,walking,pushing,talking,interacting};
enum tela {menu=0,telaInicial,fim};

int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32* ms){
    Uint32 antes = SDL_GetTicks();
    SDL_FlushEvent(SDL_MOUSEMOTION);
    if (SDL_WaitEventTimeout(evt, *ms)) {
        *ms = MAX(0, *ms - (int)(SDL_GetTicks() - antes));
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
    menuTex[1].rect = (SDL_Rect) {540,300,250,200};    
    
    menuTex[2].text = malloc(sizeof("Sair"));
    menuTex[2].text = "Sair";
    menuTex[2].font = font;
    menuTex[2].color = grey;
    menuTex[2].rect = (SDL_Rect) {540,500,250,200};

    Uint32 antes = SDL_GetTicks();
    
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
        
        *espera = MAX(0, *espera - (int)(SDL_GetTicks() - antes));
        SDL_Event evt; int isevt = AUX_WaitEventTimeoutCount(&evt, espera);
        antes = SDL_GetTicks();
        
        if (isevt){
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

void drawBackground(SDL_Renderer* ren, background * bg){
    int i, j; 
    bg->tile = (SDL_Rect) {0, 0, 40, 40};
    for (i=0; i<18; i++) {
        for (j=0; j<32; j++) {
            SDL_RenderCopy(ren, bg->tileset, &bg->sprite_cuts[i][j], &bg->tile);
            bg->tile.x = (bg->tile.x + 40) % 1280;    
        } bg->tile.y += 40;
    }
}

void telaInicialRen(SDL_Renderer* ren, SDL_Window* win, int * screen, int * espera, character * player) {

    int i, j;

    int w, h; SDL_GetWindowSize(win, &w, &h);

    character * mistWoman = malloc(sizeof(*mistWoman));
    mistWoman->rect = (SDL_Rect) {256, 256, 64, 64};
    mistWoman->sprite = IMG_LoadTexture(ren, "images/woman_idle.png");
    mistWoman->sprite_cut = (SDL_Rect) {0, 0, 37, 46}; 
    mistWoman->state = idle;
    mistWoman->speed = 10;
    int wAnimation = 0;

    mistWoman->dialog = malloc(sizeof(*screenTex));
    mist.text = malloc(sizeof("Detalhes"));
    menuTex[0].text = "Detalhes";
    menuTex[0].font = font;
    menuTex[0].color = orange;
    menuTex[0].rect = (SDL_Rect) {340,100,600,200};
    
    background * gramado = malloc(sizeof(*gramado));
    gramado->tileset = IMG_LoadTexture(ren,"images/grass_tileset.png");    
    for (i=0; i<18; i++)
        for (j=0; j<32; j++)
            gramado->sprite_cuts[i][j] = (SDL_Rect) {0,rand()%3*16,16,16}; 

    
    SDL_Point playerbox = {player->rect.x, player->rect.y};
    SDL_Point playerbox2 = {player->rect.x + player->rect.w, player->rect.y + player->rect.h};

    Uint32 antes = SDL_GetTicks();
     
    while (*screen == telaInicial){
    
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        drawBackground(ren, gramado);
        SDL_RenderCopy(ren, mistWoman->sprite, &mistWoman->sprite_cut, &mistWoman->rect);
        SDL_RenderCopy(ren, player->sprite, &player->sprite_cut, &player->rect);
        SDL_RenderPresent(ren);

        *espera = MAX(0, *espera - (int)(SDL_GetTicks() - antes));
        SDL_Event evt; int isevt = AUX_WaitEventTimeoutCount(&evt, espera);
        antes = SDL_GetTicks();
    
        if (isevt){
             switch (evt.type){
                case SDL_KEYDOWN: 
                    switch (evt.key.keysym.sym){
                         case SDLK_w:
                            if (player->sprite_cut.y == 512)
                                player->sprite_cut.x = (player->sprite_cut.x + 64) % 576;
                            player->sprite_cut.y = 512;
                            player->rect.y = MAX(player->rect.y - player->speed, 0);             
                            break;
                        case SDLK_s:
                            if (player->sprite_cut.y == 640)
                                player->sprite_cut.x = (player->sprite_cut.x + 64) % 576;
                            player->sprite_cut.y = 640;
                            player->rect.y = MIN(player->rect.y + player->speed, h - player->rect.h);
                            break;
                        case SDLK_a:
                            if (player->sprite_cut.y == 576)
                                player->sprite_cut.x = (player->sprite_cut.x + 64) % 576;
                            player->sprite_cut.y = 576;
                            player->rect.x = MAX(player->rect.x - player->speed, 0);
                            break;
                        case SDLK_d:
                            if (player->sprite_cut.y == 704)
                                player->sprite_cut.x = (player->sprite_cut.x + 64) % 576;
                            player->sprite_cut.y = 704;
                            player->rect.x = MIN(player->rect.x + player->speed, w - player->rect.w);
                            break;
                        case SDLK_LSHIFT:
                            player->speed = 10;
                            break;
                        case SDLK_KP_ENTER:
                            if (SDL_PointInRect(&playerbox, &mistWoman->rect) || SDL_PointInRect(&playerbox2 , &mistWoman->rect))
                                stringRGBA(ren, mistWoman->rect.x+mistWoman->rect.w-5, mistWoman->rect.y, mistWoman->dialog, 0x00,0x00,0x00,0xFF);
                            break;
                       case SDLK_ESCAPE:
                            *screen = menu;
                            break;
                    } break;
                case SDL_KEYUP:
                    if (evt.key.keysym.sym == SDLK_LSHIFT)
                        player->speed = 5;
                    break;
                case SDL_WINDOWEVENT:
                    if (SDL_WINDOWEVENT_CLOSE == evt.window.event)
                        *screen = fim;
                    break;
            } 
        } else {
            *espera = 20;
            if (++wAnimation == mistWoman->speed){
                mistWoman->sprite_cut.x = (mistWoman->sprite_cut.x + 37) % 259;
                wAnimation = 0;
            } 
        }
        
    }
    
}

int main (int argc, char* args[]){

    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Detalhes",SDL_WINDOWPOS_UNDEFINED
                                                 ,SDL_WINDOWPOS_UNDEFINED
                                                                ,1280,720
                                                  ,SDL_WINDOW_BORDERLESS);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    
    character * player = malloc(sizeof(*player));
    player->rect = (SDL_Rect) {64, 64, 64, 64};
    player->sprite = IMG_LoadTexture(ren, "images/player.png");
    player->sprite_cut = (SDL_Rect) {0, 512, 64, 64};
    player->state = idle;
    player->speed = 5;
    
    int screen = menu;
    int espera = 100;
    
    /* EVT LOOP */
    while (screen < fim) {
        switch (screen) {
            case menu:
                menuRen(ren,&screen,&espera);
            case telaInicial:  
                telaInicialRen(ren,win,&screen,&espera,player);
        } 
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

}




