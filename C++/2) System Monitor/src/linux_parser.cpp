#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::ifstream;
using std::istream_iterator;
using std::istringstream;
using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  float MemTotal, MemFree, MemUsed;
  string key, value;
  string line;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "MemTotal:") {
        MemTotal = std::stof(value);
      } else if (key == "MemFree:") {
        MemFree = std::stof(value);
      }
    }
  }
  MemUsed = MemTotal - MemFree;
  return MemUsed / MemTotal;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  string line;
  string insec, idle;
  long sec;

  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> insec >> idle;  // Idle process time, maybe useful later.
    sec = std::stol(insec);
  }
  return sec;  // Uptime in seconds
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() {
  std::string value, line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  getline(stream, line);
  std::istringstream buf(line);
  std::istream_iterator<string> beg(buf), end;
  std::vector<string> values(beg, end);

  long systemalltime = stol(values[3]) + stol(values[6]) +
                       stol(values[7]);  // system + irq + softirq
  long virtualtime = stol(values[9]) + stol(values[10]);  // guest + guest_nice
  long stealTime = stof(values[8]);                       // steal

  long totalJiffes = LinuxParser::ActiveJiffies() + LinuxParser::IdleJiffies() +
                     systemalltime + virtualtime + stealTime;

  return totalJiffes;
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) {
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);

  long totalTime;
  if (stream.is_open()) {
    std::string line;
    getline(stream, line);
    std::istringstream buf(line);
    std::istream_iterator<string> beg(buf), end;
    std::vector<string> values(beg, end);

    totalTime = stol(values[13]) + stol(values[14]);  // utime + stime
    totalTime = totalTime + stol(values[15]) +
                stol(values[16]);  // totaltime + cutime + cstime
  }
  return totalTime;
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {
  string line, value;
  long usertime, nicetime;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    istringstream buf(line);
    istream_iterator<string> beg(buf), end;
    vector<string> values(beg, end);

    usertime = stol(values[1]) - stol(values[9]);   // user - guest
    nicetime = stol(values[2]) - stol(values[10]);  // nice - guest_nice
  }
  return (usertime + nicetime);
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {
  string line, value;
  long idlealltime;

  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    istringstream buf(line);
    istream_iterator<string> beg(buf), end;
    vector<string> values(beg, end);

    idlealltime = stol(values[4]) + stol(values[5]);  // idle + iowait
  }
  return idlealltime;
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string line, key, value;
  int totalProcsRun;

  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "processes") totalProcsRun = std::stoi(value);
    }
  }
  return totalProcsRun;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string line, key, value;
  int numProcsRun;

  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "procs_running") {
        numProcsRun = std::stoi(value);
      }
    }
  }
  return numProcsRun;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  std::ifstream stream(kProcDirectory + to_string(pid) + kCmdlineFilename);

  string line;
  if (stream.is_open()) {
    getline(stream, line);
  }
  return line;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename);

  string line, key, value;
  int ramKb, ramMb;
  if (stream.is_open()) {
    while (getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "VmSize:") {
        ramKb = stoi(value);
        ramMb = ramKb / 1000;
      }
    }
  }

  return to_string(ramMb);
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
  string line, uid, userLine;
  string key, value, username, uservalue;

  std::ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    while (getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "Uid:") {
        uid = value;
      }
    }
  }
  return uid;
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
  string userLine, username, uservalue, uname;
  std::ifstream filestream(kPasswordPath);

  if (filestream.is_open()) {
    while (getline(filestream, userLine)) {
      std::replace(userLine.begin(), userLine.end(), ':', ' ');
      std::istringstream linestream(userLine);
      linestream >> username >> uservalue >> uservalue;
      if (uservalue == Uid(pid)) {
        uname = username;
      }
    }
  }
  return uname;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  long int uptime, uptime_in_sec;
  if (stream.is_open()) {
    std::string line;
    getline(stream, line);
    std::istringstream buf(line);
    std::istream_iterator<string> beg(buf), end;
    std::vector<string> values(beg, end);

    uptime = stol(values[21]);
    uptime_in_sec = uptime / sysconf(_SC_CLK_TCK);
  }

  return uptime_in_sec;
}