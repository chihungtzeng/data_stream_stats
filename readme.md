#### Efficiently calculate statistics of online data within a given window size.

In applications that involve IOT devices, we usually care about the statistics of recent data of length n.
The typical statisitcs include average, standard deviation etc.
When a new piece of data arrives, we push it into the list and pop out the oldest data.
We can calculate the statistics in an efficient way by leveraging the previous results.
