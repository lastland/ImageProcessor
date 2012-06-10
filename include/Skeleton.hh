#ifndef _SKELETON_H_
#define _SKELETON_H_

#include "Dilation.hh"
#include "Erosion.hh"
#include <list>
#include <QtGui/QImage>

class Skeleton
{
public:
    static QImage convert(QImage *pic, std::list<QImage> **lst);
    static QImage restore(QImage *pic, std::list<QImage> *lst);
};

#endif /* _SKELETON_H_ */
