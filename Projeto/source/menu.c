void menuRen (SDL_Renderer* ren, int * screen, int * espera) {

    int x, y;
    
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("fonts/zk.ttf",100);
    
    SDL_Color orange = {0xF6,0x6A,0x03,0xFF}; 
    SDL_Color black = {0x00,0x00,0x00,0xFF};
    SDL_Color darkGrey = {125,125,125,255}; 
    SDL_Color grey = {125,125,125,125};
    
    screenText * menuText = malloc(sizeof(*menuText) * 3);
    
    menuText[0].text = malloc(sizeof("Detalhes"));
    menuText[0].text = "Detalhes";
    menuText[0].font = font;
    menuText[0].color = orange;
    menuText[0].rect = (SDL_Rect) {340,100,600,200};
    
    menuText[1].text = malloc(sizeof("Jogar"));
    menuText[1].text = "Jogar";
    menuText[1].font = font;
    menuText[1].color = grey;
    menuText[1].rect = (SDL_Rect) {540,300,250,200};    
    
    menuText[2].text = malloc(sizeof("Sair"));
    menuText[2].text = "Sair";
    menuText[2].font = font;
    menuText[2].color = grey;
    menuText[2].rect = (SDL_Rect) {540,500,250,200};

    Uint32 antes = SDL_GetTicks();
    
    while (*screen == menu){
    
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);   
        
        int i;
        for (i = 0; i < 3; i++){
            struct SDL_Surface * tempSur = TTF_RenderText_Solid(menuText[i].font,menuText[i].text,menuText[i].color);
            struct SDL_Texture * tempTex = SDL_CreateTextureFromSurface(ren,tempSur);
            SDL_RenderCopy(ren,tempTex,NULL,&(menuText[i].rect));
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
                    menuText[1].color = grey;
                    menuText[2].color = grey;
                    if (menuText[1].rect.x < x && menuText[1].rect.x + 200 > x && 
                    menuText[1].rect.y < y && menuText[1].rect.y + 200 > y)
                        menuText[1].color = black;
                    else if (menuText[2].rect.x < x && menuText[2].rect.x + 200 > x && 
                    menuText[2].rect.y < y && menuText[2].rect.y + 200 > y)
                        menuText[2].color = black;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&x,&y);
                    if (menuText[1].rect.x < x && menuText[1].rect.x + 200 > x && 
                    menuText[1].rect.y < y && menuText[1].rect.y + 200 > y)
                        *screen = telaInicial;
                    else if (menuText[2].rect.x < x && menuText[2].rect.x + 200 > x && 
                    menuText[2].rect.y < y && menuText[2].rect.y + 200 > y)
                        *screen = fim;
                    break;
            }
        } else *espera = 100;
        
    }
    
    TTF_CloseFont(font);
    free(menuText);
    
}
