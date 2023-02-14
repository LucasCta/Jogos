void telaSulRen(SDL_Renderer* ren, SDL_Window* win, int * screen, int * espera, character * player) {

    int i, j, w, h; 
    SDL_GetWindowSize(win, &w, &h);
    SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
    //player->rect.x = 200;
    player->rect.y = 50;

    //player->rect.x = 550;

    //player->rect.x = 850;

    //player->rect.x = 1100;

    #include "../objects/terra.c"
    #include "../objects/screenBorders.c"
    #include "../objects/peixe.c"
    #include "../objects/chave.c"

    SDL_Rect cerca = {500, 0, 10, 720};
    SDL_Rect c0= {500, 0, 50, 600};
    SDL_Rect c1= {750, 0, 50, 600};
    SDL_Rect c2 = {1000, 0, 50, 600};
    SDL_Rect c3 = {1250, 0, 50, 600};
    SDL_Rect c4 = {500, 600, 700, 10};
    struct colliders * objects = createNode(); 
    for (i=0; i<4; i++) addNode(objects, screenBorder[i]);
    addNode(objects, cerca);
    addNode(objects, c0);
    addNode(objects, c1);
    addNode(objects, c2);
    addNode(objects, c3);
    addNode(objects, c4);

    Uint32 antes = SDL_GetTicks();
     
    while (*screen == telaSul){

        SDL_RenderClear(ren);
        drawBackground(ren, gramado);
        SDL_RenderCopy(ren, player->sprite, &player->sprite_cut, &player->rect);
	    if (itensEncontrados == chav) SDL_RenderCopy(ren,chave->sprite,&chave->sprite_cut, &chave->rect);
	    if (itensEncontrados == peix) SDL_RenderCopy(ren,peixe->sprite,&peixe->sprite_cut, &peixe->rect);
        SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_ADD);
        SDL_SetRenderDrawColor(ren, 0xB3, 0x8B, 0x6D, 125);
        SDL_RenderFillRect(ren, &(SDL_Rect) {550, 0, 200, 600});
        SDL_RenderFillRect(ren, &(SDL_Rect) {800, 0, 200, 600});
        SDL_RenderFillRect(ren, &(SDL_Rect) {1050, 0, 200, 600});
        SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_NONE);
        SDL_SetRenderDrawColor(ren, 0xB3, 0x8B, 0x6D, 225);
        SDL_RenderFillRect(ren, &cerca);
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
            if (isClose(player->rect, screenBorder[telaNorte-2]))
                *screen = telaInicial;
        }

    }

}
