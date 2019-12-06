// Based on the protobuf tutorial
#include <iostream>
#include <fstream>
#include <string>
#include "protos/foo.pb.h"

using namespace std;

// This function fills in a Person message based on user input.
void PromptForAddress(tutorial::Person* person) {
    int id;
    cout << "Enter person ID number: ";
    cin >> id;
    person->set_id(id);
    cin.ignore(256, '\n');

    cout << "Enter name: ";
    getline(cin, *person->mutable_name());

    string email;
    cout << "Enter email address (blank for none): ";
    getline(cin, email);
    if(!email.empty()) {
        person->set_email(email);
    }

    while(true) {
        string number;
        cout << "Enter a phone number (or leave blank to finish): ";
        getline(cin, number);
        if(number.empty()) {
            break;
        }

        tutorial::Person::PhoneNumber* phoneNumber = person->add_phones();
        phoneNumber->set_number(number);

        string type;
        cout << "Is this a mobile, home, or work phone? ";
        getline(cin, type);
        if("mobile" == type) {
            phoneNumber->set_type(tutorial::Person::MOBILE);
        } else if("home" == type) {
            phoneNumber->set_type(tutorial::Person::HOME);
        } else if("work" == type) {
            phoneNumber->set_type(tutorial::Person::WORK);
        } else {
            cout << "Unknown phone type. Using default." << endl;
            phoneNumber->set_type(tutorial::Person::HOME);
        }
    }
}

/**
 * Main function: Reads the entire address book from a file,
 *  adds one person based on user input, then writes it back out to the same
 *  file.
 */
int main(int argc, char* argv[]) {
    // Verify that the version of the library that we linked against is
    // compatible with the version of the headers we compiled against.
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    if(2 != argc) {
        cerr << "Usage: " << argv[0] << " ADDRESS_BOOK_FILE" << endl;
        return -1;
    }

    tutorial::AddressBook addressBook;

    {
        // Read existing address book.
        fstream input(argv[1], ios::in | ios::binary);
        if(!input) {
            cout << argv[1] << ": File not found. Creating new file." << endl;
        } else if(!addressBook.ParseFromIstream(&input)) {
            cerr << "Failed to parse address book." << endl;
            return -1;
        }
    }

    // Add an address
    PromptForAddress(addressBook.add_people());

    {
        fstream output(argv[1], ios::out | ios::trunc | ios::binary);
        if(!addressBook.SerializeToOstream(&output)) {
            cerr << "Failed to write to address book." << endl;
            return -1;
        }
    }

    // Optional: Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}
