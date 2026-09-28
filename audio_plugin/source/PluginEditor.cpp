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
  presetNameLabel.setText("No Preset Loaded", juce::dontSendNotification);
  presetNameLabel.setJustificationType(juce::Justification::centred);
  presetNameGroup.addChildComponent(presetNameLabel);
  addAndMakeVisible(presetNameLabel);
  addAndMakeVisible(presetNameGroup);


  // Preset control panel
  presetLeftButton.setButtonText("<");
  presetRightButton.setButtonText(">");
  openSetButton.setButtonText("Open Set");
  saveSetButton.setButtonText("Save Set");
  addMusicButton.setButtonText("Add Music");
  saveMusicButton.setButtonText("Save Music");
  moveMusicLeftButton.setButtonText("Move <");
  moveMusicRightButton.setButtonText("Move >");
  renameMusicButton.setButtonText("Rename");
  musicNameEditor.setTextToShowWhenEmpty("Music name", juce::Colours::grey);
  presetSelectorGroup.addChildComponent(presetSelector);
  presetSelectorGroup.addChildComponent(presetLeftButton);
  presetSelectorGroup.addChildComponent(presetRightButton);
  presetSelectorGroup.addChildComponent(openSetButton);
  presetSelectorGroup.addChildComponent(saveSetButton);
  presetSelectorGroup.addChildComponent(addMusicButton);
  presetSelectorGroup.addChildComponent(saveMusicButton);
  presetSelectorGroup.addChildComponent(moveMusicLeftButton);
  presetSelectorGroup.addChildComponent(moveMusicRightButton);
  presetSelectorGroup.addChildComponent(musicNameEditor);
  presetSelectorGroup.addChildComponent(renameMusicButton);
  addAndMakeVisible(presetSelector);
  addAndMakeVisible(presetLeftButton);
  addAndMakeVisible(presetRightButton);
  addAndMakeVisible(openSetButton);
  addAndMakeVisible(saveSetButton);
  addAndMakeVisible(addMusicButton);
  addAndMakeVisible(saveMusicButton);
  addAndMakeVisible(moveMusicLeftButton);
  addAndMakeVisible(moveMusicRightButton);
  addAndMakeVisible(musicNameEditor);
  addAndMakeVisible(renameMusicButton);
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

  presetSelector.onChange = [this]
  {
    loadMusic(presetSelector.getSelectedItemIndex());
  };
  presetLeftButton.onClick = [this] { loadMusic(currentMusicIndex - 1); };
  presetRightButton.onClick = [this] { loadMusic(currentMusicIndex + 1); };
  openSetButton.onClick = [this] { chooseSetDirectory(); };
  saveSetButton.onClick = [this] { saveSetAs(); };
  addMusicButton.onClick = [this] { addMusic(); };
  saveMusicButton.onClick = [this] { saveCurrentMusic(); };
    renameMusicButton.onClick = [this] { renameMusic(); };
  moveMusicLeftButton.onClick = [this] { moveMusic(-1); };
  moveMusicRightButton.onClick = [this] { moveMusic(1); };

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
  presetNameGroup.setBounds(panelArea.removeFromTop(panelArea.getHeight() / 8));
  presetNameLabel.setBounds(presetNameGroup.getBounds().reduced(10));


  presetSelectorGroup.setBounds(panelArea.removeFromTop(panelArea.getHeight() / 2 + 80) );
  auto selectorArea = presetSelectorGroup.getBounds().reduced(10);
  presetSelector.setBounds(selectorArea.removeFromTop(selectorArea.getHeight() / 4));
  auto navigationArea = selectorArea.removeFromTop(selectorArea.getHeight() / 3);
  presetLeftButton.setBounds(navigationArea.removeFromLeft(navigationArea.getWidth() / 2).reduced(3));
  presetRightButton.setBounds(navigationArea.reduced(3));
  auto nameArea = selectorArea.removeFromTop(selectorArea.getHeight() / 3);
  musicNameEditor.setBounds(nameArea.removeFromLeft(nameArea.getWidth() * 2 / 3).reduced(3));
  renameMusicButton.setBounds(nameArea.reduced(3));
  auto setArea = selectorArea.removeFromTop(selectorArea.getHeight() / 2);
  openSetButton.setBounds(setArea.removeFromLeft(setArea.getWidth() / 2).reduced(3));
  saveSetButton.setBounds(setArea.reduced(3));
  auto musicArea = selectorArea.removeFromTop(selectorArea.getHeight() / 2);
  addMusicButton.setBounds(musicArea.removeFromLeft(musicArea.getWidth() / 2).reduced(3));
  saveMusicButton.setBounds(musicArea.reduced(3));
  moveMusicLeftButton.setBounds(selectorArea.removeFromLeft(selectorArea.getWidth() / 2).reduced(3));
  moveMusicRightButton.setBounds(selectorArea.reduced(3));

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

