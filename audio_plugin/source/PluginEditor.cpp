namespace audio_plugin {
PluginEditor::PluginEditor(PluginProcessor& p)
    : AudioProcessorEditor(&p), processorRef(p) {
  juce::ignoreUnused(processorRef);
  // Make sure that before the constructor has finished, you've set the
  // editor's size to whatever you need it to be.
  
  
  for (int padIndex = 0; padIndex < 8; ++padIndex)
  {
    padGroups[padIndex].setText("Pad " + juce::String(padIndex + 1));
    padGroups[padIndex].setTextLabelPosition(juce::Justification::centred);
    padLoadButtons[padIndex].setButtonText("Load");
    padClearButtons[padIndex].setButtonText("Clear");
    padPlayButtons[padIndex].setButtonText("Play");
    padNames[padIndex].setText("No sample", juce::dontSendNotification);
    padNames[padIndex].setJustificationType(juce::Justification::centred);

    addAndMakeVisible(padGroups[padIndex]);
    addAndMakeVisible(padLoadButtons[padIndex]);
    addAndMakeVisible(padClearButtons[padIndex]);
    addAndMakeVisible(padPlayButtons[padIndex]);
    addAndMakeVisible(padNames[padIndex]);

    padLoadButtons[padIndex].onClick = [this, padIndex]
    {
      choosePadFile(padIndex);
    };

    padClearButtons[padIndex].onClick = [this, padIndex]
    {
      processorRef.clearPadBuffer(padIndex);
      padNames[padIndex].setText("No sample", juce::dontSendNotification);
    };

    padPlayButtons[padIndex].onClick = [this, padIndex]
    {
      PlayPad(padIndex);
    };
  }

  // Preset name panel
  presetNameLabel.setText("Tool - Schism", juce::dontSendNotification);
  presetNameLabel.setJustificationType(juce::Justification::centred);
  presetNameGroup.addChildComponent(presetNameLabel);
  addAndMakeVisible(presetNameLabel);
  addAndMakeVisible(presetNameGroup);


  // Preset control panel
  presetLeftButton.setButtonText("<");
  presetRightButton.setButtonText(">");
  presetSelectorGroup.addChildComponent(presetSelector);
  presetSelectorGroup.addChildComponent(presetLeftButton);
  presetSelectorGroup.addChildComponent(presetRightButton);
  addAndMakeVisible(presetSelector);
  addAndMakeVisible(presetLeftButton);
  addAndMakeVisible(presetRightButton);
  addAndMakeVisible(presetSelectorGroup);

  // Control panel

  masterSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  masterSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
  masterSlider.setTextValueSuffix(" Master");
  masterSlider.setRange(0.0, 1.0, 0.01);
  controlGroup.setText("Controls");
  controlGroup.setTextLabelPosition(juce::Justification::centred);
  controlGroup.addChildComponent(masterSlider);
  addAndMakeVisible(masterSlider);
  addAndMakeVisible(controlGroup);

  setSize(540*2, 270*2); // dimensions of the Roland Octapad hardware
}

void PluginEditor::paint(juce::Graphics& g) {
  // (Our component is opaque, so we must completely fill the background with a
  // solid colour)
  g.fillAll(
      getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

  g.setColour(juce::Colours::white);
  g.setFont(15.0f);
  // g.drawFittedText("Octapad VST3", getLocalBounds(),
  //                  juce::Justification::centred, 1);

  
}

void PluginEditor::resized() {
  // This is generally where you'll want to lay out the positions of any
  // subcomponents in your editor..
  // Placing the pads

  auto bounds = getLocalBounds(); 
  int gap = 10;

  auto octoPadArea = bounds.removeFromLeft(bounds.getWidth() * 3 / 4);
  
  auto linePad1 = octoPadArea.removeFromTop(octoPadArea.getHeight() / 2);
  auto linePad2 = octoPadArea;

  for (int padIndex = 0; padIndex < 4; ++padIndex)
  {
    auto padArea = linePad1.removeFromLeft(
        linePad1.getWidth() / (4 - padIndex));
    padGroups[padIndex].setBounds(padArea.reduced(gap));
    layoutPad(padIndex);
  }

  for (int padIndex = 4; padIndex < 8; ++padIndex)
  {
    auto padArea = linePad2.removeFromLeft(
        linePad2.getWidth() / (8 - padIndex));
    padGroups[padIndex].setBounds(padArea.reduced(gap));
    layoutPad(padIndex);
  }
  
  auto panelArea = bounds.reduced(gap);
  // Name of the preset
  presetNameGroup.setBounds(panelArea.removeFromTop(panelArea.getHeight() / 4));
  presetNameLabel.setBounds(presetNameGroup.getBounds().reduced(10));


  presetSelectorGroup.setBounds(panelArea.removeFromTop(panelArea.getHeight() / 3));
  auto selectorArea = presetSelectorGroup.getBounds().reduced(10);
  presetSelector.setBounds(selectorArea.removeFromTop(selectorArea.getHeight() / 2).reduced(10));
  presetLeftButton.setBounds(selectorArea.removeFromLeft(presetSelectorGroup.getWidth() / 2).reduced(10));
  presetRightButton.setBounds(selectorArea.reduced(10));

  controlGroup.setBounds(panelArea);
  masterSlider.setBounds(controlGroup.getBounds().reduced(60));
}

void PluginEditor::PlayPad(int padIndex){
  DBG("PlayPad called with padIndex: " << padIndex);
  processorRef.triggerPad(padIndex); // Adjust for 0-based index in the processor
}

void PluginEditor::choosePadFile(int padIndex)
{
  fileChooser = std::make_unique<juce::FileChooser>(
      "Choose a WAV file", juce::File{}, "*.wav");

  fileChooser->launchAsync(
      juce::FileBrowserComponent::openMode |
          juce::FileBrowserComponent::canSelectFiles,
      [this, padIndex](const juce::FileChooser& chooser)
      {
        const auto file = chooser.getResult();
        if (file.existsAsFile() && processorRef.loadPadBuffer(padIndex, file))
          padNames[padIndex].setText(file.getFileName(),
                                     juce::dontSendNotification);
      });
}

void PluginEditor::layoutPad(int padIndex)
{
  auto area = padGroups[padIndex].getBounds();
  area.removeFromTop(20);
  padNames[padIndex].setBounds(area.removeFromTop(30));

  auto settings = area.removeFromTop(area.getHeight() / 4);
  padLoadButtons[padIndex].setBounds(
      settings.removeFromLeft(settings.getWidth() / 2));
  padClearButtons[padIndex].setBounds(settings);
  padPlayButtons[padIndex].setBounds(area);
}

}  // namespace audio_plugin
