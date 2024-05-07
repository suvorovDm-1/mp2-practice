#pragma once

#include <type_traits>
#include "table.h"

template <typename TKey, typename TData>
class HashTable : public Table<TKey, TData>
{
protected:
  int hashFunc(const TKey key);

public:
  HashTable(int n) : Table<TKey, TData>(n) {}
};

template <typename TKey, typename TData>
int HashTable<TKey, TData>::hashFunc(TKey key)
{
  return key.length() % maxSize;
}
// КАК ОБРАБОТАТЬ СЛУЧАЙ, КОГДА TKey == int?!?!?!
// % не работает, выдает ошибку, что не перегружена для TKEY
// преобразование типа к int static_cast не работает
// спецификация класса - тоже не получилась!!!

template <typename TKey, typename TData>
class ArrayHashTable : public HashTable<TKey, TData>
{
private:
  TabRecord<TKey, TData>** recs;
  TabRecord<TKey, TData>* pMark;
  int freePos;
  int hashStep;
  int GetNextPos(int h_val) { return (h_val + hashStep) % maxSize; }

public:
  ArrayHashTable(int n, int step);
  ArrayHashTable(const ArrayHashTable<TKey, TData> &ahtable);
  ~ArrayHashTable();
  TabRecord<TKey, TData>* Find(const TKey key);
  void Insert(TKey key, TData *data);
  void Remove(TKey key);
  bool Reset();
  void Next();
  TabRecord<TKey, TData>* GetCurrent() const
  {
    if (IsEmpty())
      throw std::exception("Table_is_empty\n");
    return recs[currPos];
  }

  friend std::ostream& operator<<(std::ostream& out, const ArrayHashTable<TKey, TData>& aht)
  {
    if (aht.IsEmpty())
    {
      out << "EMPTY_TABLE\n";
      return out;
    }

    ArrayHashTable<TKey, TData> tmp(aht);
    tmp.Reset();
    while (!tmp.IsEnded())
    {
      out << *tmp.GetCurrent();
      tmp.Next();
    }
    return out;
  }
};

template <typename TKey, typename TData>
ArrayHashTable<TKey, TData>::ArrayHashTable(int n, int step)
: HashTable(n) {
  maxSize = n;
  hashStep = step;
  recs = new TabRecord<TKey, TData>* [n];
  for (int i = 0; i < maxSize; i++)
  {
    recs[i] = nullptr;
  }
  pMark = new TabRecord<TKey, TData>();
  freePos = -1;
  count = 0;
  currPos = -1;
}

template <typename TKey, typename TData>
ArrayHashTable<TKey, TData>::~ArrayHashTable()
{
  delete pMark;
  for (int i = 0; i < maxSize; i++)
  {
    if (recs[i] != nullptr) delete recs[i];
  }
  delete[] recs;
}

template <typename TKey, typename TData>
ArrayHashTable<TKey, TData>::ArrayHashTable(const ArrayHashTable<TKey, TData>& ahtable) 
: ArrayHashTable<TKey, TData>(ahtable.maxSize, ahtable.hashStep) {
  if (ahtable.IsEmpty())
  {
    return;
  }

  for(int i = 0; i < maxSize; i++)
  {
    recs[i] = new TabRecord<TKey, TData>(ahtable.recs[i]->key, ahtable.recs[i]->data);
  }
}

template <typename TKey, typename TData>
TabRecord<TKey, TData>* ArrayHashTable<TKey, TData>::Find(const TKey key)
{
  TabRecord<TKey, TData> *res = nullptr;
  int hash_value = hashFunc(key);
  currPos = hash_value;
  freePos = -1;
  for (int i = 0; i < maxSize; i++)
  {
    if (recs[hash_value] == nullptr)
    {
      freePos = hash_value;
      break;
    }
    else if (recs[hash_value] == pMark)
    {
      if (freePos == -1)
        freePos = hash_value;
    }
    else if (recs[hash_value]->key == key)
    {
      res = recs[hash_value];
      break;
    }

    hash_value = GetNextPos(hash_value);
    currPos = hash_value;
  }

  return res;
}

template <typename TKey, typename TData>
void ArrayHashTable<TKey, TData>::Insert(TKey key, TData *data) 
{
  if (IsFull()) throw std::exception("table_is_full\n");

  TabRecord<TKey, TData>* res = Find(key);
  if (freePos == -1 || res != nullptr)
    throw std::exception("there are no places or there is already such an element\n");
  currPos = freePos;
  recs[currPos] = new TabRecord<TKey, TData>(key, data);
  count++;
}

template <typename TKey, typename TData>
void ArrayHashTable<TKey, TData>::Remove(TKey key)
{
  if (IsEmpty()) throw std::exception("table_is_empty\n");

  TabRecord<TKey, TData>* res = Find(key);
  if (res == nullptr) throw std::exception("no such element\n");

  delete recs[currPos];
  recs[currPos] = pMark;
  count--;
}

template <typename TKey, typename TData>
bool ArrayHashTable<TKey, TData>::Reset()
{
  currPos = 0;
  while (!IsEnded())
  {
    if (recs[currPos] != nullptr && recs[currPos] != pMark)
      break;
    currPos++;
  }
  return IsEnded();
}

template <typename TKey, typename TData>
void ArrayHashTable<TKey, TData>::Next()
{
  if (IsEnded())
    throw std::exception("table is ended\n");
    
  while (!IsEnded())
  {
    if (recs[currPos] != nullptr && recs[currPos] != pMark)
      break;
    currPos++;
  }
}