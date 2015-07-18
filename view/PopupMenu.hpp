#include "Sprite.hpp"

class PopupMenu : public Sprite {
public:
    PopupMenu() {
        add_event(MouseEvent::UP, onUp)
    }

    void onUp(void *e) {

    }

    void show() {

    }

    void hide() {

    }

private:
    int _itemHeight = 20;
};