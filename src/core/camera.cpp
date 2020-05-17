// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "camera.hpp"

TCamera::TCamera(QObject* parent) : QObject(parent)
{
    
}

TCamera::~TCamera()
{

}

void TCamera::setLocation(QVector3D value)
{
    Eye = value;
    emit cameraChanged();
}

void TCamera::setLookAt(QVector3D value)
{
    Target = value;
    emit cameraChanged();
}

void TCamera::setResolution(QPoint value)
{
    Resolution = value;
    Projection.setToIdentity();
    const auto aspect_ratio = Resolution.x() /(float)Resolution.y();
    const auto vertical_angle = verticalAngle(FOV,aspect_ratio);
    Projection.perspective(vertical_angle, aspect_ratio, 0.01f, 100.0f);
    emit cameraChanged();
}

void TCamera::setFOV(float value)
{
    FOV = value;
    const auto aspect_ratio = Resolution.x() /(float)Resolution.y();
    const auto vertical_angle = verticalAngle(FOV,aspect_ratio);
    Projection.perspective(vertical_angle, aspect_ratio, 0.01f, 100.0f);
    emit cameraChanged();
}
    
