#include <iostream>
#include "job.h"
#include <cmath>
#include <ctime>
#include <iterator>
#include <iomanip>

using namespace std;


float job::getTimeStart() {
    return timeStart;
}

float job::getTimeEnd() {
    return timeEnd;
}

float job::getTimeEnter() {
    return timeEnter;
}

void job::setTimeEnd(float time) {
    timeEnd = time;
}

void job::setTimeEnter(float remainingTime) {
    timeEnter = remainingTime;
}


int job::getJobID() {
    return jobID;
}


float job::getJobType() {
    return jobType;
}

void job::setJobTime(float jobTime) {
    this->jobTime=jobTime;
}

float job::getJobTime() {
    return jobTime;
}


float job::getTimeExit() {
    return timeExit;
}

float job::getInitialJobTime() {
    return initialJobTime;
}

job::job(float timeStart, int jobID) {
    this->timeStart = timeStart;
    this->jobID = jobID;

    int ranNum = (rand() % 2);
    jobType = ranNum;
    //sets the job type

    float randomNum = (float) ((rand() % 10) * 0.1);
    jobTime = randomNum;
    //time required to complete the job

     initialJobTime=randomNum;

}



////////////////////////////////////////////////////////////////////////////////////




CPU::CPU(int jobs, float probability, ofstream& outfile) {
    srand(std::time(NULL));
    this->outfile=&outfile;
    this->jobs = jobs;
    this->probability = probability;

    setTargetJobAmount(jobs);
}

float CPU::getTime() {
    return time;
}



//sets the amount of jobs to be done based on the user input
void CPU::setTargetJobAmount(int jobs) {
    this->jobs = jobs;
    targetJobAmount = jobs;
}



//clock function to create new jobs until the input number of jobs have been processed
void CPU::clock() {


    float counter = 0.0;    //clock time
    float second = 1.0;

    while (jobsComplete < targetJobAmount) {
        second = 1.0;
        float randomNum = (float) ((rand() % 10) * 0.1);
        if (randomNum <= probability) {
            time = counter;
            waitQueue.push(job(time, jobID));
            jobID++;
        }


        //creates job and puts it in the wait queue
        if (CPUqueue.empty() && !waitQueue.empty()) { //if the cpu queue is empty
            CPUqueue.push(waitQueue.front()); //move jobs from wait queue to cpu queue
            waitQueue.pop();


            if (int(counter) % 60 == 0 && counter / 60 < 10) {
                *outfile << "Job #" << waitQueue.back().getJobID()
                        << "  Job Type: " << waitQueue.back().getJobType();
                if (waitQueue.back().getJobType() == 0)
                    *outfile << " (I/O-bound)";
                else
                    *outfile << " (CPU-bound)";

                *outfile << "  CPU time job needs: " << waitQueue.back().getInitialJobTime()
                        << "seconds  Time job entered system: " << waitQueue.back().getTimeStart() << endl;
            }

        }

        //one data member for all jobs that keeps track of time it takes
        //to exit the wait queue.
        // when you pop the job out, you must modify
        //its data member to keep track of what time is it at that time
        //and that's the time that the job exits the wait queue
        //also set the value of another data member for the job, time it enters
        //the cpu queue. then push the job into that.


///////////////////////////////job/////execution/////////////////////////////////



        //loop takes job from the CPU queue and processes it
        //increments the data member that keeps track of how long the job has been processed.
        //increment that by 0.1 or 0.2 seconds depending on the type of job.

        while (second > 0.0) {
            //if the cpu queue is not empty
            if (!CPUqueue.empty()) {

                float timeSlice;

                if (CPUqueue.front().getJobType() == 0) {
                    timeSlice = 0.1;
                }
                else if (CPUqueue.front().getJobType() == 1) {
                    timeSlice = 0.2;
                }

                float x = fmin(second, timeSlice);  //the minimum of second & 0.1
                x = fmin(x, CPUqueue.front().getJobTime());
                CPUqueue.front().setJobTime(CPUqueue.front().getJobTime() - x);
                second = second - x;

                //determines if the job is complete. If it is complete, it is removed from the cpuQ
                //if it isn't it's put back at the end of the cpuQ. (note:multitasking loop program)
                if (CPUqueue.front().getJobTime() == 0) {
                    cpuList.push_back(CPUqueue.front());
                    CPUqueue.pop();
                    jobsComplete++;
                }
                else {
                    CPUqueue.push(CPUqueue.front()); //puts the job on the back of the cpuQ because it isn't complete.
                    CPUqueue.pop(); //removes the front object from the cpuQ
                }

            }
                //if the cpuQ is empty
            else {
                idle = idle + 0.05f;    //adds idle time
                second = second - 0.05f;
                time = time + 0.05f;
            }




            if((int)counter % 60 == 0 && counter > 10) {
                *outfile << "\n\n60 second system summary:" << endl;
                //time, number of jobs in each queue, job number of job at front of queue

                *outfile << "Time: " << CPUqueue.front().getTimeStart() << "  Number of wait queue jobs: "
                        << waitQueue.size() << "  Number of cpu queue jobs: " << CPUqueue.size()
                        << "  Job # at front of cpu queue: #" << CPUqueue.front().getJobID() << endl;

            }



        } //end of internal while loop

        counter++;

//        //prints the first 10 minutes of simulated clock time: jobID, jobType, CPU time,
//        //and time each job entered the system.
//
//        list<job>::iterator curr = cpuList.begin();
//        list<job>::iterator stop = cpuList.end();
//
//
//        if((int)counter % 60 == 0 && counter <= 10) {
//            while (curr != stop) {
//                *outfile << "Job #" << curr->getJobID() << "  Job Type: " << curr->getJobType();
//
//                if (curr->getJobType() == 0)
//                    *outfile << " (I/O-bound)";
//                else
//                    *outfile << " (CPU-bound)";
//
//                *outfile << "  CPU time job needs: " << curr->getInitialJobTime()
//                        << "seconds  Time job entered system: " << curr->getTimeStart() << endl;
//                curr++;
//            }


    }//end of external while loop



}
