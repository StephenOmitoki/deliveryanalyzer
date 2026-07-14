// analyzer.h
// Declarations: the Delivery struct, type aliases, and function prototypes.

#ifndef ANALYZER_H
#define ANALYZER_H
#include <string>
#include <vector>
#include <map>
// Type aliases
using Money = double; //just a double with a meaningful name
using Minutes = double; //same idea, so function signatures explain themselves
using Totals = std::map<std::string, Money>; //maps a group name to its dollars per hour
//One delivery = one logged order
struct Delivery {
	std::string zone; //area label like downtown or campus
	std::string restaurant;
	int hour; //hour of day the order was accepted (0-23)
	Money payout; //total earned including tip
	Minutes totalMin; //minutes from accepting to dropoff
};
//The log is a vector of Delivery structs
using DeliveryLog = std::vector<Delivery>;
//my functions, implemented in analyzer.cpp
DeliveryLog parseDeliveries(const std::string &csvData);
Totals earningsPerHourBy(const DeliveryLog &log, const std::string &field);
void printReport(const std::string &title, const Totals &results);
#endif