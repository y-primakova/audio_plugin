/*
float* delay(float* buffer, float* delayBuffer, int channel, double changeDelayMs, double changeFeedback, 
             int writePosition, int bufferSize, int delayBufferSize, double sample) {
    fillBuff(buffer, delayBuffer, channel, writePosition, bufferSize, delayBufferSize);
    readFromBuff(buffer, delayBuffer, channel, changeDelayMs, changeFeedback, writePosition, bufferSize, delayBufferSize, sample);
    fillBuff(buffer, delayBuffer, channel, writePosition, bufferSize, delayBufferSize);
    return delayBuffer;
}
*/

float* fillBuff(float* buffer, float* delayBuffer, int channel, int writePosition, int bufferSize, int delayBufferSize) {
    if (delayBufferSize > bufferSize + writePosition) {
        delayBuffer += writePosition;
        for (int i = 0; i < bufferSize; i++) {
            delayBuffer[channel + i] = buffer[i];
        }
    }
    else {
        int numSamplesToEnd = delayBufferSize - writePosition;
        delayBuffer += writePosition;
        for (int i = 0; i < numSamplesToEnd; i++) {
            delayBuffer[channel + i] = buffer[i];
        }

        int numSamplesAtStart = bufferSize - numSamplesToEnd;
        float* b = buffer + numSamplesToEnd;
        for (int i = 0; i < numSamplesAtStart; i++) {
            delayBuffer[channel + i] = b[i];
        }
    }
    return delayBuffer;
}

void readFromBuff(float* buffer, float* delayBuffer, int channel, double changeDelayMs, double changeFeedback,
                    int writePosition, int bufferSize, int delayBufferSize, double sample) {

    int readPosition = writePosition - (sample * changeDelayMs);

    if (readPosition < 0) {
        readPosition += delayBufferSize;
    }

    if (readPosition + bufferSize < delayBufferSize) {
        float* d = buffer;
        float* b = delayBuffer + readPosition;
        for (int i = 0; i < bufferSize; i++) {
            d[channel + i] = b[i] * changeFeedback;
        }   
    }
    else {
        int numSamplesToEnd = delayBufferSize - readPosition;
        float* d = buffer;
        float* b = delayBuffer + readPosition;
        for (int i = 0; i < numSamplesToEnd; i++) {
            d[channel + i] = b[i] * changeFeedback;
        }
        
        int numSamplesAtStart = bufferSize - numSamplesToEnd;
        for (int i = 0; i < numSamplesAtStart; i++) {
            d[channel + i] = b[i] * changeFeedback;
        }
    }
}

int updateBuffPositions(int writePosition, int bufferSize, int delayBufferSize) {
    writePosition += bufferSize;
    writePosition %= delayBufferSize;
    return writePosition;
}