from multiprocessing import Pool
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

	# creating process 
	start = time.time()
	with Pool(num_tasks) as p:
		print(p.map(Fibonacci_driver, [40, 40, 40, 40, 40]))

	p.join()
	end = time.time()
	process_duration = end-start
	print(f"Processes completed their tasks in {process_duration} s!\n")
	