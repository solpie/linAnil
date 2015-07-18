#include "Sprite.hpp"

class Viewport : public VsObjContainer {

public:
    Viewport() {
        height = 720;
    }

    void render() override {
        nvgBeginPath(vg);
        nvgRect(vg, gX(), gY(), width, height);
        nvgFillColor(vg, _3RGB(80));
        nvgFill(vg);

        VS_RENDER_CHILDREN();
    }
    void resize(int w,int h)
    {
        width = w;
//        height = h;
    }
private:
    Sprite *transport;
};