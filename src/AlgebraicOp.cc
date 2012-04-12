#include <QtGui/QColor>
#include "AlgebraicOp.hh"

inline void color_range(int* c)
{
    *c = *c < 255 ? *c : 255;
    *c = *c > 0 ? *c : 0;
}

QImage AlgebraicOp::operate(QImage a, QImage b, char op)
{
    QImage res(a);
    for (int i = 0; i < a.width(); i++)
        for (int j = 0; j < a.height(); j++)
        {
            if (i < b.width() && j < b.height())
                res.setPixel(i, j, operate(a.pixel(i, j), b.pixel(i, j), op));
            else
                res.setPixel(i, j, a.pixel(i, j));
        }
    return res;
}

QRgb AlgebraicOp::operate(QRgb ca, QRgb cb, char op)
{
    int r = 0, g = 0, b = 0;
    switch (op)
    {
    case '+':
        r = qRed(ca) + qRed(cb);
        g = qGreen(ca) + qGreen(cb);
        b = qBlue(ca) + qBlue(cb);
        break;
    case '-':
        r = qRed(ca) - qRed(cb);
        g = qGreen(ca) - qGreen(cb);
        b = qBlue(ca) - qBlue(cb);
        break;
    case '*':
        r = qRed(ca) * qRed(cb);
        g = qGreen(ca) * qGreen(cb);
        b = qBlue(ca) * qBlue(cb);
        break;
    case '/':
	if (qRed(cb) == 0)
	    r = 255;
	else
	    r = qRed(ca) / qRed(cb);
	if (qGreen(cb) == 0)
	    g = 255;
	else
	    g = qGreen(ca) / qGreen(cb);
	if (qBlue(cb) == 0)
	    b = 255;
	else
	    b = qBlue(ca) / qBlue(cb);
        break;
    }
    color_range(&r);
    color_range(&g);
    color_range(&b);
    return QColor(r, g, b).rgb();
}
