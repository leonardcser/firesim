#include "imgui.h"

void renderSidebar() {
    // Set up the position and size of the sidebar
    ImGuiIO &io = ImGui::GetIO();
    ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x - 250.0f, 0.0f),
                            ImGuiCond_Always); // Align to the right
    ImGui::SetNextWindowSize(ImVec2(250.0f, io.DisplaySize.y),
                             ImGuiCond_Always); // Full height, fixed width

    // Begin the sidebar
    ImGui::Begin("Settings", nullptr,
                 ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoMove);

    // Add sidebar content here
    if (ImGui::Button("Button")) {
        ImGui::Text("Button Pressed!");
    }

    // End the sidebar
    ImGui::End();
}
