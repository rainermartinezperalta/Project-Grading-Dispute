### Assignment Instructions

#### Q1. Dining Philosopher's Problem (50 Points)

A popular restaurant serves delicious food, and hungry customers keep coming back. The restaurant has two kinds of tables: small and big. The customers come in two kinds of groups: small and big. A big group can dine at a big table, but not at a small table. A small group can dine at a small table. In addition, a small group can dine at a big table if:
- There is no small table available.
- There is a big table available.
- No big group is waiting.

If no proper table is available, a group must wait. To simplify the problem, the groups are not seated in order of arrival (i.e., the arrival time of a group does not determine when the group is seated). For example, group 1 may arrive earlier but is seated later than group 2.

In this problem, we write a multi-threaded program to simulate the process of groups of guests dining at the restaurant. Each group is a thread, and each group will dine at the restaurant `n_meals` times. The structures for restaurants (`restaurant_t`) and groups (`group_t`) are provided in `dining.h`. Descriptions of each field are included in the header file.

The starter code is provided in `dining.c`. The `main()` function has been implemented for you. The function takes 5 command line arguments:
1. `n_small_groups` (number of small groups),
2. `n_big_groups` (number of big groups),
3. `n_small_tables` (number of small tables),
4. `n_big_tables` (number of big tables),
5. `n_meals` (the number of meals each group will have).

The `main()` function sets up the computation by creating an instance of the shared struct `restaurant_t` and `nbT` number of threads. Each thread takes its instance of the `group_t` struct and calls the function `thread_grp()`. The `main()` function finally joins all threads and destroys the mutex and condition variables.

The function `thread_grp()` has also been implemented for you. This function:
- Sets a random wait time for each thread.
- Repeats the following process `n_meals` times:
  1. A thread (group) waits for a random amount of time and then prints a message that it has arrived.
  2. If the group size is small, it calls the function `small_group_dining()`.
  3. Otherwise, it calls the function `big_group_dining()`.

Your task is to implement two functions:
1. `small_group_dining()`
2. `big_group_dining()`

The structure of the functions is similar to what is provided in `dining_process()`. Detailed instructions on how to implement the functions are also provided in the starter code. Please read the instructions carefully. Note that you do not need to implement the function `dining_process()`. It has only been included to give you a template for what needs to be done. **To receive full credit, a leaving group cannot simply broadcast to all waiting groups. It should wake up only an appropriate group.**

#### Sample Output

A sample output of the program is provided in the file `sample-output.txt`. The output is produced by running the following command that passes as command-line arguments 5 small groups, 5 big groups, 3 small tables, 3 big tables, and 5 meals per group. Like the other multi-threaded programs we have written, the program likely produces different outputs on multiple runs, even if the parameters are the same.

```bash
➜ ./dining 5 5 3 3 5 > sample-output.txt
```

---

#### Q2. Multithreaded Sorting (50 Points)

In this question, you need to implement a multithreaded sorting algorithm inspired by selection sort. This algorithm divides the input array into segments, and each thread independently finds the smallest element within its assigned segment. The smallest element among all segments is then identified and appended to the sorted output array.

This process is repeated until the entire input array is sorted. Below are the specific steps given an input array of length `n` and `t` threads:

1. **Create an empty output array of size `n`** to store the sorted elements.
2. **Divide the input array into `t` segments** of approximately equal length.
3. **Iterative Sorting:**
   - Each thread finds the smallest element within its assigned segment.
   - Determine the smallest element among the `t` smallest elements found in the previous step.
   - Add the global minimum to the output array.
   - Swap the global minimum with the first element of its segment and reduce the segment size.
4. **Repeat Steps 3a-3d** until the output array is full.

Here is an example of how the algorithm should work with `n = 4` and `t = 2`:

**Input array:**
```plaintext
2; 3; 4; 1
```

**Output array:**
```plaintext

```
**Divide the input array into `t = 2` segments:**
```plaintext
Thread 1 array: 2; 3
Thread 2 array: 4; 1
```

1. The smallest element from Thread 1 is `2` and the smallest element from Thread 2 is `1`. The smallest element out of the collection of smallest elements is `1` and is added to the output:
```plaintext
Output array: 1
```
1 is swapped with the head of segment 2 before shrinking the segment to eliminate it:
```plaintext
Thread 1 array: 2; 3
Thread 2 array: 1(crossed out); 4
```

**Repeat the process until all elements are sorted.**

You need to finish implementing the `sortThread()` function in `selectionSort.c`. Open `selectionSort.h`. Each thread is given a `Segment`. During each "wave" of step 3, each thread determines the minimum element in its segment. When the thread determines its minimum element, it compares it to the `best` field of the `Share` structure that the threads share. If it is lower than `best`, it updates `best` and `winner` fields of the `Share` structure. Note that threads need to "meet up" at the end of the wave, before finding the next minimum to add to the result array. This is where the condition variable (`done`) in the `Share` structure comes in.

#### Sample Sessions
Below are some sample sessions of running the program:

```bash
$ ./selectionSortTest 10 3
238335 289383 516649 636915 641421 692777 747793 760492 885386 930886

$ ./selectionSortTest 100000 1
...
real    0m12.507s
user    0m12.435s
sys     0m0.017s

$ ./selectionSortTest 100000 4
...
real    0m4.830s
user    0m4.158s
sys     0m1.569s
```

---

For questions or clarifications, please reach out to the instructor or teaching assistant.