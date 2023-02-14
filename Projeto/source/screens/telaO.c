void telaOesteRen(SDL_Renderer* ren, SDL_Window* win, int * screen, int * espera, character * player) {

    int i, j, w, h; 
    SDL_GetWindowSize(win, &w, &h);
    SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
    absToRelative(&player->rect);

    #include "../objects/gramado_verde.c"
    #include "../objects/screenBorders.c"
    #include "../objects/oldMan.c"
    #include "../objects/peixe.c"
    #include "../objects/chave.c"
    #include "../objects/semente.c"
    #include "../objects/fruto.c"

    struct colliders * objects = createNode(); 
    for (i=0; i<4; i++) addNode(objects, screenBorder[i]);
    addNode(objects, oldman->rect);
    int dialogCounter = 0;

    Uint32 antes = SDL_GetTicks();
     
    while (*screen == telaOeste){
    
        SDL_RenderClear(ren);
        drawBackground(ren, gramado);
        SDL_RenderCopy(ren, player->sprite, &player->sprite_cut, &player->rect);
        if (itensEncontrados <= chav) SDL_RenderCopy(ren, oldman->sprite, &oldman->sprite_cut, &oldman->rect);
	    if (itensEncontrados == chav) SDL_RenderCopy(ren,chave->sprite,&chave->sprite_cut, &chave->rect);
	    if (itensEncontrados == peix) SDL_RenderCopy(ren,peixe->sprite,&peixe->sprite_cut, &peixe->rect);
	    if (itensEncontrados == sement) SDL_RenderCopy(ren,semente->sprite,&semente->sprite_cut, &semente->rect);
	    if (itensEncontrados == frut) SDL_RenderCopy(ren,fruto->sprite,&fruto->sprite_cut, &fruto->rect);
        if (itensEncontrados <= chav) stringRGBA(ren, oldman->rect.x+oldman->rect.w-5, oldman->rect.y, oldman->dialog[actualDialog], 0x00,0x00,0x00,0xFF);
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
            if (++wAnimation == oldman->speed){
                oldman->sprite_cut.x = MIN((oldman->sprite_cut.x + 34),238);
                wAnimation = 0;
            } 
            if (isClose(player->rect, screenBorder[telaLeste-2]))
                *screen = telaInicial;
            if (isClose(player->rect, oldman->rect)) {
                switch (itensEncontrados){
                    case nada:
                        if (actualDialog == 0) actualDialog = 1;
                        break;
                    case peix:
                        if (actualDialog == 0) actualDialog = 2;
                        if (actualDialog >=  2 && actualDialog < 4) { 
                            dialogCounter += 1; 
                            dialogCounter %= 200;
                            if(dialogCounter == 199)
                                actualDialog += 1; 
                        } 
                        else if (actualDialog == 4) {
                            itensEncontrados = chav;
                        }
                        break;
                    }
            }
        }
    
    }

}
