// analyzer.cpp
// Implementations of the functions declared in analyzer.h

#include "analyzer.h"
#include <iostream>
#include <sstream>
//Turn the raw CSV text into a vector of Delivery structs
DeliveryLog parseDeliveries(const std::string &csvData) {
	DeliveryLog log; //empty log to fill and return
	std::stringstream data(csvData); //treat the string like a file we can read from
	std::string line;
	while (std::getline(data, line)) { //read one row at a time until the text runs out
		if (line.empty()) continue; //skip blank lines, stoi would crash on them
		std::stringstream ss(line); //wrap this one row in its own stream
		std::string date, hourStr, zone, restaurant, payoutStr, kmStr, waitStr, totalStr;
		//split the row at each comma, order must match the CSV format
		std::getline(ss, date, ','); /* the third argument changes the stop character */
		std::getline(ss, hourStr, ','); /* from newline to comma, one field per call */
		std::getline(ss, zone, ',');
		std::getline(ss, restaurant, ',');
		std::getline(ss, payoutStr, ',');
		std::getline(ss, kmStr, ',');
		std::getline(ss, waitStr, ',');
		std::getline(ss, totalStr, ',');
		Delivery d; //build the struct from the fields
		d.zone = zone;
		d.restaurant = restaurant;
		d.hour = std::stoi(hourStr); //string to int
		d.payout = std::stod(payoutStr); //string to double
		d.totalMin = std::stod(totalStr);
		log.push_back(d); //add it to the log
	}
	return log; //hand the finished vector back to the caller
}
//Which field of the delivery are we grouping by?
static std::string keyOf(const Delivery &d, const std::string &field) { //static = private to this file
	if (field == "zone")
		return d.zone;
	if (field == "restaurant")
		return d.restaurant;
	return std::to_string(d.hour) + ":00"; //default is hour, converted to text like "18:00"
}
//How many dollars per hour does each group earn?
Totals earningsPerHourBy(const DeliveryLog &log, const std::string &field) {
	Totals money; //group -> total dollars
	std::map<std::string, Minutes> minutes; //group -> total minutes worked
	for (const Delivery &d : log) { //loop over every delivery in the log
		std::string key = keyOf(d, field); //pick the group this delivery belongs to
		money[key] += d.payout; //map creates the key at 0 the first time we touch it
		minutes[key] += d.totalMin; //same trick for the minutes
	}
	Totals perHour; //to store the final answer
	for (const auto &entry : money) { //entry.first is the group name, entry.second is the dollars
		double hours = minutes[entry.first] / 60.0; //minutes to hours, 60.0 keeps the division double
		perHour[entry.first] = entry.second / hours; //dollars divided by hours
	}
	return perHour;
}
void printReport(const std::string &title, const Totals &results) {
	std::cout << "\n--- " << title << " ---\n";
	for (const auto &entry : results) //maps keep keys sorted so this prints alphabetically
		std::cout << entry.first << ": $" << entry.second << " per hour\n";
}