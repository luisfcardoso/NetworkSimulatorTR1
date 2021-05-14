#ifndef APLICATION_LAYER_H  
#define APLICATION_LAYER_H

#include <iostream>             // IO services
#include <vector>               // Vector services
#include <stdio.h>              
#include "physical_layer.hpp"   // Physical layer header (services)
using namespace std;

// Definition of Application Layer's Functions
void transmitter_application(void);                                                 // Transmitter Application Function
void transmitter_application_layer(string message, int physical_code);      // Transmitter Application Layer Function
void receiver_application_layer(vector<int> frame);                                 // Receiver Application Layer Function
void receiver_application(string message);                                          // Receiver Application Function

// Auxiliary Functions
vector<int> convert_message_to_ASCII(string message);           // Convert Message to ASCII Code (using a vector of int) of each word
string convert_received_message_to_string(vector<int> frame);   // Convert Received Message to String Again
int code_option_selection(string input);                // Calculate the code option value
#endif