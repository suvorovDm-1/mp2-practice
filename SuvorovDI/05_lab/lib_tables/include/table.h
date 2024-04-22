#pragma once

#include <iostream>

template <typename TKey, typename TData>
struct TabRecord {
  TKey key;
  TData* data;

  TabRecord(TKey key, TData* data) {
    this->key = key;
    this->data = new TData(*data);
  }

  friend std::ostream& operator<<(std::ostream& out, const TabRecord<TKey, TData>& r) {
    out << "KEY: " << r.key << "\n-> VALUE: " << r.data << "\n";
    return out;
  }
};

template <typename TKey, typename TData>
class Table{
protected:
  int count;
  int maxSize;
  int currPos;
public:
  Table(int maxSize) {
    this->maxSize = maxSize;
    count = 0;
    currPos = -1;
  }
  virtual TabRecord<TKey, TData>* Find(TKey key) = 0;
  virtual void Insert(TKey key, TData* data) = 0;
  virtual void Remove(TKey key) = 0;
  bool IsFull() const noexcept {
    return count == maxSize;
  }
  bool IsEmpty() const noexcept {
    return count == 0;
  }
  virtual void Reset() noexcept {
    currPos = 0;
  }
  virtual bool IsEnded() const noexcept {
    return currPos == maxSize;
  }
  virtual void Next() {
    if (IsEnded()) throw std::exception("table is ended");
    currPos += 1;
  }
  virtual TabRecord<TKey, TData>* GetCurrent() const = 0;
};