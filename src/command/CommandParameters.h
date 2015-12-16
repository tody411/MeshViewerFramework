
/*!
  \file     CommandParameters.h
  \author   Tody
  CommandParameters definition.
  \date     2015/09/19
*/

#ifndef COMMANDPARAMETERS_H
#define COMMANDPARAMETERS_H

#include  <QString>
#include  <QList>
#include  <QStringList>
#include  <QMap>

//! BaseParameter
class BaseParameter : QObject
{
public :
    //! Constructor.
    BaseParameter ( ) {}

    //! Constructor.
    BaseParameter ( const QString& name, const QString& description = "" )
        : _name ( name ), _description ( description )
    {}

    //! Destructor.
    virtual ~BaseParameter() {}

    //! Set Name.
    void setName ( const QString& name ) { _name = name;}


    //! Out Name.
    const QString name() const { return _name;}

    //! Set Description.
    void setDescription ( const QString& description ) { _description = description;}

    //! Out Description.
    const QString description() const { return _description;}

    //! Return string representation.
    virtual const QString str() const
    {
        return _name;
    }

protected:
    QString _name;
    QString _description;
};

//! NumericParameter
template <typename ValueType>
class NumericParameter : public BaseParameter
{
public :
    //! Constructor.
    NumericParameter() {}

    //! Constructor.
    NumericParameter ( const QString& name, ValueType v_min, ValueType v_max, ValueType v_default = 0, const QString& description = "" )
        : BaseParameter ( name, description ), _v_min ( v_min ), _v_max ( v_max ), _v_default ( v_default ), _v ( v_default )
    {}

    //! Destructor.
    virtual ~NumericParameter() {}

    void create ( ValueType v_min, ValueType v_max, ValueType v_default = 0 )
    {
        _v_min = v_min;
        _v_max = v_max;
        _v_default = v_default;
        _v = v_default;
    }

    //! Set MinValue
    void setMinValue ( ValueType v_min ) { _v_min = v_min;}

    //! Set MaxValue
    void setMaxValue ( ValueType v_max ) { _v_max = v_max;}

    //! Out minValue.
    ValueType minValue() const { return _v_min;}

    //! Out maxValue.
    ValueType maxValue() const { return _v_max;}

    //! Set Value.
    void setValue ( ValueType v )
    {
        _v = v;
        if ( v < _v_min ) _v = _v_min;
        if ( v > _v_max ) _v = _v_max;
    }

    //! Out Value.
    ValueType value() const { return _v;}

    //! Return string representation.
    const QString str() const
    {
        return QString ( "%1=%2" ).arg ( _name ).arg ( _v );
    }

private:
    //! Min value.
    ValueType _v_min;

    //! Max value.
    ValueType _v_max;

    //! Default value.
    ValueType _v_default;

    //! Value.
    ValueType _v;
};

typedef NumericParameter<int> IntParameter;
typedef NumericParameter<double> DoubleParameter;

//! StringParameter
class StringParameter : public BaseParameter
{
public:
    //! Constructor.
    StringParameter () {}

    //! Constructor.
    StringParameter ( const QString& name, const QString& v_default = "", const QString& description = "" )
        : BaseParameter ( name, description ), _v ( v_default )
    {}

    //! Destructor.
    virtual ~StringParameter() {}

    //! Set Value.
    void setValue ( const QString& v )
    {
        _v = v;
    }

    //! Out Value.
    const QString value() const { return _v;}

    //! Return string representation.
    const QString str() const
    {
        return QString ( "%1=%2" ).arg ( _name ).arg ( _v );
    }

private:
    //! Value.
    QString _v;
};

//! BoolParameter
class BoolParameter : public BaseParameter
{
public:
    //! Constructor.
    BoolParameter () {}

    //! Constructor.
    BoolParameter ( const QString& name, bool v_default = false, const QString& description = "" )
        : BaseParameter ( name, description ), _v ( v_default )
    {}

    //! Destructor.
    virtual ~BoolParameter() {}

    //! Set Value.
    void setValue ( bool v )
    {
        _v = v;
    }

    //! Out Value.
    bool value () const { return _v;}

