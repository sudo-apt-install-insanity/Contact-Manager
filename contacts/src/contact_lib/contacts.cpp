#include "contacts.hpp"
#include<iostream>
#include<fstream>
#include <windows.h>
#include <regex>
#include <iomanip>
#include <vector>



using namespace std;

namespace contact_mngr
{
    vector<contact> contactList;
    bool ph_num_is_valid(string ph_num){
    long long num{0};
    try{
        num = stoll(ph_num);
    }catch(std::invalid_argument){
        return FALSE;
    }catch(std::out_of_range){
        return FALSE;
    }
    return TRUE;
    }
    //!! Function is sourced from : https://www.geeksforgeeks.org/check-if-given-email-address-is-valid-or-not-in-cpp/
    bool email_is_valid(string email){
        const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
        return regex_match(email,pattern);
    }
    
    bool contact::invalid_fields_present(){
        bool inv_name,inv_ph_num,inv_email,inv_address;
        inv_name = (name == "" || name == " ")? TRUE : FALSE; 
        inv_ph_num = ph_num_is_valid(ph_num) ? FALSE : TRUE;
        inv_address = (address == "" || address == " ") ? TRUE : FALSE;
        inv_email = email_is_valid(email) ? FALSE : TRUE;
        if(inv_name || inv_ph_num || inv_email || inv_address){
            string f1name = inv_name ? " Name |" : "";
            string f2ph_num = inv_ph_num ? " Phone Number |" : "";
            string f3address = inv_address ? " Address |" : "";
            string f4email = inv_email ? " Email" : "";
            set_cmd_color(red);
            cout << setw((_TERMINAL_WIDTH-50)/2) << "" << "Invalid Fields : " << f1name << f2ph_num  << f3address << f4email << endl;
            return TRUE;
        }
        return FALSE;
    }
    bool contact::is_valid(){
        return !invalid_fields_present();
    }
    void contact::make_contact(){
        system("cls");
        cout << setw((_TERMINAL_WIDTH-50)/2) << "" << "*********************************************** " << endl << endl;
        cout << setw((_TERMINAL_WIDTH-50)/2) << "" << "> Enter name         : ";
        getline(cin,name);
        cout << setw((_TERMINAL_WIDTH-50)/2) << "" << "> Enter phone number : ";
        getline(cin,ph_num);
        cout << setw((_TERMINAL_WIDTH-50)/2) << "" << "> Enter address      : ";
        getline(cin,address);     
        cout << setw((_TERMINAL_WIDTH-50)/2) << "" << "> Enter email        : ";
        getline(cin,email);
        cout << "\n" << setw((_TERMINAL_WIDTH-50)/2) << "" << "*********************************************** " << endl << endl;
    }
    ostream &operator << (ostream &out , const contact &c){
        out << c.name << "<nf>" << c.ph_num << "<nf>" << c.address << "<nf>" << c.email << endl;
    }
    istream &operator >> (istream &in , contact &c){
        string tokenlist;
        vector<string> tokens;
        string token;
        getline(in,tokenlist);
        size_t pos = 0;
        while((pos = tokenlist.find(_CUSTOM_DELIM)) != string::npos){
            token = tokenlist.substr(0,pos);
            tokens.push_back(token);
            tokenlist.erase(0,pos+_CUSTOM_DELIM.length());
        }
        tokens.push_back(tokenlist);
        if(tokens.size() < 4){
            return in;
        }
        c.name = tokens.at(0);
        c.ph_num = tokens.at(1);
        c.address = tokens.at(2);
        c.email = tokens.at(3);
        return in;
    }

