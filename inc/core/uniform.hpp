// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef _THIS_UNIFORM_
#define _THIS_UNIFORM_

// Qt includes
#include <QObject> 
#include <QVariant>
#include <QMetaType>


QT_BEGIN_NAMESPACE
class QOpenGLShaderProgram;
QT_END_NAMESPACE


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

    static const QMap<const char*,QMetaType::Type> TypeConversionMap;


    TUniform(QObject * parent, QMetaType::Type type, QString name) : QObject() , PropertyName(name)
    {
    }

    TUniform(QObject * parent = nullptr) : QObject(parent)
    {
    }

    ~TUniform()
    {
    }

    void setUniformLocation(QOpenGLShaderProgram * program);


    inline const char* getNameCStr() const  {return PropertyName.toStdString().c_str();}

public slots:

    void setValue(QVariant value);

signals:

    void valueChanged();

private: 

    QString PropertyName;

    QMetaType::Type ValueType;

    QVariant Value;

    int GLUniformPointer;

public:


    // for in-editor display :
    //static QMap<ProgramProperties, QString> PropertiesFriendlyNames;

};

#endif //_THIS_UNIFORM_