add_library(
    contacts
    src/contact_lib/contacts.hpp
    src/contact_lib/contacts.cpp
)


target_include_directories(contacts PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)