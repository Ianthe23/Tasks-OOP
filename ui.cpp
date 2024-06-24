#include "ui.h"

void AppGUI::initGUI() {
	this->srv.addObserver(this);
	QHBoxLayout* mainLayout = new QHBoxLayout;
	setLayout(mainLayout);

	QVBoxLayout* st = new QVBoxLayout;
	mainLayout->addLayout(st);

	QLabel* tabelLabel = new QLabel("Tabel tasks");
	tabelLabel->setAlignment(Qt::AlignCenter);
	st->addWidget(tabelLabel);

	tabel->resizeColumnsToContents();
	tabel->setMinimumSize(408, 350);
	st->addWidget(tabel, 2);
	st->addWidget(btn_load);

	QVBoxLayout* dr = new QVBoxLayout;
	mainLayout->addLayout(dr);

	QFormLayout* formLayout = new QFormLayout;
	dr->addLayout(formLayout);
	formLayout->addRow(new QLabel("ID: "), txt_id);
	formLayout->addRow(new QLabel("Descriere: "), txt_descriere);
	formLayout->addRow(new QLabel("Programatori: "), txt_programatori);
	formLayout->addRow(new QLabel("Stare: "), txt_stare);
	formLayout->addWidget(btn_adauga);

	dr->addSpacing(100);
	QLabel* cautaLabel = new QLabel("Cauta");
	cautaLabel->setAlignment(Qt::AlignCenter);
	dr->addWidget(cautaLabel);
	QFormLayout* formLayoutCauta = new QFormLayout;
	dr->addLayout(formLayoutCauta);
	formLayoutCauta->addRow(new QLabel("Programator: "), txt_filtrare);
	formLayoutCauta->addWidget(btn_cauta);
}

void AppGUI::loadTable(const vector<Task>& tasks) {
	model = new MyTableModel{ tasks };
	tabel->setSelectionMode(QAbstractItemView::SingleSelection);
	tabel->setModel(model);
}

void AppGUI::connectSignals() {
	QObject::connect(btn_adauga, &QPushButton::clicked, [this] {
		auto id = txt_id->text().toStdString();
		auto descriere = txt_descriere->text().toStdString();
		auto programatori = txt_programatori->text().toStdString();
		vector<string> atribute = splitLinie(programatori, ' ');
		auto stare = txt_stare->text().toStdString();

		QMessageBox msg;

		int id_corect;
		try {
			id_corect = stoi(id);
		}
		catch (std::invalid_argument& mesaj) {
			msg.warning(this, "Warning", "Id-ul trebuie sa fie nr natural");
			return;
		}
		qDebug() << id_corect << " " << descriere << " " << programatori << " " << stare << '\n';		
		try {
			srv.adauga(id_corect, descriere, atribute, stare);
		}
		catch (RepoException& mesaj) {
			msg.warning(this, "Warning", QString::fromStdString(mesaj.get_mesaj()));
		}
		catch (ValidatorException& mesaj) {
			msg.warning(this, "Warning", QString::fromStdString(mesaj.get_mesaj()));
		}

		txt_id->clear();
		txt_descriere->clear();
		txt_programatori->clear();
		txt_stare->clear();
		loadTable(srv.sort());
		});

	QObject::connect(btn_cauta, &QPushButton::clicked, [this] {
		auto programator = txt_filtrare->text().toStdString();
		loadTable(srv.filtrare(programator));
		txt_filtrare->clear();
		});

	QObject::connect(btn_load, &QPushButton::clicked, [this] {
		loadTable(srv.sort());
		});
}

void AppGUI::addWindow() {
	Window* window1 = new Window(srv, "open");
	Window* window2 = new Window(srv, "inprogress");
	Window* window3 = new Window(srv, "closed");

	window1->show();
	window2->show();
	window3->show();
}
