#include <string>
#include <cstring>
#include <memory>
#include <iostream>
#include "tracker.h"
#include "string_splitor.h"
#include "fedora_tracker.h"

using namespace std;

string Fedora_Tracker::query() {
	return do_query(url);
}

string Fedora_Tracker::do_query(string url) {
	char buffer[512];
	string res;
	string cmd = "bash -c 'rpmspec -P <(curl -s " + url + ") 2>/dev/null | egrep \"^(Version|Release)\"'";
	unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);

	if (!pipe) {
		throw std::runtime_error("popen curl process failed!");
	}
	memset(buffer, 0, sizeof(buffer));
	while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
		if (!strncmp(buffer, "Version", 7)) {
			res = split(buffer, delimits)[1];
		} else if (!strncmp(buffer, "Release", 7)) {
			res += "-" + split(buffer, delimits)[1];
		}
	}
	return res;		
}