//
// Created by toramisu on 2015/7/13.
//
#pragma once
#ifndef LINANIL_TRACK_HPP
#define LINANIL_TRACK_HPP

#endif //LINANIL_TRACK_HPP

#include <vs/Slider.hpp>
#include <vs/CheckBox.hpp>
#include "BaseTrack.hpp"
#include "TextField.hpp"

enum PressFlag {
    Left = 1, Right
};

class Track : public BaseTrack {
public:
    Track(TrackInfo *trackInfo) : BaseTrack((BaseTrackInfo *) trackInfo) {
        _trackInfo = trackInfo;

        _exHandleL = new Sprite;
        _exHandleR = new Sprite;
        _exHandleL->setSize(35, 50);
        _exHandleR->setSize(35, 50);
        _exHandleL->isInteractive = true;
        _exHandleR->isInteractive = true;
        addChild(_exHandleL);
        addChild(_exHandleR);
        add_event(MouseEvent::UP, onUp);
        add_event_on_context(MouseEvent::UP, onUp)
        setColor(52, 52, 52);

        TextField *input = new TextField;
        input->setText("lwlbgllpl");
        input->move(5, 28);
        addChild(input);

        TextField *input2 = new TextField;
        input2->setText("wwwww");
        input2->move(5, 40);
        addChild(input2);
    }

    void setTrackInfo(TrackInfo *trackInfo) {
        _trackInfo = trackInfo;
    }

    void onUp(void *e) {
        if (_isPress && isDragHide) {
//            VS_CONTEXT.showCursor();
//            if (_pressFlag == PressFlag::Left)
//            VS_CONTEXT.setCursorPos(_hideX, _hideY);
//            else if(_pressFlag == PressFlag::Right))
//                V
            _proj->curCompInfo->clearRemoveFrame();
        }
        _pressFlag = 0;


        _isPress = false;
        if (_handleTrackFrameInfo) {
            dumpTrackFrameInfo(_handleTrackFrameInfo);
        }
        _handleTrackFrameInfo = nullptr;
    }

    void onDown(void *e) override {
        BaseTrack::onDown(e);
        _lastX = _hideX = VS_CONTEXT.cursor.x;
        _lastY = _hideY = VS_CONTEXT.cursor.y;
        _isPress = true;

    }

    void setSelected(bool v) override {
        BaseTrack::setSelected(v);
        if (v) _proj->curCompInfo->dumpTrackFrameIdx(_trackInfo);
    }


