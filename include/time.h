#ifndef TIME_H
#define TIME_H

#include <fstream>
#include <iostream>

class Time
{
private:
	short hour, min;

public:
	/* defaults current time */
	Time();

	Time(short hour, short min);

	short getMin() const;
	short getHour() const;

	friend std::ostream& operator<<(std::ostream& outstream, const Time &t);
	friend std::ofstream& operator<<(std::ofstream& outstream, const Time &t);
	friend std::ifstream& operator>>(std::ifstream &instream, Time &t);
};

bool operator==(const Time& lhs, const Time& rhs);
bool operator!=(const Time& lhs, const Time& rhs);
bool operator< (const Time& lhs, const Time& rhs);
bool operator<=(const Time& lhs, const Time& rhs);
bool operator> (const Time& lhs, const Time& rhs);
bool operator>=(const Time& lhs, const Time& rhs);

#endif  // TIME_H
