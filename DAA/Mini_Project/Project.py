import argparse
import random
from contextlib import contextmanager
from multiprocessing import Pool, cpu_count
from timeit import default_timer as time
from tabulate import tabulate

CPU_COUNT = cpu_count()

class Timer:
    def __init__(self, *steps):
        self._time_per_step = dict.fromkeys(steps)

    def __getitem__(self, item):
        return self.time_per_step[item]

    @property
    def time_per_step(self):
        return {step: elapsed_time for step, elapsed_time in self._time_per_step.items() if elapsed_time is not None and elapsed_time > 0}

    def start_for(self, step):
        self._time_per_step[step] = -time()

    def stop_for(self, step):
        self._time_per_step[step] += time()

def merge_sort(array):
    array_length = len(array)
    if array_length <= 1:
        return array
    middle_index = array_length // 2
    left = merge_sort(array[:middle_index])
    right = merge_sort(array[middle_index:])
    return merge(left, right)

def merge(*arrays):
    left, right = arrays[0] if len(arrays) == 1 else arrays
    sorted_list = [0] * (len(left) + len(right))
    i = j = k = 0
    while i < len(left) and j < len(right):
        if left[i] < right[j]:
            sorted_list[k] = left[i]
            i += 1
        else:
            sorted_list[k] = right[j]
            j += 1
        k += 1
    while i < len(left):
        sorted_list[k] = left[i]
        i += 1
        k += 1
    while j < len(right):
        sorted_list[k] = right[j]
        j += 1
        k += 1
    return sorted_list

@contextmanager
def process_pool(size):
    """Create a process pool and block until all processes have completed."""
    pool = Pool(size)
    yield pool
    pool.close()
    pool.join()

def parallel_merge_sort(array, ps_count):
    """Perform parallel merge sort."""
    timer = Timer("sort", "merge", "total")
    timer.start_for("total")
    timer.start_for("sort")
    step = int(len(array) / ps_count)
    with process_pool(size=ps_count) as pool:
        array = [array[i * step: (i + 1) * step] for i in range(ps_count)] + [array[ps_count * step:]]
        array = pool.map(merge_sort, array)
        timer.stop_for("sort")
        timer.start_for("merge")
        while len(array) > 1:
            extra = array.pop() if len(array) % 2 == 1 else None
            array = [(array[i], array[i + 1]) for i in range(0, len(array), 2)]
            array = pool.map(merge, array) + ([extra] if extra else [])
        timer.stop_for("merge")
    timer.stop_for("total")
    final_sorted_list = array[0]
    return timer, final_sorted_list

def get_command_line_parameters():
    parser = argparse.ArgumentParser(description="""Implement merge sort and multithreaded merge sort.
    Compare the time required by both algorithms.
    Also, analyze the performance of each algorithm for the best case and the worst case."""
    )
    parser.add_argument(
        "-j", "--jobs", help="Number of processes to launch", required=False, default=CPU_COUNT,
        type=lambda x: int(x) if 0 < int(x) <= CPU_COUNT else parser.error(f"Number of processes must be between 1 and {CPU_COUNT}"),
    )
    parser.add_argument(
        "-l", "--length", help="Length of the array to sort", required=False, default=random.randint(3 * 10**6, 4 * 10**6),
        type=lambda x: int(x) if 0 < int(x) else parser.error("Length of the array must be greater than 0"),
    )
    parser.add_argument(
        "-a", "--all", help="Test all the variable length", required=False, default=False, action="store_true",
    )
    return parser.parse_args()

def main(jobs, length, conclusion):
    """Main function."""
    main_timer = Timer("single_core", "list_generation")
    main_timer.start_for("list_generation")
    randomized_array = [random.randint(0, i * 100) for i in range(length)]
    main_timer.stop_for("list_generation")
    print(f"List length: {length}")
    print(f"Random list generated in {main_timer['list_generation']:.6f}s\n")
    randomized_array_sorted = randomized_array[:]
    randomized_array_sorted.sort()
    print("Starting simple sort.")
    main_timer.start_for("single_core")
    sorted_array = merge_sort(randomized_array)
    main_timer.stop_for("single_core")
    assert sorted_array == randomized_array_sorted, "The sorted array is not correct."
    print(f"Single Core elapsed time: {main_timer['single_core']:.6f}s\n")
    print("Starting parallel sort.")
    parallel_timer, parallel_sorted_array = parallel_merge_sort(randomized_array, jobs)
    print(f"Final merge duration: {parallel_timer['merge']:.6f}s")
    assert parallel_sorted_array == randomized_array_sorted, "The sorted array is not correct."
    print(f"{jobs}-Core elapsed time: {parallel_timer['total']:.6f}s\n" + " -" * 40 + "\n")
    conclusion.append([length, main_timer["single_core"], parallel_timer["total"]])

if __name__ == "__main__":
    parameters = get_command_line_parameters()
    jobs = parameters.jobs
    length = parameters.length
    all_cases = parameters.all
    conclusion = []
    print(f"Using {jobs} cores\n")
    if all_cases:
        l = 1
        while l < 10**8:
            main(jobs, l, conclusion)
            l *= 10
    else:
        main(jobs, length, conclusion)
    print(tabulate(conclusion, headers=["Array Length", "Single-Threaded", "Multi-Threaded"], tablefmt="outline"))
