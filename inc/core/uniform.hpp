// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef _THIS_UNIFORM_
#define _THIS_UNIFORM_

// Qt includes
#include <QObject> 



/*!
 * \class TUniform
 * \brief class to handle a shader program uniform (auto update)
 * 
 * Update the uniform when the value change
 * 
 * \since 0.1-Qt
 */
class TUniform : public QObject
{
    Q_OBJECT
public:

    TUniform(void* value) : QObject()
    {
        
    }

public slots:

    void setValue(void* value);

signals:

    void valueChanged();

private: 

    void* Value;

    int GLUniformPointer;
};

#endif //_THIS_UNIFORM_