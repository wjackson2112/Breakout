#include "Options.h"
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/detail/xml_parser_writer_settings.hpp>

void Options::write()
{
	write_xml("breakout.xml", pt, std::locale(), 
		boost::property_tree::xml_parser::xml_writer_make_settings('\t', 1));
}

void Options::read()
{
	read_xml("breakout.xml", pt, boost::property_tree::xml_parser::trim_whitespace);
}

string Options::getValue(string path)
{
	return pt.get<std::string>(path);
}

void Options::setValue(string path, string value)
{
	pt.put(path, value);
}