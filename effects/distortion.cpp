
float distortion(float sample, double changeDistortion, double changeBlend) {
    float x;
    x = sample / changeDistortion;
    x = 2.0f / M_PI * atan(x) * changeBlend + x * (1.0f - changeBlend);
    if (x > 1) {
        x = 1;
    }
    if (x < (-1)) {
        x = (-1);
    }
    x *= changeDistortion;
    return x;
}
