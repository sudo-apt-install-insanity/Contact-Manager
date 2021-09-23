//// Handle unexpected application closing if r/w occur once.
//// Reformat to take input with whitespaces in field(change delim to <nf>(String delim))
//// Format the output better
//// Reformat to read in complete file to internal ds make changes as per need and write back to file



#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <contact_lib/contacts.hpp>


using namespace std;
using namespace contact_mngr;



int main(){
    srand(time(0));
    set_cmd_color(cyan);
    bool quit = false;
    load_from_file();

    int quit_val = atexit(save_to_file);
    do{
        switch (menu())
        {
        case '1':
            add_contact();
            break;
        case '2':
            print_contact_list();
            break;
        case '3':
            search_contact();
            break;
        case '4':
            edit_contact();
            break;
        case '5':
            delete_contact();
            break;
        case '6':
            save_to_file();
            break;
        case '0':
            quit = true;
            break;
        default:
            set_cmd_color(red);
            cout << setw((contact_mngr::_TERMINAL_WIDTH-22)/2) << "" << "Invalid choice!!Try again. " << endl;
            cin.ignore(1000,'\n');
            reset_cmd_color();
            break;
        }
    }while(!quit);
}
