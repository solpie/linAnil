//
// Created by toramisu on 2015/7/31.
//

#pragma once

#include <math.h>

// Algorithm Reference:
//http://www.robertpenner.com/easing/
//http://www.cnblogs.com/cloudgamer/archive/2009/01/06/Tween.html

#ifndef PI
#define PI    3.1415926f
#endif

const float EPSINON = 0.000001f;
#define EQUAL_ZERO(x) ((x >= - EPSINON) && (x <= EPSINON)) ? true : false

class CTween {
public:
    CTween(void);

    ~CTween(void);

    // Linear
    float Linear_easeIn(float t, float b, float c, float d) {
        return c * t / d + b;
    }

    float Linear_easeOut(float t, float b, float c, float d){
        return c * t / d + b;
    }

    float Linear_easeInOut(float t, float b, float c, float d) {
        return c * t / d + b;
    }

    // Quadratic
    float Quad_easeIn(float t, float b, float c, float d){
        return c * (t /= d) * t + b;
    }

    float Quad_easeOut(float t, float b, float c, float d){
        return -c * (t /= d) * (t - 2) + b;
    }

    float Quad_easeInOut(float t, float b, float c, float d){
        if ((t /= d / 2) < 1)
            return c / 2 * t * t + b;
        return -c / 2 * ((--t) * (t - 2) - 1) + b;
    }

    // Cubic
    float Cubic_easeIn(float t, float b, float c, float d);

    float Cubic_easeOut(float t, float b, float c, float d);

    float Cubic_easeInOut(float t, float b, float c, float d);

    // Quartic
    float Quart_easeIn(float t, float b, float c, float d);

    float Quart_easeOut(float t, float b, float c, float d);

    float Quart_easeInOut(float t, float b, float c, float d);

    // Quintic
    float Quint_easeIn(float t, float b, float c, float d);

    float Quint_easeOut(float t, float b, float c, float d);

    float Quint_easeInOut(float t, float b, float c, float d);

    // Sinusoidal
    float Sine_easeIn(float t, float b, float c, float d);

    float Sine_easeOut(float t, float b, float c, float d);

    float Sine_easeInOut(float t, float b, float c, float d);

    // Exponential
    float Expo_easeIn(float t, float b, float c, float d);

    float Expo_easeOut(float t, float b, float c, float d);

    float Expo_easeInOut(float t, float b, float c, float d);

    // Circular
    float Circ_easeIn(float t, float b, float c, float d);

    float Circ_easeOut(float t, float b, float c, float d);

    float Circ_easeInOut(float t, float b, float c, float d);

    // Elastic
    float Elastic_easeIn(float t, float b, float c, float d, float a = 0.0f, float p = 0.0f);

    float Elastic_easeOut(float t, float b, float c, float d, float a = 0.0f, float p = 0.0f);

    float Elastic_easeInOut(float t, float b, float c, float d, float a = 0.0f, float p = 0.0f);

    // Back
    float Back_easeIn(float t, float b, float c, float d, float s = 0.0f);

    float Back_easeOut(float t, float b, float c, float d, float s = 0.0f);

    float Back_easeInOut(float t, float b, float c, float d, float s = 0.0f);

    // Bounce
    float Bounce_easeOut(float t, float b, float c, float d);

    float Bounce_easeIn(float t, float b, float c, float d);

    float Bounce_easeInOut(float t, float b, float c, float d);

public:
    float t, b, c, d, a, p;
};

CTween::CTween(void) {
}

CTween::~CTween(void) {
}




// Quadratic



// Cubic
float CTween::Cubic_easeIn(float t, float b, float c, float d) {
    return c * (t /= d) * t * t + b;
}

float CTween::Cubic_easeOut(float t, float b, float c, float d) {
    return c * ((t = t / d - 1) * t * t + 1) + b;
}

float CTween::Cubic_easeInOut(float t, float b, float c, float d) {
    if ((t /= d / 2) < 1)
        return c / 2 * t * t * t + b;
    return c / 2 * ((t -= 2) * t * t + 2) + b;
}

// Quartic
float CTween::Quart_easeIn(float t, float b, float c, float d) {
    return c * (t /= d) * t * t * t + b;
}

float CTween::Quart_easeOut(float t, float b, float c, float d) {
    return -c * ((t = t / d - 1) * t * t * t - 1) + b;
}

float CTween::Quart_easeInOut(float t, float b, float c, float d) {
    if ((t /= d / 2) < 1)
        return c / 2 * t * t * t * t + b;
    return -c / 2 * ((t -= 2) * t * t * t - 2) + b;
}

// Quintic
float CTween::Quint_easeIn(float t, float b, float c, float d) {
    return c * (t /= d) * t * t * t * t + b;
}

float CTween::Quint_easeOut(float t, float b, float c, float d) {
    return c * ((t = t / d - 1) * t * t * t * t + 1) + b;
}

float CTween::Quint_easeInOut(float t, float b, float c, float d) {
    if ((t /= d / 2) < 1)
        return c / 2 * t * t * t * t * t + b;
    return c / 2 * ((t -= 2) * t * t * t * t + 2) + b;
}

// Sinusoidal
float CTween::Sine_easeIn(float t, float b, float c, float d) {
    return -c * cos(t / d * (PI / 2)) + c + b;
}

float CTween::Sine_easeOut(float t, float b, float c, float d) {
    return c * sin(t / d * (PI / 2)) + b;
}

