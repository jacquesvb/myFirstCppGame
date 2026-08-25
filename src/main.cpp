#include <iostream>
#include <raylib.h>
#include <imgui.h>
#include <rlImGui.h>

int main()
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	
	InitWindow(1920, 1080, "window name");

	rlImGuiSetup(true);
	Vector2 dpi = GetWindowScaleDPI();   // e.g. {2.0, 2.0} on a Retina display
	float dpiScale = dpi.x;                 // Usually uniform

	ImGuiIO& io = ImGui::GetIO();

	// Scale fonts
	// io.Fonts->AddFontFromFileTTF("myfont.ttf", 18.0f * dpiScale);
	// io.Fonts->Build();

	// Scale UI widgets
	ImGui::GetStyle().ScaleAllSizes(dpiScale);
	
	// Scale text rendering
	io.FontGlobalScale = dpiScale;

	int baseFontSize = 40;
	int scaledFontSize = (int)(baseFontSize * dpiScale);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		rlImGuiBegin();

		Color c;
		c.r = 255;
		c.g = 0;
		c.b = 200;
		c.a = 255;

		DrawText("Congrats! You created your first window!", 190, 200, scaledFontSize, c);

		ImGui::Begin("test");

		ImGui::Text("hello");
		ImGui::Button("button");

		ImGui::ShowDemoWindow();

		ImGui::End();

		rlImGuiEnd();

		EndDrawing();
	}

	rlImGuiShutdown();

	CloseWindow();

	return 0;
}