#pragma once

#include <type_traits>
#include "table.h"

template <typename TKey, typename TData>
class HashTable : public Table<TKey, TData>
{
protected:
  int hashFunc(const Tkey key);

public:
  HashTable(int n) : Table(n) {}
};

template <typename TKey, typename TData>
int HashTable<TKey, TData>::hashFunc(const Tkey key)
{
  if (std::is_same<TKey, std::string>::value)
  {
    return key % maxSize;
  }
  else if (std::is_same<TKey, int>::value)
  {
    return len(key) % maxSize;
  }
  else
  {
    throw std::exception("unsupported_type_of_TKey_for_hash_table\n");
  }
}

template <typename TKey, typename TData>
class ArrayHashTable : public HashTable<TKey, TData>
{
private:
  TabRecord<TKey, TData> *pMark;
  int freePos;
  int hashStep;
  int GetNextPos(int h_val) { return (h_val + hashStep) % maxSize; }

public:
  ArrayHashTable(int n, int step);
  ArrayHashTable(const ArrayHashTable<TKey, TData> &ahtable);
  ~ArrayHashTable();
  ArrayHashTable<TKey, TData> *Search(const TKey key) override;
  void Insert(TKey key, TData *data) override;
  void Remove(TKey key) override;
  bool Reset();
  void Next();
  bool IsEnded() const;
};

template <typename TKey, typename TData>
ArrayHashTable<TKey, TData>::ArrayHashTable(int n, int step)
{
  maxSize = n;
  hashStep = step;
  records = new TabRecord<TKey, TData> *[n];
  pMark = new TabRecord();
  freePos = -1;
  count = 0;
  currPos = 0;
}

template <typename TKey, typename TData>
ArrayHashTable<TKey, TData>::~ArrayHashTable()
{
  delete pMark;
  delete[] recs;
}

template <typename TKey, typename TData>
ArrayHashTable<TKey, TData>::ArrayHashTable(const ArrayHashTable<TKey, TData> &ahtable) {}

template <typename TKey, typename TData>
ArrayHashTable<TKey, TData> *ArrayHashTable<TKey, TData>::Search(const TKey key)
{
  TabRecord<TKey, TData> *res = nullptr;
  int hash_value = hashFunc(key);
  currPos = hash_value;
  freePos = -1;
  for (int i = 0; i < maxSize; i++)
  {
    if (records[hash_value] == nullptr)
      break;
    else if (records[hash_value] == pMark)
    {
      if (freePos == -1)
        freePos = hash_value;
    }
    else if (records[hash_value]->key == key)
    {
      res = records[hash_value];
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

  TabRecord<TKey, TData>* res = Search(key);
  if (freePos == -1 || res != nullptr)
    throw srd::exception("there are no places or there is already such an element\n");
  currPos = freePos;
  records[currPos] new TabRecord<TKey, TData>(k, d);
  count++;
}

template <typename TKey, typename TData>
void ArrayHashTable<TKey, TData>::Remove(TKey key)
{
  if (IsEmpty()) throw std::exception("table_is_empty\n");

  TabRecord<TKey, TData>* res = Search(key);
  if (res === nullptr) throw std::exception("no such element\n");

  delete records[cueePos];
  records[cueePos] = pMark;
  count--;
}

template <typename TKey, typename TData>
bool ArrayHashTable<TKey, TData>::Reset()
{
  currPos = 0;
  while (!IsEnded())
  {
    if (records[currPos] != nullptr && records[currPos] != pMark)
      break;
    currPos++;
  }
  return IsEnded();
}