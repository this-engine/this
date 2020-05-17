// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef _THIS_GL_WINDOW_
#define _THIS_GL_WINDOW_

// this includes
//#include "visual.hpp"


// Qt includes
#include <QOpenGLWindow>



// this forward declaration
class TCamera;
class TVisual;

/*!
 * \class TGLWindow
 * \brief Base class for opengl rendering windows
 * \since 0.1-Qt
 */
class TGLWindow : public QOpenGLWindow
{
    Q_OBJECT

public:

    TGLWindow(QWindow * parent = nullptr);
    ~TGLWindow();

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();


public slots: 

    // something changed we need to update the view
    void updateGL();

protected:

    // A camera to do rendering
    TCamera * Camera;

    QList<TVisual*> RenderObjects;

private:


};

#endif

