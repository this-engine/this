// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef _THIS_NODE_
#define _THIS_NODE_

// Qt includes
#include <QByteArray> //TODO: is the minimal include ?
#include <QObject>
#include <QMatrix4x4>

//forward declaration
class TVisual;


/*!
 * \class TNode
 * \brief class representing part of a scene 
 * 
 * \note  correspond to an element of a 3d scene (for now)
 * 
 * \since 0.1-Qt
 */
class TNode : public QObject
{
    Q_OBJECT

public:

    TNode(TNode* parent = nullptr);

    virtual TVisual* getVisual() const {return nullptr;}


protected:

    // this might need to move to another class
    QMatrix4x4 ToWorld;

    QList<TNode> Children;

};

#endif // _THIS_NODE_