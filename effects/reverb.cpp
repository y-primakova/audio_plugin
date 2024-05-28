
void process(vector<float>& buffer, int& delayIndex, vector<float>& delayBuffer, double feedback, double delayTime, double mix, double sampleRate) {
    auto numSamples = buffer.size();
    int delaySamples = static_cast<int>(delayTime * sampleRate);

    for (int sample = 0; sample < numSamples; sample++) {
        auto in = buffer[sample];
        auto out = delayBuffer[delayIndex];
        buffer[sample] = in * (1.0 - mix) + out * mix;
        buffer[sample] = max(-1.0f, min(1.0f, buffer[sample]));
        delayBuffer[delayIndex] = in * feedback;
        delayIndex++;
        delayIndex %= delaySamples;
    }
}
