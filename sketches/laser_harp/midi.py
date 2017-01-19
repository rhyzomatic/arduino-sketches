import pygame.midi
import time

pygame.midi.init()
midiOut = pygame.midi.Output(0)

print(pygame.midi.get_default_output_id())
print(pygame.midi.get_device_info(0))

midiOut.set_instrument(0)

for instrument in range(46, 88):
    midiOut.set_instrument(instrument)
    print(instrument)
    midiOut.note_on(50 + instrument%40, 127)
    time.sleep(5)
    midiOut.note_off(50 + instrument%40, 127)
    time.sleep(0.1)



midiOut.close()