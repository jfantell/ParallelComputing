import threading
import multiprocessing
import time
  
def Fibonacci_driver(n): 
	if n<0: 
		print("Invalid Input") 
	elif n==1: 
		return 0
	elif n==2: 
		return 1
	else: 
		return Fibonacci_driver(n-1)+Fibonacci_driver(n-2)

def Fibonacci(n):
	print(f"Fib {n} is {Fibonacci_driver(n)}")
  
if __name__ == "__main__": 
	num_tasks = 5

	# creating thread
	start = time.time()
	threads_list = []
	for i in range(num_tasks):
		threads_list.append(threading.Thread(target=Fibonacci, args=(40,)))

	for i in range(num_tasks):
		threads_list[i].start()
	
	for i in range(num_tasks):
		threads_list[i].join()
	
	end = time.time()
	thread_duration = end-start
	print(f"Threads completed their tasks in {thread_duration} s!\n") 

	# creating process 
	start = time.time()
	processes_list = []

	for i in range(num_tasks):
		processes_list.append(multiprocessing.Process(target=Fibonacci, args=(40,)) )

	for i in range(num_tasks):
		processes_list[i].start()
	
	for i in range(num_tasks):
		processes_list[i].join()
  
	end = time.time()
	process_duration = end-start
	print(f"Processes completed their tasks in {process_duration} s!\n")

	if process_duration < thread_duration:
		print("Multiprocessing wins!")
	else:
		print("Multithreading wins!")