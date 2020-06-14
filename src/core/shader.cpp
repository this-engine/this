// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

// this includes
#include "shader.hpp"
#include "uniform.hpp"

// Qt includes
#include <QOpenGLContext>
#include <QOpenGLShader>
#include <QByteArray>


/*!
 * \fn QByteArray versionedShaderCode(const char *src)
 * 
 * Appends the version of the the OpenGL to use with the shader
 * 
 * \note  is left alone in the cpp
 * \since 0.1-Qt
 */
QByteArray versionedShaderCode(const char *src)
{
    QByteArray versionedSrc;

    if (QOpenGLContext::currentContext()->isOpenGLES())
        versionedSrc.append(QByteArrayLiteral("#version 300 es\n"));
    else
        versionedSrc.append(QByteArrayLiteral("#version 330\n"));

    versionedSrc.append(src);
    return versionedSrc;
}

/*!
 * \fn    QList<TUniform>  getUniformDeclarationsList(const QString& src)
 * 
 * get all the uniform declarations from a source shader
 * 
 * \note  is left alone in the cpp
 * \since 0.1-Qt
 */
QHash<QString, TUniform*>  getUniformDeclarationsList(QObject * parent, const QString& src)
{
   QHash<QString, TUniform*> uniformslist;
    auto list = src.split(QRegExp("[\r\n\t; ]+"), Qt::SkipEmptyParts);
    for (auto line : list)
    {
        if(line.startsWith(QString("uniform")))
        {
            auto words = line.split(QRegExp("\\s+"), Qt::SkipEmptyParts);
            for (int idx = 1/* 0 is uniform*/; idx< words.size(); idx++)
            {
                const char* word= words[idx].toStdString().c_str();
                if(TUniform::TypeConversionMap.contains(word))
                {
                    auto type = TUniform::TypeConversionMap.find(word).value();
                    auto name =  words[idx+1];
                    auto uniform = new TUniform(parent, type,name);
                    uniformslist.insert(name,uniform);
                    break;
                }
            }
        }
    } 
    return uniformslist;

}

TShader::TShader(const QString& vertex, const QString& fragment, QObject *parent) : QObject(parent) , Program(new QOpenGLShaderProgram)
{
    // make uniform list a thing : 
    Uniforms = getUniformDeclarationsList(this, vertex);
    Uniforms.insert(getUniformDeclarationsList(this, fragment));

    Program->addShaderFromSourceCode(QOpenGLShader::Vertex, versionedShaderCode(vertex.toStdString().c_str()));
    Program->addShaderFromSourceCode(QOpenGLShader::Fragment, versionedShaderCode(fragment.toStdString().c_str()));
    // get ready

    for( auto unif: Uniforms.values())
    {
       unif->setUniformLocation(Program);
    }
}

TShader::~TShader()
{
    delete Program;
    Program = 0;

    for( auto unif: Uniforms)
    {
        if(unif)
            delete unif;
        unif = 0;
    }
}

void TShader::linkProgram() const
{
    assert(Program != nullptr);
    Program->link();
}

void TShader::bindProgram() const 
{
    assert(Program != nullptr);
    Program->bind();
}

void TShader::releaseProgram() const
{
    assert(Program != nullptr);
    Program->release();
}

const QOpenGLShaderProgram* TShader::getProgram() const
{
    return Program;
}


TUniform* TShader::findUniform(QString name) const
{
    auto unif = Uniforms.find(name);    
    return unif != Uniforms.end() ? unif.value() : nullptr;
}