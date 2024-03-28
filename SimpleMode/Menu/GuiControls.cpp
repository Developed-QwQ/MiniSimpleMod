#include "GuiControls.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "../../includes/imgui/imgui.h"
#include "../../includes/imgui/imgui_internal.h"
#include "color_t.hpp"
#include "hashes.hpp"
#include "../Config/ico.h"
#include "../Module/ModManager.h"
#include "Guiprogram.h"
    color_t border = { 1.f, 1.f, 1.f, 0.03f };

    color_t text_disabled = { 0.51f, 0.52f, 0.56f, 1.f };
    color_t text = { 1.f, 1.f, 1.f, 1.f };

    color_t frame_inactive = { 0.023f, 0.039f, 0.07f, 1.f };
    color_t frame_active = { 0.043f, 0.07f, 0.137f, 1.f };

    color_t accent_color = { 0.3f, 0.49f, 1.f, 1.f };
using namespace ImGui;
void GuiControls::Mainwindow(){

    ImGuiIO& io = ImGui::GetIO();

    SetNextWindowSize(ImVec2(905, 624));
    {  ImGui::Begin("Hello, world!", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground);
    ImVec2 P1, P2;
    ImDrawList* pDrawList;
    const auto& pos = ImGui::GetWindowPos();
    const auto& pWindowDrawList = ImGui::GetWindowDrawList();
    const auto& pBackgroundDrawList = ImGui::GetBackgroundDrawList();
    const auto& pForegroundDrawList = ImGui::GetForegroundDrawList();

    pBackgroundDrawList->AddRectFilled(ImVec2(0.000f + pos.x, 0.000f + pos.y), ImVec2(905 + pos.x, 624 + pos.y), ImColor(9, 9, 9, 180), 10); // Background

  //  pWindowDrawList->AddRectFilled(ImVec2(20.000f + pos.x, 75.000f + pos.y), ImVec2(903 + pos.x, 76 + pos.y), ImColor(255, 25, 25, 180), 10); // bar line
    pWindowDrawList->AddRectFilledMultiColor(ImVec2(20.000f + pos.x, 75.000f + pos.y) + ImVec2(0.000f, 0.000f), ImVec2(903 + pos.x, 76 + pos.y),ImColor(0.5, 0.200f, 0.200f, 0.800f), ImColor(0.00f, 0.00f, 0.00f, 0.000f), ImColor(0.00f, 0.00f, 0.00f, 0.000f), ImColor(0.5, 0.200f, 0.200f, 0.100f));
    pWindowDrawList->AddRectFilledMultiColor(ImVec2(20.000f + pos.x, 76.000f + pos.y) + ImVec2(0.000f, 0.000f), ImVec2(903 + pos.x, 77 + pos.y),ImColor(0.2, 0.200f, 0.200f, 0.800f), ImColor(0.00f, 0.00f, 0.00f, 0.000f), ImColor(0.00f, 0.00f, 0.00f, 0.000f), ImColor(0.2, 0.200f, 0.200f, 0.300f));
    pWindowDrawList->AddText(io.Fonts->Fonts[0],40, pos + ImVec2(50- io.Fonts->Fonts[1]->CalcTextSizeA(io.Fonts->Fonts[1]->FontSize, FLT_MAX, 0, ICON_FA_ACORN).x / 2, 20), GetColorU32(ImGuiCol_Text), ICON_FA_ACORN);
    pWindowDrawList->AddText(io.Fonts->Fonts[1], io.Fonts->Fonts[1]->FontSize, pos + ImVec2(180- io.Fonts->Fonts[1]->CalcTextSizeA(io.Fonts->Fonts[1]->FontSize, FLT_MAX, 0, "SIMPLEMOD").x / 2 + 2, 20+2), accent_color.to_im_color(), "SIMPLEMOD");
    pWindowDrawList->AddText(io.Fonts->Fonts[1], io.Fonts->Fonts[1]->FontSize, pos + ImVec2(180  - io.Fonts->Fonts[1]->CalcTextSizeA(io.Fonts->Fonts[1]->FontSize, FLT_MAX, 0, "SIMPLEMOD").x / 2, 20), GetColorU32(ImGuiCol_Text), "SIMPLEMOD");
    pWindowDrawList->AddRectFilled(ImVec2(0.008f + pos.x, 0.080f + pos.y), ImVec2(190 + pos.x, 624 + pos.y), ImGui::GetColorU32(ImGuiCol_ChildBg), 10, ImDrawFlags_RoundCornersLeft);
    ImGui::SetCursorPos(ImVec2(800, 21));
    if (Gui->OptButton(ICON_FA_THUMBS_UP, u8"дожњ", false))
        ShellExecuteA(NULL, "open", "https://afdian.net/a/QwQLL", NULL, NULL, SW_SHOWNORMAL);
    static int tab_count = 0;
     ImGui::SetCursorPos(ImVec2(20, 120));
     BeginChild("##tabs", ImVec2(120, 624-50));
     if (Gui->Tab(ICON_FA_UTENSIL_KNIFE, "COMBAT", true)&&tab_count!=0) {tab_count = 0;}
     if (Gui->Tab(ICON_FA_UTENSIL_KNIFE, "MOVEMENT", true) && tab_count != 1) {tab_count = 1;}
     if (Gui->Tab(ICON_FA_UTENSIL_KNIFE, "PLAYER", true) && tab_count != 2) { tab_count = 2;}
     if (Gui->Tab(ICON_FA_UTENSIL_KNIFE, "WORLD", true) && tab_count != 3) {tab_count = 3;}
     if (Gui->Tab(ICON_FA_UTENSIL_KNIFE, "MISC", true) && tab_count != 4) {tab_count = 4;}
     if (Gui->Tab(ICON_FA_UTENSIL_KNIFE, "VISUAL", true) && tab_count != 5) {tab_count = 5;}
     if (Gui->Tab(ICON_FA_UTENSIL_KNIFE, "CLIENT", true) && tab_count != 6) {tab_count = 6;}
      EndChild();
      ImGui::SetCursorPos(ImVec2(180, 120));
      ImGui::BeginChild("Editor", ImVec2(680, 480), true, ImGuiWindowFlags_NoScrollbar); {
      for (auto& mod : moduleMgr->moduleList) {
              if (tab_count == 0) {
                  if (mod->getCateg() == Category::COMBAT)
                      HUB->renderCategory(COMBAT,mod.get());
              }
              if (tab_count == 1) {
                  if (mod->getCateg() == Category::MOVEMENT)
                      HUB->renderCategory(MOVEMENT,mod.get());
              }
              if (tab_count == 2) {
                  if (mod->getCateg() == Category::PLAYER)
                      HUB->renderCategory(PLAYER,mod.get());
              }
              if (tab_count == 3) {
                  if (mod->getCateg() == Category::WORLD)
                      HUB->renderCategory(WORLD,mod.get());
              }
              if (tab_count == 4) {
                  if (mod->getCateg() == Category::MISC)
                      HUB->renderCategory(MISC,mod.get());
              }
              if (tab_count == 5) {
                  if (mod->getCateg() == Category::VISUAL)
                      HUB->renderCategory(VISUAL,mod.get());
              }
              if (tab_count == 6) {
                  if (mod->getCateg() == Category::CLIENT)
                      HUB->renderCategory(CLIENT,mod.get());
              }
              if (mod->isEnabled())
                  mod->onEnable();
          }ImGui::EndChild();
      }
    }ImGui::End();
}
bool GuiControls::Lockbutton(std::string str, bool* v) {
    auto window = GetCurrentWindow();
    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    auto id = window->GetID(str.c_str());
    const ImVec2 label_size = CalcTextSize(str.c_str(), NULL, true);

    auto pos = window->DC.CursorPos;
    auto draw = window->DrawList;
    ImRect bb(pos, ImVec2(GetWindowWidth() / 4, GetWindowHeight()));
    ItemAdd(bb, id);
    ItemSize(bb, GetStyle().FramePadding.y);
    bool hovered, held;
    bool pressed = ButtonBehavior(bb, id, &hovered, &held);

    static std::unordered_map < ImGuiID, float > values;
    auto value = values.find(id);
    if (value == values.end()) {
        values.insert({ id, 0.f });
        value = values.find(id);
    }

    value->second = ImLerp(value->second, *v ? 1.f : 0.f, 0.05f);

    window->DrawList->AddRectFilled(bb.Min, bb.Max, ImColor(0.10f, 0.10f, 0.10f, 1.00f - value->second), 10);
    if (label_size.x > 0.0f) RenderText(ImVec2(bb.Max.x + style.ItemInnerSpacing.x - 30, bb.Min.y + style.FramePadding.y - 4.0f), str.c_str());

    return pressed;
}   

