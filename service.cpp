#include "service.h"

void Service::adauga(int id, const string& denumire, const vector<string>& programatori, const string& stare) {
	Task task{ id, denumire, programatori, stare };
	validator.valideazaTask(task);
	repo.adaugaRepo(task);
	notify();
}

vector<Task> Service::sort() {
	auto sorted = repo.getAll();
	std::sort(sorted.begin(), sorted.end(), cmpStare);
	return sorted;
}

vector<Task> Service::filtrare(const string& programator) {
	vector<Task> filtered;
	for (const auto& t : getTasks()) {
		auto it = find(t.getProgramatori().begin(), t.getProgramatori().end(), programator);
		if (it != t.getProgramatori().end()) {
			filtered.push_back(t);
		}
	}
	return filtered;
}

vector<Task> Service::filtrareStare(const string& stare) {
	vector<Task> filtered;
	for (const auto& t : getTasks()) {
		if (t.getStare() == stare) {
			filtered.push_back(t);
		}
	}
	return filtered;
}

void Service::schimbaStare(int id, const string& stare) {
	for (auto& t : getTasks()) {
		if (id == t.getId()) {
			t.setStare(stare);
		}
	}
	repo.saveFile();
	repo.loadFile();
	notify();
}