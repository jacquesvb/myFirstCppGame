#include <iostream>
#include <raylib.h>
#include <imgui.h>
#include <rlImGui.h>

float DetectLinuxScale()
{
	const char* gdkScale = getenv("GDK_SCALE");
	if (gdkScale) return (float)atof(gdkScale);

	const char* qtScale = getenv("QT_SCALE_FACTOR");
	if (qtScale) return (float)atof(qtScale);

	return 1.0f; // fall back to no scaling
}

int main()
{
	// FLAG_WINDOW_HIGHDPI tells the OS window backend this app is DPI-aware
	SetConfigFlags(FLAG_WINDOW_HIGHDPI |FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
	
	InitWindow(1920, 1080, "window name");
	SetTargetFPS(60);

	float dpiScale = DetectLinuxScale();
	float widgetScale = 3.0f; // Scale ImGui widgets to be larger on high-DPI displays

	// Load the font at a size multiplied by the DPI scale
	const int baseFontSize = 40;
	const int scaledFontSize = (int)(baseFontSize * dpiScale);

	Font roboto = LoadFontEx("resources/Roboto-Regular.ttf", scaledFontSize, nullptr, 0);
	SetTextureFilter(roboto.texture, TEXTURE_FILTER_BILINEAR);

#pragma region imgui	
	rlImGuiSetup(true);
	
	ImGuiIO& io = ImGui::GetIO();
	// io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable keyboard controls
	// io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable gamepad controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;      // Enable docking
	io.FontGlobalScale = widgetScale; // Scale ImGui's own font rendering to match the display's DPI

	// ImGui::StyleColorsDark();
	// ImGui::StyleColorsLight();
	ImGui::StyleColorsClassic();
#pragma endregion
	
	// Scale all ImGui widget sizes, padding, borders, etc. to match the display's DPI
	ImGuiStyle& style = ImGui::GetStyle();
	style.ScaleAllSizes(widgetScale);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		
		Color c;
		c.r = 255;
		c.g = 0;
		c.b = 200;
		c.a = 255;
		
		Vector2 textPos = { 40.0f, 40.0f };
		DrawTextEx(roboto, "Congrats! You created your first window!", textPos, (float)scaledFontSize, 1.0f, c);
	#pragma region imgui	
		rlImGuiBegin();

		// Docking stuff...
		ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
		ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		ImGui::PopStyleColor(2);
	#pragma endregion
		ImGui::Text("Booger");
	#pragma region imgui windows
		ImGui::Begin("First Window");

		ImGui::Text("hello");
		if (ImGui::Button("First button"))
		{
			std::cout << "Text\n";
		}
		ImGui::SameLine();
		if (ImGui::Button("button2"))
		{
			std::cout << "Second button\n";
		}

		ImGui::End();
	#pragma endregion
	#pragma region imgui windows
		ImGui::Begin("Second Window");
		ImGui::Text("hello from second window");
		if (ImGui::Button("button3"))
		{
			std::cout << "Third button\n";
		}
		ImGui::End();
	#pragma endregion
	#pragma region imgui windows
		ImGui::Begin("Third Window");
		ImGui::Text("Speed");
		ImGui::SameLine();
		ImGui::TextDisabled("(?)");

		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextUnformatted("Set the speed of automatic scrolling");
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
		ImGui::End();
	#pragma endregion
	#pragma region imgui windows
		ImGui::Begin("Fourth Window");
		
		static char buffer[128] = "";

		ImGuiInputTextFlags flags =
			ImGuiInputTextFlags_CharsNoBlank | // no spaces
			ImGuiInputTextFlags_EnterReturnsTrue | // return true on enter
			ImGuiInputTextFlags_AutoSelectAll; // select all text on focus

			if (ImGui::InputText("Player Name", buffer, sizeof(buffer), flags))
			{
				std::cout << "Confirmed name: " << buffer << "\n";
			}

		ImGui::End();
	#pragma region imgui
		rlImGuiEnd();
	#pragma endregion

		EndDrawing();
	}

	UnloadFont(roboto);
	rlImGuiShutdown();
	CloseWindow();

	return 0;
}