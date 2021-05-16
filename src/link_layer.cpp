#include "../header/link_layer.hpp"    // Link Layer Header

// Parameters
int type_of_framing = 0;
int type_of_error_control = 1;
char byte_flag = '%';                       // Byte flag  
char byte_esc = '*';                        // Byte escape   

// Transmitter
void link_layer_data_transmitter(vector<int> frame, int code_option) {
    
    vector<int> frame_framed = link_layer_data_transmitter_framing(frame);

    // Next step
    vector<int> frame_framed_controled = link_layer_data_transmitter_error_control(frame_framed);

    // Next layer (Physical)
    transmitter_physical_layer(frame_framed_controled, code_option); 
}

vector<int> link_layer_data_transmitter_framing(vector<int> frame) {
    vector<int> framed_frame;

    switch (type_of_framing) {
        case 0:   // Character counter
            cout << endl << "Type of framing: Character Count";
            framed_frame = link_layer_data_transmitter_count_character(frame);
            
            break;
        
        case 1:   // Byte Stuffing 
            cout << endl << "Type of framing: Byte Stuffing" << endl;
            framed_frame = link_layer_data_transmitter_byte_stuffing(frame);
            break;

        default:
            break;
    }

    return framed_frame;
}

vector<int> link_layer_data_transmitter_count_character(vector<int> frame) {
    // Frame with character count
    vector<int> frame_with_count(frame.size() + 8, 0);  // Insert 1 byte to store character count

    // Size of the frame
    int frame_size = frame.size()/8;      // in bytes
    char frame_size_hexa = 0x0;
    frame_size_hexa = (char) frame_size;  // in hexa

    // Building the frame

    // Initiate Counters 
    int counter = 0;            
    int bit_position = 0;    

    // Insert frame size at the first byte's frame (header)
    while (counter < 8) {
        char temp = frame_size_hexa >> (7 - bit_position);
        frame_with_count[counter] = temp & 0x01; // Check if the bit is set or clear
        
        // Update counters
        counter++;
        bit_position++;
    }

    // Store frame's load (actual data) 
    counter = 8;
    while (counter < (int)frame_with_count.size()) {
        frame_with_count[counter] = frame[counter-8];
        
        // Update counter
        counter++;
    }

    // Print the frame with character count
    cout << endl << "Number of Characters: " << frame_size;
    cout << endl << "Frame with character count: ";
    auto frame_pos_value = frame_with_count.begin(); // Begin to go through frame_with_count
    
    while(frame_pos_value != frame_with_count.end()){
        cout << *frame_pos_value;

        // Update counter
        frame_pos_value++;
    }
    cout << endl;

    return frame_with_count;
}

vector<int> link_layer_data_transmitter_byte_stuffing(vector<int> frame) {
    
    // Parameters
    vector<int> frame_byte_stuffing;    // Result of the frame after byte stuffing process
    int current_character = 0;          // Counter 
    char read_character;                // Store character               

    // Initiate Byte Stuffung

    // Insert the flag at the beginning of the frame
    frame_byte_stuffing = add_character(frame_byte_stuffing, byte_flag);

    // Go through the frame
    while (current_character < (frame.size()/8)) {

        // Read the current character of the frame
        read_character = search_character(frame, current_character);

        // CHeck if the character is a flag or a escape
        if ((read_character == byte_flag) || (read_character == byte_esc)) {
            // Insert an escape if the frame contains a character with the same value of the flag and the escape
            frame_byte_stuffing = add_character(frame_byte_stuffing, byte_esc); 
        }

        // Insert read character
        frame_byte_stuffing = add_character(frame_byte_stuffing, read_character);

        // Update counter
        current_character++;
    }

    //  Insert the flag at the end of the frame
    frame_byte_stuffing = add_character(frame_byte_stuffing, byte_flag);

    // Print frame with character count
    cout << "Frame with byte stuffing: ";
    auto frame_pos_value = frame_byte_stuffing.begin(); // Begin to go through the frame with byte stuffing: 
    
    while(frame_pos_value != frame_byte_stuffing.end()){
        cout << *frame_pos_value;

        // Update counter
        frame_pos_value++;
    }
    cout << endl;

    return frame_byte_stuffing;
}

