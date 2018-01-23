#ifndef TEMPCONVERTER_H
#define TEMPCONVERTER_H

#include <QObject>

class TempConverter : public QObject
{
    Q_OBJECT
public:
    explicit TempConverter(int tempCelsius, QObject *parent = 0);
    int tempCelsius() const { return m_tempCelsius; }
    int tempFahrenheit() const { return (int)(m_tempCelsius*1.8+32); }

signals:
    void tempCelsiusChanged(int);
    void tempFahrenheitChanged(int);

public slots:
    void setTempCelsius(int);
    void setTempFahrenheit(int);

private:
    int m_tempCelsius;
};

#endif // TEMPCONVERTER_H
