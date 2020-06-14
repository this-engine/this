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

    TGLWindow();
    ~TGLWindow();

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

signals:

    void onGLcontextReady();

    void onGLinitialized();

public slots: 

    // something changed we need to update the view
    void updateGL();

    // add a object to render
    void setVisual(QList<TVisual*> render_objects);

protected:

    // A camera to do rendering
    TCamera * Camera;

    // an unsorted dictionnary of what we need to draw
    QHash<QString, TVisual* > RenderObjects;

private:


};

#endif

