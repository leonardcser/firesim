#ifndef SHADERS_H
#define SHADERS_H

namespace ShaderSources {
const char *VertexShader = R"(
        #version 120
        attribute vec3 position;
        void main() {
            gl_Position = vec4(position, 1.0);
        }
    )";

const char *FragmentShader = R"(
        #version 120
        void main() {
            gl_FragColor = vec4(1.0, 0.5, 0.0, 1.0); // Fire color
        }
    )";
} // namespace ShaderSources

#endif // SHADERS_H
