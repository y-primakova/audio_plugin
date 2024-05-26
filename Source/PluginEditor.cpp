#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SettingsDialog.h"


NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor(NewProjectAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{   
    backgroundImage = ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);
    setSize(650, 380);
   
    auto fontData = Typeface::createSystemTypefaceFor(BinaryData::SfOuterLimits_ttf,
        BinaryData::SfOuterLimits_ttfSize);
    customFont = Font(fontData);
    customFont.setHeight(14.0f);

    button.onClick = [this]() { off(); };
    button.setSize(getWidth() / 10, getHeight() / 12);

    addAndMakeVisible(sliderDelayMs);
    sliderDelayMs.setLookAndFeel(&customLookAndFeel);
    sliderDelayMs.setRange(0, 100, 1);
    sliderDelayMs.setTextBoxStyle(Slider::TextBoxBelow, 0, 100, 20);
    sliderDelayMs.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    sliderDelayMs.addListener(this);


    addAndMakeVisible(sliderFeedback);
    sliderFeedback.setLookAndFeel(&customLookAndFeel);
    sliderFeedback.setRange(0, 100, 1);
    sliderFeedback.setTextBoxStyle(Slider::TextBoxBelow, 0, 100, 20);
    sliderFeedback.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    sliderFeedback.addListener(this);

    addAndMakeVisible(sliderVolume);
    sliderVolume.setLookAndFeel(&customLookAndFeel);
    sliderVolume.setRange(0, 100, 1);
    sliderVolume.setTextBoxStyle(Slider::TextBoxBelow, 0, 100, 20);
    sliderVolume.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    sliderVolume.addListener(this);

    addAndMakeVisible(sliderDistortion);
    sliderDistortion.setLookAndFeel(&customLookAndFeel);
    sliderDistortion.setRange(0, 100, 1);
    sliderDistortion.setTextBoxStyle(Slider::TextBoxBelow, 0, 100, 20);
    sliderDistortion.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    sliderDistortion.addListener(this);

    addAndMakeVisible(sliderBlend);
    sliderBlend.setLookAndFeel(&customLookAndFeel);
    sliderBlend.setRange(0, 100, 1);
    sliderBlend.setTextBoxStyle(Slider::TextBoxBelow, 0, 100, 20);
    sliderBlend.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    sliderBlend.addListener(this);

    addAndMakeVisible(delayLabel);
    delayLabel.setText("DELAY", dontSendNotification);
    delayLabel.setFont(customFont);
    
    addAndMakeVisible(volumeLabel);
    volumeLabel.setText("VOLUME", dontSendNotification);
    volumeLabel.setFont(customFont);

    addAndMakeVisible(feedbackLabel);
    feedbackLabel.setText("FEEDBACK", dontSendNotification);
    feedbackLabel.setFont(customFont);

    addAndMakeVisible(distortionLabel);
    distortionLabel.setText("DISTORTION", dontSendNotification);
    distortionLabel.setFont(customFont);

    addAndMakeVisible(blendLabel);
    blendLabel.setText("BLEND", dontSendNotification);
    blendLabel.setFont(customFont);

    /*addAndMakeVisible(sliderReverb1);
    sliderDelayMs.setLookAndFeel(&customLookAndFeel);
    sliderDelayMs.setRange(0, 100, 1);
    sliderDelayMs.setTextBoxStyle(Slider::TextBoxBelow, 0, 100, 20);
    sliderDelayMs.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    sliderDelayMs.addListener(this);


    addAndMakeVisible(sliderReverb2);
    sliderFeedback.setLookAndFeel(&customLookAndFeel);
    sliderFeedback.setRange(0, 100, 1);
    sliderFeedback.setTextBoxStyle(Slider::TextBoxBelow, 0, 100, 20);
    sliderFeedback.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    sliderFeedback.addListener(this);

    addAndMakeVisible(sliderReverb3);
    sliderVolume.setLookAndFeel(&customLookAndFeel);
    sliderVolume.setRange(0, 100, 1);
    sliderVolume.setTextBoxStyle(Slider::TextBoxBelow, 0, 100, 20);
    sliderVolume.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    sliderVolume.addListener(this);

    addAndMakeVisible(sliderReverb4);
    sliderDistortion.setLookAndFeel(&customLookAndFeel);
    sliderDistortion.setRange(0, 100, 1);
    sliderDistortion.setTextBoxStyle(Slider::TextBoxBelow, 0, 100, 20);
    sliderDistortion.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    sliderDistortion.addListener(this);

    addAndMakeVisible(sliderReverb5);
    sliderBlend.setLookAndFeel(&customLookAndFeel);
    sliderBlend.setRange(0, 100, 1);
    sliderBlend.setTextBoxStyle(Slider::TextBoxBelow, 0, 100, 20);
    sliderBlend.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    sliderBlend.addListener(this);

    /*addAndMakeVisible(sliderReverb6);
    sliderBlend.setLookAndFeel(&customLookAndFeel);
    sliderBlend.setRange(0, 100, 1);
    sliderBlend.setTextBoxStyle(Slider::TextBoxBelow, 0, 100, 20);
    sliderBlend.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    sliderBlend.addListener(this);*/

   /* addAndMakeVisible(reverbLabel1);
    delayLabel.setText("reverbLabel1", dontSendNotification);
    delayLabel.setFont(customFont);

    addAndMakeVisible(reverbLabel2);
    volumeLabel.setText("reverbLabel2", dontSendNotification);
    volumeLabel.setFont(customFont);

    addAndMakeVisible(reverbLabel3);
    feedbackLabel.setText("reverbLabel3", dontSendNotification);
    feedbackLabel.setFont(customFont);

    addAndMakeVisible(reverbLabel4);
    distortionLabel.setText("reverbLabel4", dontSendNotification);
    distortionLabel.setFont(customFont);

    addAndMakeVisible(reverbLabel5);
    blendLabel.setText("reverbLabel5", dontSendNotification);
    blendLabel.setFont(customFont);*/

    /*addAndMakeVisible(reverbLabel6);
    blendLabel.setText("reverbLabel6", dontSendNotification);
    blendLabel.setFont(customFont);*/


    settingsButton.setImages(false, true, true,
        ImageCache::getFromMemory(BinaryData::setting_png,
            BinaryData::setting_pngSize), 1.0f,
        Colours::transparentBlack,
        ImageCache::getFromMemory(BinaryData::setting_png, BinaryData::setting_pngSize),
        1.0f, Colours::transparentBlack,
        ImageCache::getFromMemory(BinaryData::setting_png, BinaryData::setting_pngSize),
        1.0f, Colours::transparentBlack);
    addAndMakeVisible(settingsButton);
    settingsButton.onClick = [this] {openSettings(&settingsButton); };

    changeTheme(currentTheme);
    setEffect(currentEffect);

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
void NewProjectAudioProcessorEditor::paint(Graphics& g)
{
    g.drawImageAt(backgroundImage, 0, 0);

    g.setColour(Colour(205, 192, 207));
    int radius = getWidth() / 8.3;
    g.fillEllipse(getWidth() / 19 + radius, getHeight() / 4.2 - radius, radius * 2, radius * 2);

    g.setColour(Colour(205, 192, 207));
    int radius1 = getWidth() / 8.3;
    g.fillEllipse(getWidth() / 2.09 + radius1, getHeight() / 4.2 - radius1, radius1 * 2, radius1 * 2);

    g.setColour(Colour(205, 192, 207));
    int radius2 = getWidth() / 8.1;
    g.fillEllipse(getWidth() / 2 + getWidth() / 10.5 + radius2, getHeight() / 3.75 + radius2, radius2 * 2, radius2 * 2);

    g.setColour(Colour(205, 192, 207));
    int radius3 = getWidth() / 8.1;
    g.fillEllipse(getWidth() / 6.3 - radius3, getHeight() / 13 + getHeight() / 5.2 + radius3, radius3 * 2, radius3 * 2);

    g.setColour(Colour(205, 192, 207));
    int radius4 = getWidth() / 9.1;
    g.fillEllipse(getWidth() /2 - getHeight()/5.9, getHeight() / 6.6 + radius4, radius4 * 2, radius4 * 2);

}

void NewProjectAudioProcessorEditor :: setupSliderAndLabel(Slider& slider, Label& label, const String& componentID,
    int x, int y, int width, int height, int textBoxWidth, int labelHeight) 
{
    slider.setBounds(x, y, width, height);
    slider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, labelHeight);
    slider.setComponentID(componentID);
    if (componentID == "delaySlider") {
        label.setBounds(x + width / 2 - textBoxWidth / 2.7 + 2, y + height/2 + 2.2 *labelHeight, width, labelHeight);
    }
    else if (componentID == "feedbackSlider") {
        label.setBounds(x + width / 2 - textBoxWidth / 2.7 - 12, y + height/2 + 2.2 *labelHeight, width, labelHeight);
    }
    else if (componentID == "volumeSlider") {
        label.setBounds(x + width / 2 - textBoxWidth / 2.7 - 5, y + height / 2 + 2 * labelHeight, width, labelHeight);
    }
    else if (componentID == "distortionSlider") {
        label.setBounds(x + width / 2 - textBoxWidth / 2.7 - 15, y + height / 2 + 2.4 * labelHeight, width, labelHeight);
    }
    else if (componentID == "blendSlider") {
        label.setBounds(x + width / 2 - textBoxWidth / 2.7 + 2, y + height / 2 + 2.4 * labelHeight, width, labelHeight);
    }
    
}

