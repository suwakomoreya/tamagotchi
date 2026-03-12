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
    WINDOW* cover = nullptr;
    WINDOW* alerts = nullptr;
    WINDOW** windows[] = {&screenScale,&menu,&cover,&alerts};
    bool fire = true;
    keypad(menu,TRUE);  
    auto updateMenu = [&menu](){
        mvwprintw(menu,1,10,"Tamagotchi");
        box(menu,0,0);
        wrefresh(menu);
    };
    
    while(true){
        /*
        for(WINDOW** i : windows)
            delwin(*i);

        for(WINDOW** i : windows)
            wrefresh(*i);
        
        */
        /*delete previous windows*/
        resize_term(0,0);
        getmaxyx(stdscr,termY,termX);
        screenScale = newwin(24,80,0,0);
        menu = newwin(21,30,1,4);
        cover = newwin(21,39,1,37);
        alerts = newwin(1,termX,0,0);
        keypad(menu,TRUE);
        
        /*windows*/
        
        if(termX < 80 || termY < 24){
            wprintw(alerts,"Size: %dx%d (Please resize your window!)", termX,termY);
            wrefresh(alerts);
            napms(50);
            continue;
        }
        
        int ch = getch();
        if(ch == 'q'){
            box(menu,0,0);
            mvwprintw(menu,1,10,"Tamagotchi");
            updateMenu();   
        }
        
        napms(50);
    }
    


    return 0;
}