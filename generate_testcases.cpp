#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <fstream>

using namespace std;

string randomString(unsigned int size) {
    const char charset [] = 
        "0123456789"
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int maxIndex = sizeof(charset) - 1;
    string result = "";
    for(int i = 0; i < size; i++) {
        result += charset[ rand() % maxIndex ];
    }
    return result;
}

void randomCookie(int nOfCookies, int nOfTestcases, string fileName) {
    srand((int) time(0));
    string dates[5] = {
        "2022-05-21",
        "2022-05-20",
        "2022-05-19",
        "2022-05-18",
        "2022-05-17"
    };
    string time = "T00:00:00+00:00"; // unlike date, time does not matter
    // generate n number of cookies of length 10
    string cookies[nOfCookies];
    for(int i = 0; i < nOfCookies; i++) {
        cookies[i] = randomString(10);
    }
    // record frequencies the cookies for each date
    vector<unsigned int> frequencies;
    for(int i = 0; i < nOfCookies * 5; i++) {
        frequencies.push_back(0);
    }
    // create a cookies log and answer file
    ofstream logFile;
    logFile.open(fileName+".csv");
    ofstream answerFile;
    answerFile.open(fileName+"_answer.txt");

    // generate n number of testcases and count frequencies of the cookies for answer
    logFile << "cookie,timestamp" << endl;
    for(int i = 0; i < nOfTestcases; i++) {
        int cookieIndex = rand() % nOfCookies;
        string cookie = cookies[cookieIndex];
        int dateIndex = i / (nOfTestcases / 5.0);
        frequencies[cookieIndex + dateIndex * nOfCookies]++;
        cookie += "," + dates[dateIndex];
        cookie += time;
        logFile << cookie << endl;
    }

    // find most active cookies for each date
    for(int i = 0; i < 5; i++) {
        answerFile << dates[i] << " " << cookies[(max_element(frequencies.begin()+i*nOfCookies, frequencies.begin()+(i+1)*nOfCookies) - frequencies.begin()) % nOfCookies] << endl;
    }

    // close the files
    logFile.close();
    answerFile.close();
}

int main(int argc, char **argv) {

    randomCookie(stoi(argv[1]), stoi(argv[2]), argv[3]);

    return 0;
}