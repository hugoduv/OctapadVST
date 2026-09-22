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
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
}  // namespace audio_plugin
