#pragma once

namespace audio_plugin {
class PluginEditor : public juce::AudioProcessorEditor {
public:
  explicit PluginEditor(PluginProcessor&);

  void paint(juce::Graphics&) override;
  void resized() override;

  void PlayPad(int padIndex);

private:
  PluginProcessor& processorRef; // reference to the associated PluginProcessor

  juce::GroupComponent pad1Group, pad2Group, pad3Group, pad4Group, pad5Group, pad6Group, pad7Group, pad8Group;
  juce::Label pad1Text;
  juce::TextButton pad1LoadButton, pad1ClearButton;
  juce::TextButton pad1PlayButton;
  juce::Label pad2Text;
  juce::TextButton pad2LoadButton, pad2ClearButton;
  juce::TextButton pad2PlayButton;

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
