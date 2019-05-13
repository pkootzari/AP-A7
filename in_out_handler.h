#ifndef IN_OUT_HANDLER_H_
#define IN_OUT_HANDLER_H_

#include <string>
#include <iostream>
#include <sstream>
#include "manager.h"

class In_out_handler {
public:
    In_out_handler();
    void input_reader();
    void signup(std::vector<std::string> line_parts);
    friend std::vector<std::string> get_command(std::string input);
private:
    Manager* manager;
};

#endif