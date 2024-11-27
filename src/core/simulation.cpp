#include "core/simulation.h"
#include "core/shaders.h"
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <fstream>
#include <iostream>
#include <sstream>

namespace Simulation {
GLuint vertexShader = 0, fragmentShader = 0, shaderProgram = 0;

bool initialize() {
    shaderProgram = createShaderProgram();
    if (!shaderProgram) {
        return false;
    }

    return true;
}

void update(float deltaTime) {
    // Simulation logic goes here
}

void render() {
    glUseProgram(shaderProgram);
    // Add rendering logic (e.g., particles, grid, or textures)
    glUseProgram(0);
}

void cleanup() {
    if (shaderProgram) glDeleteProgram(shaderProgram);
    if (vertexShader) glDeleteShader(vertexShader);
    if (fragmentShader) glDeleteShader(fragmentShader);
}

GLuint loadShader(const std::string &filePath, GLenum shaderType) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open shader file: " << filePath << std::endl;
        return 0;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();
    const char *sourceCStr = source.c_str();

    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &sourceCStr, nullptr);
    glCompileShader(shader);

    GLint compileStatus;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus != GL_TRUE) {
        char infoLog[512];
        glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "Shader compilation error (" << filePath
                  << "): " << infoLog << std::endl;
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

GLuint createShaderProgram() {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &ShaderSources::VertexShader, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &ShaderSources::FragmentShader, nullptr);
    glCompileShader(fragmentShader);

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint linkStatus;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
    if (linkStatus != GL_TRUE) {
        char infoLog[512];
        glGetProgramInfoLog(program, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "Shader program linking error: " << infoLog << std::endl;
        glDeleteProgram(program);
        return 0;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}
} // namespace Simulation
