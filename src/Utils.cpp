#include <QtMath>
#include <QMap>

#include "Utils.h"

const int requiredVectorCount = 4;

QString Utils::calcByAverage(const QMap<QString, VectorList >& groups, const QVector<double>& value, VectorList& averagePoint)
{
  averagePoint.clear();
  QString resultGroup;
  double minDistance2 = 0.0;
  for (QMap<QString, VectorList>::const_iterator cit = groups.cbegin(); cit != groups.cend(); ++cit)
  {
    QList<QVector<double> > group = cit.value();
    QVector<double> averageVector;
    for(int vectorIndex = 0; vectorIndex < group.count(); ++vectorIndex)
    {
      if (averageVector.isEmpty())
      {
        averageVector.resize(group.at(vectorIndex).count()); // ?!
        averageVector.fill(0.0);
      }
      QVector<double> vector = group.at(vectorIndex);
      for (int i = 0; i < vector.count(); ++i)
        averageVector[i] += vector[i] / (double)group.count();
    }
    if (averageVector.count() != value.count())
      return QString();
    averagePoint.append(averageVector);
    double distance2 = -1.0;
    for (int i = 0; i < averageVector.count(); ++i)
      distance2 += pow(averageVector[i] - value[i], 2);
    if (resultGroup.isEmpty() && distance2 > 0.0)
    {
      resultGroup = cit.key();
      minDistance2 = distance2;
    }
    if (distance2 > 0.0 && distance2 < minDistance2)
    {
      minDistance2 = distance2;
      resultGroup = cit.key();
    }
  }
  return resultGroup;
}

QString Utils::calcByRegion(const QMap<QString, VectorList>& groups, const QVector<double>& value, double& radius)
{
  QString resultGroup;

  QMap<QString, QMap<double, int> > sortedVectorList;
  for (QMap<QString, VectorList>::const_iterator cit = groups.cbegin(); cit != groups.cend(); ++cit)
  {
    QList<QVector<double> > group = cit.value();
    QMap<double, int> sortedVectors;
    for(int vectorIndex = 0; vectorIndex < group.count(); ++vectorIndex)
    {
      QVector<double> vector = group.at(vectorIndex);
      double distance2 = 0.0;
      for (int i = 0; i < vector.count(); ++i)
        distance2 += pow(vector.at(i) - value.at(i), 2);
      sortedVectors.insertMulti(distance2, vectorIndex);
    }
    sortedVectorList.insert(cit.key(), sortedVectors);
  }

  double minDistance2 = -1.0;
  for (QMap<QString, QMap<double, int> >::const_iterator scit = sortedVectorList.cbegin(); scit != sortedVectorList.cend(); ++scit)
  {
    QMap<double, int>::const_iterator cit = scit->cbegin();
    if (requiredVectorCount <= scit->count())
      cit += requiredVectorCount;
    else
      continue;

    if (minDistance2 < 0.0)
    {
      minDistance2 = cit.key();
      resultGroup = scit.key();
    }

    if (cit.key() < minDistance2)
    {
      minDistance2 = cit.key();
      resultGroup = scit.key();
    }
  }

  radius = qSqrt(minDistance2);
  return resultGroup;
}

QString Utils::calcByMinValue(const QMap<QString, VectorList>& groups, const QVector<double>& value, QVector<double>& minPoint)
{
  QString resultGroup;
  double minDistance2 = -1.0;

  for (QMap<QString, VectorList>::const_iterator cit = groups.cbegin(); cit != groups.cend(); ++cit)
  {
    QList<QVector<double> > group = cit.value();
    for(int vectorIndex = 0; vectorIndex < group.count(); ++vectorIndex)
    {
      double distance2 = -1.0;
      QVector<double> vector = group.at(vectorIndex);
      for (int i = 0; i < vector.count(); ++i)
        distance2 += pow(vector.at(i) - value.at(i), 2);
      if (resultGroup.isEmpty())
      {
        resultGroup = cit.key();
        minDistance2 = distance2;
        minPoint = vector;
      }
      if (distance2 < minDistance2)
      {
        minDistance2 = distance2;
        resultGroup = cit.key();
        minPoint = vector;
      }
    }
  }

  return resultGroup;
}