    char menu(){
        /* *********************** Main Menu ***********************  */
        system("cls");
        char ch;
        const string _HEADER{"**** Welcome to Contact Management System ****"};
        cout << setw((_TERMINAL_WIDTH - _HEADER.length())/2) << "" << _HEADER << endl << endl << endl << endl;
        cout << setw((_TERMINAL_WIDTH-10)/2) << "" <<"MAIN MENU" << endl
            << setw((_TERMINAL_WIDTH-22)/2) << "" <<"=====================" << endl
            << setw((_TERMINAL_WIDTH-22)/2) << "" <<"[1] Add a new contact" << endl
            << setw((_TERMINAL_WIDTH-22)/2) << "" <<"[2] List all contacts" << endl
            << setw((_TERMINAL_WIDTH-22)/2) << "" <<"[3] Search for contact" << endl
            << setw((_TERMINAL_WIDTH-22)/2) << "" <<"[4] Edit a Contact" << endl
            << setw((_TERMINAL_WIDTH-22)/2) << "" <<"[5] Delete a Contact" << endl
            << setw((_TERMINAL_WIDTH-22)/2) << "" <<"[6] Save to file" << endl
            << setw((_TERMINAL_WIDTH-22)/2) << "" <<"[0] Exit" << endl
            << setw((_TERMINAL_WIDTH-22)/2) << "" <<"=====================" << endl
            << setw((_TERMINAL_WIDTH-22)/2) << "" << "Enter the choice : ";
        cin  >> ch;
        cin.ignore(1000,'\n');
        return ch;
    }
    void add_contact(){
        contact c;
        c.make_contact();
        if(c.is_valid()){
            contactList.push_back(c);
            set_cmd_color(green);
            cout << setw((_TERMINAL_WIDTH-50)/2) << "" << "Contact added successfully!" << endl; 
            cin.ignore(1000,'\n');
            reset_cmd_color();
        }
        else{
            set_cmd_color(red);
            cout << setw((_TERMINAL_WIDTH-50)/2) << "" << "Contact couldn't be added!!" << endl;
            cout << setw((_TERMINAL_WIDTH-50)/2) << "" << "Try again? (Y/N)" << endl;
            char choice;
            cin >> choice;
            cin.sync();
            if(choice == 'Y' || choice == 'y'){
                reset_cmd_color();
                add_contact();
            }
            reset_cmd_color();
        }
    } 
    void search_contact(){
        contact c;
        string query;
        bool found = false;
        cout << setw((_TERMINAL_WIDTH-30)/2) << "" << "Name of contact to search : ";
        getline(cin,query); 
        for(contact c : contactList){
            if(query == c.name){
                cout << setw((_TERMINAL_WIDTH-50)/2) << "" << "*********************************************** " << endl;
                cout << setw((_TERMINAL_WIDTH-50)/2) << "" << "Contact found!" << endl;
                cout << setw((_TERMINAL_WIDTH-50)/2) << "" << "Name         : " << c.name << endl;
                cout << setw((_TERMINAL_WIDTH-50)/2) << "" << "Phone Number : " << c.ph_num << endl;
                cout << setw((_TERMINAL_WIDTH-50)/2) << "" << "Address      : " << c.address << endl;
                cout << setw((_TERMINAL_WIDTH-50)/2) << "" << "Email        : " << c.email << endl;
                cout << setw((_TERMINAL_WIDTH-50)/2) << "" << "Press Enter to go main menu." << endl;
                cout << setw((_TERMINAL_WIDTH-50)/2) << "" << "*********************************************** " << endl;
                cin.ignore(1000,'\n');
                found = true;
                break;
            }
        }
        if(!found){
            set_cmd_color(red);
            cout << setw((_TERMINAL_WIDTH-30)/2) << "" << "Contact not found!!" << endl;
            cout << setw((_TERMINAL_WIDTH-30)/2) << "" << "Press Enter to go main menu." << endl;
            cin.ignore(1000,'\n');
            reset_cmd_color();
        }
        

    }
    void edit_contact(){
        string query;
        int found = 0;  
        cout << setw((_TERMINAL_WIDTH-34)/2) << "" << "Enter name of contact to edit : ";
        getline(cin,query);
        for(contact &c : contactList){
            if(c.name == query){
                contact temp;
                temp.make_contact();
                if(temp.is_valid()){
                    c = temp;
                    found = 1;
                    break;
                }
                found = 2;
                break;
            }
        }
        if(found == 1){
            set_cmd_color(green);
            cout << setw((_TERMINAL_WIDTH-30)/2) << "" << "Contact updated." << endl;
            cout << setw((_TERMINAL_WIDTH-30)/2) << "" << "Press Enter to go main menu." << endl;
            cin.ignore(1000,'\n');
            reset_cmd_color();
        }else if(found == 2){
            set_cmd_color(dark_yellow);
            cout << setw((_TERMINAL_WIDTH-30)/2) << "" << "Contact found but not updated!!." << endl;
            // cout << setw((_TERMINAL_WIDTH-30)/2) << "" << "Press Enter to go main menu." << endl;
            cout << setw((_TERMINAL_WIDTH-30)/2) << "" << "Try again? (Y/N) " << endl;
            char choice;
            cin >> choice;
            cin.sync();
            if(choice == 'Y' || choice == 'y'){
                reset_cmd_color();
                edit_contact();
            }
            // cin.ignore(1000,'\n');
            reset_cmd_color();
        }else{
            set_cmd_color(red);
            cout << setw((_TERMINAL_WIDTH-34)/2) << "" << "Contact not found!!No changes made." << endl;
            cout << setw((_TERMINAL_WIDTH-34)/2) << "" << "Press Enter to go main menu." << endl;
            cin.ignore(1000,'\n');
            reset_cmd_color();
        } 
    }
    void delete_contact(){
        string query;
        bool found = false;  
        cout << setw((_TERMINAL_WIDTH-36)/2) << "" << "Enter name of contact to delete : ";
        getline(cin,query);
        for (unsigned int i = 0; i < contactList.size(); i++)
        {
            auto iterator = contactList.begin()+i;
            if(contactList.at(i).name == query){
                contactList.erase(iterator);
                found = true;
                break;
            }
        }
        if(found){
            set_cmd_color(green);
            cout << setw((_TERMINAL_WIDTH-36)/2) << "" << "Contact deleted." << endl;
            cin.ignore(1000,'\n');
            reset_cmd_color();
        }else{
            set_cmd_color(red);
            cout << setw((_TERMINAL_WIDTH-36)/2) << "" << "Contact not found!!No changes made." << endl;
            cin.ignore(1000,'\n');
            reset_cmd_color();
        }
            
    }
    void print_contact_list(){
        system("cls");
        if(contactList.empty()){
            set_cmd_color(red);
            cout << "\n\n\n\n" << setw((_TERMINAL_WIDTH - 50)/2) << "" << "CONTACT LIST IS EMPTY. ADD SOME CONTACTS FIRST!!" << endl;
            cout << setw((_TERMINAL_WIDTH - 50)/2) << "" << "------------------------------------------------" << endl;
            cin.ignore(1000,'\n');
            reset_cmd_color();
            return;
        }
        const string _CON_LIST_TITLE{"<::::CONTACT LIST::::>"};
        cout << setw((_TERMINAL_WIDTH - _CON_LIST_TITLE.length())/2) << "" << _CON_LIST_TITLE << endl << endl;
        cout << setw(30) << left << "NAME" 
            << setw(30) << left << "PHONE NUMBER" 
            << setw(30) << left << "ADDRESS" 
            << setw(30) << left << "EMAIL" << endl << endl;
        for (contact c : contactList)
        {
            print_contact(c);
        }
        cin.ignore(1000,'\n');
    }
    void print_contact(contact &c){
        cout << setw(30) << left << c.name 
            << setw(30) << left << c.ph_num 
            << setw(30) << left << c.address
            << setw(30) << left << c.email << endl;  
    }
    void set_cmd_color(int color){
        HANDLE consoleHandle;
        consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(consoleHandle,color);
    }
    void reset_cmd_color(){
        set_cmd_color(cyan);
    }
    void save_to_file(){
        ofstream out_to_file;
        out_to_file.open("contacts.bin",ios::out | ios::binary);
        for (contact c : contactList) 
        {
            out_to_file << c;
        }
        out_to_file.close();
        set_cmd_color(green);
        cout << setw((contact_mngr::_TERMINAL_WIDTH-28)/2) << "" << "Changes saved successfully!" << endl; 
        cin.ignore(1000,'\n');
        reset_cmd_color();
    }
    void load_from_file(){
        fstream in_from_file;
        contact c;
        contactList.clear();
        in_from_file.open("contacts.bin",ios::in | ios::out |ios::binary);
        while(in_from_file >> c){
            contactList.push_back(c);
        }
        in_from_file.close();
    }
} // namespace contact_mngr

