#include <SDL3/SDL.h>
#include <stdio.h>
#include <math.h>

#define SCREEN_WIDTH 1400 
#define SCREEN_HEIGHT 800


struct Circle {
    double x, y;
    double r;
};

// a beautiful function to draw a desired circle :)
void drawCircle(struct Circle circle,SDL_Renderer* renderer) {

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    double radius_squared = pow(circle.r, 2);
    for (double x = circle.x - circle.r; x <= circle.x + circle.r; x++) {

        for (double y = circle.y - circle.r; y <= circle.y + circle.r; y ++) {
            // if it satisfies the eqn of a circle
            double distance_squared = pow(x - circle.x, 2) + pow(y - circle.y, 2);
            if(distance_squared <= radius_squared) {

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderPoint(renderer, x, y);
            }
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        }
    }
}

void moveLightSource(struct Circle* circle) {
    float cursor_x, cursor_y;
    SDL_GetMouseState(&cursor_x, &cursor_y);
    circle->x = cursor_x;
    circle->y = cursor_y;
}   


void drawRays(SDL_Renderer* renderer, struct Circle circle, double number_of_lines) {
    SDL_SetRenderDrawColor(renderer, 252, 252, 141, 255);
    double angle_spacing = 360/number_of_lines;
    double lineX;
    double lineY;
    double line_angle;
    for(double x = 0; x < number_of_lines; x++){
        line_angle =  angle_spacing * x;

        lineX = ((circle.r + SCREEN_WIDTH) * cos(line_angle * M_PI/180)) + circle.x;
        lineY = ((circle.r + SCREEN_HEIGHT) * sin(line_angle * M_PI/180)) + circle.y;

        SDL_RenderLine(renderer, circle.x, circle.y, lineX, lineY);
    }    
}   

int main()
{

    SDL_Window *window = NULL;
    SDL_Renderer* renderer = NULL;
    // initializing SDL
    SDL_Init(SDL_INIT_VIDEO);
    //creating window and renderer
    SDL_CreateWindowAndRenderer("My Window",SCREEN_WIDTH,SCREEN_HEIGHT, 0, &window, &renderer);

    // light source circle
    struct Circle lightCircle = {SCREEN_WIDTH/4, SCREEN_HEIGHT/2, 80};

    int quit = 0;
    SDL_Event event;

        int mousePressed = 0;
        int mouseMoving = 0;
    //main loop
    while (!quit) {
        // black color to draw the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xff);
        SDL_RenderClear(renderer); //clear screen to black

        while(SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    SDL_Log("SDL Quit.");
                    quit = 1; 
                    break;

                case SDL_EVENT_MOUSE_MOTION:
                    mouseMoving = 1;
                    break;
                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                    mousePressed = 1;
                    break;
                case SDL_EVENT_MOUSE_BUTTON_UP:
                    mousePressed = 0;
                    break;
                default:
                    break;
            }
            if (mousePressed && mouseMoving) 
            {
                moveLightSource(&lightCircle);
            }    
                

        }

        //draw rays coming from it
        drawRays(renderer, lightCircle,100);
        // drawing lightCircle
        drawCircle(lightCircle, renderer);

        // commit the renders or that kinda thing
        SDL_RenderPresent(renderer); 
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}



