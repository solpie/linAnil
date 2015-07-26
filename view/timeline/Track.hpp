//
// Created by toramisu on 2015/7/13.
//
#pragma once
#ifndef LINANIL_TRACK_HPP
#define LINANIL_TRACK_HPP

#endif //LINANIL_TRACK_HPP

#include <vs/Slider.hpp>
#include <vs/CheckBox.hpp>
#include "vs/Sprite.hpp"

enum PressFlag {
    Left = 1, Right
};

class Track : public OneLinker<Track>, public Sprite {
public:
    Track(TrackInfo *trackInfo) {
        _trackInfo = trackInfo;

        width = 1024;
        height = 55;

        trackVisibleBox = new CheckBox();
        trackVisibleBox->isChecked = true;
        trackVisibleBox->setX(200);
        trackVisibleBox->setY(10);
        addChild(trackVisibleBox);

        vSlider = new Slider();
        vSlider->setValue(100);
        vSlider->setX(200);
        vSlider->setY(32);
        addChild(vSlider);

        add_event(MouseEvent::DOWN, onDown);
        add_event(MouseEvent::UP, onUp);
        add_event_on_context(MouseEvent::UP, onUp)

        setColor(99, 138, 20);
    }

    void setTrackInfo(TrackInfo *trackInfo) {
        _trackInfo = trackInfo;
    }

    void onUp(void *e) {
        if (_isPress && isDragHide) {
            VS_CONTEXT.showCursor();
//            if (_pressFlag == PressFlag::Left)
            VS_CONTEXT.setCursorPos(_hideX, _hideY);
//            else if(_pressFlag == PressFlag::Right))
//                V
            _proj->curCompInfo->clearRemoveFrame();
        }
        _pressFlag = 0;
        _isPress = false;
        _handleTrackFrameInfo = nullptr;
    }

    void onDown(void *e) {
        _lastX = _lastY = 0;
        _hideX = VS_CONTEXT.cursor.x;
        _hideY = VS_CONTEXT.cursor.y;
        _isPress = true;
        VsEvent *vse = new VsEvent();
        vse->type = VsEvent::SELECTED;
        disEvent(vse);
        setSelected(true);
    }

    void setSelected(bool v) {
        cout << this << " setSelected() " << _trackInfo->name << endl;
        _trackInfo->isSelected = v;
        if (v) _proj->curCompInfo->dumpTrackFrameIdx(_trackInfo);
    }

    void setColor(int r, int g, int b) {
        _trackInfo->color.r = r;
        _trackInfo->color.g = g;
        _trackInfo->color.b = b;
        float h, s, v;
        RGBtoHSV(r, g, b, h, s, v);
        limit(v, v + 30, 255)
        float lightR, lightG, lightB;
        HSVtoRGB(h, s, v, lightR, lightG, lightB);
        selColor.r = lightR;
        selColor.g = lightG;
        selColor.b = lightB;
    }

    virtual void onDraw() override {
        if (parent && gY() < parent->gY())
            return;
        {//bg
            nvgBeginPath(vg);
            nvgRect(vg, gX(), gY(), width, height);
            if (_trackInfo->isSelected)
                nvgFillColor(vg, nvgRGBA(selColor.r, selColor.g, selColor.b, 255));
            else
                nvgFillColor(vg, nvgRGBA(_trackInfo->color.r, _trackInfo->color.g, _trackInfo->color.b, 255));
            nvgFill(vg);
        }

        {//track name
            nvgFontFace(vg, "sans");
            nvgFontSize(vg, 14.0f);
            nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
            nvgFillColor(vg, nvgRGBA(240, 240, 240, 192));
            nvgText(vg, gX() + 5, gY() + 5, _trackInfo->name.c_str(), nullptr);
        }

        drawTrackFrame();


        //bottom border
        fillRect(_3RGB(52), gX(), gY() + height - 1, width, 1);

        VsObjContainer::render();
    }

    void scrollX(int x) {
        _scrollPosX = -x + _trackLeft;
    }


private:
    int _trackDragBarHeight = 13;
    bool _isPress = false;
    bool _isPressFrameLeft, _isPressFrameRight;
    TrackFrameInfo *_handleTrackFrameInfo = nullptr;
    int frameHeight = 40;

