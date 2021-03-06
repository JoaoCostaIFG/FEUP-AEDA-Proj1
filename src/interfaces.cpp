#include <iomanip>

#include "../include/interfaces.h"
#include "../include/utilities.h"

using namespace std;

/*
 * ADMIN INTERFACE
 */
AdminInterface::AdminInterface(MuseumNetwork &rnm) : museum_network(rnm) {
	cout << "Login as the Admin!" << endl;
	utl::pauseConsole();
}

void
AdminInterface::show()
{
	/* Filter Cards by validity*/
	MenuSelectFilter<vector<Card*>> CardsValidity("By validity", flt::FilterCardByValidity);
	MenuSelectFilter<vector<Card*>> CardsInvalidity("By invalidity", flt::FilterCardByInvalidity);
	vector<MenuFilter<vector<Card*>>*> validityOpt = {&CardsValidity, &CardsInvalidity};


	/* Filter Cards */
	MenuSelectFilter<vector<Card*>> CardsName("By name", flt::FilterCardByName);
	MenuOptionsFilter<vector<Card*>> CardsValidityOptions("Filter by validity", validityOpt, [](vector<Card*>&){},
			[](){return(vector<Card*>());}, true);
	MenuSelectFilter<vector<Card*>> CardsSelect("List current selected cards",
			[this](vector<Card*>&vec) { this->museum_network.listCards(vec); });


	/* Filter Events between Dates*/
	MenuSelectFilter<vector<Event>> EventsBetweenDates("Between dates", flt::FilterBetweenDates<Event>);
	MenuSelectFilter<vector<Event>> EventsInADate("In a date", flt::FilterInDate<Event>);
	vector<MenuFilter<vector<Event>>*> dateOpt = {&EventsBetweenDates, &EventsInADate};

	/* Filter Events */
	MenuOptionsFilter<vector<Event>> EventsDate("Filter by dates", dateOpt,
			[](vector<Event>&){},
			[](){return(vector<Event>());}, true);
	MenuSelectFilter<vector<Event>> EventsLocation("Filter by location", flt::FilterByLocationCin<Event>);
	MenuSelectFilter<vector<Event>> EventsLocationName("Filter by location name", flt::FilterEventByLocationName);
	MenuSelectFilter<vector<Event>> EventsId("Select by id", flt::FilterEventById);
	MenuSelectFilter<vector<Event>> EventsTimeframe("Filter in a timeframe", flt::FilterEventByTimeFrame);
	MenuSelectFilter<vector<Event>> EventsName("Filter by name", flt::FilterByName<Event>);
	MenuSelectFilter<vector<Event>> EventsSelected("List current selected events",
			[this](vector<Event>&vec) { this->museum_network.listEvents(vec); });

	/* Filter Museums */
	MenuSelectFilter<vector<Museum>> MuseumsLocation("Filter by location", flt::FilterByLocationCin<Museum>);
	MenuSelectFilter<vector<Museum>> MuseumsName("Filter by name", flt::FilterByName<Museum>);
	MenuSelectFilter<vector<Museum>> MuseumsSelected("List current selected museums",
			[this](vector<Museum>&vec) { this->museum_network.listMuseums(vec); });


	/* Filter Enterprises */
	MenuSelectFilter<vector<Enterprise>> EnterpriseLocation("Filter by location", flt::FilterByLocationCin<Enterprise>);
	MenuSelectFilter<vector<Enterprise>> EnterpriseName("Filter by name", flt::FilterByName<Enterprise>);
	MenuSelectFilter<vector<Enterprise>> EnterpriseEvent("Filter by event ID", flt::FilterByEventID<Enterprise>);
	MenuSelectFilter<vector<Enterprise>> EnterpriseSelected("List current selected enterprises",
			[this](vector<Enterprise>&vec) { this->museum_network.listEnterprises(vec); });


	/* List Cards */
	vector<MenuFilter<vector<Card*>>*> listCardsOpt = {&CardsSelect, &CardsName, &CardsValidityOptions};
	MenuOptionsFilter<vector<Card*>> listCards("List Cards", listCardsOpt,
			[this](vector<Card*>&vec){ return vector<Card*>(); },
			[this](){ return(this->museum_network.getCards());}, // Initialize vector with all cards of the network
			false, {0});


	/* List Enterprises */
	vector<MenuFilter<vector<Enterprise>>*> listEnterprisesOpt = {&EnterpriseSelected, &EnterpriseLocation, &EnterpriseEvent, &EnterpriseName};
	MenuOptionsFilter<vector<Enterprise>> listEnterprises("List Enterprises", listEnterprisesOpt,
			[this](vector<Enterprise>&vec){ return vector<Enterprise>(); },
			[this](){ return(this->museum_network.getEnterprises());}, // Initialize vector with all enterprises of the network
			false, {0});


	/* List Events */
	vector<MenuFilter<vector<Event>>*> listEventsOpt=
		{&EventsSelected, &EventsLocation, &EventsLocationName, &EventsName, &EventsDate, &EventsTimeframe, &EventsId};
	MenuOptionsFilter<vector<Event>> listEvents("List Events", listEventsOpt,
			[this](vector<Event>){return;},
			[this](){ return(this->museum_network.getEvents());}, // Initialize vector with all events of the network
			false, {0});


	/* List Museums */
	vector<MenuFilter<vector<Museum>>*> listMuseumsOpt = {&MuseumsSelected, &MuseumsLocation, &MuseumsName};
	MenuOptionsFilter<vector<Museum>> listMuseums("List Museums", listMuseumsOpt,
			[this](vector<Museum>&vec){ return vector<Museum>(); },
			[this](){ return(this->museum_network.getMuseums());}, // Initialize vector with all museums of the network
			false, {0});


	/* List Network Options */
	MenuOptions list_network("List Network Options", std::vector<Menu*>{&listEvents, &listMuseums, &listEnterprises, &listCards});


	/* Remove Events */
	MenuSelectFilter<vector<Event>> removeEventsSelected("Remove selected events",
		[this](vector<Event> &vec){
			if(vec.size() == this->museum_network.getEvents().size()) // If user has all of them selected
				cout << "Warning! You will remove all of them!!\n";
			cout << "Are you sure? (y/n)\n"; int a = getchar(); utl::ignore(cin);
			if(!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
			if(a=='y' || a=='Y') {
				this->museum_network.removeEvents(vec);
				cout <<	"Event(s) removed!"; utl::pauseConsole();
				vec.erase(vec.begin(), vec.end());
			}
			else
				cout << "Operation aborted" << endl;
		});
	vector<MenuFilter<vector<Event>>*> removeEventsOpt = listEventsOpt;
	removeEventsOpt.push_back(&removeEventsSelected);
	MenuOptionsFilter<vector<Event>> removeEvents("Remove Events", removeEventsOpt,
			[this](vector<Event>&vec){ return; },
			[this](){ return(this->museum_network.getEvents());}, // Initialize vector with all events of the network
			false, {0});


	/* Remove Museums */
	MenuSelectFilter<vector<Museum>> removeMuseumsSelected("Remove selected museums",
		[this](vector<Museum> &vec){
			if(vec.size() == this->museum_network.getMuseums().size()) // If user has all of them selected
				cout << "Warning! You will remove all of them!!\n";
			cout << "Are you sure? (y/n)\n"; int a = getchar(); utl::ignore(cin);
			if(!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
			if(a=='y' || a=='Y') {
				this->museum_network.removeMuseums(vec);
				cout <<	"Museum(s) removed!"; utl::pauseConsole();
				vec.erase(vec.begin(), vec.end());
			}
			else
				cout << "Operation aborted" << endl;
		});
	vector<MenuFilter<vector<Museum>>*> removeMuseumsOpt = {&MuseumsSelected, &MuseumsLocation, &MuseumsName, &removeMuseumsSelected};
	MenuOptionsFilter<vector<Museum>> removeMuseums("Remove Museums", removeMuseumsOpt,
			[this](vector<Museum>&vec){ return; },
			[this](){ return(this->museum_network.getMuseums());},
			false, {0});


	/* Remove Enterprises */
	MenuSelectFilter<vector<Enterprise>> removeEnterprisesSelected("Remove selected enterprises",
		[this](vector<Enterprise> &vec){
			if(vec.size() == this->museum_network.getEnterprises().size()) // If user has all of them selected
				cout << "Warning! You will remove all of them!!\n";
			cout << "Are you sure? (y/n)\n"; int a = getchar(); utl::ignore(cin);
			if(!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
			if(a=='y' || a=='Y') {
				this->museum_network.removeEnterprises(vec);
				cout <<	"Enterprise(s) removed!"; utl::pauseConsole();
				vec.erase(vec.begin(), vec.end());
			}
			else
				cout << "Operation aborted" << endl;
		});
	vector<MenuFilter<vector<Enterprise>>*> removeEnterprisesOpt =
		{&EnterpriseSelected, &EnterpriseLocation, &EnterpriseEvent, &EnterpriseName, &removeEnterprisesSelected};
	MenuOptionsFilter<vector<Enterprise>> removeEnterprises("Remove Enterprises", removeEnterprisesOpt,
			[this](vector<Enterprise>&vec){ return; },
			[this](){ return(this->museum_network.getEnterprises());},
			false, {0});


	/* Remove Cards */
	MenuSelectFilter<vector<Card*>> removeCardsSelected("Remove all selected cards",
		[this](vector<Card*> &vec){
			if(vec.size() == this->museum_network.getCards().size()) // If user has all of them selected
				cout << "Warning! You will remove all of them!!\n";
			cout << "Are you sure? (y/n)\n"; int a = getchar(); utl::ignore(cin);
			if(!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
			if(a=='y' || a=='Y') {
				this->museum_network.removeCards(vec);
				cout <<	"Card(s) removed!"; utl::pauseConsole();
				vec.erase(vec.begin(), vec.end());
			}
			else
				cout << "Operation aborted" << endl;
		});
	vector<MenuFilter<vector<Card*>>*> removeCardsOpt =
		{&CardsSelect, &CardsName, &CardsValidity, &removeCardsSelected};
	MenuOptionsFilter<vector<Card*>> removeCards("Remove Cards", removeCardsOpt,
			[this](vector<Card*>&vec){ return; },
			[this](){ return(this->museum_network.getCards());},
			false, {0});


	/* Remove Network Options */
	MenuOptions remove_network("Network Remove Options", std::vector<Menu*>{&removeEvents, &removeMuseums, &removeEnterprises, &removeCards});


	/* Add User */
	MenuSelect addUser("Add a new account", [this](){
				Card *card;
				Card::cin_read_card(card);
				if(cin.fail()) {
					utl::stream_clear(cin);
					throw(UserInputReadingFailure("Invalid card formatting\n"));
				}
				cout << "This operation will have a cost of " << fixed << setprecision(2) << this->museum_network.getCost(card->get_type()) << endl;
				cout << "Are you sure? (y/n)\n"; int a = getchar(); utl::ignore(cin);
				if(!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
				if(a=='y' || a=='Y') {
					this->museum_network.addCard(card);
				}
				else
					cout << "Operation aborted" << endl;
			});


	/* Add Museum */
	MenuSelect addMuseum("Add a new museum", [this](){
				Museum museum;
				Museum::cin_read_museum(museum);
				if(cin.fail()) {
					utl::stream_clear(cin);
					throw(UserInputReadingFailure("Invalid museum formatting\n"));
				}
				cout << "Are you sure? (y/n)\n"; int a = getchar(); utl::ignore(cin);
				if(!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
				if(a=='y' || a=='Y') {
					this->museum_network.addMuseum(museum);
				}
				else
					cout << "Operation aborted" << endl;
			});


	/* Add Enterprise */
	MenuSelect addEnterpirse("Add a new enterprise", [this](){
				Enterprise enterprise;
				Enterprise::cin_read_enterprise(enterprise);
				if (cin.fail()) {
					utl::stream_clear(cin);
					throw(UserInputReadingFailure("Invalid enterprise formatting\n"));
				}

				cout << "Are you sure? (y/n)\n"; int a = getchar(); utl::ignore(cin);
				if (!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));

				if (a=='y' || a=='Y') {
					this->museum_network.addEnterprise(enterprise);
				}
				else
					cout << "Operation aborted" << endl;
			});


	/* Add Event */
	MenuSelectFilter<vector<Enterprise>> addEventToNetwork("Add an event to the selected enterprise",
			[this](vector<Enterprise>&vec) {
				if (vec.size() != 1)
					throw(UserInputReadingFailure("Multiple enterprises selected"));

				Event event;
				Event::cin_read_event(event);

				if (cin.fail()) {
					utl::stream_clear(cin);
					throw(UserInputReadingFailure("Invalid event formatting\n"));
				}

				this->museum_network.addEvent(vec.at(0), event);
			});
	vector<MenuFilter<vector<Enterprise>>*> listAddOpt = listEnterprisesOpt;
	listAddOpt.push_back(&addEventToNetwork);
	MenuOptionsFilter<vector<Enterprise>> addEvent("Add a new event", listAddOpt,
			[this](vector<Enterprise> &vec){ return;  },
			[this](){ return(this->museum_network.getEnterprises());},
			false, {0});


	/* Add Options */
	MenuOptions add_network("Add Network Options", std::vector<Menu*>{&addEnterpirse, &addEvent, &addMuseum, &addUser});



	/* Modify Museums*/

	MenuSelectFilter<vector<Museum>> modifyMuseumMenu("Modify the selected Museum",
			[this](vector<Museum>&vec){
				/* Opens menu that changes the current enterprise */
				if(vec.size() != 1)
					throw(UserInputReadingFailure("Multiple Museums selected"));
				Museum old_museum = vec.at(0); // Store selected museum as backup for later modifying

				MenuSelectFilter<Museum> modifyMuseumName("Modify Name",
						[](Museum &enter){
							cout << "Name?" << endl;
							string name; getline(cin, name);
							enter.set_name(name);
						});

				MenuSelectFilter<Museum> modifyMuseumClosingTime("Modify closing time",
						[](Museum &enter){
							cout << "Closing time? (hour:min)" << endl;
							Time close_time; cin >> close_time;
							if(cin.fail())
								throw(UserInputReadingFailure("Invalid closing time"));
							enter.set_close(close_time);
						});

				MenuSelectFilter<Museum> modifyMuseumOpeningTime("Modify opening time",
						[](Museum &enter){
							cout << "Opening time? (hour:min)" << endl;
							Time open_time; cin >> open_time;
							if(cin.fail())
								throw(UserInputReadingFailure("Invalid opening time"));
							enter.set_open(open_time);
						});

				MenuSelectFilter<Museum> modifyMuseumFee("Modify fee",
						[](Museum &enter){
							cout << "Fee?" << endl;
							float fee; cin >> fee;
							if(cin.fail())
								throw(UserInputReadingFailure("Invalid fee"));
							enter.set_fee(fee);
						});

				MenuSelectFilter<Museum> modifyMuseumCommit("Commit changes",
						[this, &old_museum](Museum &museum){
							this->museum_network.modifyMuseum(old_museum, museum);
						});

				MenuOptionsFilter<Museum> modifyMuseum("Modify the selected Enterprise",
						{&modifyMuseumName, &modifyMuseumOpeningTime, &modifyMuseumClosingTime, &modifyMuseumFee, &modifyMuseumCommit});

				modifyMuseum.show(vec.at(0)); // Initialize the menu with the selected enterprise
			});

	vector<MenuFilter<vector<Museum>>*> modifyMuseumOpt = listMuseumsOpt;
	modifyMuseumOpt.push_back(&modifyMuseumMenu);
	MenuOptionsFilter<vector<Museum>> modifyMuseumSelection("Modify Museums", modifyMuseumOpt,
			[](vector<Museum>&vec){},[this](){ return(this->museum_network.getMuseums());}, false, {0});


	/* Modify Enterprises */

	MenuSelectFilter<vector<Enterprise>> modifyEnterpriseMenu("Modify the selected Enterprise",
			[this](vector<Enterprise>&vec){
				/* Opens menu that changes the current enterprise */
				if(vec.size() != 1)
					throw(UserInputReadingFailure("Multiple Enterprises selected"));
				Enterprise old_enterprise = vec.at(0); // Store selected enterprise as backup for later modifying

				MenuSelectFilter<Enterprise> modifyEnterpriseName("Modify Name",
						[](Enterprise &enter){
							cout << "Name?\n";
							string name; getline(cin, name);
							enter.set_name(name);
						});

				MenuSelectFilter<Enterprise> modifyEnterpriseContact("Modify Contact",
						[](Enterprise &enter){
							cout << "Contact?\n";
							string contact; getline(cin, contact);
							enter.set_contact(contact);
						});

				MenuSelectFilter<Enterprise> modifyEnterpriseAddress("Modify Address",
						[](Enterprise &enter){
							cout << "Address (street name/XXXX-XXX/region name  or	region)?\n";
							Address address; cin >> address;
							if(cin.fail())
								throw(UserInputReadingFailure("Invalid Address"));
							enter.set_address(address);
						});

				MenuSelectFilter<Enterprise> modifyEnterpriseCommit("Commit changes",
						[this, &old_enterprise](Enterprise &enter){
							this->museum_network.modifyEnterprise(old_enterprise, enter);
						});

				MenuOptionsFilter<Enterprise> modifyEnterprise("Modify the selected Enterprise",
						{&modifyEnterpriseAddress, &modifyEnterpriseContact, &modifyEnterpriseName, &modifyEnterpriseCommit});

				modifyEnterprise.show(vec.at(0)); // Initialize the menu with the selected enterprise
			});

	vector<MenuFilter<vector<Enterprise>>*> modifyEnterpriseOpt = listEnterprisesOpt;
	modifyEnterpriseOpt.push_back(&modifyEnterpriseMenu);
	MenuOptionsFilter<vector<Enterprise>> modifyEnterpriseSelection("Modify Enterprises", modifyEnterpriseOpt,
			[](vector<Enterprise>&vec){},[this](){ return(this->museum_network.getEnterprises());}, false, {0});




	/* Modify Events */

	MenuSelectFilter<vector<Event>> modifyEventMenu("Modify the selected Event",
			[this](vector<Event>&vec){
				/* Opens menu that changes the current event */
				if(vec.size() != 1)
					throw(UserInputReadingFailure("Multiple Events selected"));
				Event old_event = vec.at(0); // Store selected event as backup for later modifying

				MenuSelectFilter<Event> modifyEventName("Modify Name",
						[](Event &event){
							cout << "Name?\n";
							string name; getline(cin, name);
							event.set_name(name);
						});

				MenuSelectFilter<Event> modifyEventContact("Modify Location Name",
						[](Event &event){
							cout << "Location Name?\n";
							string location_name; getline(cin, location_name);
							event.set_location_name(location_name);
						});

				MenuSelectFilter<Event> modifyEventAddress("Modify Address",
						[](Event &event){
							cout << "Address (street name/XXXX-XXX/region name  or	region)?\n";
							Address address; cin >> address;
							if(cin.fail())
								throw(UserInputReadingFailure("Invalid Address"));
							event.set_address(address);
						});

				MenuSelectFilter<Event> modifyEventTime("Modify starting time",
						[](Event &event){
							cout << "Starting time? (hour:min)" << endl;
							Time time; cin >> time;
							if(cin.fail())
								throw(UserInputReadingFailure("Invalid starting time"));
							event.set_time(time);
						});

				MenuSelectFilter<Event> modifyEventDate("Modify starting date",
						[](Event &event){
							cout << "Date (year/month/day)?" << endl;
							Date date; cin >> date;
							if(cin.fail())
								throw(UserInputReadingFailure("Invalid starting date"));
							event.set_date(date);
						});


				MenuSelectFilter<Event> modifyEventMaxCapacity("Modify maximux capacity",
						[](Event &event){
							cout << "Max capacity?" << endl;
							unsigned capacity; cin >> capacity;
							if(cin.fail())
								throw(UserInputReadingFailure("Invalid maximum capacity"));
							event.set_max_capacity(capacity);
						});

				MenuSelectFilter<Event> modifyEventFee("Modify fee",
						[](Event &event){
							cout << "Fee?" << endl;
							float fee; cin >> fee;
							if(cin.fail())
								throw(UserInputReadingFailure("Invalid fee"));
							event.set_ticket_fee(fee);
						});

				MenuSelectFilter<Event> setEventInvalidity("Make the event invalid",
						[](Event &event){
							cout << "Are you sure? (y/n)\n"; int a = getchar(); utl::ignore(cin);
							if(!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
							if(a == 'y' || a == 'Y')
								event.set_validity(false);
						});

				MenuSelectFilter<Event> setEventValidity("Make the event valid",
						[](Event &event){
							cout << "Are you sure? (y/n)\n"; int a = getchar(); utl::ignore(cin);
							if(!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
							if(a == 'y' || a == 'Y')
								event.set_validity(true);
						});

				MenuSelectFilter<Event> modifyEventCommit("Commit changes",
						[this, &old_event](Event &event){
							this->museum_network.modifyEvent(old_event, event);
						});


				vector<MenuFilter<Event>*> modifyCurrEventOptions =
					{&modifyEventFee, &modifyEventDate, &modifyEventTime, &modifyEventAddress, &modifyEventContact, &modifyEventName,
						&modifyEventMaxCapacity};

				if(old_event.get_validity()) // If event is valid add option to make it invalid
					modifyCurrEventOptions.push_back(&setEventInvalidity);
				else
					modifyCurrEventOptions.push_back(&setEventValidity); // Else add option to make it valid

				modifyCurrEventOptions.push_back(&modifyEventCommit);

				MenuOptionsFilter<Event> modifyEvent("Modify the selected Event", modifyCurrEventOptions,
						[](Event &ev){}, [](){return(Event());}, false, {0, 1, 2, 3, 4, 5, 6, 7, 8});

				modifyEvent.show(vec.at(0)); // Initialize the menu with the selected event
			});

	vector<MenuFilter<vector<Event>>*> modifyEventOpt = listEventsOpt;
	modifyEventOpt.push_back(&modifyEventMenu);
	MenuOptionsFilter<vector<Event>> modifyEventSelection("Modify Events", modifyEventOpt,
			[](vector<Event>&vec){},[this](){ return(this->museum_network.getEvents());}, false, {0});


	/* Modify Network Options */
	MenuOptions modify_network("Modify Network Options", {&modifyEnterpriseSelection, &modifyMuseumSelection, &modifyEventSelection});



	/* Main Menu */
	MenuOptions main_menu("Logged in as ADMIN",
			vector<Menu*>{&list_network, &remove_network, &add_network, &modify_network});


	main_menu.show();
}


/*
 * MEMBER INTERFACE
 */
MemberInterface::MemberInterface(MuseumNetwork &rnm, unsigned int cc) : museum_network(rnm) {
	vector<Card*> cards = rnm.getCards();
	vector<Card*>::iterator iter = find_if(cards.begin(), cards.end(), [&cc](Card *c1){ return(c1->get_cc() == cc); });
	if(iter == cards.end())
		throw(NoSuchObject(to_string(cc), "Card"));

	this->member_card = *(iter);
	//this->museum_network = rnm;
	cout << "Login Success!" << endl;
	utl::pauseConsole();
}

void MemberInterface::show() {
	utl::clearConsole();
	cout << "Logged in as cc with number " << this->member_card->get_cc() << " at " << Time() << endl;

	/* Send notify event prompt if intended */
	if(this->member_card->get_type() == SILVERCARD_TYPE) {
		vector<Event> events_filtered = this->museum_network.getEvents();
		flt::FilterByLocation<Event>(events_filtered, this->member_card->get_address()); // Select all events within a location
		flt::FilterEventByCapacity(events_filtered, 50); // Select all events with less than 50% capacity
		flt::FilterEventByGivenTimeFrame(events_filtered, 8, 0); // Select all events within 8 hours
		if(events_filtered.size() != 0) {
			cout << "Notification: In the next 8 hours " << events_filtered.size() <<
				" event(s) will take place in your area of residence, " << this->member_card->get_address().getRegion() << '.' << endl <<
				"All of them are, at most, 50\% full and the entry is free for you!" << endl;

			cout << "Do you want to list them? (y/n)\n"; int a = getchar(); utl::ignore(cin);
			if(!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
			if(a == 'y' || a == 'Y') {
				this->museum_network.listEvents(events_filtered);
				utl::pauseConsole();
			}
		}
	}


	/* Filter Events between Dates*/
	MenuSelectFilter<vector<Event>> EventsBetweenDates("Between dates", flt::FilterBetweenDates<Event>);
	MenuSelectFilter<vector<Event>> EventsInADate("In a date", flt::FilterInDate<Event>);
	vector<MenuFilter<vector<Event>>*> dateOpt = {&EventsBetweenDates, &EventsInADate};

	/* Filter Events */
	MenuOptionsFilter<vector<Event>> EventsDate("Filter by dates", dateOpt);
	MenuSelectFilter<vector<Event>> EventsLocation("Filter by location", flt::FilterByLocationCin<Event>);
	MenuSelectFilter<vector<Event>> EventsLocationName("Filter by location name", flt::FilterEventByLocationName);
	MenuSelectFilter<vector<Event>> EventsName("Filter by name", flt::FilterByName<Event>);
	MenuSelectFilter<vector<Event>> EventsTimeframe("Filter in a timeframe", flt::FilterEventByTimeFrame);
	MenuSelectFilter<vector<Event>> EventsId("Select by id", flt::FilterEventById);
	MenuSelectFilter<vector<Event>> EventsSelected("List current selected events",
			[this](vector<Event>&vec) { this->museum_network.listEvents(vec, this->member_card->get_type()); });

	/* Filter Museums */
	MenuSelectFilter<vector<Museum>> MuseumsLocation("Filter by location", flt::FilterByLocationCin<Museum>);
	MenuSelectFilter<vector<Museum>> MuseumsName("Filter by name", flt::FilterByName<Museum>);
	MenuSelectFilter<vector<Museum>> MuseumsSelected("List current selected events",
			[this](vector<Museum>&vec) { this->museum_network.listMuseums(vec); });



	/* List Events */
	vector<MenuFilter<vector<Event>>*> listEventsOpt =
		{&EventsSelected, &EventsLocation, &EventsLocationName, &EventsName, &EventsDate, &EventsTimeframe, &EventsId};
	MenuOptionsFilter<vector<Event>> listEvents("List Events", listEventsOpt,
			[this](vector<Event>){return;},
			[this](){ return(this->museum_network.getEvents());},
			false, {0});

	/* List Museums */
	vector<MenuFilter<vector<Museum>>*> listMuseumsOpt = {&MuseumsSelected, &MuseumsLocation, &MuseumsName};
	MenuOptionsFilter<vector<Museum>> listMuseums("List Museums", listMuseumsOpt,
			[this](vector<Museum>&vec){ return vector<Museum>(); },
			[this](){ return(this->museum_network.getMuseums());},
			false, {0});

	/* List Member and Network */
	MenuSelect listUser("List your information", [this](){ this->museum_network.listCards(vector<Card*> { this->member_card }); });
	MenuOptions list_network("Network List Options", std::vector<Menu*>{&listEvents, &listMuseums});



	/* Renew Membership */
	MenuSelect renewCard ("Renew your membership", [this](){
				cout << "Renewing your membership has a cost of " << fixed << setprecision(2) << this->museum_network.getCost(this->member_card->get_type()) << endl;
				cout << "Are you sure? (y/n)\n"; int a = getchar(); utl::ignore(cin);
				if(!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
				if(a=='y' || a=='Y') {
					this->member_card->renew();
					cout <<	"Membership renewed\n";
					}
				else
					cout << "Operation aborted" << endl;
			});



	/* Purchase Event */
	MenuSelectFilter<vector<Event>> purchaseEvent("Purchase selected event",
			[this](vector<Event>&vec) {
				if (!this->member_card->isvalid())
					throw(CardExpired(this->member_card->get_cc()));
				if (vec.size() != 1)
					throw(UserInputReadingFailure("Multiple Events selected"));

				bool is_event_free = false;
				if (this->member_card->get_type() == SILVERCARD_TYPE) {
					vector<Event> silver_event = vec;
					flt::FilterEventByCapacity(silver_event, 50);  // max capacity 50%
					flt::FilterByLocation(silver_event,  this->member_card->get_address());
					flt::FilterEventByGivenTimeFrame(silver_event, 8, 0);  // events happening in the next 8 hours;

					if (!silver_event.empty()) {
						is_event_free = true;
						cout << "This event is free for you!" << endl;
					}
				}

				if (!is_event_free){
					cout << "This action will have a price of " << fixed << setprecision(2) <<
						vec.at(0).get_fee() * (1 - this->museum_network.getDiscount(member_card->get_type())) << endl;
				}

				cout << "Are you sure? (y/n)" << endl;
				int a = getchar(); utl::ignore(cin);

				if(!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
				if(a=='y' || a=='Y') {
					this->museum_network.purchaseEvent(this->member_card->get_cc(), vec.at(0));
					vec = this->museum_network.getEvents();  // Reset all events after purchase
					cout <<	"Event purchased successfully" << endl;
				}
				else
					cout << "Operation aborted" << endl;

			});
	vector<MenuFilter<vector<Event>>*> purchaseEventOpt =
		{&purchaseEvent, &EventsSelected, &EventsLocation, &EventsLocationName, &EventsName, &EventsDate, &EventsId};
	MenuOptionsFilter<vector<Event>> purchaseEventMenu("Purchase Event", purchaseEventOpt,
			[this](vector<Event>&vec){},
			[this](){ return(this->museum_network.getEvents()); }, false, {1});



	/* Change current Member */
	MenuSelect changeContact("Change your contact",
			[this](){
				cout << "Contact?" << endl;
				string contact;
				getline(cin, contact);
				this->member_card->set_contact(contact);
			});
	MenuSelect changeName("Change your name",
			[this](){
				cout << "Name?" << endl;
				string name;
				getline(cin, name);
				this->member_card->set_name(name);
			});
	MenuSelect changeBirthDate("Change your birth date",
			[this](){
					Date date;
					cout << "Date (year/month/day)?" << endl;
					cin >> date;
					if(cin.fail()) {
						utl::stream_clear(cin);
						throw(UserInputReadingFailure("Invalid Date"));
					}
					this->member_card->set_birth_date(date);
			});
	MenuSelect changeAddress("Change your address",
			[this](){
				Address addr;
				cout << "Address (street name/XXXX-XXX/region name  or	region)?" << endl;
				cin >> addr;
				if(cin.fail()) {
					utl::stream_clear(cin);
					throw(UserInputReadingFailure("Invalid Address"));
				}
				this->member_card->set_address(addr);
			});
	MenuOptions changeMember("Change your information",
			vector<Menu*>{&changeContact, &changeName, &changeBirthDate, &changeAddress});



	/* Account deletion */
	MenuSelect removeMember("Delete your account", [this](){
				cout << "Are you sure? (y/n)" << endl; int a = getchar(); utl::ignore(cin);
				if(!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
				if(a=='y' || a=='Y') {
					this->museum_network.removeCard(this->member_card);
					throw(MenuForceExit("Member menu"));
				}
				else
					cout << "Operation aborted" << endl;
			;});


	/* Main Menu */
	MenuOptions main_menu("Logged in as " + to_string(this->member_card->get_cc()),
			vector<Menu*>{&list_network, &renewCard, &listUser, &purchaseEventMenu, &changeMember, &removeMember});

	main_menu.show();
}


/*
 * USER INTERFACE
 */
UserInterface::UserInterface(MuseumNetwork &rnm) : museum_network(rnm) {
	return;
}

void UserInterface::show(){
	/* Filter Events between Dates */
	MenuSelectFilter<vector<Event>> EventsBetweenDates("Between dates", flt::FilterBetweenDates<Event>);
	MenuSelectFilter<vector<Event>> EventsInADate("In a date", flt::FilterInDate<Event>);
	vector<MenuFilter<vector<Event>>*> dateOpt = {&EventsBetweenDates, &EventsInADate};

	/* Filter Events */
	MenuOptionsFilter<vector<Event>> EventsDate("Filter by dates", dateOpt);
	MenuSelectFilter<vector<Event>> EventsLocation("Filter by location", flt::FilterByLocationCin<Event>);
	MenuSelectFilter<vector<Event>> EventsLocationName("Filter by location name", flt::FilterEventByLocationName);
	MenuSelectFilter<vector<Event>> EventsName("Filter by name", flt::FilterByName<Event>);
	MenuSelectFilter<vector<Event>> EventsId("Select by id", flt::FilterEventById);
	MenuSelectFilter<vector<Event>> EventsTimeframe("Filter in a timeframe", flt::FilterEventByTimeFrame);
	MenuSelectFilter<vector<Event>> EventsSelected("List current selected events",
			[this](vector<Event>&vec) { this->museum_network.listEvents(vec); });

	/* Filter Museums */
	MenuSelectFilter<vector<Museum>> MuseumsLocation("Filter by location", flt::FilterByLocationCin<Museum>);
	MenuSelectFilter<vector<Museum>> MuseumsName("Filter by name", flt::FilterByName<Museum>);
	MenuSelectFilter<vector<Museum>> MuseumsSelected("List current selected events",
			[this](vector<Museum>&vec) { this->museum_network.listMuseums(vec); });


	/* List Events */
	vector<MenuFilter<vector<Event>>*> listEventsOpt =
		{&EventsSelected, &EventsLocation, &EventsLocationName, &EventsName, &EventsDate, &EventsId, &EventsTimeframe};
	MenuOptionsFilter<vector<Event>> listEvents("List Events", listEventsOpt,
			[this](vector<Event>){return;},
			[this](){ return(this->museum_network.getEvents());},
			false, {0});

	/* List Museums */
	vector<MenuFilter<vector<Museum>>*> listMuseumsOpt = {&MuseumsSelected, &MuseumsLocation, &MuseumsName};
	MenuOptionsFilter<vector<Museum>> listMuseums("List Museums", listMuseumsOpt,
			[this](vector<Museum>&vec){ return vector<Museum>(); },
			[this](){ return(this->museum_network.getMuseums());},
			false, {0});


	/* List Network */
	MenuOptions list_network("List Network Options", std::vector<Menu*>{&listEvents, &listMuseums});

	/* Register */
	MenuSelect registerUser("Purchase a new account\n", [this](){
				Card *card;
				Card::cin_read_card(card);
				if(cin.fail()) {
					utl::stream_clear(cin);
					throw(UserInputReadingFailure("Invalid card formatting\n"));
				}
				cout << "This operation will have a cost of " << fixed << setprecision(2) << this->museum_network.getCost(card->get_type()) << endl;
				cout << "Are you sure? (y/n)" << endl; int a = getchar(); utl::ignore(cin);
				if(!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
				if(a=='y' || a=='Y') {
					this->museum_network.addCard(card);
					throw(MenuForceExit("Please login with your new account"));
				}
				else
					cout << "Operation aborted" << endl;
			});

	MenuOptions main_menu("Logged in as an NON-REGISTERED user",
			vector<Menu*>{&list_network, &registerUser});

	main_menu.show();
}


/*
 * GUI
 */
void GUI::show() {
	utl::clearConsole();
	MenuSelect adminMenu("Admin menu", [this](){ AdminInterface admin_interface(museum_network); admin_interface.show(); });

	MenuSelect userMenu("Non-registered User menu", [this](){ UserInterface user_interface(museum_network); user_interface.show(); });;

	MenuSelect memberMenu("Member menu", [this](){
			unsigned cc;
			cout << "Please type your CC" << endl; cin >> cc; utl::ignore(cin);
			MemberInterface member_interface(museum_network, cc);
			member_interface.show();
		});;

	MenuSelect importMenu("Import from a file", [this](){
			cout << "Insert the config file name (path relative to executable directory)" << endl;
			string config_file;
			cin >> config_file; utl::ignore(cin);
			this->museum_network.importFiles(config_file);
			cout << "File read successfully!" << endl;
		});

	MenuSelect exportMenu("Export to a file", [this](){
			string config_file, cards_file, museum_file, enterprise_file;
			cout << "Insert the config file name (path relative to executable directory)" << endl; cin >> config_file;
			cout << "Insert the cards file name (path relative to executable directory)" << endl; cin >> cards_file;
			cout << "Insert the museum file name (path relative to executable directory)" << endl; cin >> museum_file;
			cout << "Insert the enterprise file name (path relative to executable directory)" << endl; cin >> enterprise_file; utl::ignore(cin);
			this->museum_network.exportFiles(config_file, cards_file, museum_file, enterprise_file);
			cout << "Files were exported with success" << endl;});

	MenuOptions main_menu("Welcome to RNM\n", vector<Menu*> {&adminMenu, &memberMenu, &userMenu, &importMenu, &exportMenu});
	main_menu.show();
}
