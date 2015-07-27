#pragma once
//
// Created by manoyuria on 2015/7/25.
//

#ifndef LINANIL_COMMONMETHOD_HPP
#define LINANIL_COMMONMETHOD_HPP

#endif //LINANIL_COMMONMETHOD_HPP

bool isInRect(int mX, int mY, int gX, int gY, int width, int height) {
    return mX >= gX && mY >= gY && mX <= gX + width && mY <= gY + height;
}

#define isMouseInRect(rx, ry, w, h) isInRect(VS_CONTEXT.cursor.x, VS_CONTEXT.cursor.y,rx,ry,w,h)
