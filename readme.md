#### Efficiently calculate statistics of online data within a given window size.

In applications that involve IOT devices, we usually care about the statistics of recent data of length n.
The typical statisitcs include average, standard deviation etc.
When a new piece of data arrives, we push it into the list and pop out the oldest data.
We can calculate the statistics in an efficient way by leveraging the previous results.

|          | Ours     | Trivial implementation |
|----------|----------|------------------------|
| sum      | O(1)     | O(n)                   |
| average  | O(1)     | O(n)                   |
| min      | O(1)     | O(n)                   |
| max      | O(1)     | O(n)                   |
| median   | O(log n) | O(n)                   |
| variance | O(1)     | O(n)                   |
| std      | O(1)     | O(n)                   |

