#pragma once

#include "repo.h"
#include "validator.h"
#include "observer.h"

#include <algorithm>
#include <functional>

class Service : public Observable{
	Repo& repo;
	Validator validator;
public:
	Service(Repo& r, Validator v) : repo(r), validator(v) {

	};

	Service(Service& other) = delete;

	void adauga(int id, const string& denumire, const vector<string>& programatori, const string& stare);
	vector<Task> sort();
	vector<Task> filtrare(const string& programator);
	vector<Task> filtrareStare(const string& stare);
	void schimbaStare(int id, const string& stare);

	vector<Task>& getTasks() {
		return repo.getAll();
	}
};