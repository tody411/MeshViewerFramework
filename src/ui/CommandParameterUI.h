
/*!
  \file     CommandParameterUI.h
  \author   Tody
  CommandParameterUI definition.
  \date     2015/09/19
*/

#ifndef COMMANDPARAMETERUI_H
#define COMMANDPARAMETERUI_H

#include <QWidget>

#include "SceneParameters.h"

class QSlider;
class QLineEdit;
class QCheckBox;
class QComboBox;

//! IntParameterUI implementation.
class IntParameterUI : public QWidget
{
    Q_OBJECT
public :
    //! Constructor.
    IntParameterUI ( IntParameter* param )
        : _param ( param )
    {
        createUI();
    }

    //! Destructor.
    virtual ~IntParameterUI() {}

signals:
    void valueChanged();

private slots:
    void sliderChanged ( int value );
    void textChanged ( );

private:
    void createUI();

private:
    IntParameter* _param;
    QSlider*    _slider;
    QLineEdit*  _lineEdit;
};

//! DoubleParameterUI implementation.
class DoubleParameterUI : public QWidget
{
    Q_OBJECT
public :
    //! Constructor.
    DoubleParameterUI ( DoubleParameter* param )
        : _param ( param )
    {
        createUI();
    }

    //! Destructor.
    virtual ~DoubleParameterUI() {}

signals:
    void valueChanged();

private slots:
    void sliderChanged ( int value );
    void textChanged ();

private:
    void createUI();

private:
    DoubleParameter* _param;
    QSlider*    _slider;
    QLineEdit*  _lineEdit;

    double _sliderScale;
};

//! VectorParameterUI implementation.
class VectorParameterUI : public QWidget
{
    Q_OBJECT
public :
    //! Constructor.
    VectorParameterUI ( VectorParameter* param )
        : _param ( param )
    {
        createUI();
    }

    //! Destructor.
    virtual ~VectorParameterUI() {}

signals:
    void valueChanged();

private slots:
    void childValueChanged ();

private:
    void createUI();

private:
    VectorParameter* _param;
    QVector<DoubleParameter*> _childParams;
};

//! BoolParameterUI implementation.
class BoolParameterUI : public QWidget
{
    Q_OBJECT
public :
    //! Constructor.
    BoolParameterUI ( BoolParameter* param )
        : _param ( param )
    {
        createUI();
    }

    //! Destructor.
    virtual ~BoolParameterUI() {}

signals:
    void valueChanged();

private slots:
    void    stateChanged ( int state );

private:
    void createUI();

private:
    BoolParameter* _param;

    QCheckBox* _checkBox;
};

//! EnumParameterUI implementation.
class EnumParameterUI : public QWidget
{
    Q_OBJECT
public :
    //! Constructor.
    EnumParameterUI ( EnumParameter* param )
        : _param ( param )
    {
        createUI();
    }

    //! Destructor.
    virtual ~EnumParameterUI() {}

signals:
    void valueChanged();

private slots:
    void    editTextChanged ( const QString& text );

private:
    void createUI();

private:
    EnumParameter* _param;

    QComboBox* _comboBox;
};

class QPushButton;
class QVBoxLayout;

//! CommandParameterUI implementation.
class CommandParameterUI : public QWidget
{
    Q_OBJECT
public :
    //! Constructor.
    CommandParameterUI ( const QString& name, SceneParameters& params, const QString& description = "" )
        : _name ( name ), _description ( description ), _params ( &params )
    {
        createUI();
    }

    //! Destructor.
    virtual ~CommandParameterUI() {}

    QPushButton* addButton ( const QString& name );

signals:
    void paramUpdated();

    void editFinished();

private:
    void createUI();

private:
    SceneParameters* _params;
    QVBoxLayout* _layout;

    QString _name;
    QString _description;
};

#endif

