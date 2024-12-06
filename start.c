#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
const int WIDTH = 640; //Width of screen in pixel
const int HIGH = 480; //High of screen in pixel
//structure of Player
typedef struct{
  int x,y;
  int health,damage;
}Player;

typedef struct{
  int x,y;
}Image;

typedef struct {
  Player player;
  SDL_Texture *image;
  SDL_Renderer *renderer;
  Image Image2[100];

}GameState;

void drawRect(SDL_Renderer *renderer,Player *player,GameState *game){
  SDL_SetRenderDrawColor(renderer,0,0,255,0);
  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor(renderer,255,255,255,255);
  SDL_Rect rect = {player->x,player->y,100,100};
  
  SDL_RenderFillRect(renderer,&rect);
  //Draw image 
  for(int i=0;i<100;i++){
    SDL_Rect image = {game->Image2[i].x,game->Image2[i].y,80,80};
    SDL_RenderCopy(renderer,game->image,NULL,&image);
  }
  SDL_RenderPresent(renderer);
}

void loadImage(SDL_Surface *surface,GameState *game,SDL_Renderer *renderer){
  surface = IMG_Load("Free/Hello.png");
  if(surface == NULL){
    printf("Error");
    SDL_Quit();
    exit(1);
  }
  game->image = SDL_CreateTextureFromSurface(renderer,surface);
  for(int i=0;i<100;i++){
    game->Image2[i].x = random()%WIDTH;
    game->Image2[i].y = random()%HIGH;
  }
  SDL_FreeSurface(surface);
}

int drawRender(SDL_Window *window,SDL_Renderer *renderer,SDL_Event event,Player *player){
  int done = 0;
  while(SDL_PollEvent(&event)){
    switch(event.type){
      case SDL_QUIT:
        done = 1;
      break;
        case SDL_WINDOWEVENT_CLOSE:
          if(window){
              SDL_DestroyWindow(window);
              window = NULL;
            }
          break;
          case SDL_KEYDOWN:
            switch(event.key.keysym.sym){
              case SDLK_ESCAPE:
                done = 1;
              break;
              case SDLK_LEFT:
                player->x -= 10;
              break;
              case SDLK_RIGHT:
                player->x += 10;
              break;
           }
      }
    }
  const Uint8 *state = SDL_GetKeyboardState(NULL);
  if(state[SDL_SCANCODE_LEFT]){
    player->x -= 10;
  }
  if(state[SDL_SCANCODE_RIGHT]){
    player->x += 10;
  }
  if(state[SDL_SCANCODE_UP]){
    player->y -= 10;
  }
  if(state[SDL_SCANCODE_DOWN]){
    player->y += 10;
  }
  printf("Player X: %d\n",player->x);
  printf("Player Y: %d\n",player->y);
  if(player->x >= WIDTH && player->x <= WIDTH && player->y >= HIGH && player->y <= HIGH + WIDTH){
  
    printf("You Touch A border");
  }
  return done;
}
int main(){
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  SDL_Surface *surface = NULL;
  GameState gamestate;
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Event event;
  Player player;
  player.x = 100;
  player.y = 100;
  window = SDL_CreateWindow("Start game",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WIDTH,HIGH,0);
  
  renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  SDL_SetRenderDrawColor(renderer,0,0,255,0);
  srandom((int)time(NULL));//Idk what it mean gg 
  loadImage(surface,&gamestate,renderer);
  int done = 0;
  while(!done){
    done = drawRender(window,renderer,event,&player);
    drawRect(renderer,&player,&gamestate);
    SDL_Delay(10);
  }
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyTexture(gamestate.image);
  SDL_Quit();
  return 0;
}
