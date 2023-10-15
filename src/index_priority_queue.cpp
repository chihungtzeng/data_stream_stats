#include <glog/logging.h>
#include <glog/stl_logging.h>
#include <bitset>
#include <cmath>
#include <cstdint>
#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>
#include <climits>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <numeric>
#include <queue>
using namespace std;

class IPQ
{
private:
  using ipair = pair<int, int>;

  unordered_map<int, int> idx_of_;  // key -> kvs_ index
  vector<ipair> kvs_;

  void build()
  {
    for (int i = kvs_.size() >> 1; i >= 0; i--)
    {
      heapify(i);
    }
  }

  void update_pos(int idx)
  {
    idx_of_[kvs_[idx].second] = idx;
  }

  void heapify(int i)
  {
    int smallest = i;
    int lc = left(i), rc = right(i);
    int sz = kvs_.size();
    if (lc < sz && kvs_[lc] < kvs_[smallest])
      smallest = lc;
    if (rc < sz && kvs_[rc] < kvs_[smallest])
      smallest = rc;
    if (smallest != i)
    {
      swap(kvs_[smallest], kvs_[i]);
      update_pos(smallest);
      update_pos(i);
      heapify(smallest);
    }
  }
  void bubble_up(int i)
  {
    int pi = parent(i);
    while (i > 0 && kvs_[pi].first > kvs_[i].first)
    {
      swap(kvs_[i], kvs_[pi]);
      update_pos(i);
      update_pos(pi);

      i = pi;
      pi = parent(i);
    }
  }

  int parent(int i)
  {
    return (i - 1) >> 1;
  }
  int left(int i)
  {
    return (i << 1) + 1;
  }
  int right(int i)
  {
    return (i << 1) + 2;
  }
  void satisfy_invariant()
  {
    CHECK(kvs_.size() == idx_of_.size());

    int n = kvs_.size();
    for (int i = kvs_.size() / 2; i >= 0; i--)
    {
      CHECK(idx_of_[kvs_[i].second] == i);
      int lc = left(i);
      if (lc < n)
      {
        CHECK(kvs_[i].first <= kvs_[lc].first);
      }
      int rc = right(i);
      if (rc < n)
        CHECK(kvs_[i].first <= kvs_[rc].first);
    }
  }

public:
  IPQ()
  {
  }

  void dump()
  {
    LOG(INFO) << kvs_;
  }

  bool empty()
  {
    return kvs_.empty();
  }

  ipair top()
  {
    if (empty())
    {
      return { INT_MIN, INT_MIN };
    }
    return kvs_.front();
  }

  void update(int key, int val)
  {
    if (idx_of_.count(key) == 0)
      return;

    auto i = idx_of_[key];
    kvs_[i].first = val;
    heapify(i);
    bubble_up(i);
    satisfy_invariant();
  }

  void push(int key, int val)
  {
    kvs_.push_back({ val, key });

    update_pos(kvs_.size() - 1);
    bubble_up(kvs_.size() - 1);
    satisfy_invariant();
  }

  void pop()
  {
    if (empty())
      return;
    auto key = kvs_[0].second;
    swap(kvs_[0], kvs_[kvs_.size() -1]);
    kvs_.pop_back();
    heapify(0);
    idx_of_.erase(key);
    satisfy_invariant();
  }
};
