#include "../include/cards.h"

float IndividualCard::cost = 54.90;
float IndividualCard::discount = 0.25;
float UniCard::cost = 32.45;
float UniCard::discount = 0.25;
float SilverCard::cost = 30.00;
float SilverCard::discount = 0.25;

Card::Card(const string &name, const string &contact, unsigned int cc, const Date &birth_date, const Address &address)
	:creation_date(), expiration_date()
{
	this->name = name;
	this->contact = contact;
	this->cc = cc;
	this->birth_date = birth_date;

	this->expiration_date.ffyear();  // expiration date is 1 year from creation date
}

bool
Card::isvalid() const
{
	/* compare expiration date with current date */
	return this->expiration_date <= Date();
}

void
Card::renew()
{
	/* check is card is already expired */
	if (this->isvalid()){
		// TODO TODO diff dates be less than 2 months thx
		this->expiration_date.ffyear();
	}
	else {
		this->expiration_date = Date();  // compare with current date

		this->expiration_date.ffyear();  // move expiration date to 1 year from now
	}
}

unsigned int
Card::get_cc() const
{
	return this->cc;
}

string
Card::get_contact() const
{
	return this->contact;
}

string
Card::get_name() const
{
	return this->name;
}

Date
Card::get_creation_date() const
{
	return this->creation_date;
}

Date
Card::get_birth_date() const
{
	return this->birth_date;
}

Date
Card::get_expiration_date() const
{
	return this->expiration_date;
}

Address
Card::get_address() const
{
	return this->address;
}
