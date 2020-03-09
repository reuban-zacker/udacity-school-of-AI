#include "obstacle.h"
#include <iostream>

Obstacle::Obstacle(std::size_t screen_w, std::size_t screen_h, std::size_t grid_w, std::size_t grid_h){
      screen_width = screen_w;
      screen_height = screen_w;
      grid_width = grid_w;
      grid_height = grid_h;
      height = screen_height/ grid_height;
      width =  screen_width/ grid_width;
}


std::vector<SDL_Rect> Obstacle::obstacleForLevel2(){

  SDL_Rect obstacleL, obstacleR, obstacleT, obstacleB ;
  //int width = screen_width / grid_width;
  //int height = screen_height / grid_height;
  obstacleL.w = width;
  obstacleL.h = 6*height;
  obstacleR.w = width;
  obstacleR.h = 6*height;
  obstacleT.w = 6*width;
  obstacleT.h = height;
  obstacleB.w = 6*width;
  obstacleB.h = height;
  obstacleL.x = 0 ;
  obstacleL.y = 240;
  obstacleR.x = 620 ;  //608
  obstacleR.y = 240;
  obstacleT.x = 240 ;  //224
  obstacleT.y = 0;
  obstacleB.x = 240 ; //224
  obstacleB.y = 620;  //608
  std::vector <SDL_Rect> obstacles;
  obstacles.push_back(obstacleT);
  obstacles.push_back(obstacleB);
  obstacles.push_back(obstacleL);
  obstacles.push_back(obstacleR);

 // std::cout<< "size: "<< obstacles.size();
  return obstacles; 
}

std::vector<SDL_Rect> Obstacle::obstacleForLevel3(){

  SDL_Rect obstacleLeftUp, obstacleLeftDown, obstacleRightUp, obstacleRightDown ;
  SDL_Rect obstacleTopLeft, obstacleTopRight, obstacleBottomLeft, obstacleBottomRight;
  //int width = screen_width / grid_width;
  //int height = screen_height / grid_height;
  obstacleLeftUp.h = obstacleLeftDown.h = obstacleRightUp.h = obstacleRightDown.h = 4*height ;
  obstacleLeftUp.w = obstacleLeftDown.w = obstacleRightUp.w = obstacleRightDown.w = width ;
  obstacleTopLeft.h = obstacleTopRight.h = obstacleBottomLeft.h =  obstacleBottomRight.h = height ;
  obstacleTopLeft.w = obstacleTopRight.w = obstacleBottomLeft.w =  obstacleBottomRight.w = 4*width;
  
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

  std::vector <SDL_Rect> obstacles;
  obstacles.push_back(obstacleLeftUp);
  obstacles.push_back(obstacleLeftDown);
  obstacles.push_back(obstacleRightUp);
  obstacles.push_back(obstacleRightDown);
  obstacles.push_back(obstacleTopLeft);
  obstacles.push_back(obstacleTopRight);
  obstacles.push_back(obstacleBottomLeft);
  obstacles.push_back(obstacleBottomRight);
  //std::cout<< "size: "<< obstacles.size();
  return obstacles; 
}

std::vector<SDL_Rect> Obstacle::obstacleForLevel4(){

  std::vector <SDL_Rect> obstacles;
  std::vector<SDL_Rect> A= Obstacle::obstacleForLevel2();
  std::vector<SDL_Rect> B= Obstacle::obstacleForLevel3();
  obstacles.reserve( A.size() + B.size() ); // preallocate memory
  obstacles.insert(obstacles.end(), A.begin(), A.end() );
  obstacles.insert( obstacles.end(), B.begin(), B.end() );
  
  return obstacles; 
}

std::vector<SDL_Rect> Obstacle::obstacleForLevel5(){
   return Obstacle::obstacleForLevel4();
}

std::vector<SDL_Rect> Obstacle::createObstacle(int level){
   std::vector<SDL_Rect> obstacle1;
  switch(level){
    case 2: return Obstacle::obstacleForLevel2();
    case 3: return Obstacle::obstacleForLevel3();
    case 4: return Obstacle::obstacleForLevel4();
    case 5: return Obstacle::obstacleForLevel5();
  }
  return obstacle1;
}

bool Obstacle::isObstacle(int level, int x, int y){
  std::vector <SDL_Rect> obstacles = Obstacle::createObstacle(level);
 // int width = screen_width/ grid_width;
 // int height = screen_height/ grid_height;
  x = x*width;
  y = y*height; 
  for(auto const &obs: obstacles){
    //std::cout<< "Food= x: " << x << " y: " << y << std::endl;
    //std::cout<< "Obstacle: "<< obs.x<< " "<< obs.x + obs.w <<" "<< obs.y << " " << obs.y + obs.h << std::endl;
    if((x >= obs.x && x < obs.x + obs.w) && ( y >= obs.y && y < obs.y + obs.h )){
      
     // std::cout<<" food is obstacle."<< std::endl;
      return true;
    }
  } 
  return false;
}