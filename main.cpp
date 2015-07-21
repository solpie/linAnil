//#include "view/MainWin.hpp"
#include <view/UiRoot.hpp>
#include "model/App.hpp"
#include "model/ImageLoader.hpp"
UiRoot *root = nullptr;

void onInitContext(void *e) {
    App()._().init();
    root = new UiRoot();
    ImageLoader()._().setContext(VG_CONTEXT);
    _app.test();
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