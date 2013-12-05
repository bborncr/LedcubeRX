void paintUp(){
  for(int i=0; i<4; i++){
    matrix[i]=0b1111111111111111;
    delay(200);
  }
}
void paintDown(){
  for(int i=4; i-- >0;){
    matrix[i]=0b1111111111111111;
    delay(200);
  }
}
void eraseUp(){
  for(int i=0; i<4; i++){
    matrix[i]=0b0000000000000000;
    delay(200);
  }
}
void eraseDown(){
  for(int i=4; i-- >0;){
    matrix[i]=0b0000000000000000;
    delay(200);
  }
}
void fillUp(){
  for(int j=0; j<4; j++){
    matrix[j]=matrix[j]|0b0001;
    delay(100);
    for(int i=0; i<16; i++){
      matrix[j]=matrix[j]<<1;
      matrix[j]=matrix[j]|0b0001;
      delay(100);
    }
  }
}

