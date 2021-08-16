#ifndef TIME_MEASURER_H_
#define TIME_MEASURER_H_

#include <chrono>
#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "absl/synchronization/mutex.h"

namespace time_measurer {

double ToSeconds(std::chrono::steady_clock::duration duration);

class TimeMeasurer {
 public:
  TimeMeasurer(std::string name, bool print_results_on_destruction);
  ~TimeMeasurer();

  void StartMeasurement();
  void StopMeasurement();

  void AddMeasurement(double measured_time);

 private:
  absl::Mutex mutex_;
  std::string name_;
  bool print_results_on_destruction_;
  std::map<pthread_t, std::chrono::time_point<std::chrono::steady_clock>> start_time_;
  std::vector<double> time_measurements_;
};

#define MEASURE_TIME_FROM_HERE(name) \
  static time_measurer::TimeMeasurer (name ## _time_measurer)(#name, true); \
  (name ## _time_measurer).StartMeasurement()

#define STOP_TIME_MESUREMENT(name) \
  (name ## _time_measurer).StopMeasurement()

#define MEASURE_BLOCK_TIME(name) \
  static time_measurer::TimeMeasurer (name ## _time_measurer)(#name, true); \
  class name ## _time_measurer_stop_trigger_class { \
   public: \
    (name ## _time_measurer_stop_trigger_class)() {}; \
    (~name ## _time_measurer_stop_trigger_class)() {(name ## _time_measurer).StopMeasurement();}; \
  }; \
  name ## _time_measurer_stop_trigger_class    name ## _time_measurer_stop_trigger; \
  (name ## _time_measurer).StartMeasurement()

}  // namespace time_measurer

#endif  // TIME_MEASURER_H_
