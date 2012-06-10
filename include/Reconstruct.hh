#ifndef _RECONSTRUCT_H_
#define _RECONSTRUCT_H_

#include <QtGui/QImage>

enum ReconstructMethod {
    OBR,
    CBR
};

class Reconstruct
{
public:
    static QImage convert(QImage *pic, ReconstructMethod method);
};

#endif /* _RECONSTRUCT_H_ */