float CTween::Sine_easeInOut(float t, float b, float c, float d) {
    return -c / 2 * (cos(PI * t / d) - 1) + b;
}

// Exponential
float CTween::Expo_easeIn(float t, float b, float c, float d) {
    return (t == 0) ? b : c * pow(2, 10 * (t / d - 1)) + b;
}

float CTween::Expo_easeOut(float t, float b, float c, float d) {
    return (t == d) ? b + c : c * (-pow(2, -10 * t / d) + 1) + b;
}

float CTween::Expo_easeInOut(float t, float b, float c, float d) {
    if (t == 0)
        return b;
    if (t == d)
        return b + c;
    if ((t /= d / 2) < 1)
        return c / 2 * pow(2, 10 * (t - 1)) + b;
    return c / 2 * (-pow(2, -10 * --t) + 2) + b;
}

// Circular
float CTween::Circ_easeIn(float t, float b, float c, float d) {
    return -c * (sqrt(1 - (t /= d) * t) - 1) + b;
}

float CTween::Circ_easeOut(float t, float b, float c, float d) {
    return c * sqrt(1 - (t = t / d - 1) * t) + b;
}

float CTween::Circ_easeInOut(float t, float b, float c, float d) {
    if ((t /= d / 2) < 1)
        return -c / 2 * (sqrt(1 - t * t) - 1) + b;
    return c / 2 * (sqrt(1 - (t -= 2) * t) + 1) + b;
}

// Elastic
float CTween::Elastic_easeIn(float t, float b, float c, float d, float a/* = 0.0f*/, float p/* = 0.0f*/) {
    float s = 0;
    if (t == 0)
        return b;
    if ((t /= d) == 1)
        return b + c;
    if (!p)
        p = d * .3f;
    if (!a || a < abs(c)) {
        a = c;
        s = p / 4;
    }
    else
        s = p / (2 * PI) * asin(c / a);
    return -(a * pow(2, 10 * (t -= 1)) * sin((t * d - s) * (2 * PI) / p)) + b;
}

float CTween::Elastic_easeOut(float t, float b, float c, float d, float a/* = 0.0f*/, float p/* = 0.0f*/) {
    float s = 0;
    if (t == 0)
        return b;
    if ((t /= d) == 1)
        return (b + c);
    if (!p)
        p = d * .3f;
    if (!a || a < abs(c)) {
        a = c;
        s = p / 4;
    }
    else
        s = p / (2 * PI) * sin((float) c / a);

    return (a * pow(2.0f, (int) -10 * t) * sin((t * d - s) * (2 * PI) / p) + c + b);
}

float CTween::Elastic_easeInOut(float t, float b, float c, float d, float a/* = 0.0f*/, float p/* = 0.0f*/) {
    float s = 0;
    if (t == 0)
        return b;
    if ((t /= d / 2) == 2)
        return b + c;
    if (!p)
        p = d * (.3f * 1.5f);
    if (!a || a < abs(c)) {
        a = c;
        s = p / 4;
    }
    else
        s = p / (2 * PI) * asin(c / a);
    if (t < 1)
        return -.5f * (a * pow(2, 10 * (t -= 1)) * sin((t * d - s) * (2 * PI) / p)) + b;
    return a * pow(2, -10 * (t -= 1)) * sin((t * d - s) * (2 * PI) / p) * .5f + c + b;
}

// Back
float CTween::Back_easeIn(float t, float b, float c, float d, float s/* = 0.0f*/) {
    if (EQUAL_ZERO(s))
        s = 1.70158f;
    return c * (t /= d) * t * ((s + 1) * t - s) + b;
}

float CTween::Back_easeOut(float t, float b, float c, float d, float s/* = 0.0f*/) {
    if (EQUAL_ZERO(s))
        s = 1.70158f;
    return c * ((t = t / d - 1) * t * ((s + 1) * t + s) + 1) + b;
}

float CTween::Back_easeInOut(float t, float b, float c, float d, float s/* = 0.0f*/) {
    if (EQUAL_ZERO(s))
        s = 1.70158f;
    if ((t /= d / 2) < 1)
        return c / 2 * (t * t * (((s *= (1.525f)) + 1) * t - s)) + b;
    return c / 2 * ((t -= 2) * t * (((s *= (1.525f)) + 1) * t + s) + 2) + b;
}

// Bounce
float CTween::Bounce_easeOut(float t, float b, float c, float d) {
    if ((t /= d) < (1 / 2.75)) {
        return c * (7.5625f * t * t) + b;
    }
    else if (t < (2 / 2.75)) {
        return c * (7.5625f * (t -= (1.5f / 2.75f)) * t + .75f) + b;
    }
    else if (t < (2.5 / 2.75)) {
        return c * (7.5625f * (t -= (2.25f / 2.75f)) * t + .9375f) + b;
    }
    else {
        return c * (7.5625f * (t -= (2.625f / 2.75f)) * t + .984375f) + b;
    }
}

float CTween::Bounce_easeIn(float t, float b, float c, float d) {
    return c - Bounce_easeOut(d - t, 0, c, d) + b;
}

float CTween::Bounce_easeInOut(float t, float b, float c, float d) {
    if (t < d / 2)
        return Bounce_easeIn(t * 2, 0, c, d) * .5f + b;
    else return Bounce_easeOut(t * 2 - d, 0, c, d) * .5f + c * .5f + b;
}
