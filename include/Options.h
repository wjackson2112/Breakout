#ifndef OPTIONS_H
#define OPTIONS_H

#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <string>

using boost::property_tree::ptree;
using std::string;

class Options
{
	ptree pt;
public:
	void write();
	void read();

	string getValue(string path);
	void   setValue(string path, string value);
};

#endif