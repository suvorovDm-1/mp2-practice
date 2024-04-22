#pragma once

#include <iostream>
#include "table.h"

template <typename TKey, typename TData>
class ScanTable: public Table<TKey, TData> {
protected:
  TabRecord<TKey, TData>** recs;
public:
  ScanTable(int maxSize);
  ScanTable(const ScanTable&t);
  ~ScanTable();

  TabRecord<TKey, TData>* Find(TKey key) override;
  void Insert(TKey key, TData* data) override;
  void Remove(TKey key) override;

  virtual TabRecord<TKey, TData>* GetCurrent() const override {
    return recs[currPos];
  }

  friend std::ostream& operator<<(std::ostream& out, const ScanTable<TKey, TData>& t) {
    if (t.IsEmpty()) {
      out << "EMPTY_TABLE\n";
      return out;
    }

    for (int i = 0; i < t.count; i++) {
      out << *t.recs[i];
    }
    return out;
  }
};

template <typename TKey, typename TData>
ScanTable<TKey, TData>::ScanTable(int maxSize) : Table(maxSize) {
  recs = nullptr;
}

template <typename TKey, typename TData>
ScanTable<TKey, TData>::ScanTable(const ScanTable<TKey, TData>&t) {
  if (t.IsEmpty()) {
    maxSize = t.maxSize;
    count = 0;
    currPos = -1;
    recs = nullptr;
    return;
  }

  maxSize = t.maxSize;
  count = t.count;
  currPos = 0;

  for (int i = 0; i < count; i++) {
    recs[i] = new TabRecord<TKey, TData>(t.recs[i]->key, t.recs[i]->data);
  }
}

template <typename TKey, typename TData>
ScanTable<TKey, TData>::~ScanTable() {
  delete[] recs;
}
template <typename TKey, typename TData>
TabRecord<TKey, TData>* ScanTable<TKey, TData>::Find(TKey key) {
  if (IsEmpty()) return nullptr;

  for (int i = 0; i < count; i++) {
    if (recs[i]->key == key) {
      currPos = i;
      return recs[i];
    }
  }
  return nullptr;
}

template <typename TKey, typename TData>
void ScanTable<TKey, TData>::Insert(TKey key, TData* data){
  if(IsFull())
    throw std::exception("table is full\n");
  recs[count++] = new TabRecord<TKey, TData>(key, data);
}

template <typename TKey, typename TData>
void ScanTable<TKey, TData>::Remove(TKey key){
  if(IsEmpty())
    throw std::exception("table is empty\n");
  if(Find(key)==nullptr)
    throw std::exception("no such element\n");

  delete recs[currPos];
  recs[currPos] = recs[--count];
}