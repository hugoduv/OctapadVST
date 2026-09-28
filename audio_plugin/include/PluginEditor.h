#pragma once

namespace audio_plugin {
class PluginEditor : public juce::AudioProcessorEditor {
public:
  explicit PluginEditor(PluginProcessor&);

  void paint(juce::Graphics&) override;
  void resized() override;

  void PlayPad(int padIndex);

private:
  void choosePadFile(int padIndex);
  void layoutPad(int padIndex);
  void chooseSetDirectory();
  void loadSetDirectory(const juce::File& directory);
  void saveSetAs();
  void addMusic();
  void saveCurrentMusic();
  void renameMusic();
  void loadMusic(int musicIndex);
  void refreshMusicSelector();
  void moveMusic(int direction);
  void saveSetMetadata();
  bool saveMusicToDirectory(const juce::File& directory);

  PluginProcessor& processorRef; // reference to the associated PluginProcessor

  juce::GroupComponent padGroups[8];
  juce::Label padNames[8];
  juce::TextButton padLoadButtons[8], padClearButtons[8], padPlayButtons[8];
  std::unique_ptr<juce::FileChooser> fileChooser;

  juce::GroupComponent presetNameGroup, presetSelectorGroup;
  juce::Label presetNameLabel;
  juce::ComboBox presetSelector;
  juce::TextButton presetLeftButton, presetRightButton;
  juce::TextButton openSetButton, saveSetButton, addMusicButton, saveMusicButton;
  juce::TextButton moveMusicLeftButton, moveMusicRightButton;
  juce::TextEditor musicNameEditor;
  juce::TextButton renameMusicButton;
  juce::File currentSetDirectory;
  juce::StringArray musicNames;
  int currentMusicIndex = -1;
  
  juce::GroupComponent controlGroup;
  juce::Slider masterSlider;
  
  // juce::Button pad1Button, pad2Button, pad3Button, pad4Button, pad5Button, pad6Button, pad7Button, pad8Button;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
}  // namespace audio_plugin
