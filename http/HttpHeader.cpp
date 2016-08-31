#include "HttpHeader.h"

HttpHeader::HttpHeader() :m_nullString('\0')
{

}

void HttpHeader::parse(std::string header)
{
	m_headerRaw = header;
	m_header = header;
	m_mapField.clear();
	int pos = header.find_first_of("\r\n");
	if (pos == std::string::npos)
	{
		return;
	}
	m_mapField["Version"] = 5;
	m_header[8] = '\0';
	m_mapField["Status-Code"] = 9;
	m_header[12] = '\0';

	while (true)
	{
		pos = pos + 2;
		if (pos == std::string::npos)
		{
			return;
		}
		int pos2 = header.find_first_of("\r\n", pos);
		if (pos2 == std::string::npos)
		{
			return;
		}
		int pos3 = header.find_first_of(":", pos);
		if (pos3 != std::string::npos && pos3 < pos2)
		{
			m_header[pos3] = '\0';
			++pos3;
			pos3 = header.find_first_not_of(" ", pos3);
			if (pos3 != std::string::npos && pos3 < pos2)
			{
				m_header[pos2] = '\0';
				m_mapField[m_header.c_str() + pos] = pos3;
			}
		}
		pos = pos2;
	}

}

const char* HttpHeader::operator[](const char* field) const
{
	std::map<std::string, int>::const_iterator it = m_mapField.find(field);
	if (it == m_mapField.end())
	{
		return &m_nullString;
	}
	return m_header.c_str() + it->second;
}