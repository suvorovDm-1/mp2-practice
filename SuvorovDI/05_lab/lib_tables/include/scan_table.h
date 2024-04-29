#pragma once

#include <iostream>
#include "table.h"

template <typename TKey, typename TData>
class ScanTable : public Table<TKey, TData>
{
protected:
  TabRecord<TKey, TData> **recs;

public:
  ScanTable(int maxSize);
  ScanTable(const ScanTable &t);
  ~ScanTable();

  TabRecord<TKey, TData> *Find(TKey key) override; // const??
  void Insert(TKey key, TData *data) override;
  void Remove(TKey key) override;

  virtual TabRecord<TKey, TData> *GetCurrent() const override
  {
    return recs[currPos];
  }

  bool IsEnded() const noexcept override
  {
    return currPos == count;
  }

  friend std::ostream& operator<<(std::ostream& out, const ScanTable<TKey, TData>& t)
  {
    if (t.IsEmpty())
    {
      out << "EMPTY_TABLE\n";
      return out;
    }

    ScanTable<TKey, TData> tmp(t);
    while (!tmp.IsEnded())
    {
      out << *tmp.GetCurrent();
      tmp.Next();
    }
    return out;
  }
};

template <typename TKey, typename TData>
ScanTable<TKey, TData>::ScanTable(int maxSize) : Table(maxSize)
{
  recs = new TabRecord<TKey, TData>* [maxSize];
  currPos = 0;
}

template <typename TKey, typename TData>
ScanTable<TKey, TData>::ScanTable(const ScanTable<TKey, TData>& t) : Table(t.maxSize)
{
  if (t.IsEmpty())
  {
    recs = nullptr;
    return;
  }

  count = t.count;
  currPos = 0;
  recs = new TabRecord<TKey, TData> *[maxSize];

  for (int i = 0; i < count; i++)
  {
    recs[i] = new TabRecord<TKey, TData>(t.recs[i]->key, t.recs[i]->data);
  }
}

template <typename TKey, typename TData>
ScanTable<TKey, TData>::~ScanTable()
{
  delete[] recs;
}

template <typename TKey, typename TData>
TabRecord<TKey, TData>* ScanTable<TKey, TData>::Find(TKey key)
{
  if (IsEmpty())
    return nullptr;

  for (int i = 0; i < count; i++)
  {
    if (recs[i]->key == key)
    {
      currPos = i;
      return recs[i];
    }
  }
  return nullptr;
}

template <typename TKey, typename TData>
void ScanTable<TKey, TData>::Insert(TKey key, TData* data)
{
  if (IsFull())
    throw std::exception("table is full\n");
  TabRecord<TKey, TData>* res = new TabRecord<TKey, TData>(key, data);
  recs[count++] = res;
}

template <typename TKey, typename TData>
void ScanTable<TKey, TData>::Remove(TKey key)
{
  if (IsEmpty())
    throw std::exception("table is empty\n");
  if (Find(key) == nullptr)
    throw std::exception("no such element\n");

  delete recs[currPos];
  recs[currPos] = recs[--count];
}