    virtual void onDraw() override {
        BaseTrack::drawBase();
        drawTrackFrame();
        VS_RENDER_CHILDREN();
    }


private:
    int _trackDragBarHeight = 13;
    bool _isPress = false;
    bool _isPressFrameLeft, _isPressFrameRight;
    TrackFrameInfo *_handleTrackFrameInfo = nullptr;
    int frameHeight = 40;

//    void drawFrameIdx()
//    {
//
//    }
    void drawTrackFrame() {
        int frameWidth = _proj->curCompInfo->frameWidth;

        //drag bar
        int dragBarX = 0;
        int dragBarWidth = 0;

        dragBarX = gX() + _trackInfo->getStartFrame() * frameWidth + _scrollPosX;
        if (dragBarX < gX() + _trackPanelWidth)
            dragBarX = gX() + _trackPanelWidth;
        int lastFrameX = (_trackInfo->getEndFrame() + 1) * frameWidth + _scrollPosX;
//        int lastTrackFrameHoldCount = _trackInfo->trackFrameInfos->back()->getHoldFrame();

        dragBarWidth = lastFrameX - dragBarX;
        bool isPressDragBar = false;
        isPressDragBar = drawDragBar(dragBarX, dragBarWidth);
        //expand handle
        drawExHandle(dragBarX, lastFrameX);

        //trackFrame
        int left = _scrollPosX;

        int thumbHeight = 0;
        int thumbWidth;
        int thumbY = 0;

        int tx;
        int hoverTx = 0;
        int hoverTWidth = 0;
        bool isHoverLeft = false;

        int trackStartX = _trackInfo->getStartFrame() * frameWidth;
        bool isCut = false;
        int currentRenderFrame = _proj->curCompInfo->getCurrentFrame();
        int frameBgY = gY() + _trackDragBarHeight;

        for (TrackFrameInfo *tfi:*_trackInfo->trackFrameInfos) {
            tx = gX() + left + trackStartX;
            if (thumbHeight == 0) {
                thumbHeight = frameWidth * tfi->imageInfo->height / tfi->imageInfo->width;
                thumbY = gY() + _trackDragBarHeight - (thumbHeight - frameHeight) * .5;
            }

            //update render frame idx
            if (currentRenderFrame > -1
                && currentRenderFrame >= tfi->getStartFrame() + _trackInfo->getStartFrame() - 1
                && currentRenderFrame <= tfi->getEndFrame() + _trackInfo->getStartFrame() - 1) {
                _trackInfo->setCurrenTrackFrameIdx(tfi->getIdx());
                currentRenderFrame = -1;//break;
            }


            thumbWidth = frameWidth * tfi->getHoldFrame();
            if (tx < gX() + _trackPanelWidth) {
                left += thumbWidth;
                if (tx + frameWidth > gX() + _trackPanelWidth) {
                    isCut = true;
                    nvgScissor(vg, gX() + _trackPanelWidth, gY(), frameWidth, height);
                }
                else
                    continue;
            }
            else
                left += thumbWidth;
            if (tx > gX() + width)
                break;


            //frame idx
            char str[10];
            nvgFontFace(vg, "sans");
            nvgFontSize(vg, THEME_FONT_SIZE_NORMAL);
            nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
            nvgFillColor(vg, nvgRGB(240, 240, 240));
            sprintf(str, "%d", tfi->getIdx() + 1);
//            sprintf(str, "%d", tfi->getStartFrame());
            nvgText(vg, tx, gY() + 1, str, nullptr);

            if (tfi->getHoldFrame() > 1) {
                fillRect(_3RGBA(255, 50), tx + frameWidth, frameBgY, thumbWidth - frameWidth,
                         frameHeight)
                nvgFontFace(vg, "sans");
                nvgFontSize(vg, THEME_FONT_SIZE_NORMAL);
                nvgTextAlign(vg, NVG_ALIGN_RIGHT | NVG_ALIGN_TOP);
                nvgFillColor(vg, nvgRGB(240, 240, 240));
//            sprintf(str, "%d", tfi->getIdx() + 1);
                sprintf(str, "%d", tfi->getHoldFrame());
                nvgText(vg, tx + thumbWidth - 5, gY() + 15, str, nullptr);
            }

            //white bg
            fillRect(_3RGB(255), tx, frameBgY, frameWidth, frameHeight);

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
            bool isInFrame;
            isInFrame = isInRect(VS_CONTEXT.cursor.x, VS_CONTEXT.cursor.y,
                                 tx, gY() + _trackDragBarHeight,
                                 thumbWidth,
                                 frameHeight);


            if (hoverTx == 0 && isInFrame) {
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

        }//end loop


        if (hoverTx != 0) {//hover mask
            if (!_isPress)
                drawBlockHint(isHoverLeft, hoverTx, hoverTWidth);
            else if (!isPressDragBar)
                onDragTrackFrame(hoverTx, hoverTx + hoverTWidth);
        }
        else if (_pressFlag == PressFlag::Right && _handleTrackFrameInfo) {
            onDragTrackFrame(hoverTx, hoverTx + hoverTWidth);
        }
    }

    bool drawDragBar(int dragBarX, int dragWidth) {
        if (_trackInfo->trackFrameInfos->size()) {
            fillRect(_3RGB(29), dragBarX, gY(), dragWidth, 1);
            fillRect(_3RGB(60), dragBarX, gY() + 1, dragWidth, 1);
            if (_isPress && isMouseInRect(dragBarX, gY(), dragWidth, _trackDragBarHeight + 2)) {
//            VS_CONTEXT.setCursorPos(VS_CONTEXT.cursor.x, _hideY);
                int dx = mouseX() - _lastX;
                if (dx != 0) {
                    if (dx < -_dragSense) {
                        _trackInfo->setStartFrame(_trackInfo->getStartFrame() - 1);
                        _lastX = mouseX();
                    }
                    else if (dx > _dragSense) {
                        _trackInfo->setStartFrame(_trackInfo->getStartFrame() + 1);
                        _lastX = mouseX();
                    }
                }
                fillRect(_3RGB(52), dragBarX, gY() + 2, dragWidth, _trackDragBarHeight);
                return true;
            }
            else {
                fillRect(_3RGB(47), dragBarX, gY() + 2, dragWidth, _trackDragBarHeight);
            }
        }
        return false;
    }

    void drawBlockHint(bool isHoverLeft, int hoverTx, int hoverTWidth) {
        //left block
        int blockWidth = 5;
        int blockY = gY() + _trackDragBarHeight + 2;
        NVGcolor colorL = nvgRGB(THEME_COLOR_TRACK_THUMB_BLOCK);
        NVGcolor colorR = nvgRGBA(THEME_COLOR_TRACK_THUMB_BLOCK, 128);
        if (isHoverLeft) {
            colorL = nvgRGBA(THEME_COLOR_TRACK_THUMB_BLOCK, 128);
            colorR = nvgRGB(THEME_COLOR_TRACK_THUMB_BLOCK);
        }
        fillRect(colorL, hoverTx - 5, blockY, blockWidth, frameHeight - 2);
        fillRect(colorR, hoverTx + hoverTWidth, blockY, blockWidth, frameHeight - 2);
    }

    void drawExHandle(int trackX, int trackEndX) {
        if (trackEndX > gX() + _trackPanelWidth) {

            _exHandleL->setX(trackX);
            _exHandleR->setX(trackEndX);

//        fillRect(_3RGB(200), _exHandleL->gX() - _exHandleL->width,
//                 _exHandleL->gY(),
//                 _exHandleL->width,
//                 _exHandleL->height)


            nvgBeginPath(vg);
            nvgCircle(vg, _exHandleR->gX() + 20 + 5,
                      _exHandleR->gY() + 30, 5);
            if (_exHandleR->isHover) {
                nvgFillColor(vg, _3RGB(200));
            }
            else {
                nvgFillColor(vg, _3RGB(120));
            }
            nvgFill(vg);
            nvgBeginPath(vg);
            nvgCircle(vg, _exHandleR->gX() + 20 + 5,
                      _exHandleR->gY() + 30, 5);
            nvgStrokeWidth(vg, 1);
            nvgStrokeColor(vg, _3RGB(20));
            nvgStroke(vg);

            vsColoredNodeWire(vg, _exHandleR->gX(),
                              _exHandleR->gY() + 2,
                              _exHandleR->gX() + 20,
                              _exHandleR->gY() + 30,
                              _3RGB(200), _3RGB(52));
        }

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
//            nvgFillColor(vg, nvgRGB(THEME_COLOR_TITLEBAR_BOTTOM_BORDER));
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
//            nvgFillColor(vg, nvgRGB(THEME_COLOR_TITLEBAR_BOTTOM_BORDER));
//            nvgFill(vg);
    }

    int _dragSense = 30;
    bool isDragHide = false;
    int _pressFlag = 0;


    void onDragTrackFrame(int left, int right) {
        int dx = 0;
        int frameWidth = _proj->curCompInfo->frameWidth;
        int mx = VS_CONTEXT.cursor.x;
        if (_lastX)
            dx = mx - _lastX;
        else
            _lastX = mx;
        if (dx != 0) {
//            VS_CONTEXT.hideCursor();
            VS_CONTEXT.setCursorPos(VS_CONTEXT.cursor.x, _hideY);
            if (_pressFlag == PressFlag::Left) {
                if (dx > _dragSense) {
                    //fixme when _dragSense < frameWidth
                    isDragHide = true;
                    //fixme call L2R L2L when mouse up
                    _proj->curCompInfo->L2R(_handleTrackFrameInfo, _trackInfo);
                    _hideX += frameWidth;
                    _lastX = mx;

                }
                else if (dx < -_dragSense) {
                    isDragHide = true;
                    _proj->curCompInfo->L2L(_handleTrackFrameInfo, _trackInfo);
                    _lastX = mx;
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
                    _lastX = mx;
                }
                else if (dx < -_dragSense && _handleTrackFrameInfo->getHoldFrame() > 1) {
                    _proj->curCompInfo->R2L(_handleTrackFrameInfo);
                    isDragHide = true;
                    _hideX -= frameWidth;
                    _lastX = mx;
                }
            }
        }
    }


    void onOpacity(void *e) override {
        _trackInfo->setOpacity(double(vSlider->getValue()) / (100));
    }

    Sprite *_exHandleL;
    Sprite *_exHandleR;
    int _lastX, _lastY;
    int _hideX, _hideY;
    TrackInfo *_trackInfo;

};
