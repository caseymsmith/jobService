
This program will simulate the service of jobs (programs) by the CPU of a multi-user computer. 

This is a clock-driven simulation, in which the clock is a counter that is incremented each simulated second. 

The clock is initially 0, and continues "ticking" until all the jobs in the input have been serviced and left the system. This simulation runs until a particular number of jobs have been serviced and left the system. This number is input by the user. When a job enters the system, it is enqueued on a wait queue. The CPU's "queue" represents the jobs that are currently being serviced. If there is room in the CPU's queue, a job is dequeued from the wait queue and enqueued onto the CPU queue. Jobs in the CPU queue are serviced using the following scheme: although the CPU actually executes only one job at a time, there can be as many as ten jobs in the CPU queue. To service these jobs, the CPU queue allocates a "time slice" to each job in the CPU queue, depending on its class. To the observer, it appears that the CPU services several jobs simultaneously; however most jobs are interrupted when they require I/O or other services. To avoid idleness while waiting for the required service, the CPU starts working on the next job in the CPU queue. 
We simulate this by having each job fall into one of two job classes: I/O bound and CPU bound. I/O-bound jobs have a time-slice of 0.1 seconds, while CPU-bound jobs have a time-slice of 0.2 seconds. The job at the front of the CPU queue executes for its required time-slice; then it is dequeued and enqueued at the rear of the CPU queue. Jobs remain in the CPU queue until they complete their service time. Note that jobs may leave the CPU at non-integral times.


The program gathers statistics, computes, and report the following information:

1.	The number of jobs for each job class and CPU requirement.
2.	The average time that a job spends in the wait queue.
3. 	The average elapsed time that a job spends in the CPU queue, for each of the job types, broken down by CPU time required and job class.
4. 	The percentage of the time that the CPU is busy. (The CPU is idle if there are no jobs in the system.)
5. 	The "through-put" of the system, expressed as the number of jobs handled per hour.
 	

To summarize, in each clock cycle (a simulated second), the following tasks are performed

1. 	The clock is incremented.
 	
2. 	If a job (or jobs) enters the system, determine the job number, job class, and CPU time required. The job class and CPU time required for each job must be determined by a random number generator. Time stamp the job, and enqueue it in the wait queue.
 	
3. 	If the CPU queue is not full, dequeue the front job(s) from the wait queue and enqueue the job(s) in the CPU queue.
 	
4. 	If the CPU queue is not empty, service the jobs in the CPU queue, giving each job serviced the correct time-slice. (Do not dequeue a job from the CPU queue until its "execution" is complete.) Otherwise, if the CPU queue is empty, increment the CPU idle time.
 	
5. 	If a job (or jobs) completes its execution, remove it from the CPU queue and calculate the elapsed times for statistics.
 	

The program prompts the user to input the simulation parameters:

1.	The number of jobs to be generated.
	
2. 	The probability of one job entering the system in each simulated second.
 	

All program output is written to a text file, "CpuSim.out"

1. 	Echo print the simulation parameters supplied by the user.
 	
2. 	For the first 10 minutes of simulated clock time, print the job number, job class, CPU time and time each job entered the system.
 	
3.	After the first 10 minutes of simulated clock time, print out a system summary every 60 seconds. The summary should contain the time, the number of jobs in each queue, and the job number of the job at the front of the queue.
	
4. 	When the simulation is complete (the specified number of jobs have been executed), print a report of the job statistics as noted above. 
 	


The results for this simulation are variable. A sequence of random numbers generating more jobs than average or longer jobs than average tends to increase the size of the wait queue. There may also be some detectable "dry" times when few jobs enter the system. 
