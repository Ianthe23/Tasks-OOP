#pragma once

#include "service.h"
#include "MyTableModel.h"
#include "observer.h"

#include <QWidget>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QTableWidget>
#include <QListWidget>
#include <QTableView>
#include <QLineEdit>
#include <QDebug>

class Window : public QWidget, public Observer {
private:
	Service& srv;
	string stare;
	QListWidget* lista = new QListWidget;
	QHBoxLayout* layout = new QHBoxLayout;
	QPushButton* btn1 = new QPushButton{ "&Open" };
	QPushButton* btn2 = new QPushButton{ "&Inprogress" };
	QPushButton* btn3 = new QPushButton{ "&Closed" };
public:
	Window(Service& srv, const string& stare) : srv(srv), stare(stare) {
		this->srv.addObserver(this);
		setWindowTitle(QString::fromStdString(stare));
		setLayout(layout);
		setMinimumSize(250, 100);
		layout->addWidget(lista);
		layout->addWidget(btn1);
		layout->addWidget(btn2);
		layout->addWidget(btn3);
		loadList(srv.filtrareStare(stare));
		connect();
		
	}

	void connect() {
		QObject::connect(btn1, &QPushButton::clicked, [this] {
			auto selectedIndexes = lista->selectionModel()->selectedIndexes();
			if (!selectedIndexes.isEmpty()) {
				auto i = selectedIndexes.first().row();
				auto tasks = srv.filtrareStare(stare);
				if (i >= 0 && i < tasks.size()) {
					srv.schimbaStare(tasks[i].getId(), "open");
					loadList(srv.filtrareStare(stare));
					srv.notify();
				}
				else {
					qDebug() << "Selected index is out of range.";
				}
			}
			else {
				qDebug() << "No items selected.";
			}
			});
		
		QObject::connect(btn2, &QPushButton::clicked, [this] {
			auto selectedIndexes = lista->selectionModel()->selectedIndexes();
			if (!selectedIndexes.isEmpty()) {
				auto i = selectedIndexes.first().row();
				auto tasks = srv.filtrareStare(stare);
				if (i >= 0 && i < tasks.size()) {
					srv.schimbaStare(tasks[i].getId(), "inprogress");
					loadList(srv.filtrareStare(stare));
					srv.notify();
				}
				else {
					qDebug() << "Selected index is out of range.";
				}
			}
			else {
				qDebug() << "No items selected.";
			}
			});

		QObject::connect(btn3, &QPushButton::clicked, [this] {
			auto selectedIndexes = lista->selectionModel()->selectedIndexes();
			if (!selectedIndexes.isEmpty()) {
				auto i = selectedIndexes.first().row();
				auto tasks = srv.filtrareStare(stare);
				if (i >= 0 && i < tasks.size()) {
					srv.schimbaStare(tasks[i].getId(), "closed");
					loadList(srv.filtrareStare(stare));
					srv.notify();
				}
				else {
					qDebug() << "Selected index is out of range.";
				}
			}
			else {
				qDebug() << "No items selected.";
			}
			});
	}

	void loadList(vector<Task> v) {
		this->lista->clear();
		for (auto& el : v) {
			lista->addItem(QString::fromStdString(std::to_string(el.getId()) + " " + el.getDescriere() + " " + el.getStare()));
		}
	}

	~Window() {
		this->srv.removeObserver(this);
	}
	void update() override {
		loadList(srv.filtrareStare(stare));
	}
};

class AppGUI : public QWidget, public Observer {
public:
	AppGUI(Service& service) : srv(service) {
		initGUI();
		loadTable(srv.sort());
		connectSignals();
		addWindow();
	}

	virtual void update() override {
		loadTable(srv.sort());
	}
private:
	Service& srv;
	MyTableModel* model = nullptr;
	QTableView* tabel = new QTableView;

	QPushButton* btn_adauga = new QPushButton{ "&Adauga" };
	QPushButton* btn_load = new QPushButton{ "&Load" };
	QPushButton* btn_cauta = new QPushButton{ "&Cauta" };
	QLineEdit* txt_id = new QLineEdit;
	QLineEdit* txt_descriere = new QLineEdit;
	QLineEdit* txt_programatori = new QLineEdit;
	QLineEdit* txt_stare = new QLineEdit;
	QLineEdit* txt_filtrare = new QLineEdit;

	void initGUI();
	void loadTable(const vector<Task>& tasks);
	void connectSignals();
	void addWindow();
};
