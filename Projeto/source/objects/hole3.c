object * buraco3 = malloc(sizeof(*buraco3));
buraco3->rect = (SDL_Rect) {1000, 240, 180, 90};
buraco3->sprite = IMG_LoadTexture(ren, "images/hole.png");
buraco3->sprite_cut = (SDL_Rect) {0,0,330,180}; 
