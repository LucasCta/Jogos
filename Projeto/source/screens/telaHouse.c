void telaHouseRen(SDL_Renderer* ren, SDL_Window* win, int * screen, int * espera, character * player) {

    int i, j, w, h; 
    SDL_GetWindowSize(win, &w, &h);
    SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
    absToRelative(&player->rect);
  
    player->rect.x = 100;
    player->rect.y = 600;

    #include "../objects/floor.c"
    #include "../objects/hole1.c"
    #include "../objects/hole2.c"
    #include "../objects/hole3.c"
    #include "../objects/screenBorders.c"
    #include "../objects/peixe.c"
    #include "../objects/chave.c"
    #include "../objects/semente.c"
    #include "../objects/fruto.c"

    struct colliders * objects = createNode(); 
    for (i=0; i<4; i++) addNode(objects, screenBorder[i]);

    Uint32 antes = SDL_GetTicks();
     
    while (*screen == hous){
    
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, floor->sprite, &floor->sprite_cut, &floor->rect);
        SDL_RenderCopy(ren, buraco1->sprite, &buraco1->sprite_cut, &buraco1->rect);
        SDL_RenderCopy(ren, buraco2->sprite, &buraco2->sprite_cut, &buraco2->rect);
        SDL_RenderCopy(ren, buraco3->sprite, &buraco3->sprite_cut, &buraco3->rect);
        SDL_RenderCopy(ren, player->sprite, &player->sprite_cut, &player->rect);
        SDL_RenderPresent(ren);
    
        *espera = MAX(0, *espera - (int)(SDL_GetTicks() - antes));
        SDL_Event evt; int isevt = AUX_WaitEventTimeoutCount(&evt, espera);
        antes = SDL_GetTicks();

        if (isevt){
                switch (evt.type){
                    #include "../player_controls.c"
                    } break;
                    case SDL_WINDOWEVENT:
                        if (SDL_WINDOWEVENT_CLOSE == evt.window.event)
                            *screen = fim;
                        break;
                }
        } else {
            *espera = 20;
            if (isClose(player->rect, buraco1->rect)){
                *screen = telaSul;
                player->rect.x = 600;
            } 
            if (isClose(player->rect, buraco2->rect)){
                *screen = telaSul;
                player->rect.x = 850;
            } 
            if (isClose(player->rect, buraco3->rect)){
                *screen = telaSul;
                player->rect.x = 1100;
            } 
        }
  
    }
    
}
