
void calculateCoefficientsHp(double sampleRate, double cutoffFrequency, double& b0, double& b1, double& a1) {
    double thetaC = 2.0 * M_PI * cutoffFrequency / sampleRate;
    double gamma = cos(thetaC) / (1.0 + sin(thetaC));
    b0 = (1.0 + gamma) / 2.0;
    b1 = -(1.0 + gamma) / 2.0;
    a1 = -gamma;
}

void processHp(std::vector<float>& buffer, double sampleRate, double cutoffFrequency, double& prevInput, double& prevOutput) {
    cutoffFrequency = cutoffFrequency * 5 + 20;
    double b0, b1, a1;
    calculateCoefficientsHp(sampleRate, cutoffFrequency, b0, b1, a1);
    for (auto& sample : buffer) {
        double filteredSample = b0 * sample + b1 * prevInput - a1 * prevOutput;
        prevInput = sample;
        sample = filteredSample;
        prevOutput = filteredSample;
    }
}  
