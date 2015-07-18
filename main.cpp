//#include "view/MainWin.hpp"
#include <view/UiRoot.hpp>
#include "model/App.hpp"

UiRoot *root = nullptr;

void onInitContext(void *e) {
    root = new UiRoot();

}

int main(int argc, char *argv[]) {
    App()._().start(argc, argv);
    VS_CONTEXT.add(VsEvent::INITED, onInitContext);
    VS_CONTEXT.run();
//    FileWatcher *f = new FileWatcher();
//    f->start("c:\\test");
//    MainWin *m = new MainWin();
//    m->show();
//    m->start();
//    App()._().test();
//    while (1) { }
//    while (!m->isClose) { }
}