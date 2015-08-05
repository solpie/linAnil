//
// Created by toramisu on 2015/7/29.
//
#pragma once

#include "VsObj.hpp"

class TextField : public Sprite {
public:
    TextField() {
        add_event_on_context(KeyEvent::UP, onKeyUp)
        add_event(MouseEvent::DOWN, onDown)
        textPosWidth = new vector<int>;
        isInteractive = true;
        height = 14;
    }

    void onKeyUp(void *e) {

    }

    void onDown(void *e) {
        if(textPosWidth->size())
        {
            for(int len:*textPosWidth)
            {
                if(mouseX()>len)
                {
                    _cursorPos = len;
                    break;
                }
            }
        }
//        mouseX()
    }

    void setText(string t) {
        _text = t;
        isChangeText = true;
        _textLength = t.length();
        nvgSave(vg);
        textPosWidth->clear();
        int tWidth;
        for (int i = 0; i < _textLength; ++i) {
            nvgFontFace(vg, "sans");
            nvgFontSize(vg, _fontSize);
            nvgTextAlign(vg, _align);
            nvgFillColor(vg, _col);
            tWidth = nvgText(vg, gX(), gY(), _text.substr(0, i+1).c_str(), nullptr);
//            textPosWidth->push_back(tWidth);
            textPosWidth->insert(textPosWidth->begin(), tWidth);
        }
        nvgRestore(vg);
    }

    void setColor(NVGcolor col) {
        _col = col;
    }

    void setFontSize(int size) {
        _fontSize = size;
    }

    void setAlign(int align) {
        _align = align;
    }

protected:
    virtual void onDraw() override {
        //
        if(_cursorPos)
        {
            fillRect(_3RGB(200),gX()+_cursorPos,gY(),2,height)

        }
        nvgFontFace(vg, "sans");
        nvgFontSize(vg, _fontSize);
        nvgTextAlign(vg, _align);
        nvgFillColor(vg, _col);
        if (isChangeText) {
            isChangeText = false;
            _textWidth = nvgText(vg, gX(), gY(), _text.c_str(), nullptr);
            width = _textWidth;
        }
        else
            nvgText(vg, gX(), gY(), _text.c_str(), nullptr);

        VS_RENDER_CHILDREN();
    }

private:
    int _align = NVG_ALIGN_LEFT | NVG_ALIGN_TOP;
    int _cursorPos = 0;
    int _textLength = 0;
    bool isChangeText = false;
    float _textWidth = 0;
    vector<int> *textPosWidth;
    string _text;
    NVGcolor _col = nvgRGB(240, 240, 240);
    float _fontSize = 14.0f;
};

