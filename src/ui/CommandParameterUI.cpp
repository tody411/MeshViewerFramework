
/*!
  \file     CommandParameterUI.cpp
  \author       Tody
  CommandParameterUI definition.
  date      2015/09/19
*/

#include "CommandParameterUI.h"

#include <QtWidgets>

void IntParameterUI::createUI()
{
    QLabel* labelUI =  new QLabel ( _param->name() , this );
    _slider = new QSlider ( Qt::Horizontal, this );

    _slider->setMinimum ( _param->minValue() );
    _slider->setMaximum ( _param->maxValue() );
    _slider->setValue ( _param->value() );

    QValidator* validator = new QIntValidator ( _param->minValue(), _param->maxValue() );
    _lineEdit = new QLineEdit();
    _lineEdit->setText ( QString::number (  _param->value()  ) );
    _lineEdit->setValidator ( validator );

    connect ( _slider, & QSlider::valueChanged, this, & IntParameterUI::sliderChanged );
    connect ( _lineEdit, & QLineEdit::editingFinished, this, & IntParameterUI::textChanged );

    QGridLayout* layout = new QGridLayout();
    layout->addWidget ( labelUI, 0, 0 );
    layout->addWidget ( _slider, 0, 1 );
    layout->addWidget ( _lineEdit, 0, 2 );
    setLayout ( layout );
}

void IntParameterUI::sliderChanged ( int value )
{
    QString text = QString::number ( value );

    _lineEdit->setText ( text );

    _param->setValue ( value );
    emit valueChanged();
}

void IntParameterUI::textChanged ( )
{
    QString text = _lineEdit->text();
    int value = text.toInt();
    _slider->setTracking ( false );
    _slider->setValue ( value );
    _slider->setTracking ( true );

    _param->setValue ( value );
    emit valueChanged();
}


void DoubleParameterUI::createUI()
{
    QLabel* labelUI =  new QLabel ( _param->name() , this );
    _slider = new QSlider ( Qt::Horizontal, this );

    _sliderScale = 100.0 / ( _param->maxValue() - _param->minValue() );

    _slider->setMinimum ( _sliderScale * _param->minValue() );
    _slider->setMaximum ( _sliderScale *  _param->maxValue() );
    _slider->setValue ( _sliderScale * _param->value() );

    QValidator* validator = new QDoubleValidator ( _param->minValue(), _param->maxValue(), 5 );
    _lineEdit = new QLineEdit();
    _lineEdit->setText ( QString::number (  _param->value()  ) );
    _lineEdit->setValidator ( validator );

    connect ( _slider, & QSlider::valueChanged, this, & DoubleParameterUI::sliderChanged );
    connect ( _lineEdit, & QLineEdit::editingFinished, this, & DoubleParameterUI::textChanged );

    QGridLayout* layout = new QGridLayout();
    layout->addWidget ( labelUI, 0, 0 );
    layout->addWidget ( _slider, 0, 1 );
    layout->addWidget ( _lineEdit, 0, 2 );
    setLayout ( layout );
}

void DoubleParameterUI::sliderChanged ( int value )
{
    double value_d = value / _sliderScale;

    QString text = QString::number ( value_d );
    _lineEdit->setText ( text );

    _param->setValue ( value_d );
    emit valueChanged();
}

void DoubleParameterUI::textChanged ( )
{
    QString text = _lineEdit->text();
    double value_d = text.toDouble();
    int value = _sliderScale * value_d;
    _slider->setTracking ( false );
    _slider->setValue ( value );
    _slider->setTracking ( true );

    _param->setValue ( value_d );
    emit valueChanged();
}

void VectorParameterUI::createUI()
{
    QLabel* labelUI =  new QLabel ( _param->name() , this );

    QGridLayout* layout = new QGridLayout();
    for ( int i = 0; i < _param->size(); i++ )
    {
        DoubleParameter* childParam = new DoubleParameter();
        _childParams.append ( childParam );

        DoubleParameterUI* childUI = new DoubleParameterUI ( childParam );
        layout->addWidget ( childUI, i, 0 );

        connect ( childUI, &DoubleParameterUI::valueChanged, this, &VectorParameterUI::childValueChanged );
    }

    setLayout ( layout );
}

