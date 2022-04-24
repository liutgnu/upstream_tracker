#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "upstream_tracker.h"
#include "fedora_tracker.h"

using namespace std;

Tracker *Tracker::init() {
	if (name.find("upstream") != string::npos) {
		Upstream_Tracker *utp = new Upstream_Tracker(name, url ,filter);
		return utp;
	} else if (name.find("fedora") != string::npos) {
		Fedora_Tracker *ftp = new Fedora_Tracker(name, url ,filter);
		return ftp;
	} else {
		throw std::runtime_error("Invalid project: " + name);
	}
}