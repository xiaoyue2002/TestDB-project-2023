#pragma once
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class Logger {
public:
    // Log error info and force exit
    static void logError(const string& message){
        // cout << "Error: " << message << endl;
        // exit(EXIT_FAILURE);
    }

    static void log(const string & message){
        // cerr << "Error:" << message << endl; 
    }

    // Log Info
    static void logging(const string& message){
        // cout << "Logging: " << message << endl;
    }
};