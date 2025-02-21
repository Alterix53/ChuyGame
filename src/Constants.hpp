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
}