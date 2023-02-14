void telaLesteRen(SDL_Renderer* ren, SDL_Window* win, int * screen, int * espera, character * player) {

    int i, j, w, h; 
    SDL_GetWindowSize(win, &w, &h);
    SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
    absToRelative(&player->rect);

    #include "../objects/gramado_verdao.c"
    #include "../objects/screenBorders.c"
    #include "../objects/peixe.c"
    #include "../objects/chave.c"
    #include "../objects/semente.c"
    #include "../objects/fruto.c"
    #include "../objects/arv1.c"
    #include "../objects/arv2.c"
    #include "../objects/arv3.c"

    SDL_Rect water = {850,210,300,300};
    struct colliders * objects = createNode(); 
    for (i=0; i<4; i++) addNode(objects, screenBorder[i]);
    addNode(objects, water);

    Uint32 antes = SDL_GetTicks();
     
    while (*screen == telaLeste){

        SDL_RenderClear(ren);
        drawBackground(ren, gramado);
	    SDL_RenderCopy(ren, player->sprite, &player->sprite_cut, &player->rect);
	    if (itensEncontrados == chav) SDL_RenderCopy(ren,chave->sprite,&chave->sprite_cut, &chave->rect);
	    if (itensEncontrados == peix) SDL_RenderCopy(ren,peixe->sprite,&peixe->sprite_cut, &peixe->rect);
	    if (itensEncontrados == sement) SDL_RenderCopy(ren,semente->sprite,&semente->sprite_cut, &semente->rect);
	    if (itensEncontrados == frut) SDL_RenderCopy(ren,fruto->sprite,&fruto->sprite_cut, &fruto->rect);
        if (itensEncontrados == wfrut0) SDL_RenderCopy(ren,arv1->sprite,&arv1->sprite_cut, &arv1->rect);
        if (itensEncontrados == wfrut1) SDL_RenderCopy(ren,arv2->sprite,&arv2->sprite_cut, &arv2->rect);
        if (itensEncontrados >= wfrut2) SDL_RenderCopy(ren,arv3->sprite,&arv3->sprite_cut, &arv3->rect);
        if (itensEncontrados == wfrut2) {
            SDL_SetRenderDrawColor(ren, 0xFF, 0x00, 0x00, 255);
            SDL_RenderFillRect(ren, &(SDL_Rect) {1050,350,10,10});
        } 
        if (itensEncontrados < wfrut0) {
            SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x66, 125);
            SDL_RenderFillRect(ren, &water);
        } SDL_RenderPresent(ren);

        *espera = MAX(0, *espera - (int)(SDL_GetTicks() - antes));
        SDL_Event evt; int isevt = AUX_WaitEventTimeoutCount(&evt, espera);
        antes = SDL_GetTicks();
    
        if (isevt){
             switch (evt.type){
                #include "../player_controls.c"
                case SDLK_x:
                    if (isClose(player->rect, water))
                        if (itensEncontrados == sement)
                            itensEncontrados = wfrut0;
                    if (isClose(player->rect, water))
                        if (itensEncontrados == wfrut2)
                            itensEncontrados = frut;
		        } break;
                case SDL_WINDOWEVENT:
                    if (SDL_WINDOWEVENT_CLOSE == evt.window.event)
                        *screen = fim;
                    break;
             } 
        } else {
            *espera = 20;
            if (isClose(player->rect, screenBorder[telaOeste-2]))
                *screen = telaInicial;
        }
        
    }

    if (itensEncontrados >= wfrut0 && itensEncontrados < wfrut2)
        itensEncontrados ++;

}  
