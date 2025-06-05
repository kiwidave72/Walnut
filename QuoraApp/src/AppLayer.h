#pragma once
#include "Walnut/Application.h"
#include "Walnut/Image.h"
#include "Walnut/UI/UI.h"


class AppLayer : public Walnut::Layer
{
private:
	bool m_AboutModalOpen = false;
	Walnut::Application* app;

public:

	virtual void OnUIRender() override
	{
		static bool show = false;

		ImGui::Begin("Command Bar", &show, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove );
		ImGui::SetWindowSize(ImVec2(200, 200));
		ImGui::Button("Button");
		ImGui::End();

		ImGui::Begin("Hello", &show);
		ImGui::Button("Button");
		ImGui::End();

		//ImGui::ShowDemoWindow();
		UI_DrawAboutModal();
	}

	void InitLayer(Walnut::Application* app)
	{
		app = app;

		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
			{
				app->Close();
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("About"))
			{
				ShowAboutModal();
			}
			ImGui::EndMenu();
		}
	}

	
	void UI_DrawAboutModal()
	{
		if (!m_AboutModalOpen)
			return;

		ImGui::OpenPopup("About");
		m_AboutModalOpen = ImGui::BeginPopupModal("About", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		if (m_AboutModalOpen)
		{
			auto image = Walnut::Application::Get().GetApplicationIcon();
			ImGui::Image(image->GetDescriptorSet(), { 48, 48 });

			ImGui::SameLine();
			Walnut::UI::ShiftCursorX(20.0f);

			ImGui::BeginGroup();
			ImGui::Text("Quora ");
			ImGui::Text("by kiwidave.");
			ImGui::EndGroup();

			if (Walnut::UI::ButtonCentered("Close"))
			{
				m_AboutModalOpen = false;
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
	}

	void ShowAboutModal()
	{
		m_AboutModalOpen = true;
	}

};