#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"
#include "obstacle.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height, int screen_w, int screen_h)
      : grid_width(grid_width),
        grid_height(grid_height),
        screen_width(screen_w),
        screen_height(screen_h),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {}

  void Update();

  void GrowBody();
  bool SnakeCell(int x, int y);
  void updateLevel();
  bool isAlive();

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;
  int level{1} ; // custom code
  int life{3}; //custom code

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);
  
  bool growing{false};
  int grid_width;
  int grid_height;
  int screen_width;
  int screen_height;
};

#endif