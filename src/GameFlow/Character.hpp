#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include "../Player.hpp"
#include "../Constants.hpp"
#include "../Utils.hpp"

using namespace Constants::Frame;

namespace Character {
    void display(Player &player);
    void show(Player &player);   
}