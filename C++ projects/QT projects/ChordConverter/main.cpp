#include "ChordConverter.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ChordConverter w;
	w.show();
	return a.exec();
}