bool GuiControls::Checkbox(std::string str, bool* v){
    auto window = GetCurrentWindow();
    auto id = window->GetID(str.c_str());

    auto label_size = CalcTextSize(str.c_str(), 0, 1);

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;

    auto pos = window->DC.CursorPos;
    auto draw = window->DrawList;
    ImVec2 size = { 80, 37 };
    str += *v ? "[OPEN]" : "[OFF]";
    ImRect bb(pos, pos + ImVec2((GetWindowWidth()), 60));
    ItemAdd(bb, id);
    ItemSize(bb, GetStyle().FramePadding.y);

    //ImRect frame_bb(pos + ImVec2(GetWindowWidth() - size.x-80, 0), pos + ImVec2(GetWindowWidth()-80, size.y));
    ImRect frame_bb(pos + ImVec2(GetWindowWidth() - size.x-10, 15), pos + ImVec2(GetWindowWidth()-50, size.y));
    ImRect total_bb(pos, pos + ImVec2(GetWindowWidth(), label_size.y));
    ItemAdd(total_bb, id);
    ItemSize(total_bb, style.FramePadding.y);

    bool frame_hovered, frame_held;
    bool frame_pressed = ButtonBehavior(frame_bb, id, &frame_hovered, &frame_held);
    if (frame_pressed) {
        *v = !(*v);
        MarkItemEdited(id);
    }
    bool hovered, held;
    bool pressed = ButtonBehavior(bb, id, &hovered, &held);

    static std::unordered_map < ImGuiID, float > values;
    auto value = values.find(id);
    if (value == values.end()) {
        values.insert({ id, 0.f });
        value = values.find(id);
    }

    value->second = ImLerp(value->second, hovered ? 1.f : 0.150f, g.IO.DeltaTime * 5.f);
    value->second *= style.Alpha;
    value->second = ImLerp(value->second, held ? 1.f : 0.20f, g.IO.DeltaTime * 0.8f);

    window->DrawList->AddRectFilledMultiColor(bb.Min + ImVec2(0.000f, 0.000f), bb.Max + ImVec2(bb.Min.x - bb.Min.x - 20, bb.Min.y - bb.Min.y), held ? ImColor(value->second, 0.300f, 0.300f, 0.600f) : ImColor(9, 9, 9, 180), ImColor(0.00f, 0.00f, 0.00f, 0.000f), ImColor(0.00f, 0.00f, 0.00f, 0.000f), held ? ImColor(value->second, 0.400f, 0.100f, 0.800f) : ImColor(9, 9, 9, 80));
    window->DrawList->AddRectFilledMultiColor(bb.Min + ImVec2(0.000f, 0.000f), bb.Max + ImVec2(bb.Min.x - bb.Min.x - 20, bb.Min.y - bb.Min.y), hovered ? ImColor(value->second, 0.300f, 0.300f, 0.200f) : ImColor(9, 9, 9, 180), ImColor(0.00f, 0.00f, 0.00f, 0.000f), ImColor(0.00f, 0.00f, 0.00f, 0.000f), hovered ? ImColor(value->second, 0.400f, 0.100f, 0.400f) : ImColor(9, 9, 9, 80));
    window->DrawList->AddRectFilledMultiColor(bb.Min + ImVec2(0.000f, 0.000f), bb.Max + ImVec2(bb.Min.x - bb.Min.x - 20, bb.Min.y - bb.Min.y), *v ? ImColor(0, 255, 255, 60) : ImColor(255, 255, 255, 50), ImColor(0.00f, 0.00f, 0.00f, 0.000f), ImColor(0.00f, 0.00f, 0.00f, 0.000f), *v ? ImColor(value->second, 0.200f, 0.200f, 0.200f) : ImColor(9, 9, 9, 80));

    draw->AddText(ImGui::GetIO().Fonts->Fonts[2], ImGui::GetIO().Fonts->Fonts[2]->FontSize, ImVec2(bb.Min.x + 40, bb.GetCenter().y - label_size.y / 2), held ? ImColor(value->second * 0.3f, 0.49f, 1.f, 0.5f) : ImColor(value->second * 255, 255.f, 255.f, 1.f), str.c_str());
    ////////

    draw->AddRect(frame_bb.Min, frame_bb.Max, border.to_im_color(), 10);
    auto frame = ImLerp(value->second, (*v ? 1.f : 0.f), 0.08f);
    draw->AddCircleFilled(ImVec2(frame_bb.Min.x + (29 *(*v? frame : frame* frame/ frame)), frame_bb.GetCenter().y), 7, *v ? accent_color.to_im_color() : text_disabled.to_im_color(), 30);

    return pressed;
}

