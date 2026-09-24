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
  pad1Group.addChildComponent(pad1LoadButton);
  pad1Group.addChildComponent(pad1ClearButton);
  pad1Group.addChildComponent(pad1PlayButton);
  addAndMakeVisible(pad1LoadButton);
  addAndMakeVisible(pad1ClearButton);
  addAndMakeVisible(pad1PlayButton);
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

  addAndMakeVisible(pluginNameGroup);
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
  int octoPadWidth = bounds.getWidth()* 3/4 - gap*2;
  int octoPadHeight = bounds.getHeight() - 2*gap;

  int padWidth = (octoPadWidth - gap*2)/4; // 4 pads in a row
  int padHeight = (octoPadHeight - gap*2)/2; // 2 pads in a column

  pad1Group.setBounds(gap, gap, padWidth, padHeight);
  auto area = pad1Group.getBounds();
  area.removeFromTop(20); // Leave space for the group title
  auto areaSettings = area.removeFromTop(padHeight/4); // Leave space for the buttons
  pad1LoadButton.setBounds(areaSettings.removeFromLeft(areaSettings.getWidth()/2));
  pad1ClearButton.setBounds(areaSettings);
  pad1PlayButton.setBounds(area);

  pad2Group.setBounds(gap*2 + padWidth, gap, padWidth, padHeight);
  pad3Group.setBounds(gap*3 + padWidth*2, gap, padWidth, padHeight);
  pad4Group.setBounds(gap*4 + padWidth*3, gap, padWidth, padHeight);
  pad5Group.setBounds(gap, gap*2 + padHeight, padWidth, padHeight);
  pad6Group.setBounds(gap*2 + padWidth, gap*2 + padHeight, padWidth, padHeight);
  pad7Group.setBounds(gap*3 + padWidth*2, gap*2 + padHeight, padWidth, padHeight);
  pad8Group.setBounds(gap*4 + padWidth*3, gap*2 + padHeight, padWidth, padHeight);

  pluginNameGroup.setBounds(octoPadWidth + 6*gap, gap, padWidth, padHeight/2);

}

}  // namespace audio_plugin
