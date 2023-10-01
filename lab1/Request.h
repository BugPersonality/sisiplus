#pragma once

#include <string>

struct RequestResult {
    bool success;
    std::string message;
};

struct Request {
    std::string prompt;
    int& value;
    std::function<RequestResult(int)> action;
}; 