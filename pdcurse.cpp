#include <curses.h>
#include <iostream>

int main() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    /*create windows*/
    WINDOW* menubar = newwin(21,30, 1, 4); // small, safe window
    WINDOW* tama = newwin(21,39,1,37);
    wrefresh(menubar);
    wrefresh(tama);
    int termy, termx;
    /*terminal size*/
    while(true){
        resize_term(0,0);
        
        WINDOW* scale = newwin(24,80,0,0);
        wrefresh(scale);
        getmaxyx(stdscr, termy, termx);
        clear(); 
        if( scale == nullptr || getmaxx(scale) > termx){
            printw("Terminal too small: %d x %d", termy, termx);
        }
        else 
            printw("The terminal is fine: %d x %d", termy, termx);
         
        refresh(); 
        napms(50);
    }
    
    box(menubar, 0, 0);
    mvwprintw(menubar, 1, 10, "Tamagotchi");
    box(tama, 0, 0);

    wrefresh(menubar);
    wrefresh(tama);
    refresh(); 
 
    int chara = getch();
    std::cout << chara;
    delwin(tama);
    endwin();

    return 0;
}