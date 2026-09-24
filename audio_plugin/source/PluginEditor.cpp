namespace audio_plugin {
PluginEditor::PluginEditor(PluginProcessor& p)
    : AudioProcessorEditor(&p), processorRef(p) {
  juce::ignoreUnused(processorRef);
  // Make sure that before the constructor has finished, you've set the
  // editor's size to whatever you need it to be.
  
  
  // Here we will add text to the pads later
  pad1Group.setText("Pad 1");
  pad1Group.setTextLabelPosition(juce::Justification::centred);
  pad1LoadButton.setButtonText("Load"); 
  pad1ClearButton.setButtonText("Clear");
  pad1PlayButton.setButtonText("Play");
  pad1Text.setText("audio.wav", juce::dontSendNotification);
  pad1Text.setJustificationType(juce::Justification::centred);

  pad1Group.addChildComponent(pad1LoadButton);
  pad1Group.addChildComponent(pad1ClearButton);
  pad1Group.addChildComponent(pad1PlayButton);
  pad1Group.addChildComponent(pad1Text);
  addAndMakeVisible(pad1LoadButton);
  addAndMakeVisible(pad1ClearButton);
  addAndMakeVisible(pad1PlayButton);
  addAndMakeVisible(pad1Text);
  addAndMakeVisible(pad1Group);

  pad2Group.setText("Pad 2");
  pad2Group.setTextLabelPosition(juce::Justification::centred);
  addAndMakeVisible(pad2Group);

  pad3Group.setText("Pad 3");
  pad3Group.setTextLabelPosition(juce::Justification::centred);
  addAndMakeVisible(pad3Group);

  pad4Group.setText("Pad 4");
  pad4Group.setTextLabelPosition(juce::Justification::centred);
  addAndMakeVisible(pad4Group);

  pad5Group.setText("Pad 5");
  pad5Group.setTextLabelPosition(juce::Justification::centred);
  addAndMakeVisible(pad5Group);

  pad6Group.setText("Pad 6");
  pad6Group.setTextLabelPosition(juce::Justification::centred);
  addAndMakeVisible(pad6Group);

  pad7Group.setText("Pad 7");
  pad7Group.setTextLabelPosition(juce::Justification::centred);
  addAndMakeVisible(pad7Group);

  pad8Group.setText("Pad 8");
  pad8Group.setTextLabelPosition(juce::Justification::centred);
  addAndMakeVisible(pad8Group);

  presetNameLabel.setText("Tool - Schism", juce::dontSendNotification);
  presetNameLabel.setJustificationType(juce::Justification::centred);
  presetNameGroup.addChildComponent(presetNameLabel);
  addAndMakeVisible(presetNameLabel);
  addAndMakeVisible(presetNameGroup);


  presetLeftButton.setButtonText("<");
  presetRightButton.setButtonText(">");
  presetSelectorGroup.addChildComponent(presetSelector);
  presetSelectorGroup.addChildComponent(presetLeftButton);
  presetSelectorGroup.addChildComponent(presetRightButton);
  addAndMakeVisible(presetSelector);
  addAndMakeVisible(presetLeftButton);
  addAndMakeVisible(presetRightButton);
  addAndMakeVisible(presetSelectorGroup);

  pad1LoadButton.onClick = [this]
  {
    DBG("Load button clicked for Pad 1");
  };

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
  
  auto linePad1 = octoPadArea.removeFromTop(octoPadArea.getHeight() / 2); // row 1 of 4 pads
  auto linePad2 = octoPadArea;

  auto pad1Area = linePad1.removeFromLeft(linePad1.getWidth() / 4);

  pad1Group.setBounds(pad1Area.reduced(gap));

  auto area = pad1Group.getBounds();
  area.removeFromTop(20); // Leave space for the group title
  pad1Text.setBounds(area.removeFromTop(30));

  auto areaSettings = area.removeFromTop(area.getHeight()*1/4); // Leave space for the buttons
  pad1LoadButton.setBounds(areaSettings.removeFromLeft(areaSettings.getWidth()/2));
  pad1ClearButton.setBounds(areaSettings);
  pad1PlayButton.setBounds(area);

  auto pad2Area = linePad1.removeFromLeft(linePad1.getWidth() / 3);
  pad2Group.setBounds(pad2Area.reduced(gap));

  auto pad3Area = linePad1.removeFromLeft(linePad1.getWidth() / 2);
  pad3Group.setBounds(pad3Area.reduced(gap));

  auto pad4Area = linePad1;
  pad4Group.setBounds(pad4Area.reduced(gap));
  
  auto pad5Area = linePad2.removeFromLeft(linePad2.getWidth() / 4);
  pad5Group.setBounds(pad5Area.reduced(gap));

  auto pad6Area = linePad2.removeFromLeft(linePad2.getWidth() / 3);
  pad6Group.setBounds(pad6Area.reduced(gap));

  auto pad7Area = linePad2.removeFromLeft(linePad2.getWidth() / 2);
  pad7Group.setBounds(pad7Area.reduced(gap));

  auto pad8Area = linePad2;
  pad8Group.setBounds(pad8Area.reduced(gap));

  auto panelArea = bounds.reduced(gap);
  // Name of the preset
  presetNameGroup.setBounds(panelArea.removeFromTop(panelArea.getHeight() / 4));
  presetNameLabel.setBounds(presetNameGroup.getBounds().reduced(10));


  presetSelectorGroup.setBounds(panelArea.removeFromTop(panelArea.getHeight() / 3));
  auto selectorArea = presetSelectorGroup.getBounds().reduced(10);
  presetSelector.setBounds(selectorArea.removeFromTop(selectorArea.getHeight() / 2).reduced(10));
  presetLeftButton.setBounds(selectorArea.removeFromLeft(presetSelectorGroup.getWidth() / 2).reduced(10));
  presetRightButton.setBounds(selectorArea.reduced(10));
}

}  // namespace audio_plugin
