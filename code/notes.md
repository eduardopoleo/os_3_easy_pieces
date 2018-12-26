Chapter 6

OS Mechanism 
Limited direct execution
refers to the fact that the OS runs the process (program) directly on the CPU which will make execution faster. But the OS has no control over it
when the process it’s on this state. therefore it must cooperate with the hardware to be able to control the process.
The OS does this by setting time interrupts and interrupt handlers at boot time.
1. restricted operations
    1. Making sure user space code does not have access to all the kernel resources
    2. This is mostly accomplish through the use of traps 
    3. traps are used by the kernel and the hardware in combination 
    4. traps are like an intermediary step the user process can use to execute system calls to require system resources
2. Time sharing
    1. Cooperative approach
        1. Waits until the user program “yields” control to the kerne. this can happen when:
            1. the program issues a system call
            2. the program makes an illegal operation (divide by zero
        2. The problem is what happens when the program runs an infinite loop and never gives back control to the OS
    2. Non-cooperative interrupt
        1. there’s basically a timer and and timer interrupt interactions that allows the hardware to periodically return control back to the os 

Chapter 7
OS Policies
How exactly does the OS decides which jobs, processes run first?
Different policies that increase in complexity. Contrains:
- All jobs arrive at the same time
- All jobs take the same amount to complete
- Once started all jobs run to completion
- Jobs only use CPU they do not make system call that return control to the OS
- The runtime is know (that is the OS know preemtively how long a job will take with repect to others)

A good metric to measure the effectiveness of a policy is the turnaround time with is measure as follows
T_around  = T_completion - T_inital (if they are multiple jobs we divide by the number of jobs) 
This give us a measure on how effectively we handled jobs

Relaxes: NONE
FIFO: It’s enough when all constrains are true (which is no realistic at all). Because since all jobs take the same amount of time it really does no matter which one we initiate first.

Relaxes: Jobs do not take the same time
SJF(smaller job first): If all jobs get at the same time and the OS knows how long the take the OS can initially organized the jobs in such a way that the shorter jobs finish first 

Relaxes: Jobs do not arrive at the same time
STCF (shortest time to completion): Since the OS knows what jobs are taking  the longer it can decide to stop long running jobs first and enqueue the others. This forcefully relaxes: jobs do not run to completion once started.

Fairness
Another useful metric is Time to response
T_response = T_job_is_process - T_initial (divided by the number of jobs)
Indicates how long it took to the user to start seeing their job being processed.
STCF is pretty bad for T_response cuz it only cares about processing job that complete fast first so it does not care about providing fast response to users.

Round robin (Time slicing)
It basically slice each job and context switch quite frequently to be able to provide response to all jobs (consequently) jobs completion times are elongated but response is much better. This makes it terrible for T_around.
Amortization is key. The time slice has to be tuned so that context switching does no incur on huge penalty.

relaxes: jobs do not perform I/O
If we consider that there can be subjobs (e.g we consider that a job time only exist when it’s performed on the CPU) we can intercalate so that the second job runs when the firs process is doing I/O

But we still need to relax the most important constrain: The oracle OS that know about time completions in advance.

Chapter 8
relaxes: The OS does not know how long a job is going to take
MLFQ(Multi Level Feedback Queue)
- Priority changes depending on different factors based on the process historical behaviour (require a lot of user)

Rule 1: Highest priority jobs get processed first
Rule 2: Jobs in the same queue are processed using round robing

How does the algorithm decides what goes into which queue?

Rule 3: New jobs are put on the top priority queue
Rule 4a: Jobs that take longer than their time slice are downgraded a queue
Rule 4b: If a job gives off the CPU before their time slice finishes (e.g makes an I/O request) stays on the same queue.

3 drawbacks:
- Many highly interactive jobs could potentially over take the CPU (starvation)
- A bad user could game the scheduler by issuing some I/O right before the time slice finishes therefore staying on the same queie
- jobs can change behaviour but that would not matter if they are already on the least priority queue.

How to prevent jobs from starving?
Rule 5: Boost all jobs every certain period of time e/g 50ms

This long running jobs will not starve if they are multiple interactive jobs running and if their nature change they'll be treated accordingly.

Drawback:
- How long should that S (period) should be?

How to prevent gaming the schedule?
Better accounting.
Rule 4 (modified). Once the an job has used up all his allotted time on a particular queue just drop it down a queue. This is less bad since we know that they'll keep getting boosted at a certain point.

CHAPTER 9
Lottery system
- Each job is assined a number of tickets and a "lottery" number is assigned.
- Jobs are stored in queue 
- We iterate over the queue and keep adding the ticket number until the #tickets is higher than winner ticket
- That current job gets to run

Strides
- Divide a big number e.g 10,000 by the number of tickets of each job and we each job strides
- Pick a random job from the queue
- After it completes add its stride to it pass number
- Pick another job with least amount of pass ..
- Repeat
It's more deterministic than lotterry because it gets the proportions right but it's harder to implement because it requires to keep track of global state (pass for each job). The problem is when a new job comes in what should it be the pass number for it.

Completely Fair Scheduler (CFS)
- Runs all jobs equally and keeps track of the vruntine to know who to run next
- Introcudes the concept of niceness. The nicest the process the more tim will yield to other processes
- Nice value add weights to the calculation of vruntime therefore changing the likelyhood of this process to be picked later
- Uses optimized data structure such as red/black trees to be able to retrieve processes to run fast. These data structures convert the linear scan into log n.
- When a process sleeps for too long (because it was going I/O) it inserts it on the minimum vruntime value already present on the red/black tree to prevent that job to starve consequent ones.
