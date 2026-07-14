# deliveryanalyzer

Stephen Omitoki
Overview:
This program analyzes a personal delivery driving log and reports earnings per hour worked, grouped three ways: by zone, by hour of the day, and by restaurant. Most drivers judge orders by the payout per order, which is misleading because long restaurant waits eat into hourly earnings. This program computes real dollars per hour so the driver can see which zones, times and restaurants actually pay the best.

How to Run:
Run the program using a C++ compiler.
The delivery data is stored inside main.cpp in the csvData string. Add one line per delivery in the format: date,hour,zone,restaurant,payout,km,wait_min,total_min
The program will parse the log and print the three earnings reports.
On OnlineGDB, add all three files to the project. Do not add any .csv file to the project because the compiler will try to compile it.

Requirements:
C++ compiler 

Files:
main.cpp : Contains the delivery log data and the main program flow.
analyzer.h : The Delivery struct, type aliases and function prototypes.
analyzer.cpp : Implementation of all helper functions (parseDeliveries, earningsPerHourBy, printReport).
