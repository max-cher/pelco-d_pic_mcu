import serial
from time import sleep
#from time import time
#from math import pi, sin, cos


class PelcoD():
    def __init__(self, port, speed, addr):
        self.addr = addr
        self.ss = serial.Serial(
                    port=port,
                    baudrate=speed,
                    parity=serial.PARITY_NONE,
                    stopbits=serial.STOPBITS_ONE,
                    bytesize=serial.EIGHTBITS,
                    timeout=1.1)
        self.busy_flag = False

    def send_cmd(self, cmd):
        for i in range(7):
            data = bytearray([cmd[i]])
            self.ss.write(data)

    def crc(self, A):
        crc = 0
        for i in A:
            crc += i
        crc %= 0x100
        return crc

    def turn(self, speed, direction):
        """Move X"""
        msg = [0]*7
        msg[0] = 0xff
        msg[1] = self.addr
        msg[2] = 0x00
        msg[3] = 0x02 if direction else 0x04
        msg[4] = speed
        msg[5] = 0x00
        msg[6] = self.crc(msg[1:])
        while self.busy_flag:
            sleep(0.001)
            pass
        self.busy_flag = True
        self.send_cmd(msg)
        self.busy_flag = False

    def bend(self, speed, direction):
        """Move Y"""
        msg = [0]*7
        msg[0] = 0xff
        msg[1] = self.addr
        msg[2] = 0x00
        msg[3] = 0x08 if direction else 0x10
        msg[4] = 0x00
        msg[5] = speed
        msg[6] = self.crc(msg[1:])
        while self.busy_flag:
            sleep(0.001)
            pass
        self.busy_flag = True
        self.send_cmd(msg)
        self.busy_flag = False

    def move(self, speed_x, speed_y, dir_x, dir_y):
        """Move X, Y"""
        msg = [0]*7
        msg[0] = 0xff
        msg[1] = self.addr
        msg[2] = 0x00
        msg[3] = (0x02 if dir_x else 0x04) + (0x08 if dir_y else 0x10)
        msg[4] = speed_x
        msg[5] = speed_y
        msg[6] = self.crc(msg[1:])
        while self.busy_flag:
            sleep(0.001)
            pass
        self.busy_flag = True
        self.send_cmd(msg)
        self.busy_flag = False
        sleep(0.01)

    def stop(self):
        msg = [0]*7
        msg[0] = 0xff
        msg[1] = self.addr
        msg[2] = 0x00
        msg[3] = 0x00
        msg[4] = 0x00
        msg[5] = 0x00
        msg[6] = self.crc(msg[1:])
        while self.busy_flag:
            sleep(0.001)
            pass
        self.busy_flag = True
        self.send_cmd(msg)
        self.busy_flag = False
        sleep(0.01)

    def call_preset(self, preset):
        msg = [0]*7
        msg[0] = 0xff
        msg[1] = self.addr
        msg[2] = 0x00
        msg[3] = 0x07
        msg[4] = 0x00
        msg[5] = preset
        msg[6] = self.crc(msg[1:])
        while self.busy_flag:
            sleep(0.001)
            pass
        self.busy_flag = True
        self.send_cmd(msg)
        self.busy_flag = False
        sleep(0.01)

    def set_preset(self, preset):
        msg = [0]*7
        msg[0] = 0xff
        msg[1] = self.addr
        msg[2] = 0x00
        msg[3] = 0x03
        msg[4] = 0x00
        msg[5] = preset
        msg[6] = self.crc(msg[1:])
        while self.busy_flag:
            sleep(0.001)
            pass
        self.busy_flag = True
        self.send_cmd(msg)
        self.busy_flag = False
        sleep(0.01)

    def get_angle(self, direction):
        #startTime = time()
        
        msg = [0xff, self.addr, 0x00, 0x00, 0x00, 0x00, 0x00]
        msg[3] = 0x53 if direction else 0x51
        msg[6] = self.crc(msg[1:])
        while self.busy_flag:
            sleep(0.001)
            pass
        self.busy_flag = True
        #print('time 0:', abs(time() - startTime))
        self.send_cmd(msg)
        #print('time 1:', abs(time() - startTime))
        data_bytes = self.ss.read(7)
        self.busy_flag = False
        #print('time 2:', abs(time() - startTime))
        
        data=[]
        for el in data_bytes:
            data.append(el)
        
        if not len(data):
            print('ERROR: wrong angle answer')
            return -100/100
        
        if data[0] == 0xff:
            pass
        elif data[0] == 1:
            data.insert(0, 0xff)
        
        if(len(data)) >= 7:
            if(data[3] == (0x5b if direction else 0x59)):
                angle = data[4]*0x100 + data[5]
                if direction:
                    if angle > 18000:
                        angle = 36000 - angle
                    else:
                        angle *= -1
                return angle/100
            else:
                for i in data:
                    print('0x{0:02x}'.format(i), end=' | ')
                print('\n')
        else:
            print('ERROR: wrong angle answer')
            return -100/100


