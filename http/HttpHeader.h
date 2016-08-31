#ifndef HTTPHEADER_H
#define HTTPHEADER_H

#include <string>
#include <map>

class HttpHeader
{
public:
	HttpHeader();
	const char* operator[](const char*) const;
	void parse(std::string header);
protected:
private:
	char m_nullString;
	std::string m_headerRaw;
	std::string m_header;
	std::map<std::string, int> m_mapField;
};

#endif