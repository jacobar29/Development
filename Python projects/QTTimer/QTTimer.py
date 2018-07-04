import sys
from PyQt5.QtCore import QTimer
from PyQt5.QtWidgets import QWidget, QApplication, QLCDNumber, QPushButton, QGridLayout, QLabel, QLineEdit


class CountDown(QWidget):
    def __init__(self):

        super().__init__()
        self.setWindowTitle("Digital Clock")
        self.resize(300, 300)

        grid = QGridLayout()
        self.setLayout(grid)

        lm = QLabel('Mins:');
        grid.addWidget(lm, 0, 0)
        self.medit = QLineEdit();
        self.medit.setFixedSize(65, 35);
        grid.addWidget(self.medit, 0, 1)
        ls = QLabel('Secs:');
        grid.addWidget(ls, 1, 0)
        self.sedit = QLineEdit();
        self.sedit.setFixedSize(65, 35);
        grid.addWidget(self.sedit, 1, 1)

        btn = QPushButton('start')
        btn.setFixedSize(65, 65)
        btn.clicked.connect(self.getTime)
        grid.addWidget(btn, 3, 0)

        self.disp = QLCDNumber()
        self.disp.display('0:00')
        self.disp.setSegmentStyle(QLCDNumber.Filled)
        grid.addWidget(self.disp, 2, 0, 1, 0)

        stpbtn = QPushButton('stop')
        stpbtn.setFixedSize(65, 65)
        stpbtn.clicked.connect(self.stopTimer)
        grid.addWidget(stpbtn, 3, 1)

        self.timer = QTimer(self)
        self.running = False

    def getTime(self):

        if not self.running and self.sedit.text() != '':
            if self.medit.text() == '':
                self.min = '0'
            else:
                self.min = int(self.medit.text())
            self.sec = int(self.sedit.text())
            self.showTime()
            self.running = True

    def showTime(self):
        if self.sec == -1:
            self.min -= 1
            self.sec = 59

        if len(str(self.sec)) != 2:
            time = str(self.min) + ':0' + str(self.sec)
        else:
            time = str(self.min) + ':' + str(self.sec)

        if time != '0:00':
            self.sec -= 1
            self.timer.singleShot(1000, self.showTime)
        else:
            self.running = False

        self.disp.display(time)

    def stopTimer(self):

        self.sec = 0
        self.min = 0
        self.showTime()


if __name__ == '__main__':
    app = QApplication(sys.argv)
    clock = CountDown()
    clock.show()
    sys.exit(app.exec_())
