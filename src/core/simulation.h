#ifndef SIMULATION_H
#define SIMULATION_H

#include <GL/glew.h>

namespace Simulation {
// Public functions
bool initialize();
void update(float deltaTime);
void render();
void cleanup();

// Utility for shader management
GLuint createShaderProgram();
} // namespace Simulation

#endif // SIMULATION_H
