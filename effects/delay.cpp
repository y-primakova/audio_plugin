
void fill(std::vector<float>& buffer, std::vector<float>& delayBuffer, int writePosition) {
    if (delayBuffer.size() > buffer.size() + writePosition) {
        for (int sample = 0; sample < buffer.size(); sample++) {
            delayBuffer[writePosition + sample] = buffer[sample];
        }
    }
    else {
        auto numSamplesToEnd = delayBuffer.size() - writePosition;
        for (int sample = 0; sample < numSamplesToEnd; sample++) {
            delayBuffer[writePosition + sample] = buffer[sample];
        }

        auto numSamplesAtStart = buffer.size() - numSamplesToEnd;
        for (int sample = 0; sample < numSamplesAtStart; sample++) {
            delayBuffer[sample] = buffer[numSamplesToEnd + sample];
        }
    }
}

void read(std::vector<float>& buffer, std::vector<float>& delayBuffer, double changeDelayMs, double changeFeedback, double sampleRate, int writePosition) {
    int readPosition = writePosition - (sampleRate * changeDelayMs);

    if (readPosition < 0) {
        readPosition += delayBuffer.size();
    }

    if (readPosition + buffer.size() < delayBuffer.size()) {
        if (buffer.size() > 0 && changeFeedback != 0) {
            for (int sample = 0; sample < buffer.size(); sample++) {
                buffer[sample] += delayBuffer[readPosition + sample] * changeFeedback;
            }
        }
    }
    else {
        int numSamplesToEnd = delayBuffer.size() - readPosition;
        if (numSamplesToEnd > 0 && changeFeedback != 0) {
            for (int sample = 0; sample < numSamplesToEnd; sample++) {
                buffer[sample] += delayBuffer[readPosition + sample] * changeFeedback;
            }
        }
        int numSamplesAtStart = buffer.size() - numSamplesToEnd;
        if (numSamplesToEnd >= 0 && numSamplesAtStart > 0 && changeFeedback != 0) {
            for (int sample = 0; sample < numSamplesAtStart; sample++) {
                if (sample == delayBuffer.size()) break;
                buffer[numSamplesToEnd + sample] += delayBuffer[sample] * changeFeedback;
            }
        }
    }
}

int update(int bufferSize, int delayBufferSize, int writePosition) {
    writePosition += bufferSize;
    writePosition %= delayBufferSize;
    return writePosition;
}

void delay(std::vector<float>& buffer, std::vector<float>& delayBuffer, double changeDelayMs, double changeFeedback, double sampleRate, int writePosition) {
    fill(buffer, delayBuffer, writePosition);
    read(buffer, delayBuffer, changeDelayMs, changeFeedback, sampleRate, writePosition);
    fill(buffer, delayBuffer, writePosition);
}
