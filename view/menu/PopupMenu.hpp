#pragma once

#include "Sprite.hpp"
#include "MenuItem.hpp"
#include "model/Settings.hpp"
#include "Theme.hpp"

class PopupMenu : public Sprite, public Singleton<PopupMenu> {
public:
    void init(VsObjContainer *parent) {
        parent->addChild(this);
        width = 320;
        height = 600;
        _title = "PopupMenu";
        add_event(MouseEvent::UP, onUp)
    }

    void onUp(void *e) {

    }

    void show(std::string title, vector<MenuItem *> *menuItems) {
        _menuItems = menuItems;
        _title = title.c_str();
        height = _menuItems->size() * _itemHeight + 5;
    }

    void hide() {

    }


protected:
    virtual void onDraw() override {
        int textY = 5;
        fillRoundRect(nvgRGBA(THEME_COLOR_PANEL, 180), gX(), gY(), width, height,VS_MENU_RADIUS)
        fillRect(nvgRGB(THEME_COLOR_TITLEBAR_BOTTOM_BORDER), gX()+VS_MENU_RADIUS, gY(), width-VS_MENU_RADIUS*2, 1)
        //title
        nvgBeginPath(vg);
        nvgFontFace(vg, "sans");
        nvgFontSize(vg, THEME_FONT_SIZE_TITLE);
        nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
        nvgFillColor(vg, nvgRGB(240, 240, 240));
        nvgText(vg, gX() + 5, gY() + textY + 2, _title, nullptr);

        //items
        textY = gY() + 5;
        if (_menuItems) {
            for (MenuItem *menuItem:*_menuItems) {
                nvgBeginPath(vg);
                nvgFontFace(vg, "sans");
                nvgFontSize(vg, THEME_FONT_SIZE_NORMAL);
                nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
                nvgFillColor(vg, nvgRGB(240, 240, 240));
                nvgText(vg, gX() + 4, textY, menuItem->c_str(), nullptr);
                textY += _itemHeight;
            }
        }

        vsDropShadow(vg, gX(), gY(), width, height, VS_MENU_RADIUS, VS_MENU_SHADOW_FEATHER, VS_MENU_SHADOW_ALPHA);
        VS_RENDER_CHILDREN();
    }

private:
    const char *_title;
    vector<MenuItem *> *_menuItems = nullptr;
    int _itemHeight = 20;
};

#define _popupMenu PopupMenu()._()