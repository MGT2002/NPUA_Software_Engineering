import random
import string
import time
import os
from collections import defaultdict
from concurrent.futures import ThreadPoolExecutor
import multiprocessing


# Step 1: Create a large text file with random words and sentences
def create_large_file(filename, num_lines=100000, num_words_per_line=10):
    """Generates a large text file with random words."""
    with open(filename, 'w') as f:
        for _ in range(num_lines):
            line = ' '.join(''.join(random.choices(string.ascii_lowercase, k=random.randint(3, 10))) for _ in range(num_words_per_line))
            f.write(line + '\n')


# Step 2: Sequential word counting function
def count_words_sequential(filename):
    """Count word frequencies sequentially from the file."""
    word_count = defaultdict(int)
    
    with open(filename, 'r') as f:
        for line in f:
            words = line.split()
            for word in words:
                word_count[word] += 1
                
    return word_count


# Step 3: Multithreading word counting function
def count_words_in_chunk(start, end, filename):
    """Count words in a file chunk."""
    word_count = defaultdict(int)
    
    with open(filename, 'r') as f:
        f.seek(start)
        lines = f.read(end - start).splitlines()
        
        for line in lines:
            words = line.split()
            for word in words:
                word_count[word] += 1
                
    return word_count


def count_words_multithreading(filename, num_threads=4):
    """Count word frequencies using multithreading."""
    file_size = os.path.getsize(filename)
    chunk_size = file_size // num_threads
    futures = []
    word_count = defaultdict(int)

    # Create a ThreadPoolExecutor to handle multithreading
    with ThreadPoolExecutor(max_workers=num_threads) as executor:
        for i in range(num_threads):
            start = i * chunk_size
            end = start + chunk_size if i != num_threads - 1 else file_size
            futures.append(executor.submit(count_words_in_chunk, start, end, filename))

        for future in futures:
            chunk_word_count = future.result()
            for word, count in chunk_word_count.items():
                word_count[word] += count
                
    return word_count

def count_words_in_chunk_mp(start, end, filename, result_queue):
    """Count words in a chunk of the file using multiprocessing."""
    word_count = defaultdict(int)
    
    with open(filename, 'r') as f:
        f.seek(start)  # Move to the start position
        lines = f.read(end - start).splitlines()  # Read the chunk of the file
        
        for line in lines:
            words = line.split()  # Split the line into words
            for word in words:
                word_count[word] += 1
    
    result_queue.put(word_count)  # Put the result into the queue


def count_words_multiprocessing(filename, num_processes=4):
    """Count word frequencies using multiprocessing."""
    file_size = os.path.getsize(filename)  # Get the size of the file
    chunk_size = file_size // num_processes  # Determine the size of each chunk
    
    processes = []
    result_queue = multiprocessing.Queue()  # Queue to store results
    word_count = defaultdict(int)
    
    # Create and start processes
    for i in range(num_processes):
        start = i * chunk_size
        end = start + chunk_size if i != num_processes - 1 else file_size  # Ensure the last process reads until the end
        p = multiprocessing.Process(target=count_words_in_chunk_mp, args=(start, end, filename, result_queue))
        processes.append(p)
        p.start()
    
    # Wait for all processes to finish
    for p in processes:
        p.join()
    
    # Collect results from the queue
    while not result_queue.empty():
        chunk_word_count = result_queue.get()
        for word, count in chunk_word_count.items():
            word_count[word] += count
                
    return word_count



# Step 5: Helper function to measure execution time
def measure_time(func, *args, **kwargs):
    """Helper function to measure the execution time."""
    start_time = time.time()
    result = func(*args, **kwargs)
    end_time = time.time()
    print(f"{func.__name__} executed in {end_time - start_time:.4f} seconds.")
    return result


filename = 'large_text_file.txt'

# Create a large file (this only needs to be done once)
print("Creating a large text file...")
create_large_file(filename, num_lines=100000, num_words_per_line=10)
print(f"Large file '{filename}' created.\n")

# Sequential Word Counting
print("Sequential word counting:")
measure_time(count_words_sequential, filename)

# Multithreading Word Counting
print("\nMultithreading word counting:")
measure_time(count_words_multithreading, filename, num_threads=4)

# Multiprocessing Word Counting
print("\nMultiprocessing word counting:")
measure_time(count_words_multiprocessing, filename, num_processes=4)
