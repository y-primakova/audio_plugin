
void calculateCoefficientsLp(double sampleRate, double cutoffFrequency, double& b0, double& b1, double& a1) {
    double thetaC = 2.0 * M_PI * cutoffFrequency / sampleRate;
    double gamma = sin(thetaC) / (1.0 + cos(thetaC));
    b0 = gamma / 2.0;
    b1 = gamma / 2.0;
    a1 = gamma - 1.0;
}

void processLp(std::vector<float>& buffer, double sampleRate, double cutoffFrequency, double& prevInput, double& prevOutput) {
    cutoffFrequency = (100 - cutoffFrequency) * 100 + 1000;
    double b0, b1, a1;
    calculateCoefficientsLp(sampleRate, cutoffFrequency, b0, b1, a1);
    for (auto& sample : buffer) {
        double filteredSample = b0 * sample + b1 * prevInput - a1 * prevOutput;
        prevInput = sample;
        sample = filteredSample;
        prevOutput = filteredSample;
    }
}
