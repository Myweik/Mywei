#include "logbase.h"

LogBase::LogBase(LOG_LOCATION_TYPE type, QObject *parent)
    : QObject(parent)
    , _type(type)
{

}
