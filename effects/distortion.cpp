
void distortion(vector<float>& buffer, double changeDistortion, double changeBlend) {
    for (int sample = 0; sample < buffer.size(); sample++) {
        buffer[sample] = buffer[sample] / changeDistortion;
        buffer[sample] = 2.0f / M_PI * atan(buffer[sample]) * changeBlend + buffer[sample] * (1.0f - changeBlend);
        if (buffer[sample] > 1) {
            buffer[sample] = 1;
        }
        if (buffer[sample] < (-1)) {
            buffer[sample] = (-1);
        }
    }
}
