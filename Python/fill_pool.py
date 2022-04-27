# An example of how to fill a multi-processing / multi-threading pool with dependent tasks.
#
# Some observations:
#
# - `map` will immediately turn `iterable` into `list(iterable)`, then apply them to each task.
# - `imap` will call `next` on `iterable` lazily.
# - Once `imap` is called, it starts executing on the background. If we call next on the iterator, we will block until
#   the result is returned. It does not postpone the execution of tasks to the time we call next on it.
#
# Ref: https://stackoverflow.com/questions/71907940/how-to-explain-these-multiprocessing-execution-results

import time
from multiprocessing import Pool, current_process, Value, Array
from itertools import chain

worker_num = 8
big_task_num = 10

start = Value('d', 0.0)
table = [Array('c', b' ' * 40) for _ in range(worker_num)]


def measure(f):
    start.value = time.time()
    for r in table:
        r.value = b'| ' * 20
    f()
    print(f'##### {f.__name__}: {time.time() - start.value}s #####')
    print('\n'.join(r.value.decode() for r in table))
    print(flush=True)


def write_table(msg):
    proc_idx = int(current_process().name[len('ForkPoolWorker-'):]) - 1
    time_idx = int(time.time() - start.value) * 2 + 1
    table[proc_idx][time_idx:time_idx + len(msg)] = msg


def big_task(_):
    write_table(b'b b b')
    time.sleep(3)
    return range(3)


def small_task(_):
    write_table(b's')
    time.sleep(1)


p = Pool(worker_num)


@measure
def test1():
    """
    ##### test1: 16.0493221282959s #####
    |b b b| | | |s| |s| | |s| | |s| | | | |
    |b b b| | | | |s| | |s| |s| | |s| | | |
    |b b b| | | |s| | |s| |s| | |s| | | | |
    |b b b| | | | |s| | |s| | |s| | | | | |
    |b b b|b b b| | |s| | |s| |s| | | | | |
    |b b b| | | | |s| |s| | |s| | |s| | | |
    |b b b| | | |s| | |s| | |s| |s| | | | |
    |b b b|b b b| | |s| |s| | |s| |s| | | |
    """
    for i in p.map(big_task, range(big_task_num)):
        p.map(small_task, i)


@measure
def test2():
    """
    ##### test2: 13.053321838378906s #####
    |b b b| |s| |s| |s| | |s| | | | | | | |
    |b b b|b b b| |s| | |s| |s| | | | | | |
    |b b b| |s| |s| | |s| |s| | | | | | | |
    |b b b|s| |s| |s| | |s| | | | | | | | |
    |b b b|s| |s| | |s| |s| | | | | | | | |
    |b b b|s| |s| | |s| | |s| | | | | | | |
    |b b b| |s| |s| | |s| | |s| | | | | | |
    |b b b|b b b| |s| |s| | |s| | | | | | |
    """
    for i in p.imap(big_task, range(big_task_num)):
        p.map(small_task, i)


@measure
def test3():
    """
    ##### test3: 10.020010232925415s #####
    |b b b| | | |s|s|s|s| | | | | | | | | |
    |b b b| | | |s|s|s|s| | | | | | | | | |
    |b b b| | | |s|s|s|s| | | | | | | | | |
    |b b b|b b b|s|s|s|s| | | | | | | | | |
    |b b b| | | |s|s|s| | | | | | | | | | |
    |b b b|b b b|s|s|s|s| | | | | | | | | |
    |b b b| | | |s|s|s| | | | | | | | | | |
    |b b b| | | |s|s|s|s| | | | | | | | | |
    """
    p.map(
        small_task,
        chain.from_iterable(
            p.imap(big_task, range(big_task_num))
        )
    )


@measure
def test4():
    """
    ##### test4: 8.007385969161987s #####
    |b b b|s|s|s|s| | | | | | | | | | | | |
    |b b b|s|s|s|s| | | | | | | | | | | | |
    |b b b|s|s|s|s| | | | | | | | | | | | |
    |b b b|b b b|s|s| | | | | | | | | | | |
    |b b b|s|s|s|s| | | | | | | | | | | | |
    |b b b|b b b|s|s| | | | | | | | | | | |
    |b b b|s|s|s|s|s| | | | | | | | | | | |
    |b b b|s|s|s|s|s| | | | | | | | | | | |
    """
    list(p.imap(
        small_task,
        chain.from_iterable(
            p.imap(big_task, range(big_task_num))
        )
    ))
