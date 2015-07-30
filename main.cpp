#include <windows.h>
#include <mmsystem.h>

#include "Stage.hpp"

Stage *stage = nullptr;

#include "test/Test.hpp"
void onInitContext(void *e) {
    App()._().init();
    stage = new Stage();

    ImageLoader()._().setContext(VG_CONTEXT);
    _app.test();
    testMain();
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