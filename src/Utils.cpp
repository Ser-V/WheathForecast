#include <QMap>

#include "Utils.h"

const int requiredVectorCount = 2;

int Utils::calcByAverage(const QList< QList<QVector<double> > >& groups, const QVector<double>& value)
{
  int resultGroup = -1;
  double minDistance2 = 0.0;
  for (int groupIndex = 0; groupIndex < groups.count(); ++groupIndex)
  {
    QList<QVector<double> > group = groups.at(groupIndex);
    QVector<double> averageVector;
    for(int vectorIndex = 0; vectorIndex < group.count(); ++vectorIndex)
    {
      if (averageVector.isEmpty())
      {
        averageVector.resize(group.at(vectorIndex).count());
        averageVector.fill(0.0);
      }
      QVector<double> vector = group.at(vectorIndex);
      for (int i = 0; i < vector.count(); ++i)
        averageVector[i] += vector[i] / group.count();
    }
    double distance2 = -1.0;
    for (int i = 0; i < averageVector.count(); ++i)
      distance2 += pow(averageVector[i] - value[i], 2);
    if (resultGroup == -1 && distance2 > 0.0)
    {
      resultGroup = groupIndex;
      minDistance2 = distance2;
    }
    if (distance2 > 0.0 && distance2 < minDistance2)
    {
      minDistance2 = distance2;
      resultGroup = groupIndex;
    }
  }
  return resultGroup;
}

int Utils::calcByRegion(const QList< QList<QVector<double> > >& groups, const QVector<double>& value)
{
  int resultGroup = -1;

  QList<QMap<double, int> > sortedVectorList;
  for (int groupIndex = 0; groupIndex < groups.count(); ++groupIndex)
  {
    QList<QVector<double> > group = groups.at(groupIndex);
    QMap<double, int> sortedVectors;
    for(int vectorIndex = 0; vectorIndex < group.count(); ++vectorIndex)
    {
      QVector<double> vector = group.at(vectorIndex);
      double distance2 = -1.0;
      for (int i = 0; i < vector.count(); ++i)
        distance2 += pow(vector.at(i) - value.at(i), 2);
      sortedVectors.insertMulti(distance2, vectorIndex);
    }
    sortedVectorList.append(sortedVectors);
  }

  double minDistance2 = -1.0;
  for (int i = 0; i < sortedVectorList.count(); ++i)
  {
    QMap<double, int>::const_iterator cit = sortedVectorList.at(i).cbegin();
    if (requiredVectorCount <= sortedVectorList.at(i).count())
      cit += requiredVectorCount;
    else
      continue;

    if (minDistance2 < 0.0)
    {
      minDistance2 = cit.key();
      resultGroup = i;
    }

    if (cit.key() < minDistance2)
    {
      minDistance2 = cit.key();
      resultGroup = i;
    }
  }

  return resultGroup;
}

int Utils::calcByMinValue(const QList< QList<QVector<double> > >& groups, const QVector<double>& value)
{
  int resultGroup = -1;
  double minDistance2 = 0.0;

  for (int groupIndex = 0; groupIndex < groups.count(); ++groupIndex)
  {
    QList<QVector<double> > group = groups.at(groupIndex);
    double distance2 = -1.0;
    for(int vectorIndex = 0; vectorIndex < group.count(); ++vectorIndex)
    {
      QVector<double> vector = group.at(vectorIndex);
      for (int i = 0; i < vector.count(); ++i)
        distance2 += pow(vector.at(i) - value.at(i), 2);
      if (resultGroup == -1 && distance2 > 0.0)
      {
        resultGroup = groupIndex;
        minDistance2 = distance2;
      }
      if (distance2 > 0.0 && distance2 < minDistance2)
      {
        minDistance2 = distance2;
        resultGroup = groupIndex;
      }
    }
  }

  return resultGroup;
}