#include <curses.h>
#include <iostream>

int main() {
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
    auto runSelection = [&](int selected){

    };
    int selected=0;

    enum menuSelections {
        PLAY,
        NEWTOMO,
        SETTINGS,
        EXIT
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

        int input = wgetch(menu);
        switch(input){
            case KEY_UP:
                selected--;
                break;
            case KEY_DOWN:
                selected++;
                break;
            case '\n':
                runSelection(selected);
                break;
        }

        alertupdate = false;
        fire = false;
        napms(50);
    }
    return 0;
}