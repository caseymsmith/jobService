
#include <iostream>
#include <queue>
#include <fstream>

#include "job.h"

using namespace std;

int main() {

    ofstream outfile;

    outfile.open("/Users/Casey/Documents/CpuSim.out");

    int numOfJobs;
    float prob;


    cout << "Enter the number of jobs to be generated" << endl;
    cin >> numOfJobs;

    cout << "Enter the percent probability in decimal form of "
            "one job entering the system in each simulated second" << endl;
    cin >> prob;


    outfile << "\nNumber of jobs to be generated: " << numOfJobs << endl
            << "Probabilty of one job entering the system in each simulated second: "
            << prob*100 << "%" << endl << endl
            << "First 10 minutes of simulated clock time:" << endl;


    CPU c(numOfJobs, prob, outfile);
    c.clock();


    outfile.close();

    return 0;
}
