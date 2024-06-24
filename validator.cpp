#include "validator.h"

void Validator::valideazaId(int id) {
	if (id < 0) {
		throw ValidatorException("Id invalid!\n");
	}
}

void Validator::valideazaDescriere(const string& descriere) {
	if (descriere == "") {
		throw ValidatorException("Descriere invalida!\n");
	}
}

void Validator::valideazaProgramatori(const vector<string>& programatori) {
	if (programatori.size() < 1 || programatori.size() > 4) {
		throw ValidatorException("Id invalid!\n");
	}
}

void Validator::valideazaStare(const string& stare) {
	if (stare != "open" && stare != "inprogress" && stare != "closed") {
		throw ValidatorException("Stare invalida!\n");
	}
}

void Validator::valideazaTask(const Task& task) {
	string exceptii;
	auto id = task.getId();
	auto descriere = task.getDescriere();
	auto programatori = task.getProgramatori();
	auto stare = task.getStare();

	try {
		valideazaId(id);
	}
	catch (ValidatorException& mesaj) {
		exceptii += mesaj.get_mesaj();
	}
	try {
		valideazaDescriere(descriere);
	}
	catch (ValidatorException& mesaj) {
		exceptii += mesaj.get_mesaj();
	}
	try {
		valideazaProgramatori(programatori);
	}
	catch (ValidatorException& mesaj) {
		exceptii += mesaj.get_mesaj();
	}
	try {
		valideazaStare(stare);
	}
	catch (ValidatorException& mesaj) {
		exceptii += mesaj.get_mesaj();
	}
	
	if (!exceptii.empty()) {
		throw ValidatorException(exceptii);
	}
}