void VectorParameterUI::childValueChanged ()
{
    for ( int i = 0; i < _param->size(); i++ )
    {
        _param->setValue ( _childParams[i]->value(), i );
    }
}

void BoolParameterUI::createUI()
{
    QLabel* labelUI =  new QLabel ( _param->name()  , this );

    _checkBox = new QCheckBox ( this );

    Qt::CheckState state = Qt::Unchecked;
    if ( _param->value() )
    {
        state = Qt::Checked;
    }
    _checkBox->setCheckState ( state );

    connect ( _checkBox, & QCheckBox::stateChanged, this, & BoolParameterUI::stateChanged );

    QGridLayout* layout = new QGridLayout;
    layout->addWidget ( labelUI, 0, 0 );
    layout->addWidget ( _checkBox, 0, 1 );
    setLayout ( layout );
}

void    BoolParameterUI::stateChanged ( int state )
{
    bool v = Qt::Unchecked != state;

    _param->setValue ( v );

    emit valueChanged();
}


void EnumParameterUI::createUI()
{
    QLabel* labelUI =  new QLabel ( _param->name()  , this );

    _comboBox = new QComboBox ( this );
    _comboBox->addItems ( _param->enumNames() );
    _comboBox->setEditText ( _param->value() );

    connect ( _comboBox, & QComboBox::editTextChanged, this, & EnumParameterUI::editTextChanged );

    QGridLayout* layout = new QGridLayout;
    layout->addWidget ( labelUI, 0, 0 );
    layout->addWidget ( _comboBox, 0, 1 );
    setLayout ( layout );
}

void    EnumParameterUI::editTextChanged ( const QString& text )
{
    _param->setValue ( text );
}

QPushButton* CommandParameterUI::addButton ( const QString& name )
{
    QPushButton* button = new QPushButton ( name );
    _layout->addWidget ( button );
    return button;
}

void CommandParameterUI::createUI()
{
    this->setWindowTitle ( _name );

    QStringList paramNames = _params->paramNames();

    QMap<QString, IntParameter*> intParameters = _params->intParameters();

    QMap<QString, DoubleParameter*> doubleParameters = _params->doubleParameters();

    QMap<QString, BoolParameter*> boolParameters = _params->boolParameters();

    QMap<QString, EnumParameter*> enumParameters = _params->enumParameters();

    _layout = new QVBoxLayout;


    foreach ( QString paramName, paramNames )
    {
        if ( intParameters.contains ( paramName ) )
        {
            IntParameterUI* paramUI = new IntParameterUI ( intParameters[paramName] );
            _layout->addWidget ( paramUI );
            connect ( paramUI, &IntParameterUI::valueChanged, this, &CommandParameterUI::paramUpdated );
        }

        if ( doubleParameters.contains ( paramName ) )
        {
            DoubleParameterUI* paramUI = new DoubleParameterUI ( doubleParameters[paramName] ) ;
            _layout->addWidget ( paramUI );
            connect ( paramUI, &DoubleParameterUI::valueChanged, this, &CommandParameterUI::paramUpdated );
        }

        if ( boolParameters.contains ( paramName ) )
        {
            BoolParameterUI* paramUI = new BoolParameterUI ( boolParameters[paramName] );
            _layout->addWidget ( paramUI );
            connect ( paramUI, &BoolParameterUI::valueChanged, this, &CommandParameterUI::paramUpdated );
        }

        if ( enumParameters.contains ( paramName ) )
        {
            EnumParameterUI* paramUI = new EnumParameterUI ( enumParameters[paramName] ) ;
            _layout->addWidget ( paramUI );
            connect ( paramUI, &EnumParameterUI::valueChanged, this, &CommandParameterUI::paramUpdated );
        }
    }

    QPushButton* applyButton = new QPushButton ( "Apply" );
    connect ( applyButton, &QPushButton::clicked, this, &CommandParameterUI::editFinished );

    _layout->addWidget ( applyButton );
    _layout->addStretch();

    setLayout ( _layout );
}