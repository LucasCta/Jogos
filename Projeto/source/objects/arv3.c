object * arv3 = malloc(sizeof(*arv3));
arv3->rect = (SDL_Rect) {850,170,300,350};
arv3->sprite = IMG_LoadTexture(ren, "images/trees.png");
arv3->sprite_cut = (SDL_Rect) {180, 0, 90, 132}; 