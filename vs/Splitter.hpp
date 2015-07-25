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
            if (_dir == Direction::Vertical)
                nvgRect(vg, _bar->gX(), _bar->gY(), _bar->width, _bar->height);
            else
                nvgRect(vg, _bar->gX(), _bar->gY(), _bar->width, _bar->height);
            nvgFillColor(vg, _3RGB(20));
            nvgFill(vg);
            if (isInRect(VS_CONTEXT.cursor.x, VS_CONTEXT.cursor.y, gX(), gY(), width, height)) {
                if (_isPress || _bar->isHover) {
                    if (_dir == Direction::Vertical)
                        VS_CONTEXT.setCursor(GLFW_VRESIZE_CURSOR);
                    else
                        VS_CONTEXT.setCursor(GLFW_HRESIZE_CURSOR);
                }
                else {
                    VS_CONTEXT.setCursor(GLFW_ARROW_CURSOR);
                }
            }


            if (_isPress) {
                pos mpos = VS_CONTEXT.cursor;
                int dx = 0, dy = 0;

                if (_dir == Direction::Vertical) {
                    VS_CONTEXT.setCursor(GLFW_VRESIZE_CURSOR);
                    if (_lastY)
                        dy = mpos.y - _lastY;
                    _lastY = mpos.y;
                    if (dy != 0) {

                        int my = _bar->y() + dy;
                        limit(my, 0, height - _bar->height)
                        _bar->setY(my);
                        child1->height = my;
                        child2->setY(_bar->y() + _bar->height);
                        child2->setSize(width, height - _bar->y() - _bar->height);
                    }
                }
                else {
                    //todo
                    VS_CONTEXT.setCursor(GLFW_HRESIZE_CURSOR);
                    if (_lastX)
                        dx = mpos.x - _lastY;
                    _lastX = mpos.x;
                    if (dx != 0) {
                        int mx = _bar->x() + dx;
                        limit(mx, 0, width - _bar->width)
                        _bar->setX(mx);
                        child1->width = mx;
                        child2->setX(_bar->x() + _bar->width);
                        child2->setSize(width - _bar->x() - _bar->width, height);
                    }
                }
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
            child1->setSize(w, _bar->y());
            child2->setSize(w, h - _bar->y() - _bar->height);
        }
        else {
            _bar->height = h;
            child1->setSize(_bar->x(), h);
            child2->setSize(w - _bar->x() - _bar->width, h);
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
