#ifndef __job_H_
#define __job_H_

#include<string>
#include<queue>
#include <fstream>
#include<list>

using namespace std;


class job {
private:
    float timeStart;   //time enter waitQ
    float timeEnd;        //time exit waitQ
    float timeEnter;    //time entered cpuQ
    float timeExit;     //time exited cpuQ
    int jobID;          //job number
    int jobType;        //job class
    float jobTime;  //time required to complete the job
    float initialJobTime; //jobtime before it is altered.

public:
    job(float timeStart, int jobID);
    void setJobTime(float);
    void setTimeEnd(float);
    void setTimeEnter(float);
    float getInitialJobTime();
    float getTimeStart();
    float getTimeEnd();
    float getTimeExit();
    float getTimeEnter();
    int getJobID();
    float getJobType();
    float getJobTime();
};


class CPU {
private:

    queue<job> CPUqueue;   //queue for arrival objects. (there can be as many as 10 objects in this
    queue<job> waitQueue;
    list<job> cpuList;
    float time, jobs;
    float probability, idle=0.0, remainingTime;
    int jobID, jobsComplete, targetJobAmount;

public:
    CPU(int jobs, float probability, ofstream& outfile);          //class constructor, creates list queue size
                            //based on number of jobs input to be generated
    void clock();
    float getTime();
    void setTargetJobAmount(int);




    std::ofstream * outfile;
    //output file stream for CpuSim.out

};


#endif //__job_H_




