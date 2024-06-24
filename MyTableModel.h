#pragma once

#include <QAbstractTableModel>
#include <QAbstractItemView>
#include <vector>

#include "domain.h"

using std::vector;

class MyTableModel : public QAbstractTableModel {
	vector<Task> tasks;
public:
	MyTableModel(const vector<Task>& tasks) {
		this->tasks = tasks;
	}

	int rowCount(const QModelIndex& parent = QModelIndex{}) const override {
		return tasks.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex{}) const override {
		return 4;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			const Task& t = tasks[index.row()];
			switch (index.column()) {
			case 0:
				return QString::number(t.getId());
			case 1:
				return QString::fromStdString(t.getDescriere());
			case 2:
				return QString::fromStdString(t.getStare());
			case 3:
				return QString::number(t.getProgramatori().size());
			}
		}
		return QVariant();
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
			switch (section) {
			case 0:
				return "ID";
			case 1:
				return "Descriere";
			case 2:
				return "Stare";
			case 3:
				return "Nr programatori";
			default:
				return QString("");
			}
		}
		return QVariant();
	}

	void setTasks(const vector<Task> tasks) {
		this->tasks = tasks;
		auto topLeft = createIndex(0, 0);
		auto bottomRight = createIndex(rowCount(), columnCount());
		emit layoutChanged();
		emit dataChanged(topLeft, bottomRight);
	}
};
