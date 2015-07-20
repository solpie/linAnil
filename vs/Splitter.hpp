#include "Sprite.hpp"
#include "events/ErrorEvent.hpp"

class Splitter : public VsObjContainer {
public:
    Splitter(int dir) {
        _dir = dir;
        _bar = new Sprite();
        if (_dir == Direction::Vertical) {
            _bar->height = barWidth;
        }
        else {
            _bar->width = barWidth;
        }
        _bar->parent = this;

        add_event_on(_bar, MouseEvent::DOWN, onDown)
        add_event_on(_bar, MouseEvent::UP, onUp)
        add_event_on_context(VsEvent::STAGE_MOUSE_UP, onUp)

        add_event_on(_bar, SpriteEvent::DRAW, onDrawBar)
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
            nvgRect(vg, _bar->gX(), _bar->gY(), _bar->width, _bar->height);
            nvgFillColor(vg, _3RGB(20));
            nvgFill(vg);
            if (_isPress || _bar->isHover) {
//                glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);
                VS_CONTEXT.setCursor(GLFW_VRESIZE_CURSOR);
            }
            else {
                VS_CONTEXT.setCursor(GLFW_ARROW_CURSOR);
            }

            if (_isPress) {
                glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);
                pos mpos = VS_CONTEXT.cursor;
                int dx = 0, dy = 0;

                if (_dir == Direction::Vertical) {
                    if (_lastY)
                        dy = mpos.y - _lastY;
                    _lastY = mpos.y;
                    if (dy != 0) {

                        int my = _bar->y() + dy;
                        limit(my, 0, height - _bar->height)
                        _bar->setY(my);
                        child1->height = my;
                        child2->setY(_bar->y() + _bar->height);
                        int h2 =  height - _bar->y() - _bar->height;
                        child2->setSize(width, h2);
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
                _bar->setY(vsObj->height);
            }
            else {
                _bar->setX(vsObj->width);
            }
        }
        else if (n == 1) {
            child2 = vsObj;
            if (_dir == Direction::Vertical) {
                child2->setY(_bar->y() + _bar->height);
            }
            else {
                child2->setX(_bar->x() + _bar->width);
            }
        }
        else {
            throw runtime_error(ErrorEvent::FULL);
        }
        VsObjContainer::addChild(vsObj);
    }


    void setSize(int w, int h) override {
        VsObj::setSize(w, h);
        if (_dir == Direction::Vertical) {
            _bar->width = w;
            int h2 =  h - _bar->y() - _bar->height;
            child2->setSize(w, h2);
        }
        else {
            _bar->height = h;
        }
    }

    virtual void render() override {
        VS_RENDER_CHILDREN();
        _bar->render();
    }

    int barWidth = 8;
private:
    int _dir;
    bool _isPress = false;
    int _lastX, _lastY;
    VsObj *child1 = nullptr;
    VsObj *child2 = nullptr;
    Sprite *_bar;
};