void NewProjectAudioProcessorEditor::setEffect(const String& effectName)
{
    currentEffect = effectName;

    if (effectName == "reverb")
    {
        setupReverbEffects();
    }
    else if (effectName == "basic")
    {
        setupBasicEffects();
    }
}

void NewProjectAudioProcessorEditor::setupBasicEffects()
{
    // Remove reverb sliders
    sliderReverb1.setVisible(false);
    sliderReverb2.setVisible(false);
    sliderReverb3.setVisible(false);
    sliderReverb4.setVisible(false);
    sliderReverb5.setVisible(false);
    //sliderReverb6.setVisible(false);

    reverbLabel1.setVisible(false);
    reverbLabel2.setVisible(false);
    reverbLabel3.setVisible(false);
    reverbLabel4.setVisible(false);
    reverbLabel5.setVisible(false);
    //reverbLabel6.setVisible(false);

    // Show basic effect sliders
    sliderDelayMs.setVisible(true);
    sliderFeedback.setVisible(true);
    sliderVolume.setVisible(true);
    sliderDistortion.setVisible(true);
    sliderBlend.setVisible(true);

    // Show and set text for basic effect labels
    delayLabel.setVisible(true);
    delayLabel.setText("DELAY", dontSendNotification);

    feedbackLabel.setVisible(true);
    feedbackLabel.setText("FEEDBACK", dontSendNotification);

    volumeLabel.setVisible(true);
    volumeLabel.setText("VOLUME", dontSendNotification);

    distortionLabel.setVisible(true);
    distortionLabel.setText("DISTORTION", dontSendNotification);

    blendLabel.setVisible(true);
    blendLabel.setText("BLEND", dontSendNotification);

    resized();
}