void PluginEditor::chooseSetDirectory()
{
  fileChooser = std::make_unique<juce::FileChooser>(
      "Choose a set folder", juce::File{}, "");

  fileChooser->launchAsync(
      juce::FileBrowserComponent::openMode |
          juce::FileBrowserComponent::canSelectDirectories,
      [this](const juce::FileChooser& chooser)
      {
        const auto directory = chooser.getResult();
        if (directory.isDirectory())
          loadSetDirectory(directory);
      });
}

void PluginEditor::loadSetDirectory(const juce::File& directory)
{
  currentSetDirectory = directory;
  musicNames.clear();

  const auto metadataFile = directory.getChildFile("set.json");
  if (metadataFile.existsAsFile())
  {
    const auto metadata = juce::JSON::parse(metadataFile.loadFileAsString());
    if (const auto* object = metadata.getDynamicObject())
    {
      if (const auto* names = object->getProperty("musics").getArray())
      {
        for (const auto& name : *names)
          musicNames.add(name.toString());
      }
    }
  }

  if (musicNames.isEmpty())
  {
    juce::Array<juce::File> directories;
    directory.findChildFiles(directories, juce::File::findDirectories,
                             false);
    for (const auto& musicDirectory : directories)
    {
      if (musicDirectory.getFileName() != "")
        musicNames.add(musicDirectory.getFileName());
    }
  }

  refreshMusicSelector();
  if (!musicNames.isEmpty())
    loadMusic(0);
}

void PluginEditor::refreshMusicSelector()
{
  presetSelector.clear(juce::dontSendNotification);
  for (int index = 0; index < musicNames.size(); ++index)
    presetSelector.addItem(musicNames[index], index + 1);

  presetSelector.setSelectedItemIndex(currentMusicIndex,
                                      juce::dontSendNotification);
  presetNameLabel.setText(currentSetDirectory.isDirectory()
                              ? currentSetDirectory.getFileName()
                              : "No set loaded",
                          juce::dontSendNotification);
  if (currentMusicIndex >= 0 && currentMusicIndex < musicNames.size())
    musicNameEditor.setText(musicNames[currentMusicIndex],
                            juce::dontSendNotification);
}

void PluginEditor::loadMusic(int musicIndex)
{
  if (!currentSetDirectory.isDirectory() ||
      musicIndex < 0 || musicIndex >= musicNames.size())
    return;

  currentMusicIndex = musicIndex;
  const auto musicDirectory =
      currentSetDirectory.getChildFile(musicNames[currentMusicIndex]);

  for (int padIndex = 0; padIndex < 8; ++padIndex)
  {
    processorRef.clearPadBuffer(padIndex);
    const auto padFile = musicDirectory.getChildFile(
        "pad" + juce::String(padIndex + 1) + ".wav");
    if (processorRef.loadPadBuffer(padIndex, padFile))
      padNames[padIndex].setText(padFile.getFileName(),
                                 juce::dontSendNotification);
    else
      padNames[padIndex].setText("No sample", juce::dontSendNotification);
  }

  refreshMusicSelector();
}

