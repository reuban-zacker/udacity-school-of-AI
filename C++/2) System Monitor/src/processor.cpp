#include "processor.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() 
{
    double currentIdle, currentTotal, deltaIdle, deltaTotal;
    double cpuFreq = sysconf(_SC_CLK_TCK);
    
    currentIdle = LinuxParser::IdleJiffies();
    currentTotal = LinuxParser::Jiffies();

    deltaIdle = (currentIdle - lastIdleJiffes_) / cpuFreq;
    deltaTotal = (currentTotal - lastTotalJiffes_) / cpuFreq;
    
    float utilization = 1.0 - (deltaIdle / deltaTotal);

    lastIdleJiffes_ = currentIdle;
    lastTotalJiffes_ = currentTotal;

    return utilization;
}
