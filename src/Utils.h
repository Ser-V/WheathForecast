#ifndef UTILS_H
#define UTILS_H

#include <QCoreApplication>
#include <QList>
#include <QMap>
#include <QObject>
#include <QString>
#include <QVector>

typedef  QList<QVector<double> > VectorList;

class Utils
{
  Q_DECLARE_TR_FUNCTIONS(Utils)

public:
  struct AverageCalcOutput
  {
    QMap< QString, QVector<double> > averagePoints;
    double distance;
    QString error;
  };

  static QString calcByAverage(const QMap<QString, VectorList>& groups, const QVector<double>& value, AverageCalcOutput& output);
  static QString calcByRegion(const QMap<QString, VectorList>& groups, const QVector<double>& value, double& radius);
  static QString calcByMinValue(const QMap<QString, VectorList>& groups, const QVector<double>& value, QVector<double>& minPoint);
};

#endif // UTILS_H