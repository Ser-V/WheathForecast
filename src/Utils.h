#ifndef UTILS_H
#define UTILS_H

#include <QList>
#include <QVector>

class Utils
{
public:
  static int calcByAverage(const QList< QList<QVector<double> > >& groups, const QVector<double>& value, QList<QVector<double> >& averagePoint);
  static int calcByRegion(const QList< QList<QVector<double> > >& groups, const QVector<double>& value, double& radius);
  static int calcByMinValue(const QList< QList<QVector<double> > >& groups, const QVector<double>& value, QVector<double>& minPoint);
};

#endif // UTILS_H