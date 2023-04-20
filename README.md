# Bottleneck-Predictions-of-Parallel-Programs

NYU Multiple Processor final project

2023.04

Authors:

Scott Chu zc2396@nyu.edu

Qiyuan Huang qh2086@nyu.edu

Yiwei Shao ys5070@nyu.edu

Juexiao Zhang jz4725@nyu.edu

## Omptracing Configuration
[Omptracing](https://ompcluster.readthedocs.io/en/latest/omptracing.html) requires support of a new feature of OpenMP, [OMPT](https://www.openmp.org/spec-html/5.0/openmpsu15.html). It is implemented by clang and cannot be easily configured on CIMS server. So we use docker to configure the environment locally and here are the instructions:
1. Get the docker image of omptracing  
```docker pull ompcluster/runtime:latest``` 
2. Enter the root of repository, run  
```docker run -v "$PWD:$PWD" -w "$PWD" -it ompcluster/runtime:latest bash```
3. Link the omptracing library and config file 
```
export OMP_TOOL_LIBRARIES=/opt/omptracing/lib/libomptracing.so
export OMPTRACING_CONFIG_PATH=./config.json
```
4. Compile with  
``` clang++ -O3 -Wall -g -fopenmp -latomic -o <output_path> <source_path> ```
5. Run the program and there will be a json file produced in the PWD, using ```chrome://tracing``` to visualize or ```get_tracing()``` in [analyze.ipynb](https://github.com/suker0723/Bottleneck-Predictions-of-Parallel-Programs/blob/main/analyze.ipynb) to get the result.

## Jupyter notebook environments
package: numpy, pandas, json, regex, os


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













