# Most Active Cookie

## Introduction
The task is to develop a program that finds the most active cookie in a given cookie log file in the following format:

```
cookie,timestamp
AtY0laUfhglK3lC7,2018-12-09T14:19:00+00:00
SAZuXPGUrfbcn5UA,2018-12-09T10:13:00+00:00
5UAVanZf6UtGyKVS,2018-12-09T07:25:00+00:00
AtY0laUfhglK3lC7,2018-12-09T06:19:00+00:00
SAZuXPGUrfbcn5UA,2018-12-08T22:03:00+00:00
4sMM2LxV07bPJzwf,2018-12-08T21:30:00+00:00
fbcn5UAVanZf6UtG,2018-12-08T09:30:00+00:00
4sMM2LxV07bPJzwf,2018-12-07T23:30:00+00:00
```

The most active cookie is defined as the most seen cookie during a given day. So
in the above example, the most active cookie for 2018-12-09 would be `AtY0laUfhglK3lC7`. There can be multiple most active cookies during the given day as 2018-12-08 in the above example where `SAZuXPGUrfbcn5UA`, `4sMM2LxV07bPJzwf`, and `fbcn5UAVanZf6UtG` are the most active cookies.

## How to run the program

First compile `most_active_cookie.cpp`:
```sh
g++ most_active_cookie.cpp -o most_active_cookie
```
Then run the executable with three command line parameters:
```sh
./most_active_cookie cookie_log.csv -d 2018-12-09
```

- The first parameter is the input cookie log file
- The second parameter `-d` takes date in UTC time zone.
- The third parameter is the input date

## Testing

A bash script was written to automate the testing process. The script can be run by executing the following command:

```sh
./most_active_cookie_test.sh
```

The directory `Program_tests` contain both manually written testcases and automatically generated testcases. Each testcase contains cookies with dates among `2022-05-21`, `2022-05-20`, `2022-05-19`, `2022-05-18`, and `2022-05-17`. The program is tested using the testcases with each of the available dates. Then the output was checked by the answers in the `Answers` sub-folder in both `ManualTest` and `AutomatedTest`.

### Manual testcases

There are 4 manual testcases in the directory. However, a user can add a custom testcase by simply adding a log file in Program_tests/ManualTest/Testcases and the correct output in `Program_tests/ManualTest/Answers`.

1. manual_log_1.csv
    - A general cookie log with all the dates.
2. some_dates_missing_log.csv
    - A general cookie log with some dates missing.
3. empty_log.csv
    - An empty cookie log to test the behaviour of the program when an empty file was given.
4. millionCookies.csv
    - A cookie log that contains one million cookies. 

### Randomly generated testcases

The bash script `most_active_cookie_test.sh` creates various testcases using the program `generate_testcases.cpp`. The program can generate a given number of random cookies with a specified distinct number of cookies. In the bash script, the distinct number of cookies is set to be `8` and the number of cookies in each testcase is varied among `100`, `1000`, `10000`, `100000`, and `1000000`. While the testcases are generated, the correct outputs are also calculated to check the accuracy of the `most_active_cookie` program. When the bash script is executed, a message indicating the number of testcases passed out of the total number will be printed in the terminal.

## Platform

The program was developed in mac OS. 