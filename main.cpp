#include "view/MainWin.hpp"
#include "model/App.hpp"
int main(int argc, char *argv[]) {
//    App::_().start(argc, argv);
    MainWin *m = new MainWin();
    m->show();

}