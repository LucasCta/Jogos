#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

typedef struct {
    SDL_Rect tile;
    SDL_Texture * tileset;
    SDL_Rect sprite_cuts[18][32];
} background;

typedef struct {
    char * text;
    TTF_Font * font;
    SDL_Color color;
    SDL_Rect rect;
    SDL_Texture * tex;
} screenText;

typedef struct {
    SDL_Rect rect;
    SDL_Texture * sprite;
    SDL_Rect sprite_cut;
} object;

typedef struct {
    SDL_Rect rect;
    SDL_Texture * sprite;
    SDL_Rect sprite_cut;
    char ** dialog;
    int state;
    int speed;
} character;

enum itens {nada=0,peix,chav,lampada};
int itensEncontrados = 0;

enum tela {menu=0,telaInicial,telaOeste,telaNorte,telaLeste,telaSul,fim};
enum states {idle=0,walking,pushing,talking,interacting};

#define MAX(x,y) (((x) > (y)) ? (x) : (y))
#define MIN(x,y) (((x) < (y)) ? (x) : (y))

#include "source/event_handler.c"
#include "source/collision_handler.c"
#include "source/background_renderer.c"
#include "source/position_converter.c"

#include "source/screens/menu.c"
#include "source/screens/telainicial.c"
#include "source/screens/telaN.c"
#include "source/screens/telaS.c"
#include "source/screens/telaL.c"
#include "source/screens/telaO.c"

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
    int screenBef = telaInicial;
    int espera = 100;

    /* EVT LOOP */
    while (screen < fim) {
        switch (screen) {
            case menu:
                menuRen(ren,&screen,&screenBef);
                break;
            case telaInicial:  
                telaInicialRen(ren,win,&screen,&espera,player);
                screenBef = telaInicial;
                break;
            case telaNorte:
                telaNorteRen(ren,win,&screen,&espera,player);
                screenBef = telaNorte;
                break;
            case telaSul:
                telaSulRen(ren,win,&screen,&espera,player);
                screenBef = telaSul;
                break;
            case telaLeste:
                telaLesteRen(ren,win,&screen,&espera,player);
                screenBef = telaLeste;
                break;
            case telaOeste:
                telaOesteRen(ren,win,&screen,&espera,player);
                screenBef = telaOeste;
                break;
        } 
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

}