bool GuiControls::Tab(const char* icon, const char* str, bool v){
    auto window = GetCurrentWindow();   
    auto id = window->GetID(str);

    auto icon_size = CalcTextSize(icon);
    auto label_size = CalcTextSize(str, 0, 1);

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;

    auto pos = window->DC.CursorPos;
    auto draw = window->DrawList;

    ImRect bb(pos, pos + ImVec2((GetWindowWidth()/8)+180, 50));
    ItemAdd(bb, id);
    ItemSize(bb, GetStyle().FramePadding.y);

    bool hovered, held;
    bool pressed = ButtonBehavior(bb, id, &hovered, &held);

    static std::unordered_map < ImGuiID, float > values;
    auto value = values.find(id);
    if (value == values.end()) {
        values.insert({ id, 0.f });
        value = values.find(id);}
    value->second = ImLerp(value->second, hovered ? 1.f : 0.150f, g.IO.DeltaTime * 5.f);
    value->second *= style.Alpha;
    value->second = ImLerp(value->second, held ? 1.f : 0.50f, g.IO.DeltaTime * 8.f);
  //  window->DrawList->AddRectFilled(bb.Min, bb.Max, ImColor(0.10f, 0.10f, 0.10f, 1.00f - value->second), 10);
    window->DrawList->AddRectFilledMultiColor(bb.Min + ImVec2(0.000f, 0.000f), bb.Max + ImVec2(bb.Min.x - bb.Min.x - 20, bb.Min.y - bb.Min.y), held ? ImColor(value->second, 0.200f, 0.200f, 0.200f) :ImColor(value->second, 0.200f, 0.200f, 0.100f), ImColor(0.00f, 0.00f, 0.00f, 0.000f), ImColor(0.00f, 0.00f, 0.00f, 0.000f), held ? ImColor(value->second, 0.200f, 0.200f, 0.200f) : ImColor(value->second, 0.200f, 0.200f, 0.100f));
    draw->AddText(ImVec2(bb.Min.x + 10, bb.GetCenter().y - label_size.y / 2), held ?ImColor(value->second * 0.3f, 0.49f, 1.f, 0.5f): ImColor(value->second * 255, 255.f, 255.f, 1.f), icon);
    draw->AddText(ImVec2(bb.Min.x + 40, bb.GetCenter().y - label_size.y / 2), held ? ImColor(value->second * 0.3f, 0.49f, 1.f, 0.5f) : ImColor(value->second * 255, 255.f, 255.f, 1.f), str);
   
    return pressed;
}

