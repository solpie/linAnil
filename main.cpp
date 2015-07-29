#include <windows.h>
#include <mmsystem.h>

#include "Stage.hpp"

Stage *stage = nullptr;
//test
//#include "model/AudioTrackInfo.hpp"
#include "view/playback/portaudioTest.hpp"
//#include "view/playback/OpenAltest.hpp"
//#include "view/playback/SDLtes1t.hpp"


void test() {
//    WaveForm w;
//    w.test();
//    test1();
//    test2("test\\test.wav");
//    test2("test\\test3.wav");
//    test6();
//    test3();
//    test5();
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