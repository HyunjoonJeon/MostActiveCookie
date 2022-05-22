#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// date1 < date2 -> -1, date1 == date2 -> 0, date1 > date2 -> 1
int8_t compareDates(string date1, string date2) {
    int year1, month1, day1;
    int year2, month2, day2;
    sscanf(date1.data(), "%d-%d-%d", &year1, &month1, &day1);
    sscanf(date2.data(), "%d-%d-%d", &year2, &month2, &day2);
    if(year1 < year2 || year1 == year2 && month1 < month2 || year1 == year2 && month1 == month2 && day1 < day2) {
        return -1;
    } else if(date1 == date2) {
        return 0;
    } else {
        return 1;
    }
}

// extract and find most active cookie simultaneously
void mostActiveCookies(string fileName, vector<string> &cookies, string date) {
    string line;
    fstream file (fileName, ios::in);
    if(file.is_open()) {
        unordered_map<string,unsigned int> table;
        unsigned int maxFrequency = 1;
        getline(file, line); // ignore the first line: cookie,timestamp
        while(getline(file, line)) {
            int splitPos = line.find(',');
            string cookie = line.substr(0, splitPos);
            string cookieDateAndTime = line.substr(splitPos + 1);
            string cookieDate = cookieDateAndTime.substr(0, cookieDateAndTime.find('T'));
            int8_t compare = compareDates(cookieDate, date);
            if(compare == -1) {
                break;
            } else if(compare == 0){
                if(table.find(cookie) == table.end()) { // cookie occured for the first time
                    table[cookie] = 1;
                } else {
                    unsigned int count = table[cookie] + 1;
                    table[cookie] = count;
                    if(maxFrequency < count) maxFrequency = count;
                }
            }
        }
        for(auto itr = table.begin(); itr != table.end(); itr++) {
            if(itr->second == maxFrequency) {
                cout << itr->first << endl;
            }
        }
    } else {
        cout << "Error: Could not open the file. Please check the file name." << endl;
    }
}

int main(int argc, char **argv) {

    // check if the correct number of arguments are given
    if(argc != 4) {
        cout << "Error: Invalid number of command line arguments: " + to_string(argc) << endl;
        return 1;
    }

    vector<string> cookies;

    // using the new function
    mostActiveCookies(argv[1], cookies, argv[3]);

    return 0;
}