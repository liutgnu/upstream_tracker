#include "upstream_tracker.h"
#include <string>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <memory>
#include "string_splitor.h"

string Upstream_Tracker::query() {
	if (filter != "")
		return do_query(url + "| egrep -v '" + filter + "'");
	else
		return do_query(url);
}

string Upstream_Tracker::do_query(string url) {
	char buffer[512];

	string cmd = "git ls-remote --sort='version:refname' --tags " + url;
	unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);

	if (!pipe) {
		throw std::runtime_error("popen git process failed!");
	}
	memset(buffer, 0, sizeof(buffer));
	while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {}

	vector<string> res = split(buffer, delimits);

	return res[1];
}