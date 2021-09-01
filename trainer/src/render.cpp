#include "render.hpp"

#define SIZE_CONSTANT  25
#define MENU_HEIGHT    50
#define MENU_WIDTH    210
#define N_ITEMS         2

extern unsigned current_entity;
extern EntityList* entityList;

extern float x_cam; // TODO: Move to hacks.cpp
extern float y_cam;
extern float z_cam;

// Hack variables
bool bCheatsEnabled = false;
bool bMaximizeMenu  = true;
bool bIsLocked      = false;
bool bLastPass      = false;
bool bInGame        = false;
bool bInit          = false;

ImVec2 vecWindowSizeDefault{MENU_WIDTH, MENU_HEIGHT + N_ITEMS * SIZE_CONSTANT};
ImVec2 vecWindowSizeMinimized{MENU_WIDTH, MENU_HEIGHT};
ImVec4 color_hint{255, 80, 80, 160};

void Render::MainUI(void)
{
    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

	//////////////////////////////////////
	//////////////// Begin ///////////////
	//////////////////////////////////////
	if (bCheatsEnabled)
		ImGui::Begin("Shitman Trainer (ACTIVE)", &bInit, ImGuiWindowFlags_NoResize);
	else
		ImGui::Begin("Shitman Trainer", &bInit, ImGuiWindowFlags_NoResize);

	ImGui::SetWindowPos({ 0, 0 }, 0);
	if (bMaximizeMenu)
	{
		// Size
		ImGui::SetWindowSize(vecWindowSizeDefault, 0);

		// Contents
        if (bCheatsEnabled && bInGame)
        {
			float hp = entityList->ents[current_entity].entity->hp;
			ImGui::Text("Enemy %u:  HP = %.0f", current_entity+1, hp);
			ImGui::Text("Teleport: %.0f, %.0f, %.0f", x_cam, y_cam, z_cam);
        }
        else
        {
			if (bCheatsEnabled && !bInGame)
				ImGui::Text("Not in a game...");
        }
		ImGui::TextColored(color_hint, "[ TAB to toggle cheats ]");
        ImGui::TextColored(color_hint, "[ END to minimize Menu ]");
	}
	else
	{
		// Size
		ImGui::SetWindowSize(vecWindowSizeMinimized, 0);

		// Contents
        ImGui::TextColored(color_hint, "[ END to maximize Menu ]");
	}
	//////////////////////////////////////
	////////////////  End  ///////////////
	//////////////////////////////////////
	
	ImGui::End();
	ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}
