void telaFinalRen(SDL_Renderer* ren, SDL_Window* win, int * screen, int * espera, character * player) {

    int i, j, w, h; 
    SDL_GetWindowSize(win, &w, &h);
    SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);

    SDL_Color orange = {0xF6,0x6A,0x03,0xFF}; 

    TTF_Init();
    TTF_Font *font = TTF_OpenFont("fonts/enchantedland.otf", 100);
    
    SDL_SetRenderDrawColor(ren, 0x46, 0x29, 0x5A, 255);

    screenText * endText = malloc(sizeof(*endText));
    
    endText->text = malloc(sizeof("Fim")+1);
    endText->text = "Fim";
    endText->font = font;
    endText->color = orange;
    endText->rect = (SDL_Rect) {500,100,300,300};

    struct SDL_Surface * tempSur = TTF_RenderText_Solid(endText->font,endText->text,endText->color);
    struct SDL_Texture * tempTex = SDL_CreateTextureFromSurface(ren,tempSur);

    #include "../objects/peixe.c"
    #include "../objects/chave.c"
    #include "../objects/semente.c"
    #include "../objects/fruto.c"

    peixe->rect.x = 100;
    peixe->rect.y = -100;
    chave->rect.x = 500;
    chave->rect.y = -250;
    semente->rect.x = 700;
    semente->rect.y = -200;
    fruto->rect.x = 1000;
    fruto->rect.y = -350;

    while (*screen == telaFinal){
    
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren,tempTex,NULL,&(endText->rect));	   
        SDL_RenderCopy(ren, peixe->sprite,&peixe->sprite_cut, &peixe->rect);
	    SDL_RenderCopy(ren,chave->sprite,&chave->sprite_cut, &chave->rect);
	    SDL_RenderCopy(ren,semente->sprite,&semente->sprite_cut, &semente->rect);
	    SDL_RenderCopy(ren,fruto->sprite,&fruto->sprite_cut, &fruto->rect);
        SDL_RenderPresent(ren);

        SDL_Event evt;
	    if (SDL_WaitEventTimeout(&evt,200)){
             switch (evt.type){
                case SDL_KEYDOWN: 
                    if (evt.key.keysym.sym == SDLK_ESCAPE)
                        *screen = fim;
                    break;
                case SDL_WINDOWEVENT:
                    if (SDL_WINDOWEVENT_CLOSE == evt.window.event)
                        *screen = fim;
                    break;
             } 
        } else {
            *espera = 5;
            peixe->rect.y += 5;
            chave->rect.y += 5;
            semente->rect.y += 5;
            fruto->rect.y += 5;
        }

    }

    TTF_CloseFont(font);

}
