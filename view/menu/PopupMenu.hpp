#pragma once

#include "Sprite.hpp"
#include "MenuItem.hpp"
#include "model/Configs.hpp"
#include "Theme.hpp"

class PopupMenu : public Sprite, public Singleton<PopupMenu> {
public:
    void init(VsObjContainer *parent) {
        if (!isInit) {
            isInit = true;
            parent->addChild(this);
            width = 320;
            height = 480;
            _title = "PopupMenu";
            add_event(MouseEvent::UP, onUp)
        }
    }

    void onUp(void *e) {
        if (mouseY() > _titleHeight) {
            int itemIdx = (mouseY() - _titleHeight) / _itemHeight;
            _menuItems->at(itemIdx)->select();
            hide();
//            cout << typeid(this).name() << " menu item idx: " << itemIdx << endl;
        }
    }

    void show(std::string title, vector<MenuItem *> *menuItems, int width = 0) {
        move(VS_CONTEXT.cursor.x - 20, VS_CONTEXT.cursor.y - _titleHeight - 5);
        _menuItems = menuItems;
        _title = title.c_str();
        if (width)
            this->width = width;
        height = _menuItems->size() * _itemHeight + 5 + _titleHeight;
        visible = true;

    }

    void hide() {
        visible = false;
    }


protected:
    bool isInit = false;

    virtual void onDraw() override {
        //auto hide
        if (mouseX() < -50 || mouseY() < -30 || mouseY() > height + 100 || mouseX() > width + 100) {
            hide();
        }
        //
        fillRoundRect(nvgRGBA(THEME_COLOR_PANEL, 200), gX(), gY(), width, height, THEME_MENU_RADIUS)
        fillRect(nvgRGB(THEME_COLOR_TITLEBAR_BOTTOM_BORDER), gX() + THEME_MENU_RADIUS, gY(),
                 width - THEME_MENU_RADIUS * 2, 1)
        //title
        nvgBeginPath(vg);
        nvgFontFace(vg, "sans");
        nvgFontSize(vg, THEME_FONT_SIZE_TITLE);
        nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
        nvgFillColor(vg, nvgRGB(240, 240, 240));
        nvgText(vg, gX() + 5, gY() + 10, _title, nullptr);


        //items
        int textY = gY() + _titleHeight + 2;
        if (_menuItems) {
            int gmy = VS_CONTEXT.cursor.y;
            bool isSelect = false;
            for (MenuItem *menuItem:*_menuItems) {
                isSelect = (gmy > textY && gmy < textY + _itemHeight) && isHover;
                if (isSelect) {
                    fillRect(nvgRGB(THEME_MENU_COL_SELECT), gX() + 1, textY + 2, 4, _itemHeight - 2)
                }

                nvgBeginPath(vg);
                nvgFontFace(vg, "sans");
                nvgFontSize(vg, THEME_FONT_SIZE_MENU_ITEM);
                nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
                if (isSelect)
                    nvgFillColor(vg, nvgRGB(THEME_MENU_COL_SELECT_TEXT));
                else
                    nvgFillColor(vg, nvgRGB(240, 240, 240));
                nvgText(vg, gX() + 10, textY, menuItem->text.c_str(), nullptr);
//                if (!isSelect) {
                fillRect(nvgRGB(THEME_COLOR_PANEL_BORDER_DARK), gX(), textY, width, 1)
                fillRect(nvgRGB(THEME_COL_PANEL_BORDER_LIGHT), gX(), textY + 1, width, 1)
//                }
                textY += _itemHeight;
            }
        }

        vsDropShadow(vg, gX(), gY(), width, height, THEME_MENU_RADIUS, THEME_MENU_SHADOW_FEATHER,
                     THEME_MENU_SHADOW_ALPHA);
        VS_RENDER_CHILDREN();
    }

private:
    const char *_title;
    vector<MenuItem *> *_menuItems = nullptr;
    int _itemHeight = 20;
    int _titleHeight = 30;

};

#define _popupMenu PopupMenu()._()