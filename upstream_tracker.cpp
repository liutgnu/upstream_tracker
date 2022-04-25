#include "upstream_tracker.h"
#include <string>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <memory>
#include "string_splitor.h"

void Upstream_Tracker::query() {
	if (filter != "")
		version = do_query(url + "| egrep -v '" + filter + "'");
	else
		version = do_query(url);
}

void Upstream_Tracker::display() {
	printf("\n%#25s:%#25s", split(name, delimits)[0].c_str(), version.c_str());
}

string Upstream_Tracker::do_query(string url) {
	char buffer[512];

	string cmd = "git ls-remote --sort='version:refname' --tags " + url + "| sed 's/refs\\/tags\\///g'";
	unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);

	if (!pipe) {
		throw std::runtime_error("popen git process failed!");
	}
	memset(buffer, 0, sizeof(buffer));
	while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {}

	vector<string> res = split(buffer, delimits);

	return res[1];
}