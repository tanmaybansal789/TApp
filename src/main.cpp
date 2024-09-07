#include "TApp.h"
#include <vector>
#include <string>

using namespace TApp;

class EnhancedUILayer : public Layer {
public:
    explicit EnhancedUILayer(Window* window) : window(window) {}

private:
    // Variables to store the state of the UI elements
    bool showAdditionalWindow = false; // New variable to control the visibility of an additional window

    void onAttach(LayerId id) override {
        // Initialize any resources if needed
    }

    void onDetach() override {
        // Clean up resources if needed
    }

    void onUpdate(float deltaTime) override {
        // Update any logic if needed
    }

    void onRender() override {
        showDemoWindow();
        showCustomWindow();
        showOptionalWindow();  // Call the new function to display the optional window
    }

    void showDemoWindow() {
        // Show the built-in ImGui demo window
        ImGui::ShowDemoWindow();
    }

    void showCustomWindow() {
        ImGui::Begin("ImGui Feature Showcase");

        if (ImGui::CollapsingHeader("Basic Widgets")) {
            static bool checkboxValue = false;
            ImGui::Checkbox("Checkbox", &checkboxValue);

            static int radioValue = 0;
            ImGui::RadioButton("Radio 1", &radioValue, 0); ImGui::SameLine();
            ImGui::RadioButton("Radio 2", &radioValue, 1); ImGui::SameLine();
            ImGui::RadioButton("Radio 3", &radioValue, 2);

            static float sliderValue = 0.0f;
            ImGui::SliderFloat("Slider", &sliderValue, 0.0f, 100.0f);

            static int intValue = 0;
            ImGui::InputInt("Input Int", &intValue);

            static float floatValue = 0.0f;
            ImGui::InputFloat("Input Float", &floatValue);

            static std::string inputText;
            static char buffer[256] = "";
            ImGui::InputText("Input Text", buffer, sizeof(buffer));
            inputText = buffer;

            // Action for the "Click me!" button
            if (ImGui::Button("Click me!")) {
                showAdditionalWindow = !showAdditionalWindow; // Toggle the visibility of the additional window
            }
        }

        if (ImGui::CollapsingHeader("Color Widgets")) {
            static ImVec4 color = ImVec4(0.4f, 0.7f, 0.0f, 1.0f);
            ImGui::ColorEdit3("Color Picker", (float*)&color);

            ImGui::ColorButton("Color Button", color);
        }

        if (ImGui::CollapsingHeader("Lists and Combos")) {
            static int listboxItem = 0;
            const char* items[] = { "Apple", "Banana", "Cherry", "Date", "Elderberry" };
            ImGui::ListBox("Listbox", &listboxItem, items, IM_ARRAYSIZE(items), 4);

            static int comboItem = 0;
            ImGui::Combo("Combo", &comboItem, "Option 1\0Option 2\0Option 3\0Option 4\0\0");
        }

        if (ImGui::CollapsingHeader("Trees and Tables")) {
            if (ImGui::TreeNode("Tree Node")) {
                ImGui::Text("This is a child of the tree node");
                if (ImGui::TreeNode("Nested Node")) {
                    ImGui::Text("Even deeper nesting");
                    ImGui::TreePop();
                }
                ImGui::TreePop();
            }

            if (ImGui::BeginTable("Simple Table", 3)) {
                ImGui::TableNextRow();
                ImGui::TableNextColumn(); ImGui::Text("Column 1");
                ImGui::TableNextColumn(); ImGui::Text("Column 2");
                ImGui::TableNextColumn(); ImGui::Text("Column 3");

                ImGui::TableNextRow();
                ImGui::TableNextColumn(); ImGui::Text("Row 2 Col 1");
                ImGui::TableNextColumn(); ImGui::Text("Row 2 Col 2");
                ImGui::TableNextColumn(); ImGui::Text("Row 2 Col 3");

                ImGui::EndTable();
            }
        }

        if (ImGui::CollapsingHeader("Plotting")) {
            static float values[90] = {};
            static int values_offset = 0;
            static double refresh_time = 0.0;
            if (refresh_time == 0.0)
                refresh_time = ImGui::GetTime();
            while (refresh_time < ImGui::GetTime()) // Create data at fixed 60 Hz rate
            {
                static float phase = 0.0f;
                values[values_offset] = cosf(phase);
                values_offset = (values_offset + 1) % IM_ARRAYSIZE(values);
                phase += 0.10f * values_offset;
                refresh_time += 1.0f / 60.0f;
            }
            ImGui::PlotLines("Lines", values, IM_ARRAYSIZE(values), values_offset, "avg 0.0", -1.0f, 1.0f, ImVec2(0, 80));
            ImGui::PlotHistogram("Histogram", values, IM_ARRAYSIZE(values), values_offset, nullptr, -1.0f, 1.0f, ImVec2(0, 80));
        }

        ImGui::End();
    }

    void showOptionalWindow() {
        if (showAdditionalWindow) {
            ImGui::Begin("Additional Window");
            ImGui::Text("This window was toggled by the button!");
            if (ImGui::Button("Close")) {
                showAdditionalWindow = false; // Close the window when the button is pressed
            }
            ImGui::End();
        }
    }

    Window* window;
};

class ImGuiDemoApp : public Application {
    void onInit() override {
        TAPP_INFO("Initialising ImGui Demo App");
        LayerStack& stack = window->getLayerStack();
        stack.addLayer<EnhancedUILayer>(window);
    }

    void update(float deltaTime) override {
        // You can add any additional update logic here if needed
    }

    void onShutdown() override {
        TAPP_INFO("Shutting down ImGui Demo App");
    }
};

int main() {
    auto* app = new ImGuiDemoApp();
    app->run({1280, 720, "ImGui Feature Showcase"});
    delete app;
    return 0;
}