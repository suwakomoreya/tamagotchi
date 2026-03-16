#include "json.hpp"
#include <curses.h>

#include <iostream>
#include <fstream>
#include <filesystem>
#include <random>

using json = nlohmann::ordered_json;
namespace fs = std::filesystem;

void menu(){
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr,true);
    
    WINDOW* menu = nullptr;
    WINDOW* cover = nullptr;
    WINDOW* alerts = nullptr;
    int termY,termX;
    int tempY,tempX;
    bool fire,alertupdate;
    auto updateMenu = [&menu](){
        wclear(menu);
        menu = newwin(21,30,1,4);
        mvwprintw(menu,1,10,"Tamagotchi");
        box(menu,0,0);
        wrefresh(menu);
    };
    auto updateCover = [&cover](){
        wclear(cover);
        cover = newwin(21,39,1,37);
        box(cover,0,0);
        wrefresh(cover);  
    };
    auto createWins = [&](){
        updateMenu();
        updateCover();
        getmaxyx(stdscr,termY,termX);
        alerts = newwin(1,termX,0,0);
    };
    auto refresh = [&](){
        wrefresh(menu);
        wrefresh(cover);
        wrefresh(alerts); 
    };
    
    createWins();
    refresh();
    while(true){
        
        /*delete previous windows*/
        resize_term(0,0);
        getmaxyx(stdscr,termY,termX);
        /*windows*/

        if(tempX < 0){
            tempX = termX;
            tempY = termY;
        }
        /*windows*/
        if(termX < 80 || termY < 24){
            if(tempX !=termX || tempY != termY){
                erase();
                refresh();
                alerts = newwin(1,termX,0,0);
                werase(alerts);
                wprintw(alerts,"Size: %dx%d (Please resize your window!)", termX,termY);
                wrefresh(alerts);
                tempX = termX;
                tempY = termY;
            }
            napms(50);
            fire = true;
            continue;
        }
        if(fire==true){
            wclear(alerts);
            updateMenu();
            updateCover();    
        }
        alertupdate = false;
        fire = false;
        napms(50);
    }
}
void createtomo(){
    std::string petname;
    std::fstream petFile;
    
    /*gen */
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> age(1,5);
    std::uniform_int_distribution<> otherStats(50,100);
    
    std::cout << "What should be the name of your friend?: ";
    for(;;){
        std::getline(std::cin,petname);
        if(!petname.empty())
            break;
        
        std::cout << "Please give them a name!!" << std::endl;
    }

    json petStats = {
        {"Name", petname},
        {"Age",  age(gen)},
        {"Hunger", {
            {"Appetite", otherStats(gen) },
            {"Thirst", otherStats(gen)}
        }},
        {"Happiness", otherStats(gen)-10},
        {"Energy", otherStats(gen)-10},
        {"LastTimeUpdate", 0},
        {"LastSavedTime", 0}
    };

    if(petname.back() == '.')
        petname.erase(petname.size()-1,1);
    petname += ".json";
    petFile.open("tomodachis/"+petname, std::ios::out);
    petFile << petStats.dump(4);
    petFile.close();

    std::ifstream info("info.json");
    json infoobject;
    info >> infoobject;
    info.close();
    infoobject["existingTomos"] = infoobject.value("existingTomos", 0) + 1;
    std::ofstream out("info.json");
    out << infoobject.dump(4);
    out.close();
    
    std::cout << "Great news, " << petname << " is now at your house!\n Take care of them.";
}
