#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"
#include "core/simulation.h"
#include "imgui.h"
#include "ui/sidebar.h"
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <iostream>

// Function prototypes
bool initializeSDL(SDL_Window *&window, SDL_GLContext &gl_context);
void setupImGui(SDL_Window *window, SDL_GLContext gl_context);
void cleanup(SDL_Window *window, SDL_GLContext gl_context);
void mainLoop(SDL_Window *window, SDL_GLContext gl_context);

int main() {
    SDL_Window *window = nullptr;
    SDL_GLContext gl_context;

    if (!initializeSDL(window, gl_context)) {
        return 1;
    }

    setupImGui(window, gl_context);

    if (!Simulation::initialize()) {
        std::cerr << "Failed to initialize simulation!" << std::endl;
        cleanup(window, gl_context);
        return 1;
    }

    mainLoop(window, gl_context);

    Simulation::cleanup();
    cleanup(window, gl_context);

    return 0;
}

bool initializeSDL(SDL_Window *&window, SDL_GLContext &gl_context) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window =
        SDL_CreateWindow("firesim", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    gl_context = SDL_GL_CreateContext(window);
    if (!gl_context) {
        std::cerr << "SDL_GL_CreateContext Error: " << SDL_GetError()
                  << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    if (glewInit() != GLEW_OK) {
        std::cerr << "GLEW initialization failed!" << std::endl;
        SDL_GL_DeleteContext(gl_context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    return true;
}

void setupImGui(SDL_Window *window, SDL_GLContext gl_context) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init("#version 120");
}

void mainLoop(SDL_Window *window, SDL_GLContext gl_context) {
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // Update and render simulation
        Simulation::update(0.016f);
        Simulation::render();

        // Render ImGui UI
        renderSidebar();

        ImGui::Render();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        SDL_GL_SwapWindow(window);
    }
}

void cleanup(SDL_Window *window, SDL_GLContext gl_context) {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
