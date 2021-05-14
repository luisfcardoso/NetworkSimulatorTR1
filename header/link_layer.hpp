#ifndef LINK_LAYER_H  
#define LINK_LAYER_H

#include <iostream>             // IO services
#include <vector>               // Vector services
#include <stdio.h>              
#include "physical_layer.hpp"   // Physical layer header (services)
using namespace std;

// Definition of Link Layer's Functions
void link_layer_data_transmitter(vector<int> frame, int code_option);
void link_layer_data_transmitter_framing(vector<int> frame);
void link_layer_data_transmitter_error_control(vector<int> frame);
void link_layer_data_transmitter_error_control_parity_bit(vector<int> frame);
void link_layer_data_transmitter_error_control_CRC(vector<int> frame);
void link_layer_data_transmitter_error_control_Hamming_code(vector<int> frame);
vector<int> link_layer_data_transmitter_count_character(vector<int> frame);
vector<int> link_layer_data_transmitter_insert_bytes(vector<int> frame);

void link_layer_data_receiver(vector<int> frame, int code_option);
void link_layer_data_receiver_framing(vector<int> frame);
void link_layer_data_receiver_error_control(vector<int> frame);
void link_layer_data_receiver_error_control_parity_bit(vector<int> frame);
void link_layer_data_receiver_error_control_CRC(vector<int> frame);
void link_layer_data_receiver_error_control_Hamming_code(vector<int> frame);
vector<int> link_layer_data_receiver_count_character(vector<int> frame);
vector<int> link_layer_data_receiver_insert_bytes(vector<int> frame);

// Auxiliary Functions

#endif