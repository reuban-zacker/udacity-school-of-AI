#include <iostream>
#include <random>
#include "TrafficLight.h"

/* Implementation of class "MessageQueue" */

template <typename T>
T MessageQueue<T>::receive()
{
    // FP.5a : The method receive should use std::unique_lock<std::mutex> and _condition.wait() 
    // to wait for and receive new messages and pull them from the queue using move semantics. 
    // The received object should then be returned by the receive function. 
  	std::unique_lock<std::mutex> uLck(_mtx);
  	_condition.wait(uLck, [this] { return !_msgQueue.empty(); });
  	T rtnValue = std::move(_msgQueue.back());
  	_msgQueue.pop_back();
  	return rtnValue; 
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // FP.4a : The method send should use the mechanisms std::lock_guard<std::mutex> 
    // as well as _condition.notify_one() to add a new message to the queue and afterwards send a notification.
  	std::lock_guard<std::mutex> lck(_mtx);
  	_msgQueue.emplace_back(std::move(msg));
  	_condition.notify_one();
}


/* Implementation of class "TrafficLight" */


TrafficLight::TrafficLight()
{
    _currentPhase = TrafficLightPhase::red;
}

void TrafficLight::waitForGreen()
{
    // FP.5b : add the implementation of the method waitForGreen, in which an infinite while-loop 
    // runs and repeatedly calls the receive function on the message queue. 
    // Once it receives TrafficLightPhase::green, the method returns.
  	while(true){
      TrafficLightPhase phase = _phasesQueue.receive();
      if (phase == TrafficLightPhase::green){
        break;
      }
    }
}

TrafficLight::TrafficLightPhase TrafficLight::getCurrentPhase()
{
    return _currentPhase;
}

void TrafficLight::simulate()
{
    // FP.2b : Finally, the private method „cycleThroughPhases“ should be started in a thread when the public method „simulate“ is called. To do this, use the thread queue in the base class. 
  threads.emplace_back(std::thread(&TrafficLight::cycleThroughPhases, this));
}

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases()
{
    // FP.2a : Implement the function with an infinite loop that measures the time between two loop cycles 
    // and toggles the current phase of the traffic light between red and green and sends an update method 
    // to the message queue using move semantics. The cycle duration should be a random value between 4 and 6 seconds.
  	std::chrono::time_point<std::chrono::system_clock> lastUpdate;
  	std::random_device rd;
  	std::uniform_int_distribution<int> distribution(4000,6000);
  	long cycle_duration = distribution(rd);
  	// Start stopwatch
  	lastUpdate = std::chrono::system_clock::now();
  	while(true) {
      // Also, the while-loop should use std::this_thread::sleep_for to wait 1ms between two cycles. 
      
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
      long timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdate).count();
      //std::cout << "\n ######################### Time since last update = " << timeSinceLastUpdate << ", Cycle duration = "<< cycle_duration <<"\n";
      if (timeSinceLastUpdate >= cycle_duration) {
        _currentPhase = (_currentPhase == TrafficLightPhase::red) ? TrafficLightPhase::green : TrafficLightPhase::red;
        _phasesQueue.send(std::move(_currentPhase));
        // Reset stopwatch and pick a new random number for cycle number
  	    lastUpdate = std::chrono::system_clock::now();
        cycle_duration = distribution(rd);
      }
    }
}
