#include "repo.h"

void Repo::loadFile() {
	ifstream f(path);
	Task task{};
	tasks.clear();

	while (f >> task) {
		tasks.push_back(task);
	}
	f.close();
}

void Repo::saveFile() {
	ofstream g(path);

	for (const auto& t : getAll()) {
		g << t;
	}
	g.close();
}

void Repo::adaugaRepo(const Task& task) {
	for (const auto& t : getAll()) {
		if (t.getId() == task.getId()) {
			throw RepoException("Task-ul cu acest id deja exista!\n");
		}
	}
	tasks.push_back(task);
	saveFile();
}