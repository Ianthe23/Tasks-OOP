#pragma once

#include "exceptions.h"
#include "domain.h"

#include <fstream>

class Repo {
	vector<Task> tasks;
	string path;
public:
	Repo(const string& p) : path(p) {
		loadFile();
	}

	Repo(Repo& other) = delete;

	void adaugaRepo(const Task& task);
	void saveFile();
	void loadFile();

	vector<Task>& getAll() {
		return tasks;
	}
};