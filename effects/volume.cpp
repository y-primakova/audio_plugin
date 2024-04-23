
void volume(vector<float>& buffer, double changeVolume) {
    for (int sample = 0; sample < buffer.size(); sample++) {
        buffer[sample] *= changeVolume;
    }
}