    //! Return string representation.
    const QString str() const
    {
        return QString ( "%1=%2" ).arg ( _name ).arg ( _v );
    }

private:
    //! Value.
    bool _v;
};

//! EnumParameter
class EnumParameter : public BaseParameter
{
public:
    //! Constructor.
    EnumParameter () {}

    //! Constructor.
    EnumParameter ( const QString& name, const QStringList& enumNames, const QString& v_default = "", const QString& description = "" )
        : BaseParameter ( name, description ), _enumNames ( enumNames ), _v ( v_default )
    {}

    //! Destructor.
    virtual ~EnumParameter() {}

    //! Set Value.
    void setValue ( const QString v )
    {
        _v = v;
    }

    //! Out Value.
    const QString value () const { return _v;}

    const QStringList enumNames() const { return _enumNames;}

    //! Return string representation.
    const QString str() const
    {
        return QString ( "%1=%2" ).arg ( _name ).arg ( _v );
    }

private:
    //! Value.
    QString _v;

    //! Enum names.
    QStringList _enumNames;
};

//! CommandParameters implementation.
class CommandParameters
{
public :
    //! Constructor.
    CommandParameters() {}

    //! Destructor.
    virtual ~CommandParameters() {}

    //! Add IntParameter.
    void addInt ( IntParameter* param )
    {
        _paramNames.push_back ( param->name() );
        _intParameters[param->name()] = param;
    }

    //! Add DoubleParameter.
    void addDouble ( DoubleParameter* param )
    {
        _paramNames.push_back ( param->name() );
        _doubleParameters[param->name()] = param;
    }

    //! Add BoolParameter.
    void addBool ( BoolParameter* param )
    {
        _paramNames.push_back ( param->name() );
        _boolParameters[param->name()] = param;
    }

    //! Add StringParameter.
    void addString ( StringParameter* param )
    {
        _paramNames.push_back ( param->name() );
        _stringParameters[param->name()] = param;
    }

    //! Add EnumParameter.
    void addEnum ( EnumParameter* param )
    {
        _paramNames.push_back ( param->name() );
        _enumParameters[param->name()] = param;
    }

    //! Return if CommandParameters are empty.
    bool empty() const { return _paramNames.empty();}

    //! Out paramNames.
    QStringList paramNames() const { return _paramNames;}

    //! Out intParameters.
    QMap<QString, IntParameter*> intParameters() const { return _intParameters;}

    //! Out doubleParameters.
    QMap<QString, DoubleParameter*> doubleParameters() const { return _doubleParameters;}

    //! Out boolParameters.
    QMap<QString, BoolParameter*> boolParameters() const { return _boolParameters;}

    //! Out stringParameters.
    QMap<QString, StringParameter*> stringParameters() const { return _stringParameters;}

    //! Out stringParameters.
    QMap<QString, EnumParameter*> enumParameters() const { return _enumParameters;}

    const QString str() const
    {
        QString paramsStr = "";

        foreach ( const QString paramName, _paramNames )
        {
            if ( paramsStr != "" )
            {
                paramsStr += ", ";
            }

            if ( _intParameters.contains ( paramName ) )
            {
                paramsStr += _intParameters[paramName]->str();
            }

            if ( _doubleParameters.contains ( paramName ) )
            {
                paramsStr += _doubleParameters[paramName]->str();
            }

            if ( _boolParameters.contains ( paramName ) )
            {
                paramsStr += _boolParameters[paramName]->str();
            }

            if ( _stringParameters.contains ( paramName ) )
            {
                paramsStr += _stringParameters[paramName]->str();
            }

            if ( _enumParameters.contains ( paramName ) )
            {
                paramsStr += _enumParameters[paramName]->str();
            }
        }
        return paramsStr;
    }

private:
    QStringList _paramNames;

    QMap<QString, IntParameter*> _intParameters;

    QMap<QString, DoubleParameter*> _doubleParameters;

    QMap<QString, BoolParameter*> _boolParameters;

    QMap<QString, StringParameter*> _stringParameters;

    QMap<QString, EnumParameter*> _enumParameters;
};

#endif

