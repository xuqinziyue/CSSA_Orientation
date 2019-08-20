#include "sdl_helper.h"
#include <list>

//return final x position
int print_text_to_screen(SDL_Renderer* renderer, SDL_Rect rect, char const* string_out, SDL_Color color_out, TTF_Font * font ){
   SDL_Surface * temp_sur=TTF_RenderText_Solid(font, string_out , color_out);
    SDL_Texture* temp_text=SDL_CreateTextureFromSurface(renderer, temp_sur);
    
    SDL_Rect rect_revised;
    rect_revised.x=rect.x;
    rect_revised.y=rect.y;
    rect_revised.w=temp_sur->w;
    rect_revised.h=temp_sur->h;
    
    if (rect_revised.x + rect_revised.w < 0){
        return rect_revised.x + rect_revised.w;
    }
    SDL_RenderCopy(renderer, temp_text, NULL, &rect_revised);
    SDL_FreeSurface(temp_sur);
    SDL_DestroyTexture(temp_text);
    return rect_revised.x + rect_revised.w;
    
}


void set_rectangle(SDL_Rect & rect, int x_r, int y_r, int w_r, int h_r ){
    rect.x=x_r;
    rect.y=y_r;
    rect.h=h_r;
    rect.w=w_r;
    
}


bool initialize_initial_window(vector<string>& info_storage){
    
    if (TTF_Init() == -1){
        return false;
    }
    TTF_Font * font  = TTF_OpenFont("/Users/qinziyue/Documents/CSSA_APP/CSSA_APP_Xcode/CSSA_APP_Xcode/OpenSans-Italic.ttf",20);
    if(font == NULL)
    {
        fprintf(stderr,"font open failure %s\n",SDL_GetError());
        exit(-1);
    }
    //Initialization flag

    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;
    
    //The window renderer
    SDL_Renderer* gRenderer = NULL;
    
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        return false;
    }
 
        
    //Create window
    gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( gWindow == NULL )
    {
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        return false;
    }

    //Create renderer for window
    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
    if( gRenderer == NULL )
    {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        return false;
    }
   
      
        
    
   // printf("herere\n");
   // fflush(stdout);
    
    //Main loop flag
    bool quit = false;
    
    //Event handler
    SDL_Event e;
   
    
    const int total_category = 10;
    struct final_info{
        int x_coordinate;
        int y_category;
        string s;
    };
    list<final_info> stage_one_str;
    list<final_info> stage_two_str;
    vector<bool> occupied_bits(total_category, 0);
  
    int decreasing_amount = 5;
    
    //While application is running
    while( !quit )
    {
        
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
        }
        
        
        //Clear screen
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );
        
        //stage1: remove string from vector into map if there's free space in y axis
        //stage2: when string in stage 1 enters window, goes into stage 2, in this stage, just need to decrease x
        //stage3: when string exits the window, goes into stage 3, remove string from map
        
        //move strs to stage1
        int i = 0;
       // printf("test here\n");
       // fflush(stdout);
        while (info_storage.size() > 0){
            bool free_space = false;
            for (int j = 0; j < total_category && info_storage.size() > 0; j++){
                if (occupied_bits[j] == 0){
                    free_space = true;
                    occupied_bits[j] = 1;
                    final_info temp;
                    temp.x_coordinate = SCREEN_WIDTH;
                    //temp.y_category = SCREEN_HEIGHT / total_category * j;
                    temp.y_category = j;
                    temp.s = info_storage[i];
                    info_storage.erase(info_storage.begin());
                    stage_one_str.push_back(temp);
                    
                }
            }
            if (!free_space){
                printf("no enough space\n");
                fflush(stdout);
                break;
            }
        }
       // printf("here is ok\n");
       // fflush(stdout);
        
        //print stage2 before stage1 so that we don't print str twice
        for (list<final_info>::iterator it = stage_two_str.begin(); it != stage_two_str.end(); it++){
            SDL_Rect rect;
            set_rectangle(rect, it->x_coordinate, SCREEN_HEIGHT / total_category * it->y_category, 0, 0);
            it->x_coordinate -= decreasing_amount;
            SDL_Color blue={0x00,0xff,0xff};
            int ending_x = print_text_to_screen(gRenderer, rect, it->s.c_str(), blue, font );
            
            if(ending_x < 0){
                //move string to stage 2 -> needed so that str in stage 2 does not change occupied bits
                //set back bit to 0
                //currently -10 to leave some space
                
                stage_two_str.erase(it);
                
            }
        }
        
        for (list<final_info>::iterator it = stage_one_str.begin(); it != stage_one_str.end(); it++){
            SDL_Rect rect;
            set_rectangle(rect, it->x_coordinate, SCREEN_HEIGHT / total_category * it->y_category, 0, 0);
            it->x_coordinate -= decreasing_amount;
            SDL_Color blue={0x00,0xff,0xff};
            int ending_x = print_text_to_screen(gRenderer, rect, it->s.c_str(), blue, font );
            
            if(ending_x < SCREEN_WIDTH - 10){
                //move string to stage 2 -> needed so that str in stage 2 does not change occupied bits
                //set back bit to 0
                //currently -10 to leave some space
                occupied_bits[it->y_category] = 0;
                stage_two_str.push_back(*it);
                stage_one_str.erase(it);
                
            }
        }
        
        
        
        //Update screen
        SDL_RenderPresent( gRenderer );
        SDL_Delay( 100 );
    }
    
    
    
    SDL_DestroyRenderer(gRenderer);
    //Destroy window
    SDL_DestroyWindow( gWindow );
    TTF_CloseFont(font);
    //Quit SDL subsystems
    SDL_Quit();
    TTF_Quit();
    
    
    return(true);
     
    
}
