#pragma once

#include "domain.h"
#include "exceptions.h"

class Validator {
private:
	static void valideazaId(int id);

	static void valideazaDescriere(const string& descriere);

	static void valideazaProgramatori(const vector<string>& programatori);

	static void valideazaStare(const string& stare);
public:
	static void valideazaTask(const Task& task);
};
