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

//DELETE NODE

int collision(SDL_Rect * p, SDL_Rect * r) {
    return (!(p->x + p->w < r->x || p->x > r->x + r->w)&&!(p->y + p->h < r->y || p->y > r->y + r->h));
}

int checkCollisions(SDL_Rect p, collider head, int distancia, int direction){
    collider prox; prox = head;
    while (prox != NULL){
        if (direction == 0) p.x += distancia; 
        if (direction == 1) p.y += distancia;
        if (collision (&p, &prox->rect)) return 1;
        prox = prox->next;
    } return 0;
}

