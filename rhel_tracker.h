#pragma once
#include <string>
#include "fedora_tracker.h"

using namespace std;

class Rhel_Tracker : public Fedora_Tracker {
	public:
	Rhel_Tracker(const string& name, const string& url, const string& filter):
		Fedora_Tracker(name, url, filter) { }
};