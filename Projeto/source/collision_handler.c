struct colliders {
    SDL_Rect rect;
    struct colliders * next;
};

typedef struct colliders * collider; 

collider createNode(){
    collider temp;
    temp = (collider) malloc(sizeof(struct colliders));
    temp->next = NULL;
    return temp;
}

collider addNode(collider head, SDL_Rect newCollider){
    collider temp, prox; 
    temp = createNode();
    temp->rect = newCollider;
    if (head == NULL) head = temp; 
    else {
        prox = head;
        while(prox->next != NULL)
            prox = prox->next;
        prox->next = temp;
    } return head;
}

//collider deleteNode(collider head, SDL_Rect delCollider){}

//int collision(SDL_Rect * p, SDL_Rect * r) { return (!(p->x + p->w < r->x || p->x > r->x + r->w)&&!(p->y + p->h < r->y || p->y > r->y + r->h)); }

int checkCollisions(SDL_Rect p, collider head, int distancia, int direction){
    collider prox; prox = head; 
    SDL_Rect temp;
    if (direction == 0) p.y += distancia;
    else if (direction == 1) p.x += distancia;
    while (prox != NULL){
        if (SDL_IntersectRect(&p, &prox->rect, &temp)) return 1;
        prox = prox->next;
    } return 0;
}

int isClose(SDL_Rect p, SDL_Rect c){
    SDL_Rect temp;
    p.x -= 10; p.w += 20;
    p.y -= 10; p.h += 20;
    return SDL_IntersectRect(&p, &c, &temp);
}