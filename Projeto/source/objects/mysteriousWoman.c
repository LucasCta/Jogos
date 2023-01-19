character * mistWoman = malloc(sizeof(*mistWoman));
mistWoman->rect = (SDL_Rect) {256, 256, 64, 64};
mistWoman->sprite = IMG_LoadTexture(ren, "images/woman_idle.png");
mistWoman->sprite_cut = (SDL_Rect) {0, 0, 37, 46}; 
mistWoman->state = idle;
mistWoman->speed = 10;
int wAnimation = 0;

mistWoman->dialog = (char **) malloc(sizeof(char*)*2);
mistWoman->dialog[0] = (char *) malloc(sizeof("")+1);
mistWoman->dialog[0] = ""; 
mistWoman->dialog[1] = (char *) malloc(sizeof("Hello")+1);
mistWoman->dialog[1] = "Hello";
int actualDialog = 0;
