#define GLEW_STATIC
#include <sprite.h>
#include <algorithm>
#include <SOIL.h>
#include <GL/glew.h>

namespace Toy2D
{

Sprite::Sprite()
  : texture_file_(""), width_(0), height_(0), texture_(0)
{
  const GLfloat init_vertices[] = {
    //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
    0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // 右上
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   // 左下
    -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f    // 左上
  };
  std::copy(init_vertices, init_vertices + 32, vertices_);
}

Sprite::~Sprite()
{
}

int Sprite::Initialize(const std::string& path)
{
  texture_file_ = path;
  int width, height;
  unsigned char* image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
  glGenTextures(1, &texture_);
  glBindTexture(GL_TEXTURE_2D, texture_);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
  SOIL_free_image_data(image);

  glBindTexture(GL_TEXTURE_2D, 0);
  return 0;
}

}
