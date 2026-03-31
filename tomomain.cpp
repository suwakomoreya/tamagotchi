#include "json.hpp"
#include <curses.h>

#include <iostream>
#include <fstream>
#include <filesystem>
#include <random>

using json = nlohmann::ordered_json;
namespace fs = std::filesystem;

int termY,termX;
int tempY=-1, tempX=-1;
bool fire = false;
struct ui{
    // menu
    WINDOW* menu = nullptr;
    WINDOW* cover = nullptr;
    WINDOW* alerts = nullptr;
    WINDOW** menucollection[3] ={&menu,&cover,&alerts};
};
void terminalrefresh(ui& ui,int wincount){
    nodelay(stdscr, TRUE);
    resize_term(0,0); 
    getmaxyx(stdscr,termY,termX);

    // ui.alerts = newwin(termY,termX,0,0);

    if(tempX < 0){
        tempX = termX;
        tempY = termY;
    }
    if(termX < 80 || termY < 24){
        if(ui.alerts != nullptr){
            ui.alerts = newwin(1,termX,0,0);
            werase(ui.alerts);
            wresize(ui.alerts,1,termX);
            wprintw(ui.alerts,"Terminal too small: %dx%d (Resize please)", termX, termY);
            wrefresh(ui.alerts);
        }
    }
    // skip menu drawing but still process input
    // by here, ill delete windows if they exist and then recreate them in the other function since theyre all unique sizes
    else{
        if(tempX != termX || tempY != termY || fire){
            for(int i = 0; i<wincount; i++){
                if(*ui.menucollection[i]){
                    delwin(*ui.menucollection[i]);
                    *ui.menucollection[i] = nullptr;
                }
            }
            
            ui.alerts = newwin(1, termX,0,0);

            fire = true;
        }
        werase(ui.alerts);
        wrefresh(ui.alerts);
        //from here, youll update your windows right after the function ends by checking if fire was true
    }
};

void createtomo();
void mainmenu(ui& ui){
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr,true);

    int wincount = sizeof(ui.menucollection)/sizeof(ui.menucollection[0]);
    
    bool alertupdate;

    int selected = 0;
    std::string menuText[] = {"Play", "New Tomo", "Settings", "Exit"};
    int count = sizeof(menuText)/sizeof(menuText[0]);
    

    auto runSelection = [&](int selected){
        // Example: Exit menu option works
        if(selected == 3){  //quit
            endwin();
            exit(0);
        }
        if(selected == 1){ //create tomodachi
            endwin();
            createtomo();
        }
    };

    auto updateMenu = [&](){
        if(ui.menu == nullptr) ui.menu = newwin(21,30,1,4);
        werase(ui.menu);
        box(ui.menu,0,0);
        mvwprintw(ui.menu,1,10,"Tamagotchi");
        for(int i=0;i<count;i++){
            if(i == selected) wattron(ui.menu,A_REVERSE);
            mvwprintw(ui.menu,3+i,2,menuText[i].c_str());
            if(i == selected) wattroff(ui.menu,A_REVERSE);
        }
        wrefresh(ui.menu);
    };

    auto updateCover = [&](){
        if(ui.cover == nullptr) ui.cover = newwin(21,39,1,37);
        werase(ui.cover);
        box(ui.cover,0,0);
        mvwprintw(ui.cover,1,2,"Your Pet");
        wrefresh(ui.cover);  
    };

    auto createWins = [&](){
        if(ui.menu == nullptr) ui.menu = newwin(21,30,1,4);
        if(ui.cover == nullptr) ui.cover = newwin(21,39,1,37);
        getmaxyx(stdscr, termY, termX);
        // if(alerts == nullptr) alerts = newwin(1,termX,0,0);
        updateMenu();
        updateCover();
    };

    auto refreshAll = [&](){
        wrefresh(ui.menu);
        wrefresh(ui.cover);
        // wrefresh(alerts); 
    };

    terminalrefresh(ui,wincount);
    createWins();

    while(true){
         /*
         resize_term(0,0);
         getmaxyx(stdscr, termY, termX);
         if(tempX < 0){
            tempX = termX;
            tempY = termY;
        }
        

        // Terminal too small

         if(termX < 80 || termY < 24){
            if(alerts != nullptr){
                werase(alerts);
                wresize(alerts,1,termX);
                wprintw(alerts,"Terminal too small: %dx%d (Resize please)", termX, termY);
                wrefresh(alerts);
            }
            // skip menu drawing but still process input
        } 
        else {
            // Terminal big enough, recreate windows if size changed
            if(tempX != termX || tempY != termY || fire){
                if(menu) delwin(menu);
                if(cover) delwin(cover);
                if(alerts) delwin(alerts);

                menu = newwin(21,30,1,4);
                cover = newwin(21,39,1,37);
                alerts = newwin(1, termX,0,0);

                tempX = termX;
                tempY = termY;
                fire = true;
            }

            werase(alerts);
            wrefresh(alerts);

            updateMenu();
            updateCover();
        } */
        terminalrefresh(ui,wincount);
        if(ui.alerts) 
            wrefresh(ui.alerts);
        if(fire==true){
            if(ui.alerts == nullptr)
                ui.alerts =newwin(1,termX,0,0);
            updateMenu();
            updateCover();
        }
        

        // handle input
        int ch = getch();
        switch(ch){
            case KEY_UP:
                selected--;
                if(selected < 0) selected = count-1;
                break;
            case KEY_DOWN:
                selected++;
                if(selected >= count) selected = 0;
                break;
            case '\n':
                runSelection(selected);
                break;
        }

        fire = false;
        alertupdate = false;
        napms(50);
    }

    delwin(ui.menu);
    ui.menu = nullptr;
    delwin(ui.cover);
    
}
void createtomo(){
    // nocbreak();
    // noecho();
    std::string petname;
    std::fstream petFile;
    
    /*gen */
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> age(1,5);
    std::uniform_int_distribution<> otherStats(50,100);
    // windows
    WINDOW* textarea = newwin(termY,termX,0,0);
    // actually start code
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
    
    std::cout << "Great news, " << petname << " is now at your house!\nTake care of them.";
    int end = getch();

}
