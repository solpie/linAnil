#pragma once
//
// Created by manoyuria on 2015/7/10.
//

#include <oui/oui.h>
#include <oui/blendish.h>
#include <nanovg/nanovg.h>

#ifndef LINANIL_UI_HPP
#define LINANIL_UI_HPP

#endif //LINANIL_UI_HPP
//using namespace std;
#include "events/Event.hpp"
typedef enum {
    // label
            ST_LABEL = 0,
    // button
            ST_BUTTON = 1,
    // radio button
            ST_RADIO = 2,
    // progress slider
            ST_SLIDER = 3,
    // column
            ST_COLUMN = 4,
    // row
            ST_ROW = 5,
    // check button
            ST_CHECK = 6,
    // panel
            ST_PANEL = 7,
    // text
            ST_TEXT = 8,
    //
            ST_IGNORE = 9,

    ST_DEMOSTUFF = 10,
    // colored rectangle
            ST_RECT = 11,

    ST_HBOX = 12,
    ST_VBOX = 13,
} SubType;

int column() {
    int item = uiItem();
    uiSetBox(item, UI_COLUMN);
    return item;
}

int column_append(int parent, int item) {
    uiInsert(parent, item);
    // fill parent horizontally, anchor to previous item vertically
    uiSetLayout(item, UI_HFILL);
    uiSetMargins(item, 0, 1, 0, 0);
    return item;
}

typedef struct {
    int subtype;
    UIhandler handler;
} UIData;

typedef struct {
    UIData head;
    int iconid;
    const char *label;
} UIButtonData;

void drawUI(NVGcontext *vg, int item, int corners);

void drawUIItems(NVGcontext *vg, int item, int corners) {
    int kid = uiFirstChild(item);
    while (kid > 0) {
        drawUI(vg, kid, corners);
        kid = uiNextSibling(kid);
    }
}

