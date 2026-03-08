#include <curses.h>
#include <iostream>

int main() {
    initscr();
    cbreak;
    noecho();
    curs_set(0);

    int termY,termX;

    while(true){
        resize_term(0,0);
        WINDOW* screenScale = newwin(24,80,0,0);
        WINDOW* menu = newwin(21,30,1,4);
        WINDOW* cover = newwin(21,39,1,37);
        WINDOW* alerts = newwin(1,termX,0,0);
        /*windows*/
        getmaxyx(stdscr,termY,termX);
        wrefresh(screenScale);
        werase(alerts);
        if(screenScale == nullptr ||getmaxx(screenScale) > termX ||getmaxy(screenScale) > termY){
            wprintw(alerts,"Size: %dx%d (Please resize your window!)", termX,termY);
            wrefresh(alerts);
            napms(50);
            continue;
        }
        
        box(menu,0,0);
        mvwprintw(menu,1,10,"Tamagotchi");
        wrefresh(menu);
        napms(50);
        
        
        
    }
    


    return 0;
}