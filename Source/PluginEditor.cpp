#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SettingsDialog.h"


NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor(NewProjectAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{   
    backgroundImage = juce::ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);
    setSize(650, 380);
   // button.setLookAndFeel(&buttonLookAndFeel);
    auto fontData = juce::Typeface::createSystemTypefaceFor(BinaryData::SfOuterLimits_ttf,
        BinaryData::SfOuterLimits_ttfSize);
    customFont = juce::Font(fontData);
    customFont.setHeight(14.0f);

    //addAndMakeVisible(button);
    button.onClick = [this]() { off(); };
    button.setSize(getWidth() / 10, getHeight() / 12);

    addAndMakeVisible(sliderDelayMs);
    sliderDelayMs.setLookAndFeel(&customLookAndFeel);
    sliderDelayMs.setTextBoxStyle(juce::Slider::TextBoxBelow, 0, 100, 20);
    sliderDelayMs.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    sliderDelayMs.addListener(this);


    addAndMakeVisible(sliderFeedback);
    sliderFeedback.setLookAndFeel(&customLookAndFeel);
    sliderFeedback.setTextBoxStyle(juce::Slider::TextBoxBelow, 0, 100, 20);
    sliderFeedback.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    sliderFeedback.addListener(this);

    addAndMakeVisible(sliderVolume);
    sliderVolume.setLookAndFeel(&customLookAndFeel);
    sliderVolume.setTextBoxStyle(juce::Slider::TextBoxBelow, 0, 100, 20);
    sliderVolume.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    sliderVolume.addListener(this);

    addAndMakeVisible(sliderDistortion);
    sliderDistortion.setLookAndFeel(&customLookAndFeel);
    sliderDistortion.setTextBoxStyle(juce::Slider::TextBoxBelow, 0, 100, 20);
    sliderDistortion.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    sliderDistortion.addListener(this);

    addAndMakeVisible(sliderBlend);
    sliderBlend.setLookAndFeel(&customLookAndFeel);
    sliderBlend.setTextBoxStyle(juce::Slider::TextBoxBelow, 0, 100, 20);
    sliderBlend.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    sliderBlend.addListener(this);

    addAndMakeVisible(delayLabel);
    delayLabel.setText("DELAY", juce::dontSendNotification);
    delayLabel.setFont(customFont);
    
    addAndMakeVisible(volumeLabel);
    volumeLabel.setText("VOLUME", juce::dontSendNotification);
    volumeLabel.setFont(customFont);

    addAndMakeVisible(feedbackLabel);
    feedbackLabel.setText("FEEDBACK", juce::dontSendNotification);
    feedbackLabel.setFont(customFont);

    addAndMakeVisible(distortionLabel);
    distortionLabel.setText("DISTORTION", juce::dontSendNotification);
    distortionLabel.setFont(customFont);

    addAndMakeVisible(blendLabel);
    blendLabel.setText("BLEND", juce::dontSendNotification);
    blendLabel.setFont(customFont);


    settingsButton.setImages(false, true, true,
        juce::ImageCache::getFromMemory(BinaryData::setting_png,
            BinaryData::setting_pngSize), 1.0f,
        juce::Colours::transparentBlack,
        juce::ImageCache::getFromMemory(BinaryData::setting_png, BinaryData::setting_pngSize),
        1.0f, juce::Colours::transparentBlack,
        juce::ImageCache::getFromMemory(BinaryData::setting_png, BinaryData::setting_pngSize),
        1.0f, juce::Colours::transparentBlack);
    addAndMakeVisible(settingsButton);
    settingsButton.onClick = [this] {openSettings(&settingsButton); };

    //addAndMakeVisible(styleMenu);

    addAndMakeVisible(styleMenu);
    styleMenu.addItem("Settings", 1);
    styleMenu.addItem("Change your theme", 2);
    styleMenu.onChange = [this] { styleMenuChanged(); };
    styleMenu.setSelectedId(1);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
    
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint(juce::Graphics& g)
{
    //g.fillAll(juce::Colour(115, 98, 99));
    g.drawImageAt(backgroundImage, 0, 0);

    g.setColour(juce::Colour(205, 192, 207));
    int radius = getWidth() / 8.3;
    g.fillEllipse(getWidth() / 19 + radius, getHeight() / 4.2 - radius, radius * 2, radius * 2);

    g.setColour(juce::Colour(205, 192, 207));
    int radius1 = getWidth() / 8.3;
    g.fillEllipse(getWidth() / 2.09 + radius1, getHeight() / 4.2 - radius1, radius1 * 2, radius1 * 2);

    g.setColour(juce::Colour(205, 192, 207));
    int radius2 = getWidth() / 8.1;
    g.fillEllipse(getWidth() / 2 + getWidth() / 10.5 + radius2, getHeight() / 3.75 + radius2, radius2 * 2, radius2 * 2);

    g.setColour(juce::Colour(205, 192, 207));
    int radius3 = getWidth() / 8.1;
    g.fillEllipse(getWidth() / 6.3 - radius3, getHeight() / 13 + getHeight() / 5.2 + radius3, radius3 * 2, radius3 * 2);

    g.setColour(juce::Colour(170, 157, 171));
    int radius4 = getWidth() / 9.1;
    g.fillEllipse(getWidth() /2 - getHeight()/5.9, getHeight() / 6.6 + radius4, radius4 * 2, radius4 * 2);

}
    

void NewProjectAudioProcessorEditor::resized()
{
    int sliderWidth = getWidth() / 1.8;
    int sliderHeight = getHeight() / 2.2;
    int labelSize = 20;
  

    //button.setBounds(getWidth() / 2 - 150, getHeight() / 20 - 10, getWidth() / 5, getHeight() / 12);
    //button.setColour(juce::TextButton::buttonColourId, juce::Colour(50, 71, 50));

    sliderDelayMs.setBounds(getWidth() / 20 - getWidth()/6, getHeight() / 7 + sliderHeight - 40, sliderWidth, sliderHeight);
    sliderDelayMs.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    delayLabel.setBounds(getWidth() / 20 + labelSize * 2, getHeight() / 7 + sliderHeight + labelSize, sliderWidth - labelSize, sliderHeight - labelSize);

    sliderFeedback.setBounds(getWidth()/2 + getWidth() / 15, getHeight() / 7 + sliderHeight - 40, sliderWidth, sliderHeight);
    sliderFeedback.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    feedbackLabel.setBounds(getWidth()/2 + getWidth()/3.8, getHeight() / 7 + sliderHeight + labelSize, sliderWidth - labelSize, sliderHeight - labelSize);

    sliderVolume.setBounds(getWidth() / 2 - getWidth()/15 - sliderWidth/3, getHeight() / 5 + sliderHeight/3, sliderWidth - sliderWidth/20, sliderHeight - sliderWidth / 20);
    sliderVolume.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 150, 50);
    volumeLabel.setBounds(getWidth() / 2 - getWidth()/21, getHeight() / 5 + sliderHeight / 3 + labelSize, 100, 200);

    sliderDistortion.setBounds(getWidth()/2 - getWidth()/20, getHeight() / 2 - sliderHeight, sliderWidth - 9, sliderHeight - 5);
    distortionLabel.setBounds(getWidth()/2 + getWidth()/6.8, getHeight() / 2 - sliderHeight + 4*labelSize, 100, 100);

    sliderBlend.setBounds(getWidth()/20 - getWidth()/40, getHeight() / 2 - sliderHeight, sliderWidth - 9, sliderHeight - 5);
    blendLabel.setBounds(getWidth()/20 + getWidth()/5, getHeight() / 2 - sliderHeight + 2.2*labelSize, sliderWidth - 9, sliderHeight - 5);
    
    //styleMenu.setBounds(getWidth() / 45, getHeight() / 20 - 10, getWidth() / 6, getHeight() / 12);
    //styleMenu.setColour(juce::ComboBox::backgroundColourId, juce::Colour(239, 233, 240));
    //styleMenu.setColour(juce::ComboBox::textColourId, juce::Colour(144, 128, 145));

    int settingsHeight = 30;
    int settingsWidth = 30;
    settingsButton.setBounds(getWidth() / 45, getHeight() / 20, settingsWidth, settingsHeight);

}

