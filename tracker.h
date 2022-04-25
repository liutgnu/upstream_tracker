#pragma once
#include <string>
#include <vector>

using namespace std;

class Tracker {
	public:
	string name;
	string url;
	string filter;
	vector<char> delimits;
	string version;

	public:
	Tracker(const string& name, const string& url, const string filter): 
		name(name), url(url), filter(filter) {
		delimits.push_back(' ');
		delimits.push_back('\t');
		delimits.push_back('\n');
		delimits.push_back('%');
	}

	~Tracker() { }

	Tracker *init();

	virtual void query() { return; };
	virtual void display() { return; };
};