void drawUI(NVGcontext *vg, int item, int corners) {
    const UIData *head = (const UIData *) uiGetHandle(item);
    UIrect rect = uiGetRect(item);
    if (uiGetState(item) == UI_FROZEN) {
        nvgGlobalAlpha(vg, BND_DISABLED_ALPHA);
    }
    if (head) {
        switch (head->subtype) {
            default: {
//                testrect(vg, rect);
                drawUIItems(vg, item, corners);
            }
                break;
//            case ST_HBOX: {
//                drawUIItemsHbox(vg, item);
//            }
//                break;
//            case ST_VBOX: {
//                drawUIItemsVbox(vg, item);
//            }
//                break;
//            case ST_PANEL: {
//                bndBevel(vg, rect.x, rect.y, rect.w, rect.h);
//                drawUIItems(vg, item, corners);
//            }
//                break;
//            case ST_LABEL: {
//                assert(head);
//                const UIButtonData *data = (UIButtonData *) head;
//                bndLabel(vg, rect.x, rect.y, rect.w, rect.h,
//                         data->iconid, data->label);
//            }
//                break;
            case ST_BUTTON: {
                const UIButtonData *data = (UIButtonData *) head;
                bndToolButton(vg, rect.x, rect.y, rect.w, rect.h,
                              corners, (BNDwidgetState) uiGetState(item),
                              data->iconid, data->label);
            }
                break;
//            case ST_CHECK: {
//                const UICheckData *data = (UICheckData *) head;
//                BNDwidgetState state = (BNDwidgetState) uiGetState(item);
//                if (*data->option)
//                    state = BND_ACTIVE;
//                bndOptionButton(vg, rect.x, rect.y, rect.w, rect.h, state,
//                                data->label);
//            }
//                break;
//            case ST_RADIO: {
//                const UIRadioData *data = (UIRadioData *) head;
//                BNDwidgetState state = (BNDwidgetState) uiGetState(item);
//                if (*data->value == item)
//                    state = BND_ACTIVE;
//                bndRadioButton(vg, rect.x, rect.y, rect.w, rect.h,
//                               corners, state,
//                               data->iconid, data->label);
//            }
//                break;
//            case ST_SLIDER: {
//                const UISliderData *data = (UISliderData *) head;
//                BNDwidgetState state = (BNDwidgetState) uiGetState(item);
//                static char value[32];
////                sprintf(value, "%.0f%%", (*data->progress) * 100.0f);
//                bndSlider(vg, rect.x, rect.y, rect.w, rect.h,
//                          corners, state,
//                          *data->progress, data->label, value);
//            }
//                break;
//            case ST_TEXT: {
//                const UITextData *data = (UITextData *) head;
//                BNDwidgetState state = (BNDwidgetState) uiGetState(item);
//                int idx = strlen(data->text);
//                bndTextField(vg, rect.x, rect.y, rect.w, rect.h,
//                             corners, state, -1, data->text, idx, idx);
//            }
//                break;
//            case ST_DEMOSTUFF: {
//                draw_demostuff(vg, rect.x, rect.y, rect.w, rect.h);
//            }
//                break;
//            case ST_RECT: {
//                const UIRectData *data = (UIRectData *) head;
//                if (rect.w && rect.h) {
//                    BNDwidgetState state = (BNDwidgetState) uiGetState(item);
//                    nvgSave(vg);
//                    nvgStrokeColor(vg, nvgRGBAf(data->color.r, data->color.g, data->color.b, 0.9f));
//                    if (state != BND_DEFAULT) {
//                        nvgFillColor(vg, nvgRGBAf(data->color.r, data->color.g, data->color.b, 0.5f));
//                    } else {
//                        nvgFillColor(vg, nvgRGBAf(data->color.r, data->color.g, data->color.b, 0.1f));
//                    }
//                    nvgStrokeWidth(vg, 2);
//                    nvgBeginPath(vg);
//#if 0
//                    nvgRect(vg,rect.x,rect.y,rect.w,rect.h);
//                    #else
//                    nvgRoundedRect(vg, rect.x, rect.y, rect.w, rect.h, 3);
//#endif
//                    nvgFill(vg);
//                    nvgStroke(vg);
//
//                    if (state != BND_DEFAULT) {
//                        nvgFillColor(vg, nvgRGBAf(0.0f, 0.0f, 0.0f, 1.0f));
//                        nvgFontSize(vg, 15.0f);
//                        nvgBeginPath(vg);
//                        nvgTextAlign(vg, NVG_ALIGN_TOP | NVG_ALIGN_CENTER);
//                        nvgTextBox(vg, rect.x, rect.y + rect.h * 0.3f, rect.w, data->label, nullptr);
//                    }
//
//                    nvgRestore(vg);
//                }
//                nvgSave(vg);
//                nvgIntersectScissor(vg, rect.x, rect.y, rect.w, rect.h);
//
//                drawUIItems(vg, item, corners);
//
//                nvgRestore(vg);
//            }
//                break;
        }
    } else {
//        testrect(vg, rect);
        drawUIItems(vg, item, corners);
    }

    if (uiGetState(item) == UI_FROZEN) {
        nvgGlobalAlpha(vg, 1.0);
    }
}

void demohandler(int item, UIevent event) {
    const UIButtonData *data = (const UIButtonData *) uiGetHandle(item);
//    cout<<"clicked:"<<uiGetHandle(item)<< data->label<<endl;
}

void roothandler(int parent, UIevent event) {
    switch (event) {
        default:
            break;
        case UI_SCROLL: {
            UIvec2 pos = uiGetScroll();
//            printf("scroll! %d %d\n", pos.x, pos.y);
        }
            break;
        case UI_BUTTON0_DOWN: {
//            printf("%d clicks\n", uiGetClicks());
        }
            break;
    }
}

int button(int iconid, const char *label, UIhandler handler) {
    // create new ui item
    int item = uiItem();
    // set size of widget; horizontal size is dynamic, vertical is fixed
    uiSetSize(item, 0, BND_WIDGET_HEIGHT);
    uiSetEvents(item, UI_BUTTON0_HOT_UP);
    // store some custom data with the button that we use for styling
    UIButtonData *data = (UIButtonData *) uiAllocHandle(item, sizeof(UIButtonData));
    data->head.subtype = ST_BUTTON;
    data->head.handler = handler;
    data->iconid = iconid;
    data->label = label;
    return item;
}