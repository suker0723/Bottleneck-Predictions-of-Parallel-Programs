# Bottleneck-Predictions-of-Parallel-Programs

NYU Multiple Processor final project
2023.04
Scott Chu
Qiyuan Huang
Yiwei Shao
Juexiao Zhang

## Cache Miss tests
Please first compiled it using the provided Makefile.

(Optional)If you don't want to use Makefile, you may compile each program in test_cache_code using following command:

```gcc -fopenmp -g -std=c99 {matrix_*.c} -o {matrix_*}```

Install Valgrind if you haven't already. On Ubuntu, you can use the following command:
    
```sudo apt install valgrind```

Run your program with Valgrind's Cachegrind tool:

```valgrind --tool=cachegrind ./{matrix_*} ```

When finishing the valgrind, check its t number at the left, now you can see specific func's performance:

```cg_annotate cachegrind.out.<t_num> ```

(Optional) Use the kcachegrind tool to visualize the Cachegrind output:

```sudo apt install kcachegrind ```

Then check the graphs:

```kcachegrind cachegrind.out.<t_num> ```

If The D1 miss rate reaches the threshold 4.6%, you probably have a bottleneck of cache access in your program.










