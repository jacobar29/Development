
import pygame
import numpy as np
import math


class Wavemaker:

    def __init__(self):
        pygame.mixer.pre_init(44100, -16, 2, 2048)
        pygame.mixer.init()
        pygame.init()
        self.attack = 0
        self.sines = []
        self.squares = []

    def create_sounds(self):
        freqs = [493.88, 444.0, 392.00, 349.23, 329.63, 293.66, 261.63]
        for i in range(len(freqs)):
            arr = self.sine_wave(freqs[i])
            x = pygame.mixer.Sound(arr)
            self.sines.append(x)
            x.set_volume(0.5)
            arr2 = self.square_wave(freqs[i])
            y = pygame.mixer.Sound(arr2)
            self.squares.append(y)
            y.set_volume(0)

    def square_wave(self, frequency):
        length = 0.5
        num_steps = int(length * 44100)
        s = []
        length_of_plateau = int(44100 / (2 * frequency))
        counter = 0
        state = 1
        vol = 3000
        for n in range(num_steps):
            value = state * vol
            s.append([value, value])
            counter += 1
            if counter == length_of_plateau:
                counter = 0
                state *= -1
        arr = pygame.sndarray.make_sound(np.array(s))
        return arr

    def sine_wave(self, frequency):
        length = 0.5
        freq = frequency
        sample_rate = 44100
        num_steps = round(length * sample_rate)
        s = []
        volmax = 5000.0
        peaked = False
        vol = 0
        for n in range(num_steps):
            value = int(math.sin(n * freq * (6.28318 / sample_rate)) * vol)
            if vol == volmax:
                peaked = True
            if peaked:
                vol -= (vol / (num_steps / 2))
            else:
                vol += 10
            s.append([value, value])
        arr = pygame.sndarray.make_sound(np.array(s))
        return arr

    def play_sound(self, i):
        self.squares[i].play(fade_ms=self.attack)
        self.sines[i].play(fade_ms=self.attack)

    def set_vol(self, vol):
        for i in range(len(self.sines)):
            self.sines[i].set_volume(vol / 100)

    def set_sqvol(self, sqvol):
        for i in range(len(self.squares)):
            self.squares[i].set_volume(sqvol / 100)

    def set_attack(self, atk):
        self.attack = atk * 7


