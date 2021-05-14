#include "../header/application_layer.hpp"    // Application Layer Header

// Implementation of Application Layer Functions
void transmitter_application() {
    string message;    // Message to be sent

    // Store message
    cout << "Transmitter Side" << endl;
    cout << "Enter a message, please:" << endl;
    getline(cin, message);
    
    // Show the message
    cout << "You wrote: " << message << endl;

    // Choose the code
    string code_option_string;
    int code_option = -1;
    
    while(!(code_option == 1)&&!(code_option == 2)&&!(code_option == 3)) {
        cout    << "Please, choose one of the code options:" << endl
                << "1: Binary code" << endl
                << "2: Bipolar code" << endl
                << "3: Manchester code" << endl;

        getline(cin,code_option_string);        // Store the code option
        code_option = code_option_selection(code_option_string);
    }  

    cout << "You chose the option " << code_option << endl; //Show the code option

    transmitter_application_layer(message, code_option);
}

void transmitter_application_layer(string message, int code_option) {
    // Convert the input message to ASCII code
    vector<int> frame_binary_ascii_message = convert_message_to_ASCII(message);

    // Send Message to Transmitter Physical Layer
    transmitter_physical_layer(frame_binary_ascii_message, code_option);
}

void receiver_application_layer(vector<int> frame) {
    string message = convert_received_message_to_string(frame);     // Convert received message to string
    receiver_application(message);                                  // Send message to the receiver application
}

void receiver_application(string message) {
    cout << "You received the message: " << message << endl;        // Show the sent message
}


// Auxiliary Functions
vector<int> convert_message_to_ASCII(string message) {
    vector<int> frame;  // Frame that store Message ASCII codes (int) of each word

    int counter = 0;
    while(message.size() > counter) {
        int char_code = int(message.at(counter)); // Char ASCII Code

        // Convert Decimal ASCII Code to Binary ASCII Code (inverse order)
        vector<int> temporary_frame; // Temporary frame to help the conversion

        for (int inner_counter = 0; inner_counter < 8; inner_counter++) { // 1 byte = 8 bits
            if (char_code % 2 == 0) {   // If the bit (as a char) is a pair
                temporary_frame.push_back(0);   // Append 0
            } else {
                temporary_frame.push_back(1);   // Append 1
            }

            char_code = char_code >> 1;         // Using the shift operation to get the next char element
        }

        // Correct order of the Binary ASCII Code
        for (int inner_counter = 7; inner_counter >= 0; inner_counter--) {  // 1 byte = 8 bits
            frame.push_back(temporary_frame.at(inner_counter));    
        }
        
        counter++;
    }

    return frame;
}

string convert_received_message_to_string(vector<int> frame) {
    string message = "";
    int int_to_char = 0;    // Auxiliary
    int counter = 0;        // Counter

    while (counter < frame.size()) {
        if (counter != 0 && counter % 8 == 0) {     // ASCII Code <- 8 bits
            message.append(1, char(int_to_char));   // Int (ASCII Code) -> String (of Char)
            int_to_char = 0;
        }

        int_to_char = int_to_char << 1;             // Multiply by 2 (Cross the bits)
        int_to_char += frame.at(counter);

        counter ++;
    }

    message.append(1, char(int_to_char));           // Int (ASCII Code) -> String (of Char)

    return message;
}

int code_option_selection(string input) {   // The input is a ASCII code
    int option = int(input[0]);

    switch (option)  {
    case 49:        // 49 represents 1 in ASCII code
        option = 1;
        break;
    
    case 50:        // 50 represents 2 in ASCII code
        option = 2;
        break;

    case 51:        // 51 represents 3 in ASCII code                
        option = 3;
        break;

    default:        // The default (error) is -1
        option = -1;
        break;
    } 

    return option;
}
