#include "../include/museum_network.h"

using namespace std;


/* Cards */

void MuseumNetwork::addCard(Card* card) {
	int i;
	for (i = 0; i < this->cards.size(); ++i) {
		if(*card == *(this->cards.at(i)))
			throw(CardAlreadyExists(card->get_cc()));
	}
	this->cards.push_back(card);
}


void MuseumNetwork::removeCard(const Card *card) {
	vector<Card*>::iterator iter;
	iter = (find_if(this->cards.begin(), this->cards.end(),
			[&card](Card *lhs){return( *lhs == *card ); }));

	if(iter != this->cards.end()) // If the card is found
		cards.erase(iter);
	else
		throw(NoSuchCard(card->get_cc()));
}


void MuseumNetwork::removeCards(const std::vector<Card*> &cards_to_be_removed) {
	/* Given a vector of pointers to cards, remove all of the cards in the network are
	present in the given vector. */

	int i;
	for (i = 0; i < cards_to_be_removed.size(); ++i) {
		removeCard(cards_to_be_removed.at(i));
	}
}


void MuseumNetwork::modifyCard(Card* card_to_be_modified_to) {
	/* Modifies the card in the cards vector which has the same cc as the card_to_be_modified_to.
	   The data-members of the element of the vector will then be set to card_to_be_modified_to.
	*/
	vector<Card*>::iterator iter;
	iter = (find_if(this->cards.begin(), this->cards.end(),
			[&card_to_be_modified_to](Card *lhs){ return( *lhs == *card_to_be_modified_to ); }));

	if(iter != this->cards.end())
		(*iter) = card_to_be_modified_to;
	else
		throw(NoSuchCard(card_to_be_modified_to->get_cc()));
}


void MuseumNetwork::listCards(const std::vector<Card*> &cards_to_be_listed, const string &delim) const {
	int i;
	for (i = 0; i < cards_to_be_listed.size(); ++i) {
		cout << *(cards_to_be_listed.at(i));
		cout << delim;
	}
}

void MuseumNetwork::listCards(const std::string &delim) const {
	listCards(this->getCards(), delim);
}


/* Enterprises */

void MuseumNetwork::listEnterprises(const std::vector<Enterprise> &enterprises_to_be_listed, const string &delim) const {
	int i;
	for (i = 0; i < enterprises_to_be_listed.size(); ++i) {
		cout << enterprises_to_be_listed.at(i);
		cout << delim;
	}
}

void MuseumNetwork::listEnterprises(const string &delim) const {
	this->listEnterprises(this->getEnterprises(), delim);
}


void MuseumNetwork::addEnterprise(Enterprise enterprise) {
	int i;
	for (i = 0; i < this->enterprises.size(); ++i) {
		if(enterprise.get_name() == this->enterprises.at(i).get_name()) //TODO do with == operator
			throw(EnterpriseAlreadyExists(enterprise.get_name()));
	}
	this->enterprises.push_back(enterprise);
}



/* Museums */

void MuseumNetwork::listMuseums(const std::vector<Museum> &museums_to_be_listed, const string &delim) const {
	int i;
	for (i = 0; i < museums_to_be_listed.size(); ++i) {
		cout << museums_to_be_listed.at(i);
		cout << delim;
	}
}

void MuseumNetwork::listMuseums(const string &delim) const {
	this->listMuseums(this->getMuseums(), delim);
}


void MuseumNetwork::addMuseum(Museum museum) {
	int i;
	for (i = 0; i < this->museums.size(); ++i) {
		if(museum.get_name() == this->museums.at(i).get_name()) //TODO do with == operator
			throw(MuseumAlreadyExists(museum.get_name()));
	}
	this->museums.push_back(museum);
}

/* Eventos */

void MuseumNetwork::listEvents(const std::vector<Event> &events_to_be_listed, const string &delim) const {
	int i;
	for (i = 0; i < events_to_be_listed.size(); ++i) {
		cout << events_to_be_listed.at(i);
		cout << delim;
	}
}

void MuseumNetwork::listEvents(const string &delim) const{
	this->listEvents(getEvents());
}

vector<Event> MuseumNetwork::getEvents() const {
	int i, number_events(0);
	/* get size of the vector so that it doesn't have to realocate memory */
	for (i = 0; i < enterprises.size(); ++i) {
		number_events += 1;//enterprises.at(i).get_events().size();
	}

	vector<Event> events;
	for (auto &ent: this->enterprises) // Iterate through enterpises
		for (auto &x: ent.get_events()) { // Iterate through set of events
			 events.push_back(x);
		}

	return events;
}



/* File Methods */



void MuseumNetwork::importCards(std::string cards_file_name) {
	ifstream input_stream(cards_file_name);
	int card_cnt;
	vector<Card*> vec_cards;

	input_stream >> card_cnt; utl::ignore(input_stream);
	for (int i=0; i<card_cnt; ++i) {
		Card *card;
		input_stream >> card;
		if(input_stream.fail())
			throw(FileIncorrectFormatting(cards_file_name));
		vec_cards.push_back(card);
	}

	this->cards = vec_cards;
}


