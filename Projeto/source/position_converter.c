void absToRelative(SDL_Rect * o){
   if (o->x < 15) o->x = 1200;
   else if (o->x > 1200) o->x = 20;
   if (o->y < 15) o->y = 640;
   else if (o->y > 640) o->y = 20;
}
