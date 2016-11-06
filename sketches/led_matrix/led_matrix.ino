#include <assert.h>

int row_pins[8] = {A4, A5, 0, A1, 7, 1, 6, 3};
int col_pins[8] = {A0, 5, 4, A3, 2, A2, 12, 13};
long led_time = 20; //time in microseconds to turn led on

bool matrix[8][8] = {{false}};
bool row_pin_high[8] = {false};
bool col_pin_high[8] = {false};

void empty_matrix(){
  for (int i = 0; i < 8; i++){
    for (int j = 0; j < 8; j++){
      matrix[i][j] = false;
    }
  }
}

void light_row(int row){
  for (int j = 0; j < 8; j++){
    matrix[row][j] |= true;
  }
}

void light_col(int col){
  for (int i = 0; i < 8; i++){
    matrix[i][col] |= true;
  }
}

void light_dot(int row, int col){
  matrix[row][col] |= true;
}

void light_symmetric_col(int row, int col){
  matrix[row][col] |= true;
  matrix[row][7-col] |= true;
}

void light_matrix(int time_delay){
  long td = time_delay * 1000L;
  while (td > 0){
    for (int i = 0; i < 8; i++){
      digitalWrite(row_pins[i], HIGH);
      for (int j = 0; j < 8; j++){
        if (matrix[i][j]){
          digitalWrite(col_pins[j], LOW);
        }
        delayMicroseconds(led_time);
        td -= led_time;
        if (matrix[i][j]){
          digitalWrite(col_pins[j], HIGH);
        }
      }
      digitalWrite(row_pins[i], LOW);
    }
  }
  empty_matrix();
}


void setup() {
  // put your setup code here, to run once:
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);

  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  for (int i = 0; i < 8; i++){
    digitalWrite(col_pins[i], HIGH);
  }
}

void draw_heart(){
  light_symmetric_col(2, 3);
  light_symmetric_col(1, 2);
  light_symmetric_col(1, 1);
  light_symmetric_col(2, 0);
  light_symmetric_col(3, 0);
  light_symmetric_col(4, 1);
  light_symmetric_col(5, 2);
  light_symmetric_col(6, 3);
}

void draw_line(int start_i, int start_j, int rot, int len){
  int hor_delta = 0;
  int ver_delta = 0;
  if ((rot == 0) | (rot == 4)){
    hor_delta = 0;
  }
  else if (rot < 4){
    hor_delta = 1;
  }
  else {
    hor_delta = -1;
  }
  
  if ((rot == 2) | (rot == 6)){
    ver_delta = 0;
  }
  else if ((rot > 6) | (rot < 2)){
    ver_delta = -1;
  }
  else {
    ver_delta = 1;
  }

  int row = start_i;
  int col = start_j;
  for (int i = 0; i < len; i++){
      light_dot(row, col);
      row += ver_delta;
      col += hor_delta;
  }
}

void draw_i(){
  /*int rows[] = {0,1,6,7};
  int cols[] = {3,4};
  for (int i = 0; i < 4; i++){
    light_row(rows[i]);
  }
  for (int j = 0; j < 2; j++){
    light_col(cols[j]);
  }*/

  draw_line(0, 3, 4, 7);
  draw_line(0, 4, 4, 7);
}

void draw_u(){
  draw_line(0, 1, 4, 6);
  draw_line(6, 2, 2, 4);
  draw_line(5, 6, 0, 6);
}

/*
void draw_u(){
  for (int row = 0; row < 6; row++){
    for (int col = 
  }
}*/

void loop() {
  // put your main code here, to run repeatedly:
  draw_i();
  light_matrix(2000);
  //matrix[0][0] = true;
  draw_heart();
  //empty_matrix();
  light_matrix(2000);
  draw_u();
  light_matrix(2000);
}