void NewProjectAudioProcessorEditor::sliderValueChanged(juce::Slider* slider) {
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

void NewProjectAudioProcessorEditor::openSettings(juce::Button* button)
{
    if (button == &settingsButton)
    {
        juce::PopupMenu settingsMenu;
        settingsMenu.setLookAndFeel(&customLookAndFeel);

       /*juce::PopupMenu::Options options;
        options.withMinimumWidth(500)  // Минимальная ширина каждого элемента меню
            .withMaximumNumColumns(1)
            .withStandardItemHeight(80);*/

        juce::PopupMenu themeSubMenu;
        themeSubMenu.setLookAndFeel(&customLookAndFeel);

        juce::Image catIcon = juce::ImageCache::getFromMemory(BinaryData::catIcon_png, BinaryData::catIcon_pngSize);
        juce::Image minionIcon = juce::ImageCache::getFromMemory(BinaryData::minionIcon_png, BinaryData::minionIcon_pngSize);
        // Добавляем опции тем в подменю с "иконками" в виде эмодзи
        themeSubMenu.addItem(101, "cats theme", true, false, catIcon);
        themeSubMenu.addItem(102, "minions theme", true, false, minionIcon);

        // Добавляем подменю к основному меню "Интерфейс"
        settingsMenu.addSubMenu("theme settings", themeSubMenu);
        settingsMenu.addItem(2, "effects settings");

        juce::PopupMenu::Options options;
        options = options.withMinimumWidth(200).withStandardItemHeight(80).withTargetComponent(button);

        // Асинхронный вызов меню
        settingsMenu.showMenuAsync(options,
            [this](int result)
            {
                switch (result)
                {
                case 101:
                    juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::InfoIcon, "theme", "cats theme");
                    break;
                case 102:
                    juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::InfoIcon, "theme", "minions theme");
                    break;
                case 2:
                    juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::InfoIcon, "settings", "effects");
                    break;
                }
            });
    }
}


void NewProjectAudioProcessorEditor::styleMenuChanged()
{
    switch (styleMenu.getSelectedId())
    {
    case 1: addAndMakeVisible(sliderDelayMs);
            addAndMakeVisible(delayLabel);
            addAndMakeVisible(sliderFeedback);
            addAndMakeVisible(feedbackLabel);
            addAndMakeVisible(sliderDistortion);
            addAndMakeVisible(sliderBlend);
            addAndMakeVisible(distortionLabel);
            addAndMakeVisible(blendLabel);
            off();
            break;
    case 2:
            break;
    default: break;
    }
}
