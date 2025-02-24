#pragma once

namespace Constants {
    namespace Frame  {
        constexpr char A = (char)201; // ╔
        constexpr char E = (char)205; // ═
        constexpr char B = (char)187; // ╗
        constexpr char F = (char)186; // ║
        constexpr char D = (char)200; // ╚
        constexpr char C = (char)188; // ╝
        constexpr int space = 25;
    }
    namespace Color {
        constexpr int RED = 31;
        constexpr int GREEN = 32;
        constexpr int YELLOW = 33;
        constexpr int WHITE = 37;
        constexpr int CYAN = 36;
        constexpr int MAGENTA = 35;
        constexpr int BLUE = 34;
        constexpr int BOLD = 1;
        constexpr int NORMAL = 0;
        constexpr int UNDERLINE = 4;
    }
    namespace List {
        namespace Weapon {
            constexpr int NUMBER = 8;
            constexpr int NAME = 20;
            constexpr int CATEGORY = 10;
            constexpr int ATK = 5;
            constexpr int ATKSPD = 7;
            constexpr int COST = 6;
            constexpr int SEPARATOR = 70; 
        }
        namespace Armor {
            constexpr int NUMBER = 8;
            constexpr int NAME = 22;
            constexpr int CATEGORY = 11;
            constexpr int DEF = 5;
            constexpr int HEALTH = 7;
            constexpr int WEIGHT = 8;
            constexpr int COST = 6;
            constexpr int SEPARATOR = 84; 
        }
    }
    namespace others {
        constexpr int TIME_DELAY = 1405;
    }
}