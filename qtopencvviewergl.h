#ifndef QTOPENCVVIEWERGL_H
#define QTOPENCVVIEWERGL_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_2_0>
#include <opencv2/core/core.hpp>
//12-12-12

class QtOpencvViewerGL : public QOpenGLWidget, protected QOpenGLFunctions_2_0
{
    Q_OBJECT
public:
    explicit QtOpencvViewerGL(QWidget *parent = 0);

signals:
    void    imageSizeChanged( int outW, int outH ); /// Used to resize the image outside the widget

public slots:
    bool    showImage(const cv::Mat &image); /// Used to set the image to be viewed

protected:
    void 	initializeGL(); /// OpenGL initialization
    void 	paintGL(); /// OpenGL Rendering
    void 	resizeGL(int width, int height);        /// Widget Resize Event

    void    updateScene();
    void    renderImage();

private:
    bool        mSceneChanged;          /// Indicates when OpenGL view is to be redrawn

    QImage      mRenderQtImg;           /// Qt image to be rendered
    cv::Mat     mOrigImage;             /// original OpenCV image to be shown

    QColor      mBgColor;		/// Background color

    int         mOutH;                  /// Resized Image height
    int         mOutW;                  /// Resized Image width
    float       mImgRatio;             /// height/width ratio

    int         mPosX;                  /// Top left X position to render image in the center of widget
    int         mPosY;                  /// Top left Y position to render image in the center of widget


};

#endif
