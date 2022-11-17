import serial
from time import sleep
from time import time
import keyboard
import sys
from serial_ports import serial_ports, get_port
from PelcoD import PelcoD
from rotator import Rotator
#from workers import *
from funcs import *
#from glob import *

from matplotlib import pylab as plt
import threading
#import multiprocessing.dummy as multiprocessing
from multiprocessing.dummy import Queue
from math import pi, sin, cos

#import globs
#print(dir(glob))

speed_x = 10
speed_y = 10

notExit = True


def angle_worker(q, rotator, start_time):
    global notExit
    print('angle_worker >> Start')
    while notExit:
        angles = []
        #angle_x = sin(time()/40)*90 + 0#
        
        rotator.save_angles()
        
        #angle_x = rotator.get_angle(0)
        angle_x = rotator.read_angle_x()
        t = time() - start_time
        angles.append((t, angle_x))
        #sleep(0.1)
        
        #angle_y = cos(time()/40)*2 + 0#
        #angle_y = rotator.get_angle(1)
        angle_y = rotator.read_angle_y()
        t = time() - start_time
        angles.append((t, angle_y))
        q.put(angles)
        sleep(0.1)
    print('angle_worker >> Stop')


def radar_worker(q, start_time):
    global notExit
    print('radar_worker >> Start')
    while notExit:
        current_time = time() - start_time
        q.put((current_time, sin(current_time*2)*2))
        sleep(0.01)
    print('radar_worker >> Stop')





def main():
    global notExit
    PORT = get_port()
    if not PORT:
        print('No port found')
        exit()
    SPEED = 9600
    ADDR = 0x01
    interface = PelcoD(PORT, SPEED, ADDR)
    interface.call_preset(105)     # request mode angle
    #pp.set_preset(105)         # real-time mode angle
    rotator = Rotator(interface)
    
    def pressed_keys(e):
        global speed_x
        global speed_y
        if e.event_type == 'down':
            if e.name == 'a':
                rotator.move_x('l')
            if e.name == 'd':
                rotator.move_x('r')
            
            if e.name == 's':
                rotator.move_y('u')
            if e.name == 'w':
                rotator.move_y('d')
        
        if e.event_type == 'up':
            if e.name == 'a' or e.name == 'd':
                rotator.stop('x')
            if e.name == 'w' or e.name == 's':
                rotator.stop('y')
            interface.stop()
        
        if e.name.isdigit():
            rotator.set_speed(int(e.name)*3 + 1)
        
        if e.name == 'space':
            interface.stop()
    keyboard.hook(pressed_keys)
    print(rotator.get_angle(0), rotator.get_angle(1))
    start_time = time()
    
    #interface.set_preset(103)
    
    rotator.stop('a')
    
    while 1:
        sleep(0.1)
    
    #rotator.go_to(30, 30)
    
    #rotator.set_as_default('a')
    
    #rotator.go_to(0, 0)
    
    rotator.restore_defauot('x')
    
    rotator.go_to(0, 0)
    
    rotator.restore_defauot('y')
    
    rotator.go_to(0, 0)
    
    return
    
    points = []
    
    #pathname = 'runway.txt'
    pathname = 'runway_part.txt'
    
    with open(pathname, 'r') as file:
        line = file.readline()
        while line:
            point = line.split()
            x = float(point[0]) + 180
            y = float(point[1])
            points.append((x, y))
            line = file.readline()
    
    rotator.go_to(points[0][0], points[0][1])
    rotator.stop('a')
    
    queue_angle = Queue()
    queue_radar = Queue()
    angle_reader = threading.Thread(name='angle_reader', target=angle_worker, args=(queue_angle, rotator, start_time)).start()
    radar_reader = threading.Thread(name='radar_reader', target=radar_worker, args=(queue_radar, start_time)).start()
    
    
    X = []
    Y = []
    DATA = []
    start_time = time()
    counter = 1
    for el in points:
        
        if not queue_angle.empty():
            data = queue_angle.get() 
            X.append(data[0])
            Y.append(data[1])
        if not queue_radar.empty():
            queue_radar.get()
            DATA.append(queue_radar.get())
        current_time = time() - start_time
        print('#{0:04}|{0:03}'.format(counter, int(current_time)))
        rotator.quick_jump(el[0], el[1])
        
        
        counter += 1
    
    print('DONE in {} sec.'.format(time() - start_time))
    
    rotator.stop('a')
    while 0:
        sleep(0.1)
        print(rotator.get_angle(0), rotator.get_angle(1))
    
    
    #rotator.move(5, -6)
    
    
    
    
    
    #sweep_counter = 0
    #sweeps = 10
    
    current_time = time() - start_time
    print('begin: rotation')
    while 0:#current_time < 60:
        if not queue_angle.empty():
            data = queue_angle.get() 
            X.append(data[0])
            Y.append(data[1])
        if not queue_radar.empty():
            queue_radar.get()
            DATA.append(queue_radar.get())
        current_time = time() - start_time
        
        speed_x = int(sin(current_time/19)*20)
        speed_y = int(sin(current_time/19)*2)
        print('sec:{0} x:{1} y:{2}'.format(int(current_time), speed_x, speed_y))
        
        rotator.move(speed_x, speed_y)
    X.insert(0, (0, X[0][1]))
    Y.insert(0, (0, Y[0][1]))
    print('end: rotation')
    
    if DATA[-1][0] > X[-1][0]:
        x0 = X[-2][0]
        x1 = X[-1][0]
        y0 = X[-2][1]
        y1 = X[-1][1]
        dx = x1 - x0
        dy = y1 - y0
        
        x = DATA[-1][0]
        y = y1 + dx/(x - x0)*dy
        
        X.insert(len(X), (x, y))
    
    
    if DATA[-1][0] > Y[-1][0]:
        x0 = Y[-2][0]
        x1 = Y[-1][0]
        y0 = Y[-2][1]
        y1 = Y[-1][1]
        dx = x1 - x0
        dy = y1 - y0
        
        x = DATA[-1][0]
        y = y1 + dx/(x - x0)*dy
        
        Y.insert(len(Y), (x, y))
    
    print(len(X), len(Y), len(DATA))
    notExit = False
    interface.stop()
    
    fig = plt.figure()
    
    print('begin: drowing real angles')
    for i in range(len(X)):
        plt.scatter(X[i][0], X[i][1], color='blue', s=10)
        plt.scatter(Y[i][0], Y[i][1], color='red', s=10)
        #print('{0} | {1}'.format(X[i], Y[i]))
    print('end: drowing real angles')
    A = []
    
    print('begin: drowing predict angles')
    for i in range(len(DATA)):
        x = DATA[i][0]
        y_radar = DATA[i][1]
        plt.scatter(x, y_radar+30, color='green')
        x_min, x_max = find_point(X, x)
        y_min, y_max = find_point(Y, x)
        y_angle_x = calc_point(x_min, x_max, x)
        y_angle_y = calc_point(y_min, y_max, x)
        plt.scatter(x, y_angle_x, color='cyan', s=5)
        plt.scatter(x, y_angle_y, color='yellow', s=5)
        #y_angle_x_predict = sin((start_time + x)/40)*90
        #plt.scatter(x, y_angle_x_predict, color='magenta')#
        #A.append((y_angle_x, y_angle_x_predict))
    print('end: drowing predict angles')
    
    #Z = []
    #for i in A:
    #    Z.append(abs(i[0] - i[1]))
    #print('max error:', max(Z))
    print('begin: drow plot')
    plt.grid(True)
    plt.show()
    print('end: drow plot')
    
    
if __name__ == '__main__':
    main()
