#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"
#include "imgui.h"
#include "ui/sidebar.h"
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <iostream>

// Function prototypes
bool InitializeSDL(SDL_Window*& window, SDL_GLContext& gl_context);
bool InitializeOpenGL(SDL_GLContext& gl_context);
void SetupImGui(SDL_Window* window, SDL_GLContext gl_context);
void Cleanup(SDL_Window* window, SDL_GLContext gl_context);
void MainLoop(SDL_Window* window, SDL_GLContext gl_context);

// Main entry point
int main() {
    SDL_Window* window = nullptr;
    SDL_GLContext gl_context;

    if (!InitializeSDL(window, gl_context)) {
        return 1;
    }

    SetupImGui(window, gl_context);
    MainLoop(window, gl_context);
    Cleanup(window, gl_context);

    return 0;
}

// Function implementations

bool InitializeSDL(SDL_Window*& window, SDL_GLContext& gl_context) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("firesim", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    gl_context = SDL_GL_CreateContext(window);
    if (!gl_context) {
        std::cerr << "SDL_GL_CreateContext Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    return true;
}

bool InitializeOpenGL(SDL_GLContext& gl_context) {
    if (glewInit() != GLEW_OK) {
        std::cerr << "GLEW initialization failed!" << std::endl;
        return false;
    }
    return true;
}

void SetupImGui(SDL_Window* window, SDL_GLContext gl_context) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init("#version 120"); // Use #version 120 for compatibility
}

void MainLoop(SDL_Window* window, SDL_GLContext gl_context) {
    bool running = true;
    SDL_Event event;

    while (running) {
        // Poll and handle events
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // Render ImGui UI
        RenderSidebar();

        // Rendering
        ImGui::Render();
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        SDL_GL_SwapWindow(window);
    }
}

void Cleanup(SDL_Window* window, SDL_GLContext gl_context) {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
