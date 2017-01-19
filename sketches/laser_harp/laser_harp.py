import serial
import pygame.midi

connected = False

ser = serial.Serial("COM3", 9600)

serial_char = 0 # variable that holds the most recent read from serial

mask = 255
test = 0

class Piano:
    global test
    def __init__(self, notes = (60, 62, 64, 65, 67, 69), instrument = 46):
        self.num_notes = len(notes)
        self.notes = notes
        self.note_state_int = 0

        pygame.midi.init()
        self.midi_out = pygame.midi.Output(0)

        for note in range(self.num_notes):
            self.midi_out.set_instrument(instrument, note)

    def set_state(self, new_state_int):
        global test
        diff = self.note_state_int ^ new_state_int
        if (diff) != 0:
            print("new state", new_state_int)
            for note_index in range(self.num_notes):
                if (new_state_int & (1 << note_index)) & (self.note_state_int ^ mask):
                    self.midi_out.note_on(self.notes[note_index], 127, note_index)
                    test += 1
                    print(test)
                elif (self.note_state_int & (1 << note_index)) & (new_state_int ^ mask):
                    self.midi_out.note_off(self.notes[note_index], 127, note_index)

            self.note_state_int = new_state_int

piano = Piano(instrument = 82)

while True:
    serial_val = ord(ser.read())
    piano.set_state(serial_val)

