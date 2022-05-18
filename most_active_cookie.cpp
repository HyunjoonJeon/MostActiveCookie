#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// extract cookies in the given date
bool extractCookies(string fileName, vector<string> &cookies, string date) {
    string line;
    fstream file (fileName, ios::in);
    if(file.is_open()) {
        getline(file, line); // ignore the first line: cookie,timestamp
        while(getline(file, line)) {
            int splitPos = line.find(',');
            string cookie = line.substr(0, splitPos);
            string cookieDate = line.substr(splitPos + 1);
            if(cookieDate.substr(0,cookieDate.find('T')) == date) {
                cookies.push_back(cookie);
            }
        }
        return true;
    }
    cout << "Error: Could not open the file. Please check the file name." << endl;
    return false;
}

void mostActiveCookies(vector<string> &cookies) {
    if(cookies.empty()) {
        
    }
}

int main(int argc, char **argv) {

    // check if the correct number of arguments are given
    if(argc != 4) {
        cout << "Error: Invalid number of command line arguments: " + to_string(argc) << endl;
        return 1;
    }

    vector<string> cookies;

    extractCookies(argv[1], cookies, argv[3]);

    for(int i = 0; i < cookies.size(); i++) {
        cout << cookies[i] << endl;
    }
    

    // argv[0] = ./most_active_cookie
    // argv[1] = cookie_log.csv
    // argv[2] = -d
    // argv[3] = 2018-12-09


    return 0;
}