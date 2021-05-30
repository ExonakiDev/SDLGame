#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
//#include "SDL/SDL_image.h"
//#include "SDL/SDL.h"

typedef struct {
    int x, y;
    short life;
    char *name;
} Man;

typedef struct
{
    int x, y;
} Star;

typedef struct
{
    // Man struct
    Man man;

    Star stars[100];
    // Images
    SDL_Texture *star;
} GameState;

int processEvents(SDL_Window *window, GameState *game)
{
    SDL_Event event;
    int done = 0;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_WINDOWEVENT_CLOSE:
                {
                    if (window) {
                        SDL_DestroyWindow(window);
                        window = NULL;
                        done = 1;
                    }
                }
                break;
//                case SDL_KEYDOWN:
//                {
//                    switch(event.key.keysym.sym)
//                    {
//                        case SDLK_ESCAPE:
//                            done=1;
//                            break;
//                        case SDLK_LEFT:
//                            man->x-=10;
//                            break;
//                        case SDLK_RIGHT:
//                            man->x+=10;
//                            break;
//                    }
//                }
                    break;
                case SDL_QUIT:
                    done=1;
                    break;
            }
        }
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_LEFT])
        {
            game->man.x-=10;
        }
        if (state[SDL_SCANCODE_RIGHT])
        {
            game->man.x+=10;
        }
        if (state[SDL_SCANCODE_UP])
        {
            game->man.y-=10;
        }
        if (state[SDL_SCANCODE_DOWN])
        {
            game->man.y+=10;
        }
    return done;
}

void loadGame(GameState *game, SDL_Renderer *renderer)
{
    game->man.x=320-40;
    game->man.y=240-40;

    SDL_Surface *starSurface = NULL;

    // Load images and create rendering textures from them
    starSurface = IMG_Load("mushroom.png");
    if (starSurface == NULL)
    {
        printf("Cannot find mushroom.png\n\n");
        SDL_Quit();
        return;
    }

    // init mushrooms
    for (int i=0; i<100; i++)
    {
        game->stars[i].x = rand()%640;
        game->stars[i].y = rand()%480;
    }

    game->star = SDL_CreateTextureFromSurface(renderer, starSurface);
    SDL_FreeSurface(starSurface);

}

void doRender(SDL_Renderer *renderer, GameState *game)
{
    const Uint32 startMs = SDL_GetTicks();
    SDL_PumpEvents();

    //Render something
    SDL_RenderSetLogicalSize( renderer, 640, 480 );

    //Set colour of renderer
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );

    //Clear the screen to the set colour
    SDL_RenderClear( renderer );

    // draw image
    for (int i=0; i<100; i++)
    {
        SDL_Rect starRect = { game->stars[i].x, game->stars[i].y, 64, 64 };
        SDL_RenderCopy(renderer, game->star, NULL, &starRect);
    }


    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect rect = { game->man.x, game->man.y, 200, 200};
    SDL_RenderFillRect(renderer, &rect);
    //Show all the has been done behind the scenes
    SDL_RenderPresent( renderer );

}

int main(int argc, char *argv[]) {
    GameState gameState;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    if( SDL_Init( SDL_INIT_VIDEO ) != 0 )
    {
        printf("SDL_INIT() Error\n");
        return 1;
    }
    srand((int)time(NULL));

    // create application window
    window = SDL_CreateWindow("Game Window",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              640,
                              480,
                              0);

    if( window == NULL ) {
        printf("SDL_CreateWindow() Error: \n");
        return 1;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);

    if( renderer == NULL)
    {
        printf("SDL_CreateRenderer() Error \n");
        SDL_DestroyWindow(window);
        return 1;
    }


    loadGame(&gameState, renderer);
    int done=0;
    while(!done)
    {
        done = processEvents(window, &gameState);
        doRender(renderer, &gameState);
        SDL_Delay(25);
//        const Uint32 startMs = SDL_GetTicks();
    }


    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}
