# Importing Libraries
import serial
import time
import pygame
import os

# Initialize pygame
pygame.init()

SCREEN_WIDITH = 600
SCREEN_HEIGHT = 400

screen = pygame.display.set_mode((SCREEN_WIDITH, SCREEN_HEIGHT))
pygame.display.set_caption('image')
imp = pygame.image.load("/home/pedro/Arduino/simons-game-with-python/simons-game-image.png")
screen.blit(imp, (0, 0))
pygame.display.flip()
# Load the sound effect
sound_effect_path_fail = os.path.join("/home/pedro/Arduino/simons-game-with-python", "fail.mp3")
sound_effect_fail = pygame.mixer.Sound(sound_effect_path_fail)
sound_effect_path_red = os.path.join("/home/pedro/Arduino/simons-game-with-python", "red.mp3")
sound_effect_red = pygame.mixer.Sound(sound_effect_path_red)
sound_effect_path_green = os.path.join("/home/pedro/Arduino/simons-game-with-python", "green.mp3")
sound_effect_green = pygame.mixer.Sound(sound_effect_path_green)
sound_effect_path_blue = os.path.join("/home/pedro/Arduino/simons-game-with-python", "blue.mp3")
sound_effect_blue = pygame.mixer.Sound(sound_effect_path_blue)
sound_effect_path_yellow = os.path.join("/home/pedro/Arduino/simons-game-with-python", "yellow.mp3")
sound_effect_yellow = pygame.mixer.Sound(sound_effect_path_yellow)

# Conecting serial
arduino = serial.Serial(port='/dev/ttyACM0', baudrate=115200, timeout=.1)
time.sleep(2)


def write_read(x):
    arduino.write(bytes(x, 'utf-8'))
    time.sleep(0.05)
    data = arduino.readline()
    return data


run = True

while run:
    sound = arduino.readline().decode('utf-8').strip()
    if sound == "fail":
        sound_effect_fail.play()
    elif sound == "green":
        sound_effect_green.play()
    elif sound == "red":
        sound_effect_red.play()
    elif sound == "blue":
        sound_effect_blue.play()
    elif sound == "yellow":
        sound_effect_yellow.play()
    for event in pygame.event.get():
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_q:
                write_read("1")
            elif event.key == pygame.K_w:
                write_read("2")
            elif event.key == pygame.K_e:
                write_read("3")
            elif event.key == pygame.K_r:
                write_read("4")
            elif event.key == pygame.K_SPACE:
                write_read("9")
            elif event.key == pygame.K_x:
                run = False

