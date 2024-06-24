#pragma once

#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<string> splitLinie(const string& linie, char delimitator);

class Task {
private:
	int id;
	string descriere;
	vector<string> programatori;
	string stare;
public:
	Task() {
		id = -1;
		descriere = "";
		stare = "";
		programatori.clear();
	}

	Task(int id, const string& descriere, const vector<string>& programatori, const string& stare) {
		this->id = id;
		this->descriere = descriere;
		this->programatori = programatori;
		this->stare = stare;
	}

	Task& operator=(const Task& other) = default;

	//getters
	int getId() const {
		return id;
	}
	const string& getDescriere() const {
		return descriere;
	}
	const vector<string>& getProgramatori() const {
		return programatori;
	}
	const string& getStare() const {
		return stare;
	}

	//setters
	void setId(int id) {
		this->id = id;
	}
	void setDescriere(const string& descriere) {
		this->descriere = descriere;
	}
	void setProgramatori(const vector<string>& programatori) {
		this->programatori = programatori;
	}
	void setStare(const string& stare) {
		this->stare = stare;
	}

	friend istream& operator>>(istream& input, Task& task);
	friend ostream& operator<<(ostream& output, const Task& task);
};

bool cmpStare(const Task& task1, const Task& task2);