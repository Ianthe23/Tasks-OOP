#include "domain.h"

vector<string> splitLinie(const string& linie, char delimitator) {
	vector<string> atribute;
	stringstream stream(linie);
	string obiect;

	while (getline(stream, obiect, delimitator)) {
		atribute.push_back(obiect);
	}

	return atribute;
}

istream& operator>>(istream& input, Task& task) {
	string linie;
	getline(input, linie);

	if (linie.empty()) {
		return input;
	}

	vector<string> atribute = splitLinie(linie, ',');
	task.setId(stoi(atribute[0]));
	task.setDescriere(atribute[1]);
	task.setProgramatori(splitLinie(atribute[2], ' '));
	task.setStare(atribute[3]);

	return input;
}

ostream& operator<<(ostream& output, const Task& task) {
	string programatori = "";
	for (const auto& t : task.getProgramatori()) {
		programatori += t;
		programatori += ' ';
	}
	programatori.pop_back();
	output << task.getId() << "," << task.getDescriere() << "," << programatori << "," << task.getStare() << "\n";
	return output;
}

bool cmpStare(const Task& task1, const Task& task2) {
	if (task1.getStare() < task2.getStare()) {
		return true;
	}
	return false;
}