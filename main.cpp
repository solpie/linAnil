#include "view/VsRoot.hpp"
#include "model/App.hpp"
#include "model/FileWatcher.hpp"

int main(int argc, char *argv[]) {
    App()._().start(argc, argv);
    FileWatcher *f = new FileWatcher();
    f->start("c:\\test");
    VsRoot *m = new VsRoot();
    m->start();
    App()._().test();
    while (!m->isClose){}
}