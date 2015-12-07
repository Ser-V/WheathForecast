#ifndef UTILS_H
#define UTILS_H

#include <QList>
#include <QVector>

class Utils
{
public:
  static int calcByAverage(const QList< QList<QVector<double> > >& groups, const QVector<double>& value);
  static int calcByRegion(const QList< QList<QVector<double> > >& groups, const QVector<double>& value);
  static int calcByMinValue(const QList< QList<QVector<double> > >& groups, const QVector<double>& value);
};

#endif // UTILS_H