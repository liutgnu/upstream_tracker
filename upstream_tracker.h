#pragma once
#include <string>
#include "tracker.h"

using namespace std;

class Upstream_Tracker: public Tracker {
	public:
	Upstream_Tracker(const string& name, const string& url, const string& filter):
		Tracker(name, url, filter) { }
	void query();
	void display();

	private:
	string do_query(string url);
};