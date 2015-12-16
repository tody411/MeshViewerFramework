
/*!
  \file     CommandParameterUI.h
  \author   Tody
  CommandParameterUI definition.
  \date     2015/09/19
*/

#ifndef COMMANDPARAMETERUI_H
#define COMMANDPARAMETERUI_H

#include <QWidget>

#include "CommandParameters.h"

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

//! CommandParameterUI implementation.
class CommandParameterUI : public QWidget
{
    Q_OBJECT
public :
    //! Constructor.
    CommandParameterUI ( const QString& name, CommandParameters& params, const QString& description = "" )
        : _name ( name ), _description ( description ), _params ( &params )
    {
        createUI();
    }

    //! Destructor.
    virtual ~CommandParameterUI() {}

signals:
    void edited();

private:
    void createUI();

private:
    CommandParameters* _params;

    QString _name;
    QString _description;
};

#endif

