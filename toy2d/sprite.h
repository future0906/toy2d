#ifndef __TOY2D_SPRITE_H_
#define __TOY2D_SPRITE_H_
#include <string>
#include <GL/glew.h>


namespace Toy2D
{

class Sprite
{
public:
  Sprite();
  ~Sprite();
  int Initialize(const std::string& path);
private:
  std::string texture_file_;
  int width_  ;
  int height_;
  GLuint texture_;
  GLfloat vertices_[32];
};

}

#endif