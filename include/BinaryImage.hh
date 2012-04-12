#ifndef _BINARYIMAGE_H_
#define _BINARYIMAGE_H_

#include <QtGui/QImage>
#include "ConvertDialog.hh"
#include "ui_BinaryImageDialog.h"
#include "ImageHistogram.hh"
#include "ThresholdSelector.hh"
#include "OtsuThresholder.hh"
#include "EntropyThresholder.hh"

class BinaryImage : public ConvertDialog, public Ui::BinaryImageDialog
{
    Q_OBJECT
public:
    BinaryImage(QImage *pic, QWidget *parent = NULL, Qt::WindowFlags f = Qt::Dialog);
    virtual ~BinaryImage();
signals:
    void imageConverted(QImage pic);
public slots:
    void getOtsuThreshold(void);
    void getEntropyThreshold(void);
    void getThreshold(int threshold);
    virtual void accept(void);
    virtual void reject(void);
    virtual void convert(void);
protected:
    int m_threshold;
private:
    OtsuThresholder *m_otsu;
    EntropyThresholder *m_entropy;
    ImageHistogram *m_histogram;
};

#endif /* _BINARYIMAGE_H_ */
