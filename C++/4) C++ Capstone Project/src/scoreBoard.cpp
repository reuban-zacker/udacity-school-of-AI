#include "scoreBoard.h"

scoreBoard::scoreBoard( int _life, int _score, int _level)
{
    lifes = _life; 
    score = _score;
    level = _level;
}

scoreBoard::~scoreBoard()
{   
    SDL_freeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
}

void scoreBoard:: createMessage(Controller const &controller, Renderer &renderer){

TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 32 ); //this opens a font style and sets a size

SDL_Color White = {255, 255, 255};  // this is the color in rgb format

string text = "Lifes: "+ lifes.c_str() +" Score: "+ score.c_str() +" Level: "+ level.c_str() ;
text += "\n\n Instructions: \n "+ scoreBoard::instructions ;

 surfaceMessage = TTF_RenderText_Solid(Sans, text , White); 
 Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); 

SDL_Rect Message_rect; //create a rect
Message_rect.x = 100;  //controls the rect's x coordinate 
Message_rect.y = 100; // controls the rect's y coordinte
Message_rect.w = 200; // controls the width of the rect
Message_rect.h = 200; // controls the height of the rect

//Now since it's a texture, you have to put RenderCopy in your game loop area, 
//the area where the whole code executes

SDL_RenderCopy(renderer, Message, NULL, &Message_rect); //you put the renderer's name first,
// the Message, the crop size(you can ignore this if you don't want to dabble with cropping),
 // and the rect which is the size and coordinate of your texture

//Don't forget too free your surface and texture
}

