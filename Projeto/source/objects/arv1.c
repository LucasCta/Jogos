object * arv1 = malloc(sizeof(*arv1));
arv1->rect = (SDL_Rect) {900,170,300,300};
arv1->sprite = IMG_LoadTexture(ren, "images/trees.png");
arv1->sprite_cut = (SDL_Rect) {0, 132, 90, 92}; 