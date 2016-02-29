
/*!
  \file     SelectionInfo.h
  \author   Tody
  SelectionInfo definition.
  \date     2015/12/19
*/

#ifndef SELECTIONINFO_H
#define SELECTIONINFO_H

#include "SceneObject.h"
#include <QVector>

//! IndexSelection implementation.
class IndexSelection
{
public:
    //! Constructor.
    IndexSelection() {}

    //! Destructor.
    virtual ~IndexSelection() {}

    bool empty() const;

    void clear();

    void setIndexList ( const std::vector<int>& indices );

    void addIndex ( int index );

    void indexList ( std::vector<int>& indices ) const;

private:
    std::vector<int> _selection;

};

//! SelectionInfo implementation.
class SelectionInfo: public SceneObject
{
    Q_OBJECT
public :

    //! Constructor.
    SelectionInfo ( Scene* scene )
        : SceneObject ( scene )
    {}

    //! Destructor.
    virtual ~SelectionInfo() {}

    void gl();

    void clear()
    {
        _vertexSelection.clear();
        _faceSelection.clear();
    }

    void clearVertexSelection()
    {
        _vertexSelection.clear();
        emit updated();
    }

    void setVertexSelection ( const std::vector<int>& indices )
    {
        _vertexSelection.setIndexList ( indices );
        emit updated();
    }

    void addVertexSelection ( int index )
    {
        _vertexSelection.addIndex ( index );
        emit updated();
    }

    void vertexSelection ( std::vector<int>& indices ) const
    {
        _vertexSelection.indexList ( indices );
    }

    void clearFaceSelection()
    {
        _faceSelection.clear();
        emit updated();
    }

    void addFaceSelection ( int index )
    {
        _faceSelection.addIndex ( index );
        emit updated();
    }

    void setFaceSelection ( const std::vector<int>& indices )
    {
        _faceSelection.setIndexList ( indices );
        emit updated();
    }

    void faceSelection ( std::vector<int>& indices ) const
    {
        _faceSelection.indexList ( indices );
    }

private:
    void glVertexSelection();

    void glFaceSelection();

private:
    //! Selection for vertices.
    IndexSelection _vertexSelection;

    //! Selection for faces.
    IndexSelection _faceSelection;
};

class SelectionInfoSet: public SceneObject
{
    Q_OBJECT
public :

    //! Constructor.
    SelectionInfoSet ( Scene* scene )
        : SceneObject ( scene ), _currentSelectionSet ( 0 )
    {
        initSelectionSet ( scene );
    }

    //! Destructor.
    virtual ~SelectionInfoSet()
    {}

    void initSelectionSet ( Scene* scene )
    {
        for ( int i = 0; i < 10; i++ )
        {
            _selectionSet.push_back ( new SelectionInfo ( scene ) );
        }
    }

    void selectSelectionSet ( int currentSelectionSet )
    {
        _currentSelectionSet = currentSelectionSet;
        emit updated();
    }

    SelectionInfo* currentSelectionSet()
    {
        return _selectionSet[_currentSelectionSet];
    }

    void clear()
    {
        foreach ( SelectionInfo* selectionInfo, _selectionSet )
        {
            selectionInfo->clear();
        }
    }

    void gl();

    QVector<SelectionInfo*> _selectionSet;
    int _currentSelectionSet;
};

#endif

