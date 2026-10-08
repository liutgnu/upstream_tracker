#include <string>
#include <cstring>
#include <memory>
#include <iostream>
#include "tracker.h"
#include "string_splitor.h"
#include "fedora_tracker.h"

using namespace std;

void Fedora_Tracker::query() {
	if (url != "")
		version = do_query(url);
	else
		version = "";
}

void Fedora_Tracker::display() {
	printf("%#26s", version.c_str());
}

string Fedora_Tracker::do_query(string url) {
	char buffer[512];
	string res;

	string cmd =
	"bash -c '"
	"tmp=$(mktemp) || exit 1; "
	"trap \"rm -f \\\"$tmp\\\"\" EXIT; "
	"curl -sk \"" + url + "\" -o \"$tmp\" && "
	"sed -E -i \"s/^([[:space:]]*)%patch([0-9]+)([[:space:]]|$)/\\\\1%patch -P \\\\2\\\\3/\" \"$tmp\" && "
	"rpmspec -P \"$tmp\" 2>/dev/null | "
	"grep -E \"^(Version|Release)\" | "
	"sed \"s/$(rpm --eval %{?dist})//g\""
	"'";

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