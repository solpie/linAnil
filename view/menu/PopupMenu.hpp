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
        height = 480;
        _title = "PopupMenu";
        add_event(MouseEvent::UP, onUp)
    }

    void onUp(void *e) {
        if (mouseY() > _titleHeigh) {
            int itemIdx = (mouseY() - _titleHeigh) / _itemHeight;
            _menuItems->at(itemIdx)->select();
            hide();
//            cout << typeid(this).name() << " menu item idx: " << itemIdx << endl;
        }
    }

    void show(std::string title, vector<MenuItem *> *menuItems, int width = 0) {
        move(VS_CONTEXT.cursor.x, VS_CONTEXT.cursor.y);
        _menuItems = menuItems;
        _title = title.c_str();
        if (width)
            this->width = width;
        height = _menuItems->size() * _itemHeight + 5 + _titleHeigh;
        visible = true;

    }

    void hide() {
        visible = false;
    }


protected:
    virtual void onDraw() override {
        int textY = 5;
        fillRoundRect(nvgRGBA(THEME_COLOR_PANEL, 200), gX(), gY(), width, height, VS_MENU_RADIUS)
        fillRect(nvgRGB(THEME_COLOR_TITLEBAR_BOTTOM_BORDER), gX() + VS_MENU_RADIUS, gY(), width - VS_MENU_RADIUS * 2, 1)
        //title
        nvgBeginPath(vg);
        nvgFontFace(vg, "sans");
        nvgFontSize(vg, THEME_FONT_SIZE_TITLE);
        nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
        nvgFillColor(vg, nvgRGB(240, 240, 240));
        nvgText(vg, gX() + 5, gY() + textY + 2, _title, nullptr);

        fillRect(nvgRGB(THEME_COLOR_PANEL_BORDER_DARK), gX(), gY() + _titleHeigh - 1, width, 1)

        //items
        textY = gY() + _titleHeigh + 2;
        if (_menuItems) {
            for (MenuItem *menuItem:*_menuItems) {
                nvgBeginPath(vg);
                nvgFontFace(vg, "sans");
                nvgFontSize(vg, THEME_FONT_SIZE_MENU_ITEM);
                nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
                nvgFillColor(vg, nvgRGB(240, 240, 240));
                nvgText(vg, gX() + 5, textY, menuItem->text.c_str(), nullptr);
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
    int _titleHeigh = 30;

};

#define _popupMenu PopupMenu()._()