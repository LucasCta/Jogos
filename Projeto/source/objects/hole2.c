object * buraco2 = malloc(sizeof(*buraco2));
buraco2->rect = (SDL_Rect) {700, 240, 180, 90};
buraco2->sprite = IMG_LoadTexture(ren, "images/hole.png");
buraco2->sprite_cut = (SDL_Rect) {0,0,330,180}; 