void MuseumNetwork::importMuseums(std::string museum_file_name) {
	ifstream input_stream(museum_file_name);
	int museum_cnt;
	vector<Museum> vec_museums;

	input_stream >> museum_cnt; utl::ignore(input_stream);
	for (int i=0; i<museum_cnt; ++i) {
		Museum museum;
		input_stream >> museum;
		if(input_stream.fail())
			throw(FileIncorrectFormatting(museum_file_name));
		vec_museums.push_back(museum);
	}

	this->museums = vec_museums;
}

void MuseumNetwork::importEnterprises(std::string enterprise_file_name) {
	ifstream input_stream(enterprise_file_name);
	int enterprise_cnt;
	vector<Enterprise> vec_enterprises;

	input_stream >> enterprise_cnt; utl::ignore(input_stream);
	for (int i=0; i<enterprise_cnt; ++i) {
		Enterprise enterprise;
		input_stream >> enterprise;
		if(input_stream.fail())
			throw(FileIncorrectFormatting(enterprise_file_name));
		vec_enterprises.push_back(enterprise);
	}

	this->enterprises = vec_enterprises;
}


void MuseumNetwork::exportCards(std::string cards_file_name) const {
	ofstream output_stream(cards_file_name);

	unsigned int card_cnt = this->cards.size();
	output_stream << "" << card_cnt << endl;
	for (int i = 0; i < card_cnt; ++i)
		output_stream << *(cards.at(i)) << endl;
}


void MuseumNetwork::exportMuseums(std::string museum_file_name) const {
	ofstream output_stream(museum_file_name);

	unsigned int museums_cnt = this->museums.size();
	output_stream << "" << museums_cnt << endl;
	for (int i = 0; i < museums_cnt; ++i)
		output_stream << museums.at(i) << endl;
}


void MuseumNetwork::exportEnterprises(std::string enterprises_file_name) const {
	ofstream output_stream(enterprises_file_name);

	unsigned int enterprises_cnt = this->enterprises.size();
	output_stream << "" << enterprises_cnt << endl;

	for (int i = 0; i < enterprises_cnt; ++i)
		output_stream << enterprises.at(i) << endl;
}


void MuseumNetwork::exportFiles(std::string cards_file_name, std::string museum_file_name,
		std::string enterprise_file_name, std::string config_file_name) const {

	ofstream output_stream(config_file_name);
	output_stream << "cards_file_name: " << cards_file_name << endl;
	output_stream << "museum_file_name: " << museum_file_name << endl;
	output_stream << "enterprise_file_name: " << enterprise_file_name << endl;
	output_stream << "individual::cost: " << this->individual_cost << endl;
	output_stream << "individual::discount: " << individual_discount << endl;
	output_stream << "silver::cost: " << silver_cost << endl;
	output_stream << "silver::discount: " << silver_discount << endl;
	output_stream << "uni::cost: " << uni_cost << endl;
	output_stream << "uni::discount: " << uni_discount << endl;

	this->exportCards(cards_file_name);
	this->exportMuseums(museum_file_name);
	this->exportEnterprises(enterprise_file_name);
}

void MuseumNetwork::importFiles(std::string network_file_name) {
	ifstream input_stream(network_file_name);
	string museum_file_name, enterprise_file_name, cards_file_name;
	string temp_str;

	input_stream >> temp_str;
	input_stream >> cards_file_name; utl::ignore(input_stream);

	input_stream >> temp_str;
	input_stream >> museum_file_name; utl::ignore(input_stream);
	if(input_stream.fail()) throw(FileIncorrectFormatting(network_file_name));

	input_stream >> temp_str;
	input_stream >> enterprise_file_name; utl::ignore(input_stream);
	if(input_stream.fail()) throw(FileIncorrectFormatting(network_file_name));

	input_stream >> temp_str;
	input_stream >> this->individual_cost; utl::ignore(input_stream);
	if(input_stream.fail()) throw(FileIncorrectFormatting(network_file_name));
	input_stream >> temp_str;
	input_stream >> this->individual_discount; utl::ignore(input_stream);
	if(input_stream.fail()) throw(FileIncorrectFormatting(network_file_name));

	input_stream >> temp_str;
	input_stream >> this->silver_cost; utl::ignore(input_stream);
	if(input_stream.fail()) throw(FileIncorrectFormatting(network_file_name));
	input_stream >> temp_str;
	input_stream >> this->silver_discount; utl::ignore(input_stream);
	if(input_stream.fail()) throw(FileIncorrectFormatting(network_file_name));

	input_stream >> temp_str;
	input_stream >> this->uni_cost; utl::ignore(input_stream);
	if(input_stream.fail()) throw(FileIncorrectFormatting(network_file_name));
	input_stream >> temp_str;
	input_stream >> this->uni_discount; utl::ignore(input_stream);
	if(input_stream.fail()) throw(FileIncorrectFormatting(network_file_name));

	if(!utl::file_exists(network_file_name))
		throw(FileNotFound(network_file_name));
	if(!utl::file_exists(museum_file_name))
		throw(FileNotFound(museum_file_name));
	if(!utl::file_exists(enterprise_file_name))
		throw(FileNotFound(enterprise_file_name));
	if(!utl::file_exists(cards_file_name))
		throw(FileNotFound(cards_file_name));

	this->importCards(cards_file_name);
	this->importMuseums(museum_file_name);
	this->importEnterprises(enterprise_file_name);
}
