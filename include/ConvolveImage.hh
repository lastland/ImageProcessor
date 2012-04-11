#ifndef _CONVOLVEIMAGE_H_
#define _CONVOLVEIMAGE_H_

#include <QtGui/QGroupBox>
#include <QtGui/QRadioButton>
#include <QtGui/QBoxLayout>
#include "RobertsOperator.hh"
#include "PrewittOperator.hh"
#include "SobelOperator.hh"
#include "BinaryImage.hh"

class ConvolveImage : public BinaryImage
{
    Q_OBJECT
public:
    ConvolveImage(QImage *pic, QWidget *parent = NULL, Qt::WindowFlags f = Qt::Dialog);
    virtual ~ConvolveImage();
    
public slots:
    virtual void convert(void);

protected:
    QGroupBox *convolutionBox;
    QRadioButton *robertsButton;
    QRadioButton *prewittButton;
    QRadioButton *sobelButton;
    QVBoxLayout *convolutionLayout;

private:
    RobertsOperator *roberts;
    PrewittOperator *prewitt;
    SobelOperator *sobel;
};

#endif /* _CONVOLVEIMAGE_H_ */
