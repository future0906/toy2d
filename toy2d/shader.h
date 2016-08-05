#ifndef __TOY2D_SHADER_H_
#define __TOY2D_SHADER_H_
#include <string>

namespace Toy2D
{

class Shader
{
public:
  Shader();
  int Initialize(const std::string& vsh_file, const std::string& fsh_file);
  int GetUniformLocation(const std::string& name) const;
  void Use();
  ~Shader();
private:
  std::string LoadContent(const std::string& file_path) const;
private:
  int vertex_shader_;
  int fragment_shader_;
  int shader_programe_;
};


}

#endif//__TOY2D_SHADER_H_
