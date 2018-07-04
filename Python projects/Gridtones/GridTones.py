
import sys
from PyQt5.QtGui import QColor
from PyQt5.QtWidgets import QLabel, QPushButton, QGridLayout, QWidget, QApplication, QSlider, QDial
from PyQt5.QtCore import QTimer, Qt
from Wavemaker import Wavemaker
from itertools import chain


class GridTones(QWidget):
    def __init__(self):
        # noinspection PyArgumentList
        super().__init__()
        #
        self.app = QApplication(sys.argv)
        self.size = self.app.primaryScreen().size()
        self.rows = [[], [], [], [], [], [], []]
        self.waves = Wavemaker()
        self.waves.create_sounds()
        self.setStyleSheet(open("Style.qss", "r").read())
        self.setAutoFillBackground(True)
        self.timer = QTimer(self)
        self.interval = 250
        self.curr = 0
        self.cycle_length = 7
        self.init_ui()

        self.cycle()

    def init_ui(self):
        p = self.palette()
        p.setColor(self.backgroundRole(), QColor(0, 188, 207))
        self.setPalette(p)
        grid = QGridLayout()
        # create and add controla to UI

        rate = QDial()
        rate.setRange(-100, 0)
        rate.valueChanged.connect(self.set_timer)
        sine_vol = QDial()
        sine_vol.valueChanged.connect(self.waves.set_vol)
        square_vol = QDial()
        square_vol.valueChanged.connect(self.waves.set_sqvol)
        attack = QDial()
        attack.valueChanged.connect(self.waves.set_attack)
        clr = QPushButton()
        clr.clicked.connect(self.clear_pattern)

        ctrls = [rate, sine_vol, square_vol, attack, clr]
        [ctrls[i].setValue(50) for i in range(2)]
        # noinspection PyArgumentList
        [grid.addWidget(ctrls[i], 0, i) for i in range(len(ctrls))]
        labels = ['rate', 'Sine', 'Square', 'Attack', 'Clear']
        # noinspection PyArgumentList
        [grid.addWidget(QLabel(str(labels[x])), 1, x) for x in range(len(labels))]

        # create and add length slider to UI
        patt_length = QSlider(Qt.Horizontal)
        patt_length.setRange(7, 31)
        patt_length.valueChanged.connect(self.set_length)
        # noinspection PyArgumentList
        grid.addWidget(patt_length, 1, 8, 1, 24)

        [self.create_button(i, j, grid) for i in range(7) for j in range(32)]
        # noinspection PyArgumentList
        [grid.addWidget(QLabel(str(x)), 10, x - 1) for x in range(4, 33, 4)]
        grid.setSpacing(2)
        self.showMaximized()
        self.setLayout(grid)
        self.show()

    def create_button(self, row, column, layout):
        btn = QPushButton()
        btn.setMinimumHeight(self.size.height() / 10)
        btn.toggled = False
        btn.highlighted = False
        btn.clicked.connect(self.on_click)
        btn.setEnabled(False) if column > 7 else btn.setEnabled(True)
        self.set_color(btn)
        layout.addWidget(btn, row + 2, column, 1, 1)
        # noinspection PyTypeChecker
        self.rows[row].append(btn)
        self.curr = ((self.curr + 1) if self.curr != 31 else 0)

    def on_click(self):
        sender = self.sender()
        sender.toggled = (False if sender.toggled else True)
        self.set_color(sender)

    def cycle(self):
        # recursive function to create and sustain loop
        previous = (self.cycle_length if (self.curr == 0) else (self.curr - 1))
        current = self.curr

        for i in range(7):
            self.rows[i][current].highlighted = True
            self.rows[i][previous].highlighted = False
            self.set_color(self.rows[i][current], self.rows[i][previous])
            if self.rows[i][current].toggled:
                self.waves.play_sound(i)
        self.curr = self.curr + 1 if self.curr != self.cycle_length else 0
        self.timer.singleShot(self.interval, self.cycle)

    def set_timer(self, value):
        self.interval = (((abs(value) + 25) * 10) / 2)

    @staticmethod
    def set_color(*args):
        for btn in args:
            if btn.isEnabled():
                if btn.toggled and btn.highlighted:
                    btn.setStyleSheet("background-color: rgb(255,105,180);")
                elif not btn.toggled and btn.highlighted:
                    btn.setStyleSheet("background-color: rgb(255,120,255);")
                elif btn.toggled and not btn.highlighted:
                    btn.setStyleSheet("background-color: rgb(0,255,0);")
                elif not btn.toggled and not btn.highlighted:
                    btn.setStyleSheet("background-color: rgb(255,144,0);")
            else:
                btn.setStyleSheet("background-color: rgba(110,110,110);")
                btn.toggled = False

    def set_length(self, slider_value):
        # adjust number of active buttons, reset curr to avoid index outofrange error
        self.curr = 0
        self.cycle_length = slider_value
        for i in range(7):
            for j in range(32):
                self.rows[i][j].setEnabled(False) if j > self.cycle_length else self.rows[i][j].setEnabled(True)
                self.rows[i][j].highlighted = False
                self.set_color(self.rows[i][j])

    def clear_pattern(self):
        for x in chain.from_iterable(self.rows):
            x.toggled = False
            self.set_color(x)


if __name__ == '__main__':
    app = QApplication(sys.argv)

    w = GridTones()
    w.show()

    sys.exit(app.exec_())
