#include <curses.h>
#include <iostream>

int main() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    
    int termY,termX;
    WINDOW* screenScale = nullptr;
    WINDOW* menu = nullptr;
    WINDOW* alerts = nullptr;
    WINDOW* cover = nullptr;
    WINDOW** windows[] = {&screenScale,&menu,&cover,&alerts};
    bool fire = true, alertupdate = false;
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
    int tempX = -1,tempY = -1;
    while(true){
        resize_term(0,0);
        getmaxyx(stdscr,termY,termX);
        screenScale = newwin(24,80,0,0);
        
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
    return 0;
}