bool PluginEditor::saveMusicToDirectory(const juce::File& directory)
{
  if (!directory.createDirectory())
    return false;

  for (int padIndex = 0; padIndex < 8; ++padIndex)
  {
    const auto source = processorRef.getPadFile(padIndex);
    const auto destination = directory.getChildFile(
        "pad" + juce::String(padIndex + 1) + ".wav");

    if (source.existsAsFile())
    {
      if (source.getFullPathName() != destination.getFullPathName() &&
          !source.copyFileTo(destination))
        return false;
    }
    else if (destination.existsAsFile())
    {
      destination.deleteFile();
    }
  }

  return true;
}

void PluginEditor::saveCurrentMusic()
{
  if (!currentSetDirectory.isDirectory() ||
      currentMusicIndex < 0 || currentMusicIndex >= musicNames.size())
    return;

  saveMusicToDirectory(currentSetDirectory.getChildFile(
      musicNames[currentMusicIndex]));
  saveSetMetadata();
}

void PluginEditor::saveSetMetadata()
{
  if (!currentSetDirectory.isDirectory())
    return;

  juce::Array<juce::var> names;
  for (const auto& name : musicNames)
    names.add(name);

  juce::DynamicObject::Ptr object = new juce::DynamicObject();
  object->setProperty("musics", juce::var(names));
  currentSetDirectory.getChildFile("set.json").replaceWithText(
      juce::JSON::toString(juce::var(object), true));
}

void PluginEditor::saveSetAs()
{
  fileChooser = std::make_unique<juce::FileChooser>(
      "Choose the set folder", juce::File{}, "");

  fileChooser->launchAsync(
      juce::FileBrowserComponent::openMode |
          juce::FileBrowserComponent::canSelectDirectories,
      [this](const juce::FileChooser& chooser)
      {
        const auto directory = chooser.getResult();
        if (!directory.isDirectory())
          return;

        currentSetDirectory = directory;
        if (musicNames.isEmpty())
        {
          musicNames.add("Music 1");
          currentMusicIndex = 0;
        }

        saveCurrentMusic();
        saveSetMetadata();
        refreshMusicSelector();
      });
}

void PluginEditor::addMusic()
{
  if (!currentSetDirectory.isDirectory())
    return;

  auto uniqueName = "Music " + juce::String(musicNames.size() + 1);
  int suffix = 2;
  while (musicNames.contains(uniqueName))
    uniqueName = "Music " + juce::String(musicNames.size() + 1) +
                 " " + juce::String(suffix++);

  musicNames.add(uniqueName);
  currentSetDirectory.getChildFile(uniqueName).createDirectory();
  saveSetMetadata();
  refreshMusicSelector();
  loadMusic(musicNames.size() - 1);
}

void PluginEditor::moveMusic(int direction)
{
  const auto targetIndex = currentMusicIndex + direction;
  if (targetIndex < 0 || targetIndex >= musicNames.size())
    return;

  const auto movedName = musicNames[currentMusicIndex];
  musicNames.set(currentMusicIndex, musicNames[targetIndex]);
  musicNames.set(targetIndex, movedName);
  currentMusicIndex = targetIndex;
  saveSetMetadata();
  refreshMusicSelector();
}

void PluginEditor::renameMusic()
{
  if (!currentSetDirectory.isDirectory() ||
      currentMusicIndex < 0 || currentMusicIndex >= musicNames.size())
    return;

  const auto newName = musicNameEditor.getText().trim();
  if (newName.isEmpty() ||
      newName.containsAnyOf("\\/:*?\"<>|") ||
      (musicNames.contains(newName) &&
       newName != musicNames[currentMusicIndex]))
    return;

  const auto oldName = musicNames[currentMusicIndex];
  if (newName == oldName)
    return;

  const auto oldDirectory = currentSetDirectory.getChildFile(oldName);
  const auto newDirectory = currentSetDirectory.getChildFile(newName);
  if (newDirectory.exists() || !oldDirectory.moveFileTo(newDirectory))
    return;

  musicNames.set(currentMusicIndex, newName);
  saveSetMetadata();
  refreshMusicSelector();
}

}  // namespace audio_plugin