void NewProjectAudioProcessorEditor::setupReverbEffects()
{
    sliderDelayMs.setVisible(false);
    sliderFeedback.setVisible(false);
    sliderVolume.setVisible(false);
    sliderDistortion.setVisible(false);
    sliderBlend.setVisible(false);

    delayLabel.setVisible(false);
    feedbackLabel.setVisible(false);
    volumeLabel.setVisible(false);
    distortionLabel.setVisible(false);
    blendLabel.setVisible(false);

    // Show reverb effect sliders and set them as rotary
    sliderReverb1.setVisible(true);
    sliderReverb1.setSliderStyle(Slider::RotaryVerticalDrag);
    sliderReverb1.setLookAndFeel(&customLookAndFeel);

    sliderReverb2.setVisible(true);
    sliderReverb2.setSliderStyle(Slider::RotaryVerticalDrag);
    sliderReverb2.setLookAndFeel(&customLookAndFeel);

    sliderReverb3.setVisible(true);
    sliderReverb3.setSliderStyle(Slider::RotaryVerticalDrag);
    sliderReverb3.setLookAndFeel(&customLookAndFeel);

    sliderReverb4.setVisible(true);
    sliderReverb4.setSliderStyle(Slider::RotaryVerticalDrag);
    sliderReverb4.setLookAndFeel(&customLookAndFeel);

    sliderReverb5.setVisible(true);
    sliderReverb5.setSliderStyle(Slider::RotaryVerticalDrag);
    sliderReverb5.setLookAndFeel(&customLookAndFeel);

    sliderReverb6.setVisible(true);
    sliderReverb6.setSliderStyle(Slider::RotaryVerticalDrag);
    sliderReverb6.setLookAndFeel(&customLookAndFeel);

    // Show and set text for reverb effect labels
    reverbLabel1.setVisible(true);
    reverbLabel1.setText("REVERB 1", dontSendNotification);

    reverbLabel2.setVisible(true);
    reverbLabel2.setText("REVERB 2", dontSendNotification);

    reverbLabel3.setVisible(true);
    reverbLabel3.setText("REVERB 3", dontSendNotification);

    reverbLabel4.setVisible(true);
    reverbLabel4.setText("REVERB 4", dontSendNotification);

    reverbLabel5.setVisible(true);
    reverbLabel5.setText("REVERB 5", dontSendNotification);

    reverbLabel6.setVisible(true);
    reverbLabel6.setText("REVERB 6", dontSendNotification);

    resized();
}
    

