#ifndef _ALGEBRAICOP_H_
#define _ALGEBRAICOP_H_

#include <QtGui/QColor>
#include <QtGui/QImage>

class AlgebraicOp
{
public:
    AlgebraicOp() {};
    virtual ~AlgebraicOp() {};
    static QRgb operate(QRgb a, QRgb b, char op);
    static QImage operate(QImage a, QImage b, char op);
};

#endif /* _ALGEBRAICOP_H_ */
