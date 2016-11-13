int mic_pin = 0;
int mic_reading;

const int num_reads = 1200;

char sound_array[num_reads/4 * 5] = {'\x00'};

int sound_array_len = num_reads/4 * 5;

int spillover = 0;
int cur_byte;
int b;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(99999);
  delay(500);
  cur_byte = 0;
  while(cur_byte < sound_array_len){
    for (b = 0; b < 4; b++){
      mic_reading = analogRead(mic_pin); // 10 bits wide
      sound_array[cur_byte] += (char) (mic_reading << spillover);
      spillover = (spillover + 10) % 8;
      cur_byte++;
      sound_array[cur_byte] += (char) (mic_reading >> (10 - spillover));
      delayMicroseconds(40);
    } 
  }
  Serial.write(sound_array, sound_array_len);
}

void loop() {
  // put your main code here, to run repeatedly:
}
