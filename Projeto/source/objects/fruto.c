object * fruto = malloc(sizeof(*fruto));
fruto->rect = (SDL_Rect) {1200, 0, 64, 64};
fruto->sprite = IMG_LoadTexture(ren, "images/apple.png");
fruto->sprite_cut = (SDL_Rect) {0, 200, 450, 450};
