void telaInicialRen(SDL_Renderer* ren, SDL_Window* win, int * screen, int * espera, character * player) {

    int i, j, w, h; 
    SDL_GetWindowSize(win, &w, &h);
    SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
    absToRelative(&player->rect);
  
    #include "../objects/house.c"
    #include "../objects/mysteriousWoman.c"
    #include "../objects/screenBorders.c"
    #include "../objects/gramado.c"
    #include "../objects/peixe.c"
    #include "../objects/chave.c"
    #include "../objects/semente.c"
    #include "../objects/fruto.c"
    #include "../objects/mochila.c"

    if (itensEncontrados == frut) {
        mystWoman->rect.x = 600;
        mystWoman->rect.y = 300;
    }

    struct colliders * objects = createNode(); 
    for (i=0; i<4; i++) addNode(objects, screenBorder[i]);
    if (itensEncontrados < frut) addNode(objects, strangeHouse->rect);
    if (itensEncontrados <= peix || itensEncontrados == frut) addNode(objects, mystWoman->rect);
    int dialogCounter = 0;

    int endCount = 0;

    Uint32 antes = SDL_GetTicks();
     
    while (*screen == telaInicial){
    
        SDL_RenderClear(ren);
        drawBackground(ren, gramado);
        SDL_RenderCopy(ren, player->sprite, &player->sprite_cut, &player->rect);
        SDL_RenderCopy(ren, mochila->sprite, &mochila->sprite_cut, &mochila->rect);
        if (itensEncontrados < frut) SDL_RenderCopy(ren, strangeHouse->sprite, &strangeHouse->sprite_cut, &strangeHouse->rect);
        if (itensEncontrados <= peix || itensEncontrados >= frut) SDL_RenderCopy(ren, mystWoman->sprite, &mystWoman->sprite_cut, &mystWoman->rect);
	    if (itensEncontrados == peix) SDL_RenderCopy(ren, peixe->sprite,&peixe->sprite_cut, &peixe->rect);
	    if (itensEncontrados == chav) SDL_RenderCopy(ren,chave->sprite,&chave->sprite_cut, &chave->rect);
	    if (itensEncontrados == sement) SDL_RenderCopy(ren,semente->sprite,&semente->sprite_cut, &semente->rect);
	    if (itensEncontrados == frut) SDL_RenderCopy(ren,fruto->sprite,&fruto->sprite_cut, &fruto->rect);
        if (itensEncontrados <= peix) stringRGBA(ren, mystWoman->rect.x+mystWoman->rect.w-5, mystWoman->rect.y, mystWoman->dialog[actualDialog], 0x00,0x00,0x00,0xFF);
        if (itensEncontrados == f) stringRGBA(ren, mystWoman->rect.x+mystWoman->rect.w-5, mystWoman->rect.y, "Obrigada...", 0x00,0x00,0x00,0xFF);
        SDL_RenderPresent(ren);
    
        *espera = MAX(0, *espera - (int)(SDL_GetTicks() - antes));
        SDL_Event evt; int isevt = AUX_WaitEventTimeoutCount(&evt, espera);
        antes = SDL_GetTicks();

        if (isevt){
                switch (evt.type){
                    #include "../player_controls.c"
                    case SDLK_x:     
                        if (itensEncontrados == chav) 
                            if (isClose(player->rect, strangeHouse->rect))
                                    *screen = hous;
                        if (itensEncontrados == frut) 
                            if (isClose(player->rect, mystWoman->rect))
                                    itensEncontrados = f;
                        break;
                    } break;
                    case SDL_WINDOWEVENT:
                        if (SDL_WINDOWEVENT_CLOSE == evt.window.event)
                            *screen = fim;
                        break;
                }
        } else {
            *espera = 20;
            if (++wAnimation == mystWoman->speed){
                mystWoman->sprite_cut.x = (mystWoman->sprite_cut.x + 37) % 259;
                wAnimation = 0;
            } 
            if (itensEncontrados == f){
                if (endCount++ > 100)
                    *screen = telaFinal;
            } 
            if (isClose(player->rect, mystWoman->rect)) {
                switch (itensEncontrados){
                    case nada:
                        if (actualDialog == 0) actualDialog = 1;
                        if (actualDialog > 0 && actualDialog < 4) {
                            dialogCounter += 1; 
                            dialogCounter %= 200;
                            if(dialogCounter == 199)
                                actualDialog += 1; 
                        } break;
                    case peix:
                        if (actualDialog == 0) actualDialog = 5;
                        if (actualDialog >=  5 && actualDialog < 7) { 
                            dialogCounter += 1; 
                            dialogCounter %= 200;
                            if(dialogCounter == 199)
                                actualDialog += 1; 
                        } break;
                    }
            }
            for (i=telaOeste-2; i<telaLeste; i++)
                if (isClose(player->rect, screenBorder[i]))
                    *screen = i+2;
                if (*screen == telaSul)
                    player->rect.x = 200;
        }
  
    }
    
}
