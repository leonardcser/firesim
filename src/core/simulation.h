#ifndef SIMULATION_H
#define SIMULATION_H

#include <GL/glew.h>
#include <string>

namespace Simulation {
// Public functions
bool initialize();
void update(float deltaTime);
void render();
void cleanup();

// Utility for shader management
GLuint loadShader(const std::string &filePath, GLenum shaderType);
GLuint createShaderProgram();
} // namespace Simulation

#endif // SIMULATION_H