vector<int> link_layer_data_transmitter_error_control(vector<int> frame) {
    vector<int> framed_frame_control;

    switch (type_of_error_control) {
        case 0:   // Parity bit
            cout << endl << "Type of error control: Parity bit" << endl;
            framed_frame_control =  link_layer_data_transmitter_error_control_parity_bit(frame);
            break;
        
        case 1:   // CRC
            cout << endl << "Type of error control: CRC" << endl;
            framed_frame_control = link_layer_data_transmitter_error_control_CRC(frame);
            break;

        case 2:   // Hamming
            cout << endl << "Type of error control: Hamming" << endl;
            //framed_frame_control = link_layer_data_transmitter_error_control_Hamming_code(frame);
            break;

        default:
            break;
    }

    return framed_frame_control;
}

vector<int> link_layer_data_transmitter_error_control_parity_bit(vector<int> frame) {
    // Parameters
    int sum_of_1 = 0;
    int counter = 0;

    // Count how many "1" bits exists
    while(counter < frame.size()){
        if(frame[counter] == 1) {
            (sum_of_1)++;
        }
        counter ++;
    }

    // If the sum is an odd, the parity is 1. 
    // But, if the sum is an even, the parity is 0
    frame.push_back((sum_of_1)%2);

    // Print frame with parity bit
    cout << "Frame with parity bit at the end: ";
    auto frame_pos_value = frame.begin(); // Begin to go through the frame with parity bit
    
    while(frame_pos_value != frame.end()){
        cout << *frame_pos_value;

        // Update counter
        frame_pos_value++;
    }
    cout << endl;

    return frame;
}

vector<int> link_layer_data_transmitter_error_control_CRC(vector<int> frame) {
    
    // Build CRC 32 vector
    vector<int> crc_32;
    long long int crc32_value = 0x0104C11DB7;
    int counter = 0;

    while(counter < 32){
        unsigned int temp = crc32_value >> (31-counter);
        temp &= 0x01;
        crc_32.push_back(temp);

        counter++;
    }

    // Print CRC 32 Polynomial
    cout << "CRC32 Polynomial: ";
    auto crc_32_pos_value = crc_32.begin(); // Begin to go through the CRC 32 vector
    
    while(crc_32_pos_value != crc_32.end()){
        cout << *crc_32_pos_value;

        // Update counter
        crc_32_pos_value++;
    }
    cout << endl;

    // CRC process begins!
    vector<int> dividend = frame;
    vector<int> reminder;

    // Add 32 bits to dividend at the end
    dividend.insert(dividend.end(), 32, 0);

    // Do the division operation
    counter = 0;
    while((dividend.size() - counter) > 32) {

        int inner_counter = 0;
        while(inner_counter < 33) {

            if(dividend[counter+inner_counter]) { 
                if(crc_32[inner_counter]) dividend[counter+inner_counter] = 0;
                else dividend[counter+inner_counter] = 1; 
            }
            else {
                if(crc_32[inner_counter]) dividend[counter+inner_counter] = 1;
                else dividend[counter+inner_counter] = 0; 
            }

            inner_counter++;
        }

        counter++;
    }

    // Store the reminder in a vector
    reminder.insert(reminder.begin(), dividend.end()-32, dividend.end());

    // Print the reminder
    cout << "CRC Reminder: ";
    auto reminder_pos_value = reminder.begin(); // Begin to go through the reminder
    
    while(reminder_pos_value != reminder.end()){
        cout << *reminder_pos_value;

        // Update counter
        reminder_pos_value++;
    }
    cout << endl;

    // Store the frame result after CRC process
    vector<int> frame_with_crc = frame;
    frame_with_crc.insert(frame_with_crc.end(), reminder.begin(), reminder.end());

    // Print the frame result after CRC process
    cout << "Frame to be sent after CRC process: ";
    auto frame_with_crc_pos_value = frame_with_crc.begin(); // Begin to go through the frame_with_crc
    
    while(frame_with_crc_pos_value != frame_with_crc.end()){
        cout << *frame_with_crc_pos_value;

        // Update counter
        frame_with_crc_pos_value++;
    }
    cout << endl;

    return frame_with_crc;
}

//vector<int> link_layer_data_transmitter_error_control_Hamming_code(vector<int> frame) {

//}

// Receiver
void link_layer_data_receiver(vector<int> frame) {
    vector<int> frame_error_control = link_layer_data_receiver_error_control(frame);

    // Next step
    vector<int> frame_unframed = link_layer_data_receiver_unframing(frame_error_control);

    // Next layer (Application)
    receiver_application_layer(frame_unframed); 
}

