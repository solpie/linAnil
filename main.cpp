#include "Stage.hpp"
Stage *stage = nullptr;

#include "view/timeline/WaveForm.hpp"
void test() {
    WaveForm w;
    w.test();
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
//    f->play("c:\\test");
//    MainWin *m = new MainWin();
//    m->show();
//    m->play();
//    App()._().test();
//    while (1) { }
//    while (!m->isClose) { }
}