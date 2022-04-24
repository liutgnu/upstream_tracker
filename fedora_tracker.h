#pragma once
#include <string>
#include "tracker.h"

using namespace std;

class Fedora_Tracker : public Tracker {
	public:
	Fedora_Tracker(const string& name, const string& url, const string& filter):
		Tracker(name, url, filter) { }

	string query();

	private:
	string do_query(string url);
};