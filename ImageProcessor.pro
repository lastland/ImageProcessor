######################################################################
# Automatically generated by qmake (2.01a) Mon Apr 9 16:55:30 2012
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .
LIBS += -lqwt

# Input
INCLUDEPATH += include
VPATH += include src ui

HEADERS += \
Grayscale.hh \
ConvertDialog.hh \
MatrixDialog.hh \
GaussianFilterDialog.hh \
PointOpDialog.hh \
AlgebraicOp.hh \
GeometricScale.hh \
GeometricRotate.hh \
GeometricOpDialog.hh \
KernelOpDialog.hh \
Dilation.hh \
Erosion.hh \
MorphologyOpDialog.hh \
ImageHistogram.hh \
HistogramWindow.hh \
ThresholdSelector.hh \
OtsuThresholder.hh \
EntropyThresholder.hh \
BinaryImage.hh \
Convolution.hh \
RobertsOperator.hh \
PrewittOperator.hh \
SobelOperator.hh \
ConvolveImage.hh \
GaussianMatrix.hh \
MeanFilter.hh \
MedianFilter.hh \
MainWindow.hh

FORMS += \
PointOpDialog.ui \
GeometricOpDialog.ui \
MorphologyRadioWidget.ui \
BinaryImageDialog.ui \
GaussianFilterDialog.ui \
MainWindow.ui

SOURCES += \
GaussianMatrix.cc \
ConvertDialog.cc \
MatrixDialog.cc \
PointOpDialog.cc \
AlgebraicOp.cc \
GeometricScale.cc \
GeometricRotate.cc \
GeometricOpDialog.cc \
KernelOpDialog.cc \
Dilation.cc \
Erosion.cc \
MorphologyOpDialog.cc \
ImageHistogram.cc \
HistogramWindow.cc \
OtsuThresholder.cc \
EntropyThresholder.cc \
BinaryImage.cc \
Convolution.cc \
ConvolveImage.cc \
GaussianFilterDialog.cc \
MeanFilter.cc \
MedianFilter.cc \
MainWindow.cc \
main.cc
