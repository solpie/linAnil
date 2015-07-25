#include "Stage.hpp"
#include "model/App.hpp"

Stage *stage = nullptr;

#include "vs/utils/VsTimer.hpp"
VsTimer *t;
void test() {
    t = new VsTimer(1000);
    t->start();
}

void onInitContext(void *e) {
    App()._().init();
    stage = new Stage();

    ImageLoader()._().setContext(VG_CONTEXT);
    _app.test();
    test();
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