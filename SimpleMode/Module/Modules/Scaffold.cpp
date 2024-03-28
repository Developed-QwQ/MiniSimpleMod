#include "Scaffold.h"

Scaffold::Scaffold() :IModule("Scaffold",'0',Category::WORLD, "Automatically build blocks beneath you"){

}

Scaffold::~Scaffold()
{
}

std::string Scaffold::getModuleName()
{
    return "Scaffold";
}

void Scaffold::onEnable(){
    auto player = Game.getLocalPlayer();
    if (player == nullptr) return;

}

