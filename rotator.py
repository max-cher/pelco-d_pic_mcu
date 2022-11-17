from time import sleep




class Rotator():
    def __init__(self, pp):
        self.pp = pp
        self.dir_x = 's'
        self.dir_y = 's'
        self.speed_x = 10
        self.speed_y = 10
        self.angle_x = 0
        self.angle_y = 0
    
    def get_angle(self, direction):
        '''
        direction == 0 X
        direction == 1 Y
        '''
        return self.pp.get_angle(direction)
    
    def save_angles(self):
        self.angle_x = self.get_angle(0)
        self.angle_y = self.get_angle(1)
    
    def read_angle_x(self):
        return self.angle_x
    
    def read_angle_y(self):
        return self.angle_y
    
    def move_x(self, direction):
        self.dir_x = direction
        self.send_cmd()
    
    def move_y(self, direction):
        self.dir_y = direction
        self.send_cmd()
    
    def move(self, speed_x, speed_y):
        if speed_x < 0:
            self.dir_x = 'l'
        else:
            self.dir_x = 'r'
        
        if speed_y < 0:
            self.dir_y = 'd'
        else:
            self.dir_y = 'u'
        
        self.speed_x = abs(speed_x)
        self.speed_y = abs(speed_y)
        
        self.send_cmd()
    
    def stop(self, axis):
        if axis == 'x':
            self.dir_x = 's'
        if axis == 'y':
            self.dir_y = 's'
        if axis == 'a':
            self.dir_x = 's'
            self.dir_y = 's'
        self.send_cmd()
    
    def set_speed(self, speed_x, speed_y=0):
        self.speed_x = speed_x
        if speed_y:
            self.speed_y = speed_y
        else:
            self.speed_y = speed_x
    
    def send_cmd(self):
        msg = [0]*7
        msg[0] = 0xff
        msg[1] = self.pp.addr
        msg[2] = 0x00
        
        msg[3] = 0x00
        if self.dir_x == 'r':
            msg[3] += 0x02
        elif self.dir_x == 'l':
            msg[3] += 0x04
        if self.dir_y == 'u':
            msg[3] += 0x08
        if self.dir_y == 'd':
            msg[3] += 0x10
        
        msg[4] = self.speed_x
        msg[5] = self.speed_y
        msg[6] = self.pp.crc(msg[1:])
        while self.pp.busy_flag:
            sleep(0.001)
            pass
        self.pp.busy_flag = True
        self.pp.send_cmd(msg)
        self.pp.busy_flag = False
    
    def _delta_2_speed(self, delta):
        
        if delta > 14:
            return 36
        elif delta > 12:
            return 34
        elif delta > 10:
            return 32
        elif delta > 8:
            return 30
        elif delta > 6:
            return 28
        elif delta > 6:
            return 26
        elif delta > 4:
            return 22
        elif delta > 3:
            return 18
        elif delta > 2.5:
            return 16
        elif delta > 2:
            return 14
        elif delta > 1.5:
            return 12
        elif delta > 1.2:
            return 9
        elif delta > 0.8:
            return 8
        elif delta > 0.6:
            return 7
        elif delta > 0.4:
            return 6
        elif delta > 0.2:
            return 5
        elif delta > 0.1:
            return 4
        elif delta > 0.05:
            return 3
        elif delta > 0.02:
            return 2
        elif delta > 0.01:
            return 1
        elif delta > 0.00:
            return 1
        return 0
    
    def go_to(self, target_x, target_y):
        print('set:', target_x, target_y)
        current_x = self.get_angle(0)
        current_y = self.get_angle(1)
        dx = target_x - current_x
        dy = target_y - current_y
        
        while dx or dy:
            current_x = self.get_angle(0)
            current_y = self.get_angle(1)
            dx = target_x - current_x
            dy = target_y - current_y
            
            speed_x = self._delta_2_speed(abs(dx))
            speed_y = self._delta_2_speed(abs(dy))
            if dx < 0:
                speed_x *= -1
            if dy < 0:
                speed_y *= -1
            self.move(speed_x, speed_y)
            
            print('X: {0:03.2f} Y: {1:03.2f} | Delta: {2:03.2f} {3:03.2f} | Speed: {4} {5}'.format(current_x, current_y, dx, dy, speed_x, speed_y))
        
        self.stop('a')
        return
    
    def quick_jump(self, target_x, target_y):
        print('jump to: ({}, {})'.format(target_x, target_y))
        #current_x = self.read_angle_x()
        #current_y = self.read_angle_y()
        current_x = self.get_angle(0)
        current_y = self.get_angle(1)
        dx = target_x - current_x
        dy = target_y - current_y
        
        speed_x = 0
        speed_y = 0
        #if dx < 0:
        #    speed_x *= -1
        #if dy < 0:
        #    speed_y *= -1
        #self.move(speed_x, speed_y)
        
        while abs(dx) > 0.7 or abs(dy) > 0.05:
            #current_x = self.read_angle_x()
            #current_y = self.read_angle_y()
            current_x = self.get_angle(0)
            current_y = self.get_angle(1)
            dx = target_x - current_x
            dy = target_y - current_y
            
            if abs(dx) > 0.9:
                speed_x = 10
            elif abs(dx) <= 0.9:
                speed_x = 9
            elif abs(dx) <= 0.8:
                speed_x = 8
            elif abs(dx) <= 0.6:
                speed_x = 0
            
            if abs(dy) > 0.05:
                speed_y = 3
            elif abs(dy) <= 0.07:
                speed_y = 2
            elif abs(dy) <= 0.06:
                speed_y = 1
            elif abs(dy) <= 0.05:
                speed_y = 0
            
            if dx < 0:
                speed_x *= -1
            if dy < 0:
                speed_y *= -1
            
            self.move(speed_x, speed_y)
            print('X: {0:03.2f} Y: {1:03.2f} | Delta: {2:03.2f} {3:03.2f} | Speed: {4} {5}'.format(current_x, current_y, dx, dy, speed_x, speed_y))
            #sleep(0.05)
        
        print('real angles: ({}, {})'.format(current_x, current_y))
        
        
        
        
    
    def jump(self, target_x, target_y):
        print('set:', target_x, target_y)
        current_x = self.get_angle(0)
        current_y = self.get_angle(1)
        dx = target_x - current_x
        dy = target_y - current_y
        delta = 1
        
        while dx > delta or dy > delta:
            current_x = self.get_angle(0)
            current_y = self.get_angle(1)
            dx = target_x - current_x
            dy = target_y - current_y
            
            speed_x = self._delta_2_speed(abs(dx))
            speed_y = self._delta_2_speed(abs(dy))
            if dx < 0:
                speed_x *= -1
            if dy < 0:
                speed_y *= -1
            self.move(speed_x, speed_y)
            
            print('X: {0:03.2f} Y: {1:03.2f} | Delta: {2:03.2f} {3:03.2f} | Speed: {4} {5}'.format(current_x, current_y, dx, dy, speed_x, speed_y))
    
    
    
    
    def set_as_default(self, direction):
        if direction == 'x' or direction == 'a':
            print('SET DEFAULT X')
            self.pp.set_preset(103)
        if direction == 'y' or direction == 'a':
            print('SET DEFAULT Y')
            self.pp.set_preset(104)
    
    
    def restore_defauot(self, direction):
        if direction == 'x' or direction == 'a':
            print('RESTORE X')
            self.pp.set_preset(103)
            self.pp.call_preset(103)
        if direction == 'y' or direction == 'a':
            print('RESTORE Y')
            self.pp.set_preset(104)
            self.pp.call_preset(104)