vector<int> link_layer_data_receiver_unframing(vector<int> frame) {
    vector<int> unframed_frame;

    switch (type_of_framing) {
        case 0:   // Character counter
            cout << endl << "Type of unframing: Character Count";
            unframed_frame = link_layer_data_receiver_count_character(frame);
            break;
        
        case 1:   // Byte insertion 
            cout << endl << "Type of unframing: Byte Stuffing" << endl;
            unframed_frame = link_layer_data_receiver_byte_stuffing(frame);
            break;

        default:
            break;
    }

    return unframed_frame;
}

vector<int> link_layer_data_receiver_count_character(vector<int>  frame) {

    // Initiate counters and other variables
    int counter = 0;        
    int bit_position = 0;  
    int frame_size_hexa = 0x00;     // Frame size in hexa
    int mask = 0x80;                // To set bits 1 from MSB to LSB 

    // Read header
    while (bit_position < 8) {

        // Correct bit when it is 1
        if(frame[bit_position] == 1) {
            frame_size_hexa = (frame_size_hexa|mask);
        }

        // Move mask to the next bit
        mask >>= 1;

        // Update counter
        bit_position++;
    }

    // New frame without header
    vector<int> frame_without_header(frame_size_hexa*8, 0);

    // Build new frame without header using old frame 
    while (counter < frame_size_hexa*8){
        frame_without_header[counter] = frame[counter+8];  // Before eighth is the header

        // Update counter
        counter++;
    }

    // Print frame without header
    cout << endl << "Frame without character count: ";
    auto frame_pos_value = frame_without_header.begin(); // Begin to go through frame_without_header
    
    while(frame_pos_value != frame_without_header.end()){
        cout << *frame_pos_value;

        // Update counter
        frame_pos_value++;
    }
    cout << endl << endl;

    return frame_without_header;
}

vector<int> link_layer_data_receiver_byte_stuffing(vector<int> frame) {
    // Parameters
    vector<int> frame_without_byte_stuffing;    // Result of the frame without byte stuffing process
    int current_character = 0;                  // Counter 
    char read_character;                        // Store character

    while (current_character < (frame.size()/8)) {
        
        // Read the current character of the frame
        read_character = search_character(frame, current_character);

        // Check the first and the last byte flag
        if (read_character != byte_flag) {
            if (current_character == 0) {
                cout << "Error at the first byte flag!" << endl;
            } else if (current_character == (frame.size()/8 - 1)) {
                cout << "Error at the last byte flag!" << endl;
            }
        }

        // Check if there is a escape symbol
        if (read_character == byte_esc) {
            read_character = search_character(frame, ++current_character);
            frame_without_byte_stuffing = add_character(frame_without_byte_stuffing, read_character);
        }
        else if (read_character != byte_flag) {
            frame_without_byte_stuffing = add_character(frame_without_byte_stuffing, read_character);
        }

        // Update counter
        current_character++;
    }

    // Print frame without header
    cout << "Frame without byte stuffing: ";
    auto frame_pos_value = frame_without_byte_stuffing.begin(); // Begin to go through frame_without_byte_stuffing
    
    while(frame_pos_value != frame_without_byte_stuffing.end()){
        cout << *frame_pos_value;

        // Update counter
        frame_pos_value++;
    }
    cout << endl << endl;

    return frame_without_byte_stuffing;
}

vector<int> link_layer_data_receiver_error_control(vector<int> frame) {
    vector<int> frame_out;

    switch (type_of_error_control) {
        case 0:   // Parity bit
            cout << endl << "Type of error control: Parity bit" << endl;
            frame_out = link_layer_data_receiver_error_control_parity_bit(frame);
            break;
        
        case 1:   // CRC
            cout << endl << "Type of error control: CRC" << endl;
            frame_out = link_layer_data_receiver_error_control_CRC(frame);
            break;

        case 2:   // Hamming
            cout << endl << "Type of error control: Hamming" << endl;
            //frame_out = link_layer_data_receiver_error_control_Hamming_code(frame);
            break;

        default:
            break;
    }

    return frame_out;
}

