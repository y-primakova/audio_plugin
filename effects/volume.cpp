
void volume(vector<float>& buffer, double changeVolume) {
    changeVolume /= 50;
    for (int sample = 0; sample < buffer.size(); sample++) {
        buffer[sample] *= changeVolume;
    }
}
