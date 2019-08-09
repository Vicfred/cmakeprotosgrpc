// Based on the protobuf tutorial
#include <iostream>
#include <fstream>
#include <string>
#include "foo.pb.h"

using namespace std;

// Iterates through all people in the AddressBook and prints info about them.
void ListPeople(const tutorial::AddressBook& addressBook) {
    for(int i = 0; i < addressBook.people_size(); ++i) {
        const tutorial::Person& person = addressBook.people(i);

        cout << "Person ID: " << person.id() << endl;
        cout << "Name: " << person.name() << endl;
        cout << "E-mail address: " << person.email() << endl;

        for(int j = 0; j < person.phones_size(); ++j) {
            const tutorial::Person::PhoneNumber& phoneNumber = person.phones(j);

            switch(phoneNumber.type()) {
                case tutorial::Person::MOBILE:
                    cout << "Mobile phone #: ";
                    break;
                case tutorial::Person::HOME:
                    cout << "Home phone #: ";
                    break;
                case tutorial::Person::WORK:
                    cout << "Work phone #: ";
                    break;
            }
            cout << phoneNumber.number() << endl;
        }
    }
}

/**
* Main function: Reads the entire address book from a file and prints all
 * the information inside.
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
        // Read the existing address book.
        fstream input(argv[1], ios::in | ios::binary);
        if(!addressBook.ParseFromIstream(&input)) {
            cerr << "Failed to parse address book." << endl;
            return -1;
        }
    }

    ListPeople(addressBook);

    // Optional: Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}
