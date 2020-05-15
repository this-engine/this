// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef _THIS_LOGO_
#define _THIS_LOGO_

#include <qopengl.h>
#include <QVector>
#include <QVector3D>

class TLogo
{
public:
    TLogo();
    const GLfloat *constData() const { return Data.constData(); }
    inline int count() const { return Count; }
    inline int vertexCount() const { return Count / 6; }

private:

    QVector<GLfloat> Data;
    int Count;
};

#endif // _THIS_LOGO_
