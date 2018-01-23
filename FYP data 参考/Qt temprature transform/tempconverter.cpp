#include "tempconverter.h"

TempConverter::TempConverter(int tempCelsius, QObject *parent) :
    QObject(parent), m_tempCelsius(tempCelsius)
{
}

void TempConverter::setTempCelsius(int tempCelsius)
{
    if(m_tempCelsius == tempCelsius)
        return;

    m_tempCelsius = tempCelsius;

    emit tempCelsiusChanged(m_tempCelsius);
    emit tempFahrenheitChanged(tempFahrenheit());
}

void TempConverter::setTempFahrenheit(int tempFahrenheit)
{
    int tempCelsius = (5.0/9.0)*(tempFahrenheit-32);
    setTempCelsius(tempCelsius);
}
