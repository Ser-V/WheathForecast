#include "Utils.h"

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
  return -1;
}

int calcByMinValue(const QList< QList<QVector<double> > >& groups, const QVector<double>& value)
{
  return -1;
}