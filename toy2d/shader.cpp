#include <shader.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Toy2D
{

Shader::Shader()
  :vertex_shader_(0), fragment_shader_(0), shader_programe_(0)
{
}

int Shader::Initialize(const std::string& vsh_file, const std::string& fsh_file)
{

  vertex_shader_ = glCreateShader(GL_VERTEX_SHADER);
  auto file_content = LoadContent(vsh_file);
  auto p = file_content.c_str();
  GLint success = 0;

  glShaderSource(vertex_shader_, 1, &p, nullptr);
  glCompileShader(vertex_shader_);
  glGetShaderiv(vertex_shader_, GL_COMPILE_STATUS, &success);
  if (!success) {
    GLchar infoLog[512];
    glGetShaderInfoLog(vertex_shader_, 512, nullptr, infoLog);
    std::cerr << "Compile default shader failed, msg:" << infoLog << std::endl;
    return -1;
  }

  success = 0;
  fragment_shader_ = glCreateShader(GL_FRAGMENT_SHADER);
  file_content = LoadContent(fsh_file);
  p = file_content.c_str();
  glShaderSource(fragment_shader_, 1, &p, nullptr);
  glCompileShader(fragment_shader_);
  glGetShaderiv(fragment_shader_, GL_COMPILE_STATUS, &success);
  if (!success) {
    GLchar infoLog[512];
    glGetShaderInfoLog(fragment_shader_, 512, nullptr, infoLog);
    std::cerr << "Compile default shader failed, msg:" << infoLog << std::endl;
    return -1;
  }

  success = 0;
  shader_programe_ = glCreateProgram();
  glAttachShader(shader_programe_, vertex_shader_);
  glAttachShader(shader_programe_, fragment_shader_);
  glLinkProgram(shader_programe_);
  glGetProgramiv(shader_programe_, GL_LINK_STATUS, &success);
  if (!success) {
    GLchar infoLog[512];
    glGetShaderInfoLog(shader_programe_, 512, nullptr, infoLog);
    std::cerr << "Link shader programe failed, msg:" << infoLog << std::endl;
    glfwTerminate();
    return -1;
  }

  return 0;
}

int Shader::GetUniformLocation(const std::string& name) const
{
  // TODO Check GL ERROR
  return glGetUniformLocation(shader_programe_, name.c_str());
}


// ReSharper disable once CppMemberFunctionMayBeConst
void Shader::Use()
{
  // TODO Check GL ERROR
  glUseProgram(shader_programe_);
}
Shader::~Shader()
{
  glDeleteShader(shader_programe_);
  glDeleteShader(vertex_shader_); 
  glDeleteShader(fragment_shader_);
}

std::string Shader::LoadContent(const std::string& file_path) const
{
  std::ifstream f;
  std::stringstream content;
  f.open(file_path, std::fstream::in | std::fstream::binary);
  content << f.rdbuf();
  f.close();
  return std::move(content.str());
}

}
