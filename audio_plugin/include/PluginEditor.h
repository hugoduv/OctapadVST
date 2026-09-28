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

  PluginProcessor& processorRef; // reference to the associated PluginProcessor

  juce::GroupComponent padGroups[8];
  juce::Label padNames[8];
  juce::TextButton padLoadButtons[8], padClearButtons[8], padPlayButtons[8];
  std::unique_ptr<juce::FileChooser> fileChooser;

  juce::GroupComponent presetNameGroup, presetSelectorGroup;
  juce::Label presetNameLabel;
  juce::ComboBox presetSelector;
  juce::TextButton presetLeftButton, presetRightButton;
  
  juce::GroupComponent controlGroup;
  juce::Slider masterSlider;
  
  // juce::Button pad1Button, pad2Button, pad3Button, pad4Button, pad5Button, pad6Button, pad7Button, pad8Button;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
}  // namespace audio_plugin
