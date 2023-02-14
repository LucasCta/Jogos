object * arv2 = malloc(sizeof(*arv2));
arv2->rect = (SDL_Rect) {880,210,300,300};
arv2->sprite = IMG_LoadTexture(ren, "images/trees.png");
arv2->sprite_cut = (SDL_Rect) {90, 132, 90, 92}; 