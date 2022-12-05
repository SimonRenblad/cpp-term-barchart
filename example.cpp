#include <ncurses.h>
#include <string>
#include <locale.h>
#include <cmath>
#include <vector>
#include "barchart.h"
using namespace std;

int main(int argc, char ** argv){
    setlocale(LC_ALL, "");
    /* NCURSES START */
    initscr();
    noecho();
    cbreak();
    
    // get screen size
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    WINDOW * inputwin = newwin(yMax, xMax, 0, 0);

    box(inputwin, 0, 0);

    wstring col1 = L"Column 1";
    wstring col2 = L"Column 2";
    wstring col3 = L"Column 3";

    BarChart chart(inputwin);
    chart.set_origin(20,20);
    chart.max_lines = 15;
    chart.max_value = 100.0;
    chart.column_gap = 8;
    chart.add_bar(50.5, col1);
    chart.add_bar(75.5, col2);
    chart.add_bar(10.5, col3);
    chart.display();

    // draw_axis(inputwin, max_lines, num_cols, col_gap, origin_x, origin_y);
    // draw_max_value(inputwin, max_value, 4, 10, origin_x, origin_y);
    // draw_axis_name(inputwin, col1, 0, 8, origin_x, origin_y, true);
    // draw_axis_name(inputwin, col2, 1, 8, origin_x, origin_y, true);
    // draw_bar(inputwin, max_value, max_lines, 8, 20.5, 0, origin_x, origin_y);
    // draw_bar(inputwin, max_value, 10, 8, 75.5, 1, origin_x, origin_y);

    wmove(inputwin,0,0);
    refresh();
    wrefresh(inputwin);

    keypad(inputwin, true);

    // wait and exit
    getch();
    endwin();
    /* NCURSES END */
    return 0;
}
