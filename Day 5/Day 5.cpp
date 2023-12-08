#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <functional>
std::ifstream fin("input.txt");

void match(std::string s, std::regex r, std::function<void(std::string)> f) {
	std::sregex_iterator begin = std::sregex_iterator(s.begin(), s.end(), r);
	std::sregex_iterator end = std::sregex_iterator();

	for (std::sregex_iterator i = begin; i != end; i++) {
		f((*i).str());
	}
}

bool trymap(int64_t&num, int64_t dest, int64_t source, int64_t length) {
	int64_t sourceend = source + length - 1;
	if (num < source || num > sourceend) {
		return false;
	}

	num = num - source + dest;
	return true;
}

struct plant {
	int64_t num = 0;
	bool mappped = false;
};

void part1()
{
	std::vector<plant> plants;
	std::string line;

	std::getline(fin, line);

	match(line, std::regex("\\b(\\d+)\\b"), [&](std::string s) {
		plants.push_back({ std::stoll(s), false });
		});

	int64_t inputs[3] = { 0 };
	while (std::getline(fin, line)) {
		if (line.empty()) {
			for (plant &p : plants) {
				p.mappped = false;
			}
			continue;
		}

		int k = 0;
		match(line, std::regex("\\b(\\d+)\\b"), [&](std::string s) {
			inputs[k++] = std::stoll(s);
			});

		if (k == 0) { continue; }

		for (plant &p : plants) {
			if (!p.mappped && trymap(p.num, inputs[0], inputs[1], inputs[2])) {
				p.mappped = true;
			}
		}
	}

	int64_t lowest = LLONG_MAX;
	for (int i = 0; i < plants.size(); i++) {
		lowest = std::min(lowest, plants[i].num);
	}

	std::cout << "Part 1: " << lowest << "\n";
}

struct range {
	long long start;
	long long length;
};

void part2() {
	std::vector<plant> plants;
	std::string line;

	std::getline(fin, line);

	int last = -1;
	bool state = 0;
	match(line, std::regex("\\b(\\d+)\\b"), [&](std::string s) {
		state = !state;
		if (state) {
			last = std::stoll(s);
		}
		else {
			for (int64_t i = 0; i < std::stoll(s); i++) {
				plants.push_back({ last + i, false });
			}
		}
		});

	int64_t inputs[3] = { 0 };
	while (std::getline(fin, line)) {
		if (line.empty()) {
			for (plant& p : plants) {
				p.mappped = false;
			}
			continue;
		}

		int k = 0;
		match(line, std::regex("\\b(\\d+)\\b"), [&](std::string s) {
			inputs[k++] = std::stoll(s);
			});

		if (k == 0) { continue; }

		for (plant& p : plants) {
			if (!p.mappped && trymap(p.num, inputs[0], inputs[1], inputs[2])) {
				p.mappped = true;
			}
		}
	}

	int64_t lowest = LLONG_MAX;
	for (int i = 0; i < plants.size(); i++) {
		lowest = std::min(lowest, plants[i].num);
	}

	std::cout << "Part 2: " << lowest << "\n";
}

int main() {
	part1();

	fin = std::ifstream("input.txt");
	part2();

	return 0;
}