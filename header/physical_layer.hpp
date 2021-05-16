#ifndef PHYSICAL_LAYER_H  
#define PHYSICAL_LAYER_H

#include <iostream>                 // IO services
#include <vector>                   // Vector services
#include <cmath>                    // Numeric library
#include "link_layer.hpp"    // Application Layer Header
using namespace std;

// Physical Layer Functions
void transmitter_physical_layer(vector<int> frame, int code_option);    // Physical layer of transmitter side (after app layer)
void channel(vector<int> stream, int code_option);                      // Simulation of the channel where the message is transmitted
void receiver_physical_layer(vector<int> stream, int code_option);      // Physical layer of receiver side (after channel)            

// Transmitter code Function
vector<int> binary_code_transmitter(vector<int> frame);                 // NRZ (reply frame) from transmitter side
vector<int> bipolar_code_transmitter(vector<int> frame);                // Switch bit "1" between "1" and "-1"
vector<int> manchester_code_transmitter(vector<int> frame);             // XOR from transmitter side 

// Receiver decode Function
vector<int> binary_code_receiver(vector<int> stream);                    // NRZ (reply bit stream) from receiver side
vector<int> bipolar_code_receiver(vector<int> stream);                   // Change "-1" to "1"
vector<int> manchester_code_receiver(vector<int> stream);                // Skip two positions and get the first bit (process to decode)

#endif