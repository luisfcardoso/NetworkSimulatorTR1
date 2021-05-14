#include "../header/physical_layer.hpp"    // Physical Layer Header

// Physical Layer Functions
void transmitter_physical_layer(vector<int> frame, int code_option) {
    vector<int> stream_of_bits;  // Stream of bits (from frame)

    // Code the frame into a stream of bits according to the code
    switch (code_option) {
        case 1:
            stream_of_bits = binary_code_transmitter(frame);
        break;
        case 2:
            stream_of_bits = bipolar_code_transmitter(frame);
        break;
        case 3:
            stream_of_bits = manchester_code_transmitter(frame);
        break;
        default:
            cout << "The input code is not accept. Please, try again." << endl;
            return;
        break;
    }

    // Channel - where bits are transmitted
    channel(stream_of_bits, code_option);
}

void channel(vector<int> stream, int code_option) {
    int error, error_percentage;
    vector<int> stream_point_a, stream_point_b;  // Stream of point A and point B. The stream of bits will travel the path between these points.

    error_percentage = 0;
    stream_point_a = stream;    // The point A receive the stream of bits
    cout << "Transmission of bits: ";

    // The transmission will start
    int counter = 0;
    while (stream_point_b.size() < stream_point_a.size()) {
        if((rand()%100)) { // TODO: Error probability
            //stream_point_b += stream_point_a;
        } else {

        }
    }
    cout << endl;

    // After travel to point b, the stream of bits have to get the receiver's physical layer
    receiver_physical_layer(stream_point_b, code_option);
}

void receiver_physical_layer(vector<int> stream, int code_option) {
    vector<int> frame;  // frame (decode the stream of bits)

    // Decode the stream of bits into a frame according to the code
    switch (code_option) {
        case 1:
            stream = binary_code_receiver(stream);
        break;
        case 2:
            stream = bipolar_code_receiver(stream);
        break;
        case 3:
            stream = manchester_code_receiver(stream);
        break;
        default:
            cout << "The input code is not accept. Please, try again." << endl;
            return;
        break;
    }

    receiver_application_layer(stream); // Send stream of bits to application layer
}   

// Transmitter code Function
vector<int> binary_code_transmitter(vector<int> frame) {
    return frame;       // Return the same frame
}   

vector<int> bipolar_code_transmitter(vector<int> frame) {
    int position = 0;   // Counter to assist the bit stream position counting
    int sum_of_1s = 0;  // Sum of bits "1"   

    while(position < frame.size()) {        // Run through the entire frame
        
        if (frame.at(position) == 1) {      // If the bit is a "1"
            if (sum_of_1s % 2 == 1) {       // If the sum of "1"'s is an odd number, change the value of bit from "1" to "-1"
                frame.at(position) = -1;
            }
            sum_of_1s++;
        }

        position++;
    }

    return frame;   // Return the codificate frame
}   

vector<int> manchester_code_transmitter(vector<int> frame) {
    vector<int> frame_manchester;   // Frame with Manchester code
    int counter = 0;                // Counter

    while(counter < frame.size()) {
        // XOR
        frame_manchester.push_back(frame.at(counter) ^ 0);  // 0 XOR 0 = 0 / 1 XOR 0 = 1
        frame_manchester.push_back(frame.at(counter) ^ 1);  // 1 XOR 0 = 1 / 1 XOR 1 = 0

        counter++;
    }

    return frame_manchester;    // Encoded frame using Manchester code
}       

// Receiver code Function
vector<int> binary_code_receiver(vector<int> stream) {
    return stream;      // Return the same stream
}  

vector<int> bipolar_code_receiver(vector<int> stream) {
    int counter = 0;    // Counter

    while(counter < stream.size()) {
        if(stream.at(counter) == -1) {
            stream.at(counter) = 1; // If the bit is "-1", change to "1"
        }

        counter++;
    }
    
    return stream;
}  

vector<int> manchester_code_receiver(vector<int> stream) {
    vector<int> stream_decoded;     // Decoded stream
    int counter = 0;                // Counter to help with while loop

    while(counter < stream.size()) {
        stream_decoded.push_back(stream.at(counter));   // Get original bit
        counter = counter + 2;                          // Skip two positions
    }

    return stream_decoded;  // Return decoded stream 
}