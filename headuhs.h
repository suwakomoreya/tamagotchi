#pragma once
#include "json.hpp"
#include "curses.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <random>
struct ui {
    WINDOW* menu = nullptr;
    WINDOW* cover = nullptr;
    WINDOW* alerts = nullptr;
    WINDOW** menucollection[3] = {&menu, &cover, &alerts};
}; 
void createtomo();
void mainmenu(ui& ui);
void terminalrefresh();
