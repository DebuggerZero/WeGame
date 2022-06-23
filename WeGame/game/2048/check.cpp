#include "check.h"

Check::Check()
{

}

Check::Check(int x, int y, int value)
{
    this->x = x;
    this->y = y;
    this->value = value;
}

QColor Check::getColor()
{
    switch (value) {
    case 0:
        return QColor(0, 0, 0, 0);
    case 2:
        return QColor(238, 228, 218);
    case 4:
        return QColor(237, 224, 200);
    case 8:
        return QColor(242, 177, 121);
    case 16:
        return QColor(245, 149, 99);
    case 32:
        return QColor(246, 124, 95);
    case 64:
        return QColor(246, 94, 59);
    case 128:
        return QColor(237, 207,114);
    case 256:
        return QColor(237, 204, 97);
    case 512:
        return QColor(237,200,80);
    case 1024:
        return QColor(237,197,63);
    case 2048:
        return QColor(237, 194,46);
    case 4096:
        return QColor(101,218,146);
    case 8192:
        return QColor(90, 188,101);
    default:
        return QColor(36,140,81);
    }
}

QFont Check::getFont()
{
    if (value < 16) {
        return QFont("宋体", 20, QFont::Bold, false);
    }
    if (value < 128) {
        return QFont("黑体", 20, QFont::Bold, false);
    }
    if (value < 1024) {
        return QFont("黑体", 16, QFont::Bold, false);
    }
    if (value < 16384) {
        return QFont("黑体", 12, QFont::Bold, false);
    }
    return QFont("黑体", 20, QFont::Bold, false);
}
