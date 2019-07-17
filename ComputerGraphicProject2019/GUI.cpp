#include "GUI.h"
#include "imgui.h"
#include <iostream>


static bool show_window = true;

GUI::GUI()
{
}


GUI::~GUI()
{
}

void GUI::  my_display_code()
{
	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).

	if (show_window)


		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{


		//ImGui::ShowDemoWindow(&show_demo_window);

		ImGui::Begin("menu");
		if (ImGui::Button("Meow")) {
			std::cout << "Meow\n";
		}

		if (ImGui::Button("Meow")) {
			std::cout << "Purr\n";
		}
		ImGui::End();


		ImGui::Begin("menu2");
		if (ImGui::Button("Meow1")) {
			std::cout << "Meow\n";
		}

		if (ImGui::Button("Meow2")) {
			std::cout << "Purr\n";
		}
		ImGui::End();
	}
	}

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.



	//ImGui::ShowDemoWindow(&show_demo_window);

	// Create a window called "Hello, world!" and append into it.








