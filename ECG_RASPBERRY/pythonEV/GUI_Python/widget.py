__author__ = "Thomas Randwijk & Lucas Bolwidt"
__copyright__ = "Open Source"
__license__ = "Public Domain"
__version__ = "1.0"

'''
Graphical representation of ECG and HRV. Based on Qt6, generation of ECG and RSP values

Features:
    - Generates a complete ECG for child, with 1 fast and 1 slow BPM.
    - Uses fast algorithm for usage on Raspberry PI.

Recommended Changes:
    - Add Sensordata
    - ECG smooth transition
'''

import sys
from PySide6.QtWidgets import QApplication, QMainWindow, QVBoxLayout, QWidget, QPushButton, QHBoxLayout, QLabel
import numpy as np
import pyqtgraph as pg
import neurokit2 as nk              #neurokit2 library for creating ECG & RSP signal

ecg_rate = 50
rsp_rate = 15
state = 0

class GraphWidget(QWidget):
    def __init__(self, parent=None):
        super(GraphWidget, self).__init__(parent)
        global ecg_rate 
        global rsp_rate
        global state
        self.ecg_rate = ecg_rate  # Default heart rate
        self.state = state      # Default off state
        self.create_ecg_signal()

        #Initializes Plot
        self.plot_widget_sin = pg.PlotWidget()
        self.plot_widget_cos = pg.PlotWidget()
        self.plot_widget_sin.setStyleSheet("border-width: 2px; border-style: solid; border-color: gray")
        self.plot_widget_cos.setStyleSheet("border-width: 2px; border-style: solid; border-color: gray")

        #Ceates box for formatting
        self.setLayout(QVBoxLayout())
        self.layout().addWidget(self.plot_widget_sin)
        self.layout().addWidget(self.plot_widget_cos)

        #Fill lines for first time
        self.x_sin = np.linspace(0, 10, len(self.ecg_part))
        self.x_cos = np.linspace(0, 20, len(self.rsp15_part))
        self.y_sin = self.ecg_part
        self.y_cos = self.rsp15_part

        #Setup lines for upper & bottom plot
        self.curve_sin = self.plot_widget_sin.plot(self.x_sin, self.y_sin, pen='g', name='Sinus')
        self.curve_cos = self.plot_widget_cos.plot(self.x_cos, self.y_cos, pen='w', name='Cosinus')

        # Set titles for the plot widgets
        self.plot_widget_sin.setTitle("ECG")
        self.plot_widget_cos.setTitle("Respiration")

        # Add button to switch between ECG signals
        self.button_switch_ecg = QPushButton("Switch ECG")
        self.button_switch_ecg.clicked.connect(self.switch_ecg_signal)
        self.button_switch_ecg.setStyleSheet("color: white; border-color: gray")
        self.layout().addWidget(self.button_switch_ecg)

        #Add button to turn of ECG signals and respiration signals
        self.button_toggle_all = QPushButton("Turn ON / OFF")
        self.button_toggle_all.clicked.connect(self.toggle_all)
        self.button_toggle_all.setStyleSheet("color: white; border-color: gray")
        self.layout().addWidget(self.button_toggle_all)

        # Set up a QTimer to update the x-axis at regular intervals
        self.timer = pg.QtCore.QTimer(self)
        self.timer.timeout.connect(self.update_plot)
        self.timer.start(100)  # Update every 100 milliseconds


    def create_ecg_signal(self):
            # Generate ECG & RSP using NeuroKit library
            self.ecg_part = nk.ecg_simulate(duration=10, sampling_rate=500, noise=0.1, heart_rate=self.ecg_rate).ravel()
            self.rsp15_part = nk.rsp_simulate(duration=20, sampling_rate=800, noise=0.005, respiratory_rate=rsp_rate, method="breathmetrics").ravel()

    def switch_ecg_signal(self):
        global ecg_rate
        # Toggle between ECG signals with heart rates of 50 and 100
        if self.ecg_rate == 50:
            self.ecg_rate = 100 
            ecg_rate = 100
        else: 
            self.ecg_rate = 50
            ecg_rate = 50
        self.create_ecg_signal()

    def toggle_all(self):
        global state
        #toggle between on and off'
        if self.state == 0:
            self.state = 1  
            state = 1
        else:
            self.state = 0
            state = 0


    def update_plot(self):
        if self.state == 1:
            # Increment the x-axis values to simulate advancing time
            self.x_sin += 0.1
            self.x_cos += 0.1

            # Update the plot with the constant sinusoidal and cosinusoidal data
            self.curve_sin.setData(self.x_sin, self.ecg_part)
            self.curve_cos.setData(self.x_cos, self.rsp15_part)

            self.ecg_part = np.roll(self.ecg_part, -50)
            self.rsp15_part = np.roll(self.rsp15_part, -50)

class InfoWidget(QWidget):
    def __init__(self, parent=None):
        super(InfoWidget, self).__init__(parent)

        #Ceates box for formatting
        self.setLayout(QVBoxLayout())

        #HB info
        self.heart_beat = QLabel("HB")
        self.heart_beat.setStyleSheet("background-color: black; color: green; min-width: 200px; border-width: 2px; border-style: solid; border-color: gray; font-size: 45px; text-align: center")
        self.layout().addWidget(self.heart_beat)

        #RP info
        self.resperation = QLabel("RP")
        self.resperation.setStyleSheet("background-color: black; color: white; min-width: 200px; border-width: 2px; border-style: solid; border-color: gray; font-size: 45px; text-align: center")
        self.layout().addWidget(self.resperation)

        #setup a timer
        self.timer = pg.QtCore.QTimer(self)
        self.timer.timeout.connect(self.update_info)
        self.timer.start(1000)  # Update every 100 milliseconds

    def update_info(self):
        #update data fieldsS
        if state == 1:
            self.heart_beat.setText(str(ecg_rate) + " BPM")
            self.resperation.setText(str(rsp_rate) + " BPM")
        else:
            self.heart_beat.setText('0')
            self.resperation.setText('0')
            





class MainWindow(QMainWindow):
    def __init__(self):
        super(MainWindow, self).__init__()

        central_widget = QWidget()
        self.setCentralWidget(central_widget)

        layout = QHBoxLayout(central_widget)
        self.graph_widget = GraphWidget()
        layout.addWidget(self.graph_widget)
        self.info_widget = InfoWidget()
        self.info_widget.setStyleSheet("margin-bottom: 60px")
        layout.addWidget(self.info_widget)

def main():
    app = QApplication(sys.argv)
    main_window = MainWindow()
    main_window.setStyleSheet("background-color: black")
    main_window.show()
    sys.exit(app.exec())

if __name__ == '__main__':
    main()
