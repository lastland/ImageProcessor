#ifndef _SKELETON_H_
#define _SKELETON_H_

#include "Dilation.hh"
#include "Erosion.hh"
#include <QtGui/QImage>

class Skeleton
{
public:
    static QImage convert(QImage *pic);
};

#endif /* _SKELETON_H_ */
