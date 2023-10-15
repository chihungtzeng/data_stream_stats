#include <vector>
#include <unordered_map>

class IndexedPriorityQueue
{
public:
  IndexedPriorityQueue();
  bool empty();
  ipair top();
  void update(int key, int val);
  void push(int key, int val);
  void pop();

private:
  using ipair = pair<int, int>;

  unordered_map<int, int> idx_of_;  // key -> kvs_ index
  vector<ipair> kvs_;

  void build();
  void update_pos(int idx);

  // Heapify at index i
  void heapify(int i);
  void bubble_up(int i);
  int parent(int i);
  int left(int i);
  int right(int i);
};
