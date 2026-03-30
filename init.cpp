#include "json.hpp"
#include "headuhs.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <random>
#include <curses.h>
using json = nlohmann::json;
namespace fs = std::filesystem;
 // function declaration
void mainmenu();
void createtomo();

int main() {
    initscr();       // must happen first
    cbreak();
    noecho();
    curs_set(0);

    fs::path infofile = "info.json";
    fs::create_directories("tomodachis"); 
    std::fstream Info;
    json infoObject;

    std::random_device rd;
    std::mt19937 gen(rd());

    // Instead of:
    std::cout << "working?\n";

    // Use:
    printw("working?\n");
    refresh();
    // std::cout << "Tamagotchi" << std::endl;
    // std::cout << "Current Path: " << fs::current_path() << std::endl;

   
    if (!fs::exists(infofile)) {
        json createInformation = { {"existingTomos", 0} };
        Info.open(infofile, std::ios::out);
        Info << createInformation.dump(4);  
        Info.close();
    }

  
    if (!fs::is_empty("tomodachis")) {
        Info.open(infofile, std::ios::in | std::ios::out);
        Info >> infoObject;
        infoObject["existingTomos"] = 0;
        for (auto i : fs::directory_iterator("tomodachis"))
            infoObject["existingTomos"] = infoObject.value("existingTomos", 0) + 1;
        Info.seekp(0);
        Info << infoObject.dump(4);  
        Info.close();
    } else {
        std::cout << "Seems like you don't have a pet, so let's get you one." << std::endl;
        createtomo();
    }
    ui myui;        
    mainmenu(myui); 

    return 0;
}