#include <ncurses.h>
#include <string>
#include <locale.h>
#include <cmath>
#include <vector>

void draw_bar(WINDOW * inputwin, float max_value, int max_lines, int col_gap, float y_value, int column, int origin_y, int origin_x, bool show_val, int sigfigs);
void draw_axis(WINDOW * inputwin, int max_lines, int max_columns, int col_gap, int origin_y, int origin_x);
void draw_max_value(WINDOW * inputwin, float max_value, int sigfigs, int max_lines, int origin_y, int origin_x);
void draw_axis_name(WINDOW * inputwin, std::wstring name, int column, int col_gap, int origin_y, int origin_x, bool staggered);
void draw_chart(WINDOW * inputwin, int origin_x, int origin_y, int col_gap, int max_lines, float max_value, int num_cols, std::vector<float>& values, std::vector<std::wstring>& col_names, bool staggered, bool show_val, int sigfigs);

class BarChart {
    public:
        int max_lines;
        int column_gap;
        int origin_x;
        int origin_y;
        float max_value;
        int num_columns;
        std::vector<float> y_values;
        std::vector<std::wstring> column_names;

        bool staggered_axis_titles;
        bool show_values_above_bar;
        int sigfigs;
        WINDOW * inputwin;
        
        BarChart(WINDOW * window) {
            inputwin = window;
            origin_x = 0;
            origin_y = 0;
            num_columns = 0;
            staggered_axis_titles = true;
            show_values_above_bar = true;
            sigfigs = 4;
            column_gap = 5;
            y_values = {};
            column_names = {};
        }

        void set_origin(int x, int y){
            origin_x = x;
            origin_y = y;
        }

        void add_bar(float y_value, std::wstring column_name){
            y_values.push_back(y_value);
            column_names.push_back(column_name);
            num_columns +=1;
        }

        void display(){
            draw_chart(inputwin, origin_x, origin_y, column_gap, max_lines, 
                    max_value, num_columns, y_values, column_names, 
                    staggered_axis_titles, show_values_above_bar, sigfigs); 
        }
};

void draw_chart(WINDOW * inputwin, int origin_x, int origin_y, int col_gap, int max_lines, float max_value, int num_cols, std::vector<float>& values, std::vector<std::wstring>& col_names, bool staggered, bool show_val, int sigfigs) {
    draw_axis(inputwin, max_lines, num_cols, col_gap, origin_x, origin_y);
    draw_max_value(inputwin, max_value, sigfigs, max_lines, origin_x, origin_y);
    for(int i = 0; i < num_cols; i++){
        draw_bar(inputwin, max_value, max_lines, col_gap, values[i], i, origin_x, origin_y, show_val, sigfigs);
        draw_axis_name(inputwin, col_names[i], i, col_gap, origin_x, origin_y, staggered);
    }
    wmove(inputwin, origin_y, origin_x);
}

void draw_axis_name(WINDOW * inputwin, std::wstring name, int column, int col_gap, int origin_y, int origin_x, bool staggered){
    const wchar_t * ws = name.c_str();
    int x_value = origin_x+(column*col_gap)+2;
    int y_value = origin_y + 1;
    if(staggered) {
        y_value += column;
    }
    mvwaddwstr(inputwin, y_value, x_value, ws);
}

// TODO
// void clear_chart(WINDOW * inputwin, int max_lines, int max_columns, int col_gap, int origin_y, int origin_x){
// 
// }

void draw_axis(WINDOW * inputwin, int max_lines, int max_columns, int col_gap, int origin_y, int origin_x){

    mvwaddch(inputwin, origin_y - max_lines, origin_x, ACS_TTEE);
    mvwvline(inputwin, origin_y - max_lines + 1, origin_x, ACS_VLINE, max_lines-1);
    mvwaddch(inputwin, origin_y, origin_x, ACS_LLCORNER);
    mvwhline(inputwin, origin_y, origin_x+1, ACS_HLINE, max_columns * col_gap);
    mvwaddch(inputwin, origin_y, origin_x + (max_columns * col_gap) + 1, ACS_RTEE); 
}

void draw_max_value(WINDOW * inputwin, float max_value, int sigfigs, int max_lines, int origin_y, int origin_x){
    std::wstring ws = std::to_wstring(max_value);
    ws = ws.substr(0, sigfigs+1);
    int sze = ws.size();
    const wchar_t * wso = ws.c_str();
    mvwaddwstr(inputwin, origin_y - max_lines, origin_x - sze - 1, wso); 
}

void draw_bar(WINDOW * inputwin, float max_value, int max_lines, int col_gap, float y_value, int column, int origin_y, int origin_x, bool show_val, int sigfigs){

    float line_height = y_value / max_value * max_lines;

    float full_lines = floor(line_height);

    float remaining = line_height - full_lines;

    int rem_eights = (int)floor(remaining * 8);

    int ifull_lines = (int) full_lines;

    int x_value = origin_x+(column*col_gap)+2;

    const wchar_t * block_choice = nullptr;

    if(rem_eights == 1) {
        block_choice = L"\u2581";
    } else if(rem_eights == 2) {
        block_choice = L"\u2582";
    } else if(rem_eights == 3) {
        block_choice = L"\u2583";
    } else if(rem_eights == 4) {
        block_choice = L"\u2584";
    } else if(rem_eights == 5) {
        block_choice = L"\u2585";
    } else if(rem_eights == 6) {
        block_choice = L"\u2586";
    } else if(rem_eights == 7) {
        block_choice = L"\u2587";
    }

    for(int i = origin_y-1; i > origin_y - ifull_lines-1; i--){
        mvwaddwstr(inputwin, i, x_value, L"\u2588");
    }
    mvwaddwstr(inputwin, origin_y - ifull_lines-1, x_value, block_choice);

    // draw number
    if(show_val) {
        std::wstring ws = std::to_wstring(y_value);
        int length = std::min(col_gap-1, sigfigs);
        ws = ws.substr(0, length);
        int sze = ws.size();
        const wchar_t * wso = ws.c_str();
        mvwaddwstr(inputwin, origin_y - ifull_lines-2, x_value, wso); 
    }
}
