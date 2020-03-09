#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (sdl_renderer == nullptr) {
    std::cerr << "Hardware Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    //custom Code //creating software renderer
    std::cerr<< "Using Software Renderer.\n";
    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_SOFTWARE);
    if (sdl_renderer == nullptr) {
    std::cerr << "Software Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Snake const snake, SDL_Point const &food) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  //update level maps
  if(snake.level == 2){
    loadLevel2();
  }
  else if (snake.level == 3){
    loadLevel3();
  }
  else if (snake.level == 4){
    loadLevel4();
  }
  else if(snake.level==5){
    loadLevel5();
  }

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps, int level) {
  std::string title{"Snake Score: " + std::to_string(score) + " Level: " + std::to_string(level) +
                     " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

void Renderer::loadLevel2()
{
  SDL_Rect obstacleL, obstacleR, obstacleT, obstacleB ;
  int width = screen_width / grid_width;
  int height = screen_height / grid_height;
  obstacleL.w = width;
  obstacleL.h = 6*height;
  obstacleR.w = width;
  obstacleR.h = 6*height;
  obstacleT.w = 6*width;
  obstacleT.h = height;
  obstacleB.w = 6*width;
  obstacleB.h = height;
  //render the obstacle on screen
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);   // Red color
  obstacleL.x = 0 ;
  obstacleL.y = 240;
  obstacleR.x = 620 ;  //608
  obstacleR.y = 240;
  obstacleT.x = 240 ;  //224
  obstacleT.y = 0;
  obstacleB.x = 240 ; //224
  obstacleB.y = 620;  //608
  SDL_RenderFillRect(sdl_renderer, &obstacleL); // fill the rectangle with red color
  SDL_RenderFillRect(sdl_renderer, &obstacleR);
  SDL_RenderFillRect(sdl_renderer, &obstacleT);
  SDL_RenderFillRect(sdl_renderer, &obstacleB);
}

void Renderer::loadLevel3()
{
  SDL_Rect obstacleLeftUp, obstacleLeftDown, obstacleRightUp, obstacleRightDown ;
  SDL_Rect obstacleTopLeft, obstacleTopRight, obstacleBottomLeft, obstacleBottomRight;
  int width = screen_width / grid_width;
  int height = screen_height / grid_height;
  obstacleLeftUp.h = obstacleLeftDown.h = obstacleRightUp.h = obstacleRightDown.h = 4*height ;
  obstacleLeftUp.w = obstacleLeftDown.w = obstacleRightUp.w = obstacleRightDown.w = width ;
  obstacleTopLeft.h = obstacleTopRight.h = obstacleBottomLeft.h =  obstacleBottomRight.h = height ;
  obstacleTopLeft.w = obstacleTopRight.w = obstacleBottomLeft.w =  obstacleBottomRight.w = 4*width;
  //render the obstacle on screen
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);   // Red color
  obstacleLeftUp.x= 0;
  obstacleLeftUp.y= 0;
  obstacleLeftDown.x = 0;
  obstacleLeftDown.y = 560 ;
  obstacleRightUp.x =  620 ; //608 
  obstacleRightUp.y = 0;
  obstacleRightDown.x = 620;   //608  
  obstacleRightDown.y = 560; //512
  obstacleTopLeft.x = 0;
  obstacleTopLeft.y = 0;
  obstacleTopRight.x= 560;
  obstacleTopRight.y = 0;
  obstacleBottomLeft.x = 0 ;
  obstacleBottomLeft.y = 620;
  obstacleBottomRight.x = 560;
  obstacleBottomRight.y = 620;

  SDL_RenderFillRect(sdl_renderer, &obstacleLeftUp); // fil the rectangle with red color
  SDL_RenderFillRect(sdl_renderer, &obstacleLeftDown);
  SDL_RenderFillRect(sdl_renderer, &obstacleRightUp);
  SDL_RenderFillRect(sdl_renderer, &obstacleRightDown);
  SDL_RenderFillRect(sdl_renderer, &obstacleTopLeft);
  SDL_RenderFillRect(sdl_renderer, &obstacleTopRight);
  SDL_RenderFillRect(sdl_renderer, &obstacleBottomLeft);
  SDL_RenderFillRect(sdl_renderer, &obstacleBottomRight);
}

void Renderer::loadLevel4()
{
  loadLevel2();
  loadLevel3();
}

void Renderer::loadLevel5()
{
  loadLevel4();
  //random block creation  
}