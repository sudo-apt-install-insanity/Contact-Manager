
#include<iostream>
#include<fstream>
#include<vector>

#ifndef _CONTACTS_HPP
#define _CONTACTS_HPP
#pragma once
	
    namespace contact_mngr{
        enum concol
        {
            black=0,
            dark_blue=1,
            dark_green=2,
            dark_aqua,dark_cyan=3,
            dark_red=4,
            dark_purple=5,dark_pink=5,dark_magenta=5,
            dark_yellow=6,
            dark_white=7,
            gray=8,
            blue=9,
            green=10,
            aqua=11,cyan=11,
            red=12,
            purple=13,pink=13,magenta=13,
            yellow=14,
            white=15
        };
        const std::string _CUSTOM_DELIM {"<nf>"};
        const int _TERMINAL_WIDTH {120}; //!!NOTE - This is a NOT a predefined(compiler) terminal width! Used for formatting purposes.

        bool ph_num_is_valid(std::string ph_num);
        bool email_is_valid(std::string email);//!! Function is sourced from : https://www.geeksforgeeks.org/check-if-given-email-address-is-valid-or-not-in-cpp/
        class contact{
        public:
            std::string name,ph_num,address,email;

            contact(){
                name = "";
                ph_num = "";
                address = "";
                email = "";
            }
            bool invalid_fields_present();
            bool is_valid();
            void make_contact();
            friend std::ostream &operator << (std::ostream &out , const contact &c);
            friend std::istream &operator >> (std::istream &in , contact &c);
        };
        char menu();
        void add_contact();
        void search_contact();
        void edit_contact();
        void delete_contact();
        void print_contact_list();
        void print_contact(contact &c);
        void set_cmd_color(int color);
        void reset_cmd_color();
        void load_from_file();
        void save_to_file();
        void save();
        
    } // namespace contact_mngr
#endif