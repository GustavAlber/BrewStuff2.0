float ringBuffer[RINGBUFFERSIZE] = {0};
int bufferLocation = 0;

float getAverageTemp(void){
  float av = 0;
  for (int i = 0; i<RINGBUFFERSIZE; i++){
    av += ringBuffer[i];
  }
  return av/RINGBUFFERSIZE;
}

void initRingBuffer(void){
  for (int i = 0; i<RINGBUFFERSIZE; i++){
    ringBuffer[i] = messungTermperatur();
    delay(100);
  }
}

void takeMeasurement(void){
  if(bufferLocation == RINGBUFFERSIZE){
    bufferLocation = 0;
  }
  ringBuffer[bufferLocation] = messungTermperatur();
  bufferLocation++;
}
#ifdef logging
void printRingbuffer(void){
  Serial.print("ringBuffer{");
  for (int i = 0; i<RINGBUFFERSIZE; i++){
    Serial.print(ringBuffer[i]);
    Serial.print(",");
  }
  Serial.println("}");
}
#endif
