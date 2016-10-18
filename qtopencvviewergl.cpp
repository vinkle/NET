#include "qtopencvviewergl.h"
#include <QOpenGLFunctions>
//12-12-12

QtOpencvViewerGL::QtOpencvViewerGL(QWidget *parent) :
    QOpenGLWidget(parent)
{
    mSceneChanged = false;
    mBgColor = QColor::fromRgb(0, 0, 0);

    mOutH = 0;
    mOutW = 0;
    mImgRatio = 4.0f/3.0f;

    mPosX = 0;
    mPosY = 0;
}

void QtOpencvViewerGL::initializeGL()
{
    makeCurrent();
    initializeOpenGLFunctions();
    glClearColor(0.0,0.0,0.0,1.0f);
}

void QtOpencvViewerGL::resizeGL(int width, int height)
{
    makeCurrent();
    glViewport(0, 0, (GLint)width, (GLint)height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, width, 0, height, 0, 1);	// To Draw image in the center of the area

    glMatrixMode(GL_MODELVIEW);

    // ---> Scaled Image Sizes
    mOutH = width/mImgRatio;
    mOutW = width;

    if(mOutH>height)
    {
        mOutW = height*mImgRatio;
        mOutH = height;
    }

    emit imageSizeChanged( mOutW, mOutH );
    // <--- Scaled Image Sizes

    mPosX = (width-mOutW)/2;
    mPosY = (height-mOutH)/2;

    mSceneChanged = true;
    updateScene();
}

void QtOpencvViewerGL::updateScene()
{
    if( mSceneChanged && this->isVisible() )
        //updateGL(); obsolete
        update();
}

void QtOpencvViewerGL::paintGL()
{
    makeCurrent();

    if( !mSceneChanged )
        return;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderImage();

    mSceneChanged = false;
}

void QtOpencvViewerGL::renderImage()
{
    makeCurrent();

    glClear(GL_COLOR_BUFFER_BIT);

    if (!mRenderQtImg.isNull())
    {
        glLoadIdentity();

        QImage image; // the image rendered

        glPushMatrix();
        {
            int imW = mRenderQtImg.width();
            int imH = mRenderQtImg.height();

            // The image is to be resized to fit the widget?
            if( imW != this->size().width() &&
                    imH != this->size().height() )
            {

                image = mRenderQtImg.scaled( //this->size(),
                                             QSize(mOutW,mOutH),
                                             Qt::IgnoreAspectRatio,
                                             Qt::SmoothTransformation
                                             );

                //qDebug( QString( "Image size: (%1x%2)").arg(imW).arg(imH).toAscii() );
            }
            else
                image = mRenderQtImg;

            // ---> Centering image in draw area

            glRasterPos2i( mPosX, mPosY );
            // <--- Centering image in draw area

            imW = image.width();
            imH = image.height();

            glDrawPixels( imW, imH, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
        }
        glPopMatrix();

        // end
        glFlush();
    }
}

bool QtOpencvViewerGL::showImage(const cv::Mat &image)
{
    image.copyTo(mOrigImage);

    mImgRatio = (float)image.cols/(float)image.rows;

    if( mOrigImage.channels() == 3)
        mRenderQtImg = QImage((const unsigned char*)(mOrigImage.data),
                              mOrigImage.cols, mOrigImage.rows,
                              mOrigImage.step, QImage::Format_RGB888)/*.rgbSwapped()*/;
    else if( mOrigImage.channels() == 1)
        mRenderQtImg = QImage((const unsigned char*)(mOrigImage.data),
                              mOrigImage.cols, mOrigImage.rows,
                              mOrigImage.step, QImage::Format_Indexed8);
    else
        return false;

    //mRenderQtImg = QGLWidget::convertToGLFormat(mRenderQtImg); obsolete

    mSceneChanged = true;

    updateScene();

    return true;
}


