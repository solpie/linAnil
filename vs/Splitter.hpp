#include "Sprite.hpp"
#include "events/ErrorEvent.hpp"

class Splitter : public VsObjContainer {
public:
    Splitter(int dir) {
        _dir = dir;
        bar = new Sprite();
        if (_dir == Direction::Vertical) {
            bar->height = barWidth;
        }
        else {
            bar->width = barWidth;
        }
        bar->parent = this;

        add_event_on(bar, MouseEvent::DOWN, onDown)
        add_event_on(bar, MouseEvent::UP, onUp)
        add_event_on_context(VsEvent::STAGE_MOUSE_UP, onUp)

        add_event_on(bar, SpriteEvent::DRAW, onDrawBar)
    }

    void onUp(void *e) {
        _isPress = false;
    }

    void onDown(void *e) {
        _isPress = true;
        _lastX = _lastY = 0;
    }

    void onDrawBar(void *e) {
        if (numChildren() == 2) {
            nvgBeginPath(vg);
            nvgRect(vg, bar->gX(), bar->gY(), bar->width, bar->height);
            nvgFillColor(vg, _3RGB(20));
            nvgFill(vg);

            if (_isPress) {
                pos mpos = VS_CONTEXT.cursor;
                int dx = 0, dy = 0;

                if (_dir == Direction::Vertical) {
                    if (_lastY)
                        dy = mpos.y - _lastY;
                    _lastY = mpos.y;
                    if (dy != 0) {

                        int my = bar->y() + dy;
                        limit(my, 0, height - bar->height)
                        bar->setY(my);

                        child2->setY(bar->y() + bar->height);
                    }
                }
                else {
                    //todo
                }
//                if (_lastX)
//                    dx = mpos.x - _lastX;
//                _lastX = mpos.x;


            }
        }
    }

    virtual void addChild(VsObj *vsObj) override {
        int n = vsobjs->size();
        if (n == 0) {
            child1 = vsObj;
            if (_dir == Direction::Vertical) {
                bar->setY(vsObj->height);
            }
            else {
                bar->setX(vsObj->width);
            }
        }
        else if (n == 1) {
            child2 = vsObj;
            if (_dir == Direction::Vertical) {
                child2->setY(bar->y() + bar->height);
            }
            else {
                child2->setX(bar->x() + bar->width);
            }
        }
        else {
            throw runtime_error(ErrorEvent::FULL);
        }
        VsObjContainer::addChild(vsObj);
    }


    void resize(int w, int h) {
        width = w;
        height = h;
        if (_dir == Direction::Vertical) {
//            bar->setY(10);
            bar->width = w;
        }
        else {
//            bar->setX(10);
            bar->height = h;
        }
//        if(child1)
//            child1->resize()
    }

    virtual void render() override {
        VS_RENDER_CHILDREN();
        bar->render();

    }

    int barWidth = 8;

private:
    int _dir;
    bool _isPress = false;
    int _lastX, _lastY;
    VsObj *child1 = nullptr;
    VsObj *child2 = nullptr;
    Sprite *bar;
};
