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
 * \note  could be left alone in the cpp
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
 * \note  could be left alone in the cpp
 * \since 0.1-Qt
 */
QList<TUniform*>  getUniformDeclarationsList(QObject * parent, const QString& src)
{
    QList<TUniform*> uniformslist;
    auto list = src.split(QRegExp("[\r\n\t; ]+"), QString::SkipEmptyParts);
    QString line;
    foreach (line, list)
    {
        if(line.startsWith(QString("uniform")))
        {
            auto words = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);
            for (int idx = 1/* 0 is uniform*/; idx< words.size(); idx++)
            {
                const char* word= words[idx].toStdString().c_str();
                if(TUniform::TypeConversionMap.contains(word))
                {
                    auto type = TUniform::TypeConversionMap.find(word).value();
                    auto name =  words[idx+1];
                    auto uniform = new TUniform(parent, type,name);
                    uniformslist.insert(uniformslist.end(),uniform);
                    break;
                }
            }
        }
    } 
    return uniformslist;

}

TShader::TShader(const QString& vertex, const QString& fragment) : program(new QOpenGLShaderProgram)
{
    // make uniform list a thing : 
    Uniforms= getUniformDeclarationsList(this, vertex);
    Uniforms.append(getUniformDeclarationsList(this, fragment));

    program->addShaderFromSourceCode(QOpenGLShader::Vertex, versionedShaderCode(vertex.toStdString().c_str()));
    program->addShaderFromSourceCode(QOpenGLShader::Fragment, versionedShaderCode(fragment.toStdString().c_str()));
    // get ready

    //m_projMatrixLoc = m_program->uniformLocation("projMatrix");
    //m_camMatrixLoc = m_program->uniformLocation("camMatrix");
    //m_worldMatrixLoc = m_program->uniformLocation("worldMatrix");
    //m_myMatrixLoc = m_program->uniformLocation("myMatrix");
    //m_lightPosLoc = m_program->uniformLocation("lightPos");
}

TShader::~TShader()
{
    delete program;
    // better be safe than sorry
    program = 0;

    // get read of our objects
    TUniform * unif;
    foreach(unif, Uniforms)
    {
        if(unif)
            delete unif;
        unif = 0;
    }
}

void TShader::linkProgram() const
{
    assert(program != nullptr);
    program->link();
}

void TShader::bindProgram() const 
{
    assert(program != nullptr);
    program->bind();
}

const QOpenGLShaderProgram* TShader::getProgram() const
{
    return program;
}



void TShader::setProgramLocations(TUniform::TypesEnum type, QString custom_name)
{

}
