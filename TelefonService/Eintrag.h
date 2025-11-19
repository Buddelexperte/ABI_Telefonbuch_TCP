#pragma once
#include <string>

class Eintrag
{
private:
	std::string name;
	std::string telefonnr;

public:
	Eintrag(std::string, std::string);
	~Eintrag();

	std::string getNr();
	std::string getName();
	void setNr(std::string);
	void setName(std::string);
};