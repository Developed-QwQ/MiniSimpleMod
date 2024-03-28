#pragma once


#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>
#include <d3dx11tex.h>
#include <D3DX11.h>
#include <D3D11.h>
class GuiControls{
public:
	static void Mainwindow();
	bool Lockbutton(std::string str,bool* v);
	bool Checkbox(std::string str,bool* v);
	bool Tab(const char* icon, const char* str, bool v);
	bool OptButton(const char* icon,std::string str,bool v);
};

extern GuiControls* Gui;
