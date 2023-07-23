#include "../include/figures.h"
#include <windows.h>

const char *pos_0 = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

int main(){
    SetConsoleOutputCP(CP_UTF8);
    _figure fig(pos_0);
    std::cout<<fig;
}