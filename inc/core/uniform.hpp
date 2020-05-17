// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef _THIS_UNIFORM_
#define _THIS_UNIFORM_

// Qt includes
#include <QObject> 
#include <QVariant>
#include <QMetaType>


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

    
    enum TypesEnum 
    { 
        LightVec3,
        CameraMat4x4,
        WorldMat4x4,
        ProjectionMat4x4,
        CustomFloat,
        CustomVec2,
        CustomVec3,
        CustomVec4,
        CustomMat4x4
    };

    static const QMap<const char *, TypesEnum> PropertiesGLSLNames;


    TUniform(QObject * parent, QMetaType::Type type, QString name) : QObject() , PropertyName(name),ValueType(type) ,Type(TUniform::CustomFloat)
    {
        //TODO : replace with find
        for (auto itrGLSL = PropertiesGLSLNames.begin(); itrGLSL != PropertiesGLSLNames.end(); ++itrGLSL)
        {
           if(name.toStdString().c_str() == itrGLSL.key())
           {
               Type = itrGLSL.value();
               break;
           }
           
        }
    }

    TUniform(QObject * parent = nullptr) : QObject(parent)
    {
    }

    ~TUniform()
    {
    }

public slots:

    void setValue(QVariant value);

signals:

    void valueChanged();

private: 

    QString PropertyName;

    QMetaType::Type ValueType;

    QVariant Value;

    int GLUniformPointer;

    TUniform::TypesEnum Type;

public:


    // for in-editor display :
    //static QMap<ProgramProperties, QString> PropertiesFriendlyNames;

};

#endif //_THIS_UNIFORM_