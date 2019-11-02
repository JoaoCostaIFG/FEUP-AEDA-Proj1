#include "../include/time.h"

#include <ctime>
#include <iomanip>

#include "../include/exceptions.h"

using namespace std;

/* WARNING: current date is compiler dependent */
Time::Time()
{
	/* current localTime for gcc/gcc based compiler */
	time_t time_now;
	time(&time_now);

	/* we need to "normalize" the information about hours, minutes and seconds */
	tm *temp_tm = localtime(&time_now);

	/* save info */
	hour = (short) temp_tm->tm_hour;
	min = (short) temp_tm->tm_min;
}

Time::Time(short hour, short min)
{
	this->hour = hour;
	this->min = min;
}

#pragma region GETTERS

short
Time::getMin() const
{
	return min;
}

short
Time::getHour() const
{
	return hour;
}

#pragma endregion

/* compare */

bool
Time::operator==(const Time &t) const
{
	return (this->hour == t.hour) && (this->min == t.min);
}

bool
Time::operator!=(const Time &t) const
{
	return !(*this == t);
}

bool
Time::operator< (const Time &t) const
{
	if (this->hour < t.hour)
		return true;
	else if (this->min < t.min)
		return true;

	return false;
}

bool
Time::operator> (const Time &t) const
{
	if (this->hour > t.hour)
		return true;
	else if (this->min > t.min)
		return true;

	return false;
}

bool
Time::operator<=(const Time &t) const
{
	return !(*this > t);
}

bool
Time::operator>=(const Time &t) const
{
	return !(*this < t);
}

ostream&
operator<<(ostream& outstream, const Time &t)
{
	outstream << setfill('0') <<
	    setw(2) << t.hour << ':' <<
	    setw(2) << t.min <<
	    setfill(' ');

	return outstream;
}

ofstream&
operator<<(std::ofstream& outstream, const Time &t)
{
	outstream << t.hour << ':' << t.min;

	return outstream;
}

ifstream&
operator>>(std::ifstream &instream, Time &t)
{
	try {
		string temp_str;
		getline(instream, temp_str);

		int div = temp_str.find(':');
		if (div == string::npos)
			throw FileReadingFailed("time: " + temp_str);

		else {
			t.hour = (short) stoi(temp_str.substr(0, div));
			t.min = (short) stoi(temp_str.substr(div + 1));
		}

	}catch(const std::exception& e) {
		instream.setstate(ios::failbit);
		t.hour = t.min = 0;

		cerr << e.what() << endl;
	}

	return instream;
}
