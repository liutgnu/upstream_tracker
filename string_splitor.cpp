#include <vector>
#include <string>

using namespace std;

auto is_delimit = [](char c, const vector<char>& delimits) -> bool {
	for (auto it = delimits.begin(); it != delimits.end(); ++it) {
		if (c == *it)
			return true;
	}
	return false;
};

vector<string> split(const string& input, const vector<char>& delimits)
{
	vector<string> res;
	string item;
	for (auto it = input.begin(); it != input.end(); ++it) {
		if (is_delimit(*it, delimits)) {
			if (item.empty()) {
				continue;
			} else {
				res.push_back(item);
				item.clear();
			}
		} else {
			item.push_back(*it);
		}
		
	}
	if (!item.empty())
		res.push_back(item);
	return res;
}
