from multiprocessing import Process, Lock, Manager
import time

def f(l, i):
	l.acquire()
	try:
		if i%2 == 0:
			time.sleep(.5)
			global_list.append(i)
		else:
			global_list.append(i)
	finally:
		l.release()

if __name__ == '__main__':
	global_list = Manager().list()
	numbers = 100
	lock = Lock()

	processes_list = []
	for i in range(numbers):
		processes_list.append(Process(target=f, args=(lock,i+1)))

	for i in range(numbers):
		processes_list[i].start()
	
	for i in range(numbers):
		processes_list[i].join()

	print("Using Lock\n")
	print(global_list)
	print()