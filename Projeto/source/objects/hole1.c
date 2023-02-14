object * buraco1 = malloc(sizeof(*buraco1));
buraco1->rect = (SDL_Rect) {400, 240, 180, 90};
buraco1->sprite = IMG_LoadTexture(ren, "images/hole.png");
buraco1->sprite_cut = (SDL_Rect) {0,0,330,180}; 
