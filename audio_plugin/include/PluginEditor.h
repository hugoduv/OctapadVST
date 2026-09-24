#pragma once

namespace audio_plugin {
class PluginEditor : public juce::AudioProcessorEditor {
public:
  explicit PluginEditor(PluginProcessor&);

  void paint(juce::Graphics&) override;
  void resized() override;

private:
  // This reference is provided as a quick way for your editor to
  // access the processor object that created it.
  PluginProcessor& processorRef;

  juce::GroupComponent pad1Group, pad2Group, pad3Group, pad4Group, pad5Group, pad6Group, pad7Group, pad8Group;
  juce::GroupComponent pluginNameGroup;
  
  juce::TextButton pad1LoadButton, pad1ClearButton;
  juce::TextButton pad1PlayButton;
  // juce::Button pad1Button, pad2Button, pad3Button, pad4Button, pad5Button, pad6Button, pad7Button, pad8Button;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
}  // namespace audio_plugin
