#ifndef UTILS_H
#define UTILS_H

#include <QList>
#include <QVector>

typedef  QList<QVector<double> > VectorList;

class Utils
{
public:
  static QString calcByAverage(const QMap<QString, VectorList>& groups, const QVector<double>& value, VectorList& averagePoint);
  static QString calcByRegion(const QMap<QString, VectorList>& groups, const QVector<double>& value, double& radius);
  static QString calcByMinValue(const QMap<QString, VectorList>& groups, const QVector<double>& value, QVector<double>& minPoint);
};

#endif // UTILS_H