#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <SDL.h>

class scoreBoard
{
private:
    int lifes; 
    int score ;
    int level ;
    SDL_Surface* surfaceMessage;
    SDL_Texture* Message;
     
public:
    startScreen( int _life, int _score, int _level );
    ~startScreen();
    void createMessage(Controller const &controller, Renderer &renderer);
    static string instructions{"Press enter to start and pause the game."}; 
};


#endif
