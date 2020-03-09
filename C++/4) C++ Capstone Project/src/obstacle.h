#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "SDL.h"
#include <vector>

class Obstacle{
    public:
    std::size_t screen_width;
    std::size_t screen_height;
    std::size_t grid_width;
    std::size_t grid_height;
    int width;
    int height;
    Obstacle(std::size_t screen_w, std::size_t screen_h, std::size_t grid_w, std::size_t grid_h);
    //~Obstacle();
    bool isObstacle(int level, int x, int y);
    std::vector<SDL_Rect> createObstacle(int level);
    std::vector<SDL_Rect> obstacleForLevel2();
    std::vector<SDL_Rect> obstacleForLevel3();
    std::vector<SDL_Rect> obstacleForLevel4();
    std::vector<SDL_Rect> obstacleForLevel5();
};

#endif