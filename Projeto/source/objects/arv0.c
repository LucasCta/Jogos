object * arv0 = malloc(sizeof(*arv0));
arv0->rect = (SDL_Rect) {960,310,64,64};
arv0->sprite = IMG_LoadTexture(ren, "images/sapling.png");
arv0->sprite_cut = (SDL_Rect) {0, 0, 840, 880}; 