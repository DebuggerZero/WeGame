#include "utility.h"

Utility::Utility()
{

}

QString Utility::getStyleSheet(QString filePath)
{
    QFile file(filePath);
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    file.close();

    return stylesheet;
}

QRectF Utility::getFontRect(QString text, int x, int y, QFont font)
{
    QFontMetrics fontMetrics(font);
    int width = fontMetrics.horizontalAdvance(text);
    int height = fontMetrics.height();
    int x1 = x - width / 2;
    int y1 = y - height / 2;
    QRectF rectf(x1, y1, width, height);

    return rectf;
}
