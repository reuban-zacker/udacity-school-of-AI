#include <string>

#include "format.h"

using std::string;
using std::to_string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long int seconds) 
{
    int hours = seconds / (60*60);
    seconds = seconds % (60*60);
    int minutes = seconds / 60;
    seconds = seconds % 60;
    int sec = seconds;
    std::string result = to_string(hours) + ":" + to_string(minutes) + ":" + to_string(sec);
    return result;
}