    void drawTrackFrame() {
        //trackFrame
        int left = _scrollPosX;
        int frameWidth = _proj->curCompInfo->frameWidth;

        int thumbHeight = 0;
        int thumbWidth;
        int thumbY = 0;

        int tx;
        int hoverTx = 0;
        int hoverTWidth = 0;
        bool isHoverLeft = false;

        int trackStartX = _trackInfo->getStartFrame() * frameWidth;
        int dragBarX = 0;
        bool hasThumbDrawing = false;
        int lastTrackFrameHoldCount = 0;
        bool isCut = false;
        int currentRenderFrame = _proj->curCompInfo->getCurrentFrame();
        for (TrackFrameInfo *tfi:*_trackInfo->trackFrameInfos) {
            lastTrackFrameHoldCount = tfi->getHoldFrame();
            tx = gX() + left + trackStartX;
            if (thumbHeight == 0) {
                thumbHeight = frameWidth * tfi->imageInfo->height / tfi->imageInfo->width;
                thumbY = gY() + _trackDragBarHeight - (thumbHeight - frameHeight) * .5;
                dragBarX = tx;
                if (dragBarX < gX() + _trackLeft)
                    dragBarX = gX() + _trackLeft;
            }

            {//update render frame idx
                if (currentRenderFrame > -1 && currentRenderFrame >= tfi->getStartFrame() &&
                    currentRenderFrame <= tfi->getEndFrame()) {
                    _trackInfo->setCurrenTrackFrameIdx(tfi->getIdx());
                    currentRenderFrame = -1;//break;
                }
            }

            thumbWidth = frameWidth * tfi->getHoldFrame();
            if (tx < gX() + _trackLeft) {
                left += thumbWidth;
                if (tx + frameWidth > gX() + _trackLeft) {
                    isCut = true;
                    nvgScissor(vg, gX() + _trackLeft, gY(), frameWidth, height);
                }
                else
                    continue;
            }
            else
                left += thumbWidth;

            hasThumbDrawing = true;
            //white bg
            fillRect(_3RGB(255), tx, gY() + _trackDragBarHeight, frameWidth, frameHeight);

            //thumb
            nvgBeginPath(vg);
            nvgRect(vg, tx, thumbY, frameWidth, thumbHeight);
            nvgFillPaint(vg,
                         nvgImagePattern(vg, tx, thumbY, frameWidth, thumbHeight, 0,
                                         tfi->imageInfo->id, 1));
            nvgFill(vg);

            //frame
            nvgBeginPath(vg);
            vsLineWidthColor(vg, 1, _3RGB(20));
            vsLineRect(vg, tx, gY() + _trackDragBarHeight, frameWidth * tfi->getHoldFrame(), frameHeight);
            nvgFill(vg);
            if (isCut) {
                isCut = false;
                nvgResetScissor(vg);
            }
            //hover check
            if (hoverTx == 0 &&
                isInRect(VS_CONTEXT.cursor.x, VS_CONTEXT.cursor.y, tx, gY() + _trackDragBarHeight, thumbWidth,
                         frameHeight)) {
                hoverTx = tx;
                hoverTWidth = tfi->getHoldFrame() * frameHeight;
                if (!_isPress) {
                    if (VS_CONTEXT.cursor.x < tx + thumbWidth * .5) {
                        isHoverLeft = true;
                        _pressFlag = PressFlag::Left;
                    }
                    else
                        _pressFlag = PressFlag::Right;

                }
                else if (!_handleTrackFrameInfo)
                    _handleTrackFrameInfo = tfi;
            }
        }

        //drag bar
        if (hasThumbDrawing && lastTrackFrameHoldCount) {
            int dragWidth = tx + lastTrackFrameHoldCount * frameWidth - dragBarX + 1;
            fillRect(_3RGB(20), dragBarX, gY() + 1, dragWidth, _trackDragBarHeight);
        }

        if (hoverTx != 0) {//hover mask
            if (!_isPress)
                drawBlockHint(isHoverLeft, hoverTx, hoverTWidth);
            else
                handlePressAndDrag(hoverTx, hoverTx + hoverTWidth);
        }
    }

    void drawBlockHint(bool isHoverLeft, int hoverTx, int hoverTWidth) {
        //left block
        int blockWidth = 5;
        int blockY = gY() + _trackDragBarHeight + 1;
        NVGcolor colorL = nvgRGB(COLOR_TRACK_THUMB_BLOCK);
        NVGcolor colorR = nvgRGBA(COLOR_TRACK_THUMB_BLOCK, 128);
        if (isHoverLeft) {
            colorL = nvgRGBA(COLOR_TRACK_THUMB_BLOCK, 128);
            colorR = nvgRGB(COLOR_TRACK_THUMB_BLOCK);
        }
        fillRect(colorL, hoverTx - 5, blockY, blockWidth, frameHeight - 2);
        fillRect(colorR, hoverTx + hoverTWidth, blockY, blockWidth, frameHeight - 2);
    }

