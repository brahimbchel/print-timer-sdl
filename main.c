#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <time.h>
#include <conio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int hour = 0; minute = 0; second = 0; flag = 0;

void delay(ms)
{
    clock_t timeDelay = ms + clock();
    while(timeDelay > clock());
}

int counter()
{
    while(!kbhit() && flag == 0)
    {
        if(second > 59)
        {
            second = 0;
            ++minute;
        }
        if(minute > 59)
        {
            minute = 0;
            ++hour;
        }
        printData();
        delay(1000);
        ++second;
    }
    selection();
}

int selection()
{
    switch(getch())    // getch = get character
    {
    case 49:           // 49 = 1
        flag = 0;
        break;
    case 50:           // 50 = 2
        flag = 1;
        break;
    case 51:           // 51 = 3
        hour = minute = second = 0;
        flag = 1;
        printData();
        break;
    case 52:           // 52 = 4
        exit(0);
        break;
    }
}


int printData()
{
    bool quit = false;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window * window = SDL_CreateWindow(
        "SDL_ttf in SDL2",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        640, 480, 0
        );
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    TTF_Font * font = TTF_OpenFont("arial.ttf", 15);
    SDL_Color color = { 0, 255, 0 };

    system("cls");
    SDL_Surface * surface1 = TTF_RenderText_Solid(font,"1.Start 2.Stop 3.Reset 4.End", color);
    SDL_Surface * surface2 = TTF_RenderText_Solid(font,"****************************", color);

        char str1[10];
    itoa(second, str1, 10);
    SDL_Surface * surface3S = TTF_RenderText_Solid(font, str1, color);
        char str2[10];
    itoa(minute, str2, 10);
    SDL_Surface * surface3Min = TTF_RenderText_Solid(font, str2, color);
        char str3[10];
    itoa(hour, str3, 10);
    SDL_Surface * surface3H = TTF_RenderText_Solid(font, str3, color);


    SDL_Texture * texture1 = SDL_CreateTextureFromSurface(renderer, surface1);
    SDL_Texture * texture2 = SDL_CreateTextureFromSurface(renderer, surface2);

    SDL_Texture * texture3S = SDL_CreateTextureFromSurface(renderer, surface3S);
    SDL_Texture * texture3Min = SDL_CreateTextureFromSurface(renderer, surface3Min);
    SDL_Texture * texture3H = SDL_CreateTextureFromSurface(renderer, surface3H);

    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(texture1, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect1 = { 0, 0, texW, texH };


    SDL_QueryTexture(texture2, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect2 = { 0, 20, texW, texH };

    SDL_QueryTexture(texture3S, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect3S = { 0, 40, texW, texH };

    SDL_QueryTexture(texture3Min, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect3Min = { 20, 40, texW, texH };

    SDL_QueryTexture(texture3H, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect3H = { 40, 40, texW, texH };

    while (!quit)
    {
        SDL_WaitEvent(&event);

        switch (event.type)
        {
            case SDL_QUIT:
                quit = true;
                break;
        }

        SDL_RenderCopy(renderer, texture1, NULL, &dstrect1);
        SDL_RenderCopy(renderer, texture2, NULL, &dstrect2);
        SDL_RenderCopy(renderer, texture3S, NULL, &dstrect3S);
        SDL_RenderCopy(renderer, texture3Min, NULL, &dstrect3Min);
        SDL_RenderCopy(renderer, texture3H, NULL, &dstrect3H);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture1);
    SDL_FreeSurface(surface1);

    SDL_DestroyTexture(texture2);
    SDL_FreeSurface(surface2);
        SDL_DestroyTexture(texture3S);
    SDL_FreeSurface(surface3S);
        SDL_DestroyTexture(texture3Min);
    SDL_FreeSurface(surface3Min);
        SDL_DestroyTexture(texture3H);
    SDL_FreeSurface(surface3H);

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

int main(int argc, char ** argv)
{
    while(1)
    {
        counter();
    }

    //printData();


    return 0;
}