void NewProjectAudioProcessorEditor::resized()
{
    const int sliderWidth = getWidth() / 2.22;
    const int sliderHeight = getHeight() / 2.2;
    const int sliderWidth1 = getWidth() / 2.22; 
    const int sliderHeight1 = getHeight() / 2.2; 
    const int sliderWidth2 = getWidth() / 2.4;
    const int sliderHeight2 = getHeight() / 2.4;
    const int sliderWidth3 = getWidth() / 1.9; 
    const int sliderHeight3 = getHeight() / 2.15;
    const int labelHeight = 20;
    const int textBoxWidth = sliderWidth1 / 3;
    const int radius1 = 8.3;
    const int radius2 = 8.1;
    const int radius3 = 9.1;


    if (currentEffect == "basic")
    {
        int delaySliderX = getWidth() / 19 + radius1 + 2;
        int delaySliderY = getHeight() / 4.2 - sliderHeight1 / 2.3;
        setupSliderAndLabel(sliderDelayMs, delayLabel, "delaySlider", delaySliderX, delaySliderY,
            sliderWidth1, sliderHeight1, textBoxWidth, labelHeight);

        int feedbackSliderX = getWidth() / 2.09 + radius1 + 3;
        int feedbackSliderY = delaySliderY;
        setupSliderAndLabel(sliderFeedback, feedbackLabel, "feedbackSlider", feedbackSliderX, feedbackSliderY,
            sliderWidth1, sliderHeight1, textBoxWidth, labelHeight);

        int volumeSliderX = getWidth() / 2 - sliderWidth2 / 2 + radius3 - 1;
        int volumeSliderY = getHeight() / 2 - sliderHeight2 / 2.7;
        setupSliderAndLabel(sliderVolume, volumeLabel, "volumeSlider", volumeSliderX, volumeSliderY,
            sliderWidth2, sliderHeight2, textBoxWidth, labelHeight);

        int distortionSliderX = getWidth() / 6 - sliderWidth3 / 2 - radius3 / 2.5 - 1;
        int distortionSliderY = getHeight() / 3.5 + sliderHeight3 / 2 - 1.2 * radius3;
        setupSliderAndLabel(sliderDistortion, distortionLabel, "distortionSlider", distortionSliderX, distortionSliderY,
            sliderWidth3, sliderHeight3, textBoxWidth, labelHeight);

        int blendSliderX = getWidth() / 3 + sliderWidth3 / 2 - radius3 - 1;
        int blendSliderY = distortionSliderY;
        setupSliderAndLabel(sliderBlend, blendLabel, "blendSlider", blendSliderX, blendSliderY,
            sliderWidth3, sliderHeight3, textBoxWidth, labelHeight);
    }
    else if (currentEffect == "reverb")
    {
        int reverbSlider1X = getWidth() / 19 + radius1 + 2;
        int reverbSlider1Y = getHeight() / 4.2 - sliderHeight1 / 2.3;
        setupSliderAndLabel(sliderReverb1, reverbLabel1, "reverbLabel1", reverbSlider1X, reverbSlider1Y,
            sliderWidth1, sliderHeight1, textBoxWidth, labelHeight);

        int reverbSlider2X = getWidth() / 2.09 + radius1 + 3;
        int reverbSlider2Y = reverbSlider1Y;
        setupSliderAndLabel(sliderReverb2, reverbLabel2, "reverbLabel2", reverbSlider2X, reverbSlider2Y,
            sliderWidth1, sliderHeight1, textBoxWidth, labelHeight);

        int reverbSlider3X = getWidth() / 2 - sliderWidth2 / 2 + radius3 - 1;
        int reverbSlider3Y = getHeight() / 2 - sliderHeight2 / 2.7;
        setupSliderAndLabel(sliderReverb3, reverbLabel3, "reverbLabel3", reverbSlider3X, reverbSlider3Y,
            sliderWidth2, sliderHeight2, textBoxWidth, labelHeight);

        int reverbSlider4X = getWidth() / 6 - sliderWidth3 / 2 - radius3 / 2.5 - 1;
        int reverbSlider4Y = getHeight() / 3.5 + sliderHeight3 / 2 - 1.2 * radius3;
        setupSliderAndLabel(sliderReverb4, reverbLabel4, "reverbLabel4", reverbSlider4X, reverbSlider4Y,
            sliderWidth3, sliderHeight3, textBoxWidth, labelHeight);

        int reverbSlider5X = getWidth() / 3 + sliderWidth3 / 2 - radius3 - 1;
        int reverbSlider5Y = reverbSlider4Y;
        setupSliderAndLabel(sliderReverb5, reverbLabel5, "reverbLabel5", reverbSlider5X, reverbSlider5Y,
            sliderWidth3, sliderHeight3, textBoxWidth, labelHeight);
    }
    

    int settingsHeight = 30;
    int settingsWidth = 30;
    settingsButton.setBounds(getWidth() / 45, getHeight() / 20, settingsWidth, settingsHeight);
    
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

void NewProjectAudioProcessorEditor::openSettings(Button* button)
{
    if (button == &settingsButton)
    {
        PopupMenu settingsMenu;
        settingsMenu.setLookAndFeel(&customLookAndFeel);

        PopupMenu themeSubMenu;
        themeSubMenu.setLookAndFeel(&customLookAndFeel);

        PopupMenu effectsSubMenu;
        effectsSubMenu.setLookAndFeel(&customLookAndFeel);

        Image catIcon = ImageCache::getFromMemory(BinaryData::catIcon_png, BinaryData::catIcon_pngSize);
        Image minionIcon = ImageCache::getFromMemory(BinaryData::minionIcon_png, BinaryData::minionIcon_pngSize);
        Image starIcon = ImageCache::getFromMemory(BinaryData::starIcon_png, BinaryData::starIcon_pngSize);
        
        // Добавляем опции тем в подменю с иконками
        themeSubMenu.addItem(101, "cats theme", true, false, catIcon);
        themeSubMenu.addItem(102, "minions theme", true, false, minionIcon);
        themeSubMenu.addItem(103, "basic theme", true, false, starIcon);

        effectsSubMenu.addItem(201, "reverb", true, false, starIcon);
        effectsSubMenu.addItem(202, "basic effects", true, false, starIcon);

        // Добавляем подменю к основному меню "Интерфейс"
        settingsMenu.addSubMenu("theme settings", themeSubMenu);
        settingsMenu.addSubMenu("effects settings", effectsSubMenu);

        PopupMenu::Options options;
        options = options.withMinimumWidth(200).withStandardItemHeight(80).withTargetComponent(button);

        // Асинхронный вызов меню
        settingsMenu.showMenuAsync(options,
            [this](int result)
            {
                switch (result)
                {
                case 101:
                    changeTheme("cats");
                    break;
                case 102:
                    changeTheme("minions");
                    break;
                case 103:
                    changeTheme("basic");
                    break;
                case 201:
                    setEffect("reverb");
                    break;
                case 202:
                    setEffect("basic");
                    break;
                }
            });
    }
}

void NewProjectAudioProcessorEditor::changeTheme(const String& themeName)
{
    currentTheme = themeName;

    if (themeName == "minions")
    {
        // Установка фона для темы "minions"
        backgroundImage = ImageCache::getFromMemory(BinaryData::background2_png, BinaryData::background2_pngSize);

        // Изменение настроек слайдеров
        sliderDelayMs.setLookAndFeel(&minionsLookAndFeel);
        sliderFeedback.setLookAndFeel(&minionsLookAndFeel);
        sliderVolume.setLookAndFeel(&minionsLookAndFeel);
        sliderDistortion.setLookAndFeel(&minionsLookAndFeel);
        sliderBlend.setLookAndFeel(&minionsLookAndFeel);
        delayLabel.setColour(Label::textColourId, Colours::white);
        volumeLabel.setColour(Label::textColourId, Colours::white);
        distortionLabel.setColour(Label::textColourId, Colours::white);
        feedbackLabel.setColour(Label::textColourId, Colours::white);
        blendLabel.setColour(Label::textColourId, Colours::white);

        sliderReverb1.setLookAndFeel(&minionsLookAndFeel);
        sliderReverb2.setLookAndFeel(&minionsLookAndFeel);
        sliderReverb3.setLookAndFeel(&minionsLookAndFeel);
        sliderReverb4.setLookAndFeel(&minionsLookAndFeel);
        sliderReverb5.setLookAndFeel(&minionsLookAndFeel);
        sliderReverb6.setLookAndFeel(&minionsLookAndFeel);
        reverbLabel1.setColour(Label::textColourId, Colours::white);
        reverbLabel2.setColour(Label::textColourId, Colours::white);
        reverbLabel3.setColour(Label::textColourId, Colours::white);
        reverbLabel4.setColour(Label::textColourId, Colours::white);
        reverbLabel5.setColour(Label::textColourId, Colours::white);
        reverbLabel6.setColour(Label::textColourId, Colours::white);
    }
    else if (themeName == "basic")
    {
        backgroundImage = ImageCache::getFromMemory(BinaryData::background5_png, BinaryData::background5_pngSize);
        sliderDelayMs.setLookAndFeel(&basicLookAndFeel);
        sliderFeedback.setLookAndFeel(&basicLookAndFeel);
        sliderVolume.setLookAndFeel(&basicLookAndFeel);
        sliderDistortion.setLookAndFeel(&basicLookAndFeel);
        sliderBlend.setLookAndFeel(&basicLookAndFeel);
        delayLabel.setColour(Label::textColourId, Colours::white);
        volumeLabel.setColour(Label::textColourId, Colours::white);
        distortionLabel.setColour(Label::textColourId, Colours::white);
        feedbackLabel.setColour(Label::textColourId, Colours::white);
        blendLabel.setColour(Label::textColourId, Colours::white);

        sliderReverb1.setLookAndFeel(&basicLookAndFeel);
        sliderReverb2.setLookAndFeel(&basicLookAndFeel);
        sliderReverb3.setLookAndFeel(&basicLookAndFeel);
        sliderReverb4.setLookAndFeel(&basicLookAndFeel);
        sliderReverb5.setLookAndFeel(&basicLookAndFeel);
        sliderReverb6.setLookAndFeel(&basicLookAndFeel);
        reverbLabel1.setColour(Label::textColourId, Colours::white);
        reverbLabel2.setColour(Label::textColourId, Colours::white);
        reverbLabel3.setColour(Label::textColourId, Colours::white);
        reverbLabel4.setColour(Label::textColourId, Colours::white);
        reverbLabel5.setColour(Label::textColourId, Colours::white);
        reverbLabel6.setColour(Label::textColourId, Colours::white);
    }
    else // default theme
    {
        // Установка стандартного фона
        backgroundImage = ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);

        // Возвращение к стандартному внешнему виду
        sliderDelayMs.setLookAndFeel(&customLookAndFeel);
        sliderFeedback.setLookAndFeel(&customLookAndFeel);
        sliderVolume.setLookAndFeel(&customLookAndFeel);
        sliderDistortion.setLookAndFeel(&customLookAndFeel);
        sliderBlend.setLookAndFeel(&customLookAndFeel);
        delayLabel.setColour(Label::textColourId, Colours::white);
        volumeLabel.setColour(Label::textColourId, Colours::white);
        distortionLabel.setColour(Label::textColourId, Colours::white);
        feedbackLabel.setColour(Label::textColourId, Colours::white);
        blendLabel.setColour(Label::textColourId, Colours::white);

        sliderReverb1.setLookAndFeel(&customLookAndFeel);
        sliderReverb2.setLookAndFeel(&customLookAndFeel);
        sliderReverb3.setLookAndFeel(&customLookAndFeel);
        sliderReverb4.setLookAndFeel(&customLookAndFeel);
        sliderReverb5.setLookAndFeel(&customLookAndFeel);
        sliderReverb6.setLookAndFeel(&customLookAndFeel);
        reverbLabel1.setColour(Label::textColourId, Colours::white);
        reverbLabel2.setColour(Label::textColourId, Colours::white);
        reverbLabel3.setColour(Label::textColourId, Colours::white);
        reverbLabel4.setColour(Label::textColourId, Colours::white);
        reverbLabel5.setColour(Label::textColourId, Colours::white);
        reverbLabel6.setColour(Label::textColourId, Colours::white);
    }

    repaint();  // Перерисовка интерфейса
    resized();  // Обновление расположения компонентов
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
