#include "../header/link_layer.hpp"    // Link Layer Header

// Transmitter
void link_layer_data_transmitter(vector<int> frame, int code_option) {
    link_layer_data_transmitter_framing(frame);

    // Next step
    link_layer_data_transmitter_error_control(frame);

    // Next layer (Physical)
    transmitter_physical_layer(frame, code_option); 
}

void link_layer_data_transmitter_framing(vector<int> frame) {
    int type_of_framing = 0;
    vector<int> framed_frame;

    switch (type_of_framing) {
        case 0:   // Character counter
            framed_frame = link_layer_data_transmitter_count_character(frame);
            break;
        
        case 1:   // Byte insertion 
            framed_frame = link_layer_data_transmitter_insert_bytes(frame);
            break;

        default:
            break;
    }
}

void link_layer_data_transmitter_error_control(vector<int> frame) {
    int type_of_error_control = 0;

    switch (type_of_error_control) {
        case 0:   // Parity bit
            
            break;
        
        case 1:   // CRC
    
            break;

        default:
            break;
    }
}

// Receiver
void link_layer_data_receiver(vector<int> frame, int code_option) {
    link_layer_data_receiver_framing(frame);

    // Next step
    link_layer_data_receiver_error_control(frame);

    // Next layer (Physical)
    receiver_physical_layer(frame, code_option); 
}

void link_layer_data_receiver_framing(vector<int> frame) {
    int type_of_framing = 0;
    vector<int> framed_frame;

    switch (type_of_framing) {
        case 0:   // Character counter
            framed_frame = link_layer_data_receiver_count_character(frame);
            break;
        
        case 1:   // Byte insertion 
            framed_frame = link_layer_data_receiver_insert_bytes(frame);
            break;

        default:
            break;
    }
}