// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef _THIS_CAMERA_
#define _THIS_CAMERA_

// std includes
#include <cmath>

// Qt includes
#include <QMatrix4x4>
#include <QVector3D>

// this includes
#include "math.hpp"


/*!
 * \class TCamera
 * \brief Base class for 3D camera
 * \note  Qt Q3DCamera is from datavisualisation and we want to avoid importing too many qt Modules (for now)
 * \since 0.1-Qt
 */
class TCamera : public QObject
{
    Q_OBJECT

public:

    TCamera(QObject* parent = nullptr);


    ~TCamera();

    QMatrix4x4 getLookAtMatrix() const
    {
        QMatrix4x4 cam;
        cam.lookAt(Eye, Target, QVector3D(0.f,1.f,0.f) );
        return cam;
    }

    QMatrix4x4 getProjectionMatrix() const { return Projection; }


    /*!
     *  \fn void TCamera::setLocation(QVector3D value);
     *  \brief change the camera position in world space
     */
    void setLocation(QVector3D value);


    /*!
     *  \fn void TCamera::setLookAt(QVector3D value);
     *  \brief change the camera "look at"  target
     */
    void setLookAt(QVector3D value);

    /*!
     *  \fn void TCamera::setResolution(QPoint value);
     *  \brief change the camera resolution (thus changing projection matrix)
     */
    void setResolution(QPoint value);

    /*!
     *  \fn void TCamera::setFOV(float value);
     *  \brief change FOV
     */
    void setFOV(float value);

public slots:


    /*!
     *  \fn void TCamera::onResolutionXChanged();
     *  \brief change the camera resolution (thus changing projection matrix)
     */
    void onResolutionXChanged(int arg);

    /*!
     *  \fn void TCamera::onResolutionYChanged();
     *  \brief change the camera resolution (thus changing projection matrix)
     */
    void onResolutionYChanged(int arg);



signals:

    /*!
     *  \fn void TCamera::cameraChanged()
     *  \brief Camera uniform have changed values, connect to refresh your data
     */
    void cameraChanged();


    /*!
     *  \fn void TCamera::transformMatrixChanged()
     *  \brief Camera uniform have changed values, connect to refresh your data
     */
    void transformMatrixChanged(QMatrix4x4 transform);


    /*!
     *  \fn void TCamera::projectionMatrixChanged()
     *  \brief Camera uniform have changed values, connect to refresh your data
     */
    void projectionMatrixChanged(QMatrix4x4 transform);


protected:

    float FOV;

    QPoint Resolution;

    QMatrix4x4 Projection;
    
    QVector3D Eye;
    
    QVector3D Target;

private:

    constexpr float verticalAngle(float h, float aspect_ratio)  {    return 2 * TMath::arctan( tan(h / 2) * aspect_ratio); }

};

#endif // _THIS_CAMERA_