bool GuiControls::OptButton(const char* icon, std::string str, bool v){
    auto window = GetCurrentWindow();
    auto id = window->GetID(str.c_str());

    auto icon_size = CalcTextSize(icon);
    auto label_size = CalcTextSize(str.c_str(), 0, 1);

    auto pos = window->DC.CursorPos;
    auto draw = window->DrawList;

    ImRect bb(pos, pos + ImVec2(GetWindowWidth(), 30));
    ItemAdd(bb, id);
    ItemSize(bb, GetStyle().FramePadding.y);

    bool hovered, held;
    bool pressed = ButtonBehavior(bb, id, &hovered, &held);

    static std::unordered_map < ImGuiID, float > values;
    auto value = values.find(id);
    if (value == values.end()) {
        values.insert({ id, 0.f });
        value = values.find(id);
    }
    value->second = ImLerp(value->second, (held ? 1.f : 0.f), 0.05f);
    draw->AddText(ImVec2(bb.Min.x + 10, bb.GetCenter().y - label_size.y / 2), held ? ImColor(value->second * 0.3f, 0.49f, 1.f, 0.5f) : ImColor(value->second * 255, 255.f, 255.f, 1.f), icon);
    draw->AddText(ImGui::GetIO().Fonts->Fonts[2], ImGui::GetIO().Fonts->Fonts[2]->FontSize+2,ImVec2(bb.Min.x + 40, bb.GetCenter().y - label_size.y / 2), held ? ImColor(value->second * 0.3f, 0.49f, 1.f, 0.5f) : ImColor(value->second * 255, 255.f, 255.f, 1.f), str.c_str());

    return pressed;
}

GuiControls* Gui = new GuiControls();