vector<int> link_layer_data_receiver_error_control_parity_bit(vector<int> frame) {
    // Parameters
    int sum_of_1 = 0;
    int counter = 0;
    int parity_bit = 0;

    // Get the last bit. The last bit is the parity.
    parity_bit = frame.back();
    frame.pop_back();       // Remove parity bit

    // Count how many "1" bits exists
    while(counter < frame.size()){
        if(frame[counter] == 1) sum_of_1++;
        counter ++;
    }

    // Check if there is an error
    if(sum_of_1%2 != parity_bit){
        cout << "Parity bit check: Error!" << endl;
    } else {
        cout << "Parity bit check: Successful!" << endl;
    }

    // Print frame without parity bit
    cout << "Frame without parity bit at the end: ";
    auto frame_pos_value = frame.begin(); // Begin to go through the frame with byte stuffing: 
    
    while(frame_pos_value != frame.end()){
        cout << *frame_pos_value;

        // Update counter
        frame_pos_value++;
    }
    cout << endl;

    return frame;
}

vector<int> link_layer_data_receiver_error_control_CRC(vector<int> frame) {
    
    // Build CRC 32 vector
    vector<int> crc_32;
    long long int crc32_value = 0x0104C11DB7;
    int counter = 0;

    while(counter < 32){
        unsigned int temp = crc32_value >> (31-counter);
        temp &= 0x01;
        crc_32.push_back(temp);

        counter++;
    }

    // CRC process begins!
    vector<int> dividend = frame;
    vector<int> reminder;

    // Do the division operation
    counter = 0;
    while((dividend.size() - counter) > 32) {

        int inner_counter = 0;
        while(inner_counter < 33) {

            if(dividend[counter+inner_counter]) { 
                if(crc_32[inner_counter]) dividend[counter+inner_counter] = 0;
                else dividend[counter+inner_counter] = 1; 
            }
            else {
                if(crc_32[inner_counter]) dividend[counter+inner_counter] = 1;
                else dividend[counter+inner_counter] = 0; 
            }

            inner_counter++;
        }

        counter++;
    }

    // Check for errors
    bool error_flag = false;
    reminder.insert(reminder.begin(), dividend.end()-32, dividend.end());

    unsigned int counter2 = 0;
    while(counter2 < reminder.size()) {
        if(reminder[counter2] != 0){
            error_flag = true;
        }

        counter2++;
    }

    if(error_flag) {
        cout<< endl << "CRC Check: Transmission with error!" << endl;
    }

    // Print the reminder
    cout << "CRC Reminder: ";
    auto reminder_pos_value = reminder.begin(); // Begin to go through the reminder
    
    while(reminder_pos_value != reminder.end()){
        cout << *reminder_pos_value;

        // Update counter
        reminder_pos_value++;
    }
    cout << endl;

    // Store the frame result without CRC process
    vector<int> frame_without_crc;
    frame_without_crc.insert(frame_without_crc.end(), frame.begin(), frame.end()-32);
    
    // Print the frame result without CRC process
    cout << "Frame received without CRC process: ";
    auto frame_without_crc_pos_value = frame_without_crc.begin(); // Begin to go through the frame_without_crc
    
    while(frame_without_crc_pos_value != frame_without_crc.end()){
        cout << *frame_without_crc_pos_value;

        // Update counter
        frame_without_crc_pos_value++;
    }
    cout << endl;

    return frame_without_crc;
}

//vector<int> link_layer_data_receiver_error_control_Hamming_code(vector<int> frame) {

//}

// Auxiliary Functions
vector<int> add_character(vector<int> vector_in, char character) {
    
    // Create vector_out with one more byte
    vector<int> vector_out(vector_in.size() + 8, 0); 

    // Counters
    int counter = 0;
    int bit_position = 0; 

    // Store vector_in inside vector_out
    while (counter < vector_in.size()) {
        vector_out[counter] = vector_in[counter];
        counter++;
    }

    // Intert character
    counter = vector_in.size(); 

    while (counter < vector_out.size()) {
        char temp = character >> (7 - bit_position);
        vector_out[counter] = temp & 0x01;

        // Update counters
        counter++;
        bit_position++;
    }

    return vector_out;
}

char search_character(vector<int> vector_in, int position) {
    // Parameters
    int counter = 0;
    char character = 0; 
    char bit_position = 0x80;

    // Search for the character using the input position
    while (counter < 8) {
        char temp = vector_in[position*8 + counter] << (7 - counter);
        temp = temp & bit_position;
        bit_position = bit_position >> 1;
        character |= temp;
        
        // Update counter
        counter++;
    }

    return character;

}