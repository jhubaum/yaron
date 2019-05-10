#include <shader.hpp>

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

#include <glm/glm.hpp>

GLuint loadShader(const std::string& filename, GLenum shaderType) {
  std::ifstream str(filename, std::ios::in);

  if (!str.good()) {
    std::cout << "Could not open shaderfile " << filename << std::endl;
    return 0;
  }
  std::stringstream sstr;
  sstr << str.rdbuf();
  std::string shaderCode = sstr.str();
  str.close();

  // Compile Shader
  GLuint shaderId = glCreateShader(shaderType);
  std::cout << "Compiling shader: " << filename << std::endl;
  const char* sourcePointer = shaderCode.c_str();
  glShaderSource(shaderId, 1, &sourcePointer, NULL);
  glCompileShader(shaderId);

  // Check Shader
  GLint result = GL_FALSE;
  int infoLogLength = 0;
  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
  glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);

  if (infoLogLength > 0) {
    // Compile Error
    std::vector<char> errorMsg(infoLogLength+1);
    glGetShaderInfoLog(shaderId, infoLogLength, NULL, &errorMsg[0]);
    std::cout << &errorMsg[0] << std::endl;
    return 0;
  }

  return shaderId;
}

ShaderBuilder::ShaderBuilder()
  : _vertex(0), _fragment(0)
{}

ShaderBuilder::~ShaderBuilder() {
  glDeleteShader(_vertex);
  glDeleteShader(_fragment);
}

ShaderBuilder& ShaderBuilder::addVertexShader(const std::string& filename) {
  if (0 != _vertex)
    glDeleteShader(_vertex);
  _vertex = loadShader(filename, GL_VERTEX_SHADER);

  return *this;
}

ShaderBuilder& ShaderBuilder::addFragmentShader(const std::string& filename) {
  if (0 != _fragment)
    glDeleteShader(_fragment);
  _fragment = loadShader(filename, GL_FRAGMENT_SHADER);

  return *this;
}

ShaderPtr ShaderBuilder::build() {
  std::cout << "Linking shaders" << std::endl;

  if (0 == _vertex || 0 == _fragment) {
    std::cout << "Both vertex and fragment shader have to be set" << std::endl;
    return nullptr;
  }

  GLuint programId = glCreateProgram();

  glAttachShader(programId, _vertex);
  glAttachShader(programId, _fragment);

  glLinkProgram(programId);

  // Check program
  GLint result = GL_FALSE;
  int infoLogLength = 0;
  glGetProgramiv(programId, GL_LINK_STATUS, &result);
  glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);

  if (infoLogLength > 0) {
    std::vector<char> errorMsg(infoLogLength+1);
    glGetProgramInfoLog(programId, infoLogLength, nullptr, &errorMsg[0]);

    std::cout << &errorMsg[0] << std::endl;
  }

  glDetachShader(programId, _vertex);
  glDetachShader(programId, _fragment);

  struct ShaderSharedEnabler : public Shader { };
  auto pShader = std::make_shared<ShaderSharedEnabler>();
  if(!pShader->init(programId))
    return nullptr;
  return pShader;
}

Shader::Shader()
  : _program(-1), _vpHandle(-1), _worldHandle(-1),
    _drawMode(DrawMode::Triangles)
{}

Shader::~Shader()
{
  glDeleteProgram(_program);
}

bool Shader::init(GLuint program) {
  _program = program;
  if (0 == _program)
    return false;

  _worldHandle = glGetUniformLocation(_program, "worldMatrix");

  if(-1 == _worldHandle) {
    std::cout << "Shader: Not all transformation matrices are available." << std::endl;
    return false;
  }
  return true;
}

void Shader::setActive() {
  glUseProgram(_program);
}

void Shader::setViewProjection(const glm::mat4 &value)
{
  glUniformMatrix4fv(_vpHandle, 1, GL_FALSE, &value[0][0]);
}

void Shader::setWorld(const glm::mat4 &value)
{
  glUniformMatrix4fv(_worldHandle, 1, GL_FALSE, &value[0][0]);
}


void Shader::enableBlending(BlendFunc sfactor, BlendFunc dfactor) {
  glEnable(GL_BLEND);
  glBlendFunc(static_cast<GLenum>(sfactor), static_cast<GLenum>(GL_ONE_MINUS_SRC_ALPHA));
}

void Shader::disableBlending() {
  glDisable(GL_BLEND);
}

CullFace operator &(CullFace a, CullFace b) {
  return static_cast<CullFace>(static_cast<int>(a) & static_cast<int>(b));
}

CullFace operator |(CullFace a, CullFace b) {
  return static_cast<CullFace>(static_cast<int>(a) | static_cast<int>(b));
}

void Shader::setCulling(CullFace cullface) {
  if (CullFace::None == cullface) {
    glDisable(GL_CULL_FACE);
    return;
  }

  glEnable(GL_CULL_FACE);

  GLenum cf;
  if (CullFace::None != (cullface & CullFace::Front) &&
      CullFace::None != (cullface & CullFace::Back))
    cf = GL_FRONT_AND_BACK;
  else if (CullFace::None != (cullface & CullFace::Front))
    cf = GL_FRONT;
  else
    cf = GL_BACK;

  glCullFace(cf);
}

void Shader::enableDepthTest(DepthTest depthTest) {
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(static_cast<GLenum>(depthTest));
}

void Shader::disableDepthTest() {
  glDisable(GL_DEPTH_TEST);
}

void Shader::setPolygonMode(PolygonMode polygonMode) {
  glPolygonMode(GL_FRONT_AND_BACK, static_cast<GLenum>(polygonMode));
}

bool safeGetHandle(GLuint program, const std::string &name, GLuint *oH) {
  *oH = glGetUniformLocation(program, name.c_str());
  if (-1 == *oH) {
    std::cout << "Shader: Unknown parameter name " << name << std::endl;
    return false;
  }
  return true;
}

template<>
void Shader::set<float>(const std::string &name, const float &value) {
  GLuint handle;
  if (safeGetHandle(_program, name, &handle))
    glUniform1f(handle, value);
}

template<>
void Shader::set<Color>(const std::string &name, const Color &value) {
  GLuint handle;
  if (safeGetHandle(_program, name, &handle))
      glUniform3f(handle, value.r, value.g, value.b);
}

template<>
void Shader::set<glm::vec3>(const std::string &name, const glm::vec3 &value) {
  GLuint handle;
  if (safeGetHandle(_program, name, &handle))
      glUniform3f(handle, value.x, value.y, value.z);
}

template<>
void Shader::set<glm::mat4>(const std::string &name, const glm::mat4 &value) {
  GLuint handle;
  if (safeGetHandle(_program, name, &handle))
    glUniformMatrix4fv(handle, 1, GL_FALSE, &value[0][0]);
}

