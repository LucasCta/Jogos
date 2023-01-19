character * mystWoman = malloc(sizeof(*mystWoman));
mystWoman->rect = (SDL_Rect) {256, 256, 64, 64};
mystWoman->sprite = IMG_LoadTexture(ren, "images/woman_idle.png");
mystWoman->sprite_cut = (SDL_Rect) {0, 0, 37, 46}; 
mystWoman->state = idle;
mystWoman->speed = 10;
int wAnimation = 0;

mystWoman->dialog = (char **) malloc(sizeof(char*)*2);
mystWoman->dialog[0] = (char *) malloc(sizeof("")+1);
mystWoman->dialog[0] = ""; 
mystWoman->dialog[1] = (char *) malloc(sizeof("Hello")+1);
mystWoman->dialog[1] = "Hello";
int actualDialog = 0;
