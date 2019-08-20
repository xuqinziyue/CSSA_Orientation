#ifndef SDL_HELPER_H
#define SDL_HELPER_H

#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_image/SDL_image.h>
#include <string>
#include <vector>
using namespace std;

const int INITIAL_SCREEN_WIDTH=800;
const int INITIAL_SCREEN_HEIGHT=600;
bool initialize_initial_window(vector<string>& info_storage );
/*
void initialize_initial_window_void(vector<string>& info_storage ){
    initialize_initial_window(info_storage );
}
 */
//void set_rectangle(SDL_Rect & rect, int x_r, int y_r, int w_r, int h_r );
//int handles_input(SDL_Event * event );
int print_text_to_screen(SDL_Renderer* renderer, SDL_Rect rect, char const* string_out, SDL_Color color_out, TTF_Font* font  );
#endif /* sdl_helper_hpp */