    void drawArrowHint() {
        //            thumbHeight = 45;
//            int s1 = 10, s2 = 15, s3 = 7, p4 = 15;
//            //left arrow
//            nvgBeginPath(vg);
//            nvgMoveTo(vg, hoverTx, gY() + _trackDragBarHeight + s1);
//            nvgLineTo(vg, hoverTx - s2, gY() + _trackDragBarHeight + s1);
//            nvgLineTo(vg, hoverTx - s2, gY() + _trackDragBarHeight + s1 - s3);
//            nvgLineTo(vg, hoverTx - s2 - p4, gY() + _trackDragBarHeight + s1 - s3 + p4);
//            nvgLineTo(vg, hoverTx - s2, gY() + _trackDragBarHeight + s1 - s3 + p4 + p4);
//            nvgLineTo(vg, hoverTx - s2, gY() + _trackDragBarHeight + s1 - s3 + p4 + p4 - s3);
//            nvgLineTo(vg, hoverTx, gY() + _trackDragBarHeight + s1 - s3 + p4 + p4 - s3);
//            nvgLineTo(vg, hoverTx, gY() + _trackDragBarHeight + s1);
//            nvgFillColor(vg, nvgRGB(COLOR_TITLEBAR_BOTTOM_BORDER));
//            nvgFill(vg);
//
//
//            hoverTx += frameWidth;
//            //right arrow
//            nvgBeginPath(vg);
//            nvgMoveTo(vg, hoverTx, gY() + _trackDragBarHeight + s1);
//            nvgLineTo(vg, hoverTx +s2, gY() + _trackDragBarHeight + s1);
//            nvgLineTo(vg, hoverTx + s2, gY() + _trackDragBarHeight + s1 - s3);
//            nvgLineTo(vg, hoverTx + s2 + p4, gY() + _trackDragBarHeight + s1 - s3 + p4);
//            nvgLineTo(vg, hoverTx + s2, gY() + _trackDragBarHeight + s1 - s3 + p4 + p4);
//            nvgLineTo(vg, hoverTx + s2, gY() + _trackDragBarHeight + s1 - s3 + p4 + p4 - s3);
//            nvgLineTo(vg, hoverTx, gY() + _trackDragBarHeight + s1 - s3 + p4 + p4 - s3);
//            nvgLineTo(vg, hoverTx, gY() + _trackDragBarHeight + s1);
//            nvgFillColor(vg, nvgRGB(COLOR_TITLEBAR_BOTTOM_BORDER));
//            nvgFill(vg);
    }

    int _dragSense = 30;
    bool isDragHide = false;
    int _pressFlag = 0;


    void handlePressAndDrag(int left, int right) {
        pos *mpos = &VS_CONTEXT.cursor;
        int dx = 0;
        int frameWidth = _proj->curCompInfo->frameWidth;
        if (_lastX)
            dx = mpos->x - _lastX;
        else
            _lastX = mpos->x;
        if (dx != 0) {
            VS_CONTEXT.hideCursor();
            if (_pressFlag == PressFlag::Left) {
                if (dx > _dragSense) {
                    //fixme when _dragSense < frameWidth
                    isDragHide = true;
                    //fixme call L2R L2L when mouse up
                    _proj->curCompInfo->L2R(_handleTrackFrameInfo, _trackInfo);
                    _hideX += frameWidth;
                    _lastX = mpos->x;

                }
                else if (dx < -_dragSense) {
                    isDragHide = true;
                    _proj->curCompInfo->L2L(_handleTrackFrameInfo, _trackInfo);
                    _lastX = mpos->x;
                    _hideX -= frameWidth;

                }
            }
            else if (_pressFlag == PressFlag::Right) {
                cout << typeid(this).name() << " press R move: " << dx
                << " handle: " << _handleTrackFrameInfo->getIdx()
                << endl;
                if (dx > _dragSense) {
                    _proj->curCompInfo->R2R(_handleTrackFrameInfo);
                    isDragHide = true;
                    _hideX += frameWidth;
                    _lastX = mpos->x;
                }
                else if (dx < -_dragSense && _handleTrackFrameInfo->getHoldFrame() > 1) {
                    _proj->curCompInfo->R2L(_handleTrackFrameInfo);
                    isDragHide = true;
                    _hideX -= frameWidth;
                    _lastX = mpos->x;
                }
            }
        }

    }

    int _hy;
    int _trackLeft = TIMELINE_TRACK_PANEL_DEF_WIDTH;
    int _scrollPosX = _trackLeft;
    int _lastX, _lastY;
    int _hideX, _hideY;
    VsColor selColor;
    TrackInfo *_trackInfo;
    Slider *vSlider;
    CheckBox *trackVisibleBox;
};
