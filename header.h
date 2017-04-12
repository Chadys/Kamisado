//
// Created by julie on 07/04/17.
//

#ifndef KAMISADO_HEADER_H
#define KAMISADO_HEADER_H



struct coord{
    int x;
    int y;
};


// All options to customize a terminal
enum TERMINAL_STYLES{
    RESET,
    BOLD,
    DARK,
    ITALIC,
    UNDERLINE,
    EXPANDED,
    BG,
    TRANSPARENT,
    STROKE,

    BLACK,
    RED,
    GREEN,
    BROWN,
    DARKBLUE,
    PURPLE,
    DARKCYAN,
    GRAY,

    DARKGRAY,
    BRIGHTRED,
    BRIGHTGREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE,

    BG_BLACK,
    BG_RED,
    BG_GREEN,
    BG_BROWN,
    BG_DARKBLUE,
    BG_PURPLE,
    BG_DARKCYAN,
    BG_GRAY,

    BG_DARKGRAY,
    BG_BRIGHTRED,
    BG_BRIGHTGREEN,
    BG_YELLOW,
    BG_BLUE,
    BG_MAGENTA,
    BG_CYAN,
    BG_WHITE
};

inline const char *codeFromStyle(enum TERMINAL_STYLES s)
{
    static char const *strings[] = {"\e[0m", "\e[1m", "\e[2m", "\e[3m", "\e[4m", "\e[6m", "\e[7m", "\e[8m", "\e[9m",
                              "\e[30m", "\e[31m", "\e[32m", "\e[33m", "\e[34m", "\e[35m", "\e[36m", "\e[37m",
                              "\e[90m", "\e[91m", "\e[92m", "\e[93m", "\e[94m", "\e[95m", "\e[96m", "\e[97m",
                              "\e[40m", "\e[41m", "\e[42m", "\e[43m", "\e[44m", "\e[45m", "\e[46m", "\e[47m",
                              "\e[100m", "\e[101m", "\e[102m", "\e[103m", "\e[104m", "\e[105m", "\e[106m", "\e[107m"};

    return strings[s];
}

inline TERMINAL_STYLES invert_color(TERMINAL_STYLES color){
    if (color == WHITE)
        return BLACK;
    return WHITE;
}



template<class InputIterator, class T>
InputIterator ptr_find (InputIterator first, InputIterator last, const T& val)
{
    while (first!=last) {
        if (**first==val)
            break;
        ++first;
    }
    return first;
}

#endif //KAMISADO_HEADER_H
