#include "PluginProcessor.h"
#include "PluginEditor.h"
using namespace juce;


NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor(NewProjectAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    setSize(650, 380);
    button.setLookAndFeel(&buttonLookAndFeel);

    addAndMakeVisible(button);
    button.onClick = [this]() { off(); };
    button.setSize(getWidth() / 10, getHeight() / 12);

    addAndMakeVisible(sliderDelayMs);
    sliderDelayMs.setRange(0.0f, 1.0f);
    sliderDelayMs.setValue(0.0f);
    sliderDelayMs.setTextBoxStyle(Slider::TextBoxBelow, 0, 100, 20);
    sliderDelayMs.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    sliderDelayMs.addListener(this);


    addAndMakeVisible(sliderFeedback);
    sliderFeedback.setRange(0.0f, 1.0f);
    sliderFeedback.setValue(0.0f);
    sliderFeedback.setTextBoxStyle(Slider::TextBoxBelow, 0, 100, 20);
    sliderFeedback.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    sliderFeedback.addListener(this);

    addAndMakeVisible(sliderVolume);
    sliderVolume.setRange(0.0, 2.0);
    sliderVolume.setValue(1.0);
    sliderVolume.setTextBoxStyle(Slider::TextBoxBelow, 0, 100, 20);
    sliderVolume.setSliderStyle(Slider::SliderStyle::LinearVertical);
    sliderVolume.addListener(this);

    addAndMakeVisible(sliderDistortion);
    sliderDistortion.setRange(0.07f, 1.0f);
    sliderDistortion.setValue(1.0f);
    sliderDistortion.setTextBoxStyle(Slider::TextBoxBelow, 0, 100, 20);
    sliderDistortion.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    sliderDistortion.addListener(this);

    addAndMakeVisible(sliderBlend);
    sliderBlend.setRange(0.0f, 1.0f);
    sliderBlend.setValue(1.0f);
    sliderBlend.setTextBoxStyle(Slider::TextBoxBelow, 0, 100, 20);
    sliderBlend.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    sliderBlend.addListener(this);

    addAndMakeVisible(delayLabel);
    delayLabel.setText("Delay", dontSendNotification);

    addAndMakeVisible(volumeLabel);
    volumeLabel.setText("Volume", dontSendNotification);

    addAndMakeVisible(feedbackLabel);
    feedbackLabel.setText("Feedback", dontSendNotification);

    addAndMakeVisible(distortionLabel);
    distortionLabel.setText("Distortion", dontSendNotification);

    addAndMakeVisible(blendLabel);
    blendLabel.setText("Blend", dontSendNotification);

    addAndMakeVisible(styleMenu);
    styleMenu.addItem("Delay", 1);
    styleMenu.addItem("Distortion", 2);
    styleMenu.addItem("Delay + Distortion", 3);
    styleMenu.onChange = [this] { styleMenuChanged(); };
    styleMenu.setSelectedId(1);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{

}

//==============================================================================
void NewProjectAudioProcessorEditor::paint(Graphics& g)
{
    g.fillAll(Colour(132, 176, 131));
}


void NewProjectAudioProcessorEditor::resized()
{
    int sliderWidth = getWidth() / 1.8;
    int sliderHeight = getHeight() / 2.2;
    int labelSize = 20;


    button.setBounds(getWidth() / 2 - 150, getHeight() / 20 - 10, getWidth() / 5, getHeight() / 12);
    button.setColour(TextButton::buttonColourId, Colour(50, 71, 50));

    sliderDelayMs.setBounds(getWidth() / 1.9, getHeight() / 2 - sliderHeight - 25, sliderWidth, sliderHeight);
    delayLabel.setBounds(getWidth() / 1.45 + labelSize * 2 + 9, getHeight() / 1.5 - sliderHeight - 25, sliderWidth - labelSize, sliderHeight - labelSize);

    sliderFeedback.setBounds(getWidth() / 1.9, getHeight() / 7 + sliderHeight - 40, sliderWidth, sliderHeight);
    feedbackLabel.setBounds(getWidth() / 1.9 + 145, getHeight() / 7 + sliderHeight + 25, sliderWidth - labelSize, sliderHeight - labelSize);

    sliderVolume.setBounds(getWidth() / 2, getHeight() / 8 - 40, 80, 330);
    volumeLabel.setBounds(getWidth() / 2.5 + labelSize + 60, getHeight() / 5 + labelSize * 9 - 10, 50, 200);

    sliderDistortion.setBounds(getWidth() / 2 - 410, getHeight() / 3 - 10, sliderWidth - 9, sliderHeight - 5);
    distortionLabel.setBounds(getWidth() / 2 - 110, getHeight() / 3 + 80, sliderWidth - 9, sliderHeight - 5);

    sliderBlend.setBounds(getWidth() / 2 - 250, getHeight() / 3 - 10, sliderWidth - 9, sliderHeight - 5);
    blendLabel.setBounds(getWidth() / 2 - 250 - 15, getHeight() / 3 + 80, sliderWidth - 9, sliderHeight - 5);

    styleMenu.setBounds(getWidth() / 35, getHeight() / 20 - 10, getWidth() / 5, getHeight() / 12);
    styleMenu.setColour(ComboBox::backgroundColourId, Colour(50, 71, 50));
}

void NewProjectAudioProcessorEditor::sliderValueChanged(Slider* slider) {
    if (slider == &sliderDelayMs) {
        audioProcessor.changeDelayMs = sliderDelayMs.getValue();
    }
    if (slider == &sliderFeedback) {
        audioProcessor.changeFeedback = sliderFeedback.getValue();
    }
    if (slider == &sliderVolume) {
        audioProcessor.changeVolume = sliderVolume.getValue();
    }
    if (slider == &sliderDistortion) {
        audioProcessor.changeDistortion = sliderDistortion.getValue();
    }
    if (slider == &sliderBlend) {
        audioProcessor.changeBlend = sliderBlend.getValue();
    }
}

void NewProjectAudioProcessorEditor::off() {
    audioProcessor.changeDelayMs = 0.0f;
    sliderDelayMs.setValue(0.0f);
    audioProcessor.changeFeedback = 0.0f;
    sliderFeedback.setValue(0.0f);
    audioProcessor.changeVolume = 1.0;
    sliderVolume.setValue(1.0);
    audioProcessor.changeDistortion = 1.0;
    sliderDistortion.setValue(1.0);
    audioProcessor.changeBlend = 1.0;
    sliderBlend.setValue(1.0);
}

void NewProjectAudioProcessorEditor::styleMenuChanged()
{
    switch (styleMenu.getSelectedId())
    {
    case 1: addAndMakeVisible(sliderDelayMs);
        addAndMakeVisible(delayLabel);
        addAndMakeVisible(sliderFeedback);
        addAndMakeVisible(feedbackLabel);
        off();
        removeChildComponent(&sliderDistortion);
        removeChildComponent(&sliderBlend);
        removeChildComponent(&distortionLabel);
        removeChildComponent(&blendLabel);
        break;
    case 2: addAndMakeVisible(sliderDistortion);
        addAndMakeVisible(sliderBlend);
        addAndMakeVisible(distortionLabel);
        addAndMakeVisible(blendLabel);
        off();
        removeChildComponent(&sliderDelayMs);
        removeChildComponent(&delayLabel);
        removeChildComponent(&sliderFeedback);
        removeChildComponent(&feedbackLabel);
        break;
    case 3: addAndMakeVisible(sliderDelayMs);
        addAndMakeVisible(delayLabel);
        addAndMakeVisible(sliderFeedback);
        addAndMakeVisible(feedbackLabel);
        addAndMakeVisible(sliderDistortion);
        addAndMakeVisible(sliderBlend);
        addAndMakeVisible(distortionLabel);
        addAndMakeVisible(blendLabel);
        off();
        break;
    default: break;
    }
}
