/** uhr: generic time performance tester
 * Author: LELE */

 #include <cstdint>
 #include <chrono>
 #include <cmath>
 #include <fstream>
 #include <iostream>
 #include <random>
 #include <vector>
 #include "utils.cpp"
 
 #include "point.h"
 #include "brute_force.cpp"
 
 int main(int argc, char *argv[]) {
     // Validate and sanitize input
     std::int64_t runs, lower, upper, step;
     validate_input(argc, argv, runs, lower, upper, step);
 
     // Set up clock variables
     std::int64_t n, i, executed_runs;
     std::int64_t total_runs_additive = runs * (((upper - lower) / step) + 1);
     std::int64_t total_runs_multiplicative = runs * (floor(log(upper / double(lower)) / log(step)) + 1);
     std::vector<double> times(runs);
     double mean_time, time_stdev, dev;
     auto begin_time = std::chrono::high_resolution_clock::now();
     auto end_time = std::chrono::high_resolution_clock::now();
     std::chrono::duration<double, std::nano> elapsed_time = end_time - begin_time;
 
     // Set up random number generation
     std::random_device rd;
     std::mt19937_64 rng(rd());
     std::uniform_real_distribution<double> u_distr(0.0, 100.0);
 
     // File to write time data
     std::ofstream time_data;
     time_data.open(argv[1]);
     time_data << "n,t_mean,t_stdev" << std::endl;
 
     // Begin testing
     std::cerr << "\033[0;36mRunning tests...\033[0m" << std::endl << std::endl;
     executed_runs = 0;
     for (n = lower; n <= upper; n *= step) {
         mean_time = 0;
         time_stdev = 0;
 
         
         std::vector<Point> points;
         for (int i = 0; i < n; ++i) {
             points.push_back({u_distr(rng), u_distr(rng)});
         }
 
         // Run to compute elapsed time
         for (i = 0; i < runs; i++) {
             display_progress(++executed_runs, total_runs_additive);
 
             begin_time = std::chrono::high_resolution_clock::now();
             bruteForceMinDistance(points);
             end_time = std::chrono::high_resolution_clock::now();
 
             elapsed_time = end_time - begin_time;
             times[i] = elapsed_time.count();
 
             mean_time += times[i];
         }
 
         // Compute statistics
         mean_time /= runs;
 
         for (i = 0; i < runs; i++) {
             dev = times[i] - mean_time;
             time_stdev += dev * dev;
         }
 
         time_stdev /= runs - 1; // Subtract 1 to get unbiased estimator
         time_stdev = std::sqrt(time_stdev);
 
         // Write results to file
         time_data << n << "," << mean_time << "," << time_stdev << std::endl;
     }
 
     // This is to keep loading bar after testing
     std::cerr << std::endl << std::endl;
     std::cerr << "\033[1;32mDone!\033[0m" << std::endl;
 
     time_data.close();
 
     return 0;
 }