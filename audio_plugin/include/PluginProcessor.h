#pragma once
#include <atomic>

namespace audio_plugin {
class PluginProcessor : public juce::AudioProcessor {
public:
  PluginProcessor();

  void prepareToPlay(double sampleRate, int samplesPerBlock) override;
  void releaseResources() override;

  bool isBusesLayoutSupported(const BusesLayout& layouts) const override;

  void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
  using AudioProcessor::processBlock;

  juce::AudioProcessorEditor* createEditor() override;
  bool hasEditor() const override;

  const juce::String getName() const override;

  bool acceptsMidi() const override;
  bool producesMidi() const override;
  bool isMidiEffect() const override;
  double getTailLengthSeconds() const override;

  int getNumPrograms() override;
  int getCurrentProgram() override;
  void setCurrentProgram(int index) override;
  const juce::String getProgramName(int index) override;
  void changeProgramName(int index, const juce::String& newName) override;

  void getStateInformation(juce::MemoryBlock& destData) override;
  void setStateInformation(const void* data, int sizeInBytes) override;

  void loadPadBuffer(int padIndex);
  bool loadPadBuffer(int padIndex, const juce::File& file);
  void clearPadBuffer(int padIndex);

  void triggerPad(int padIndex);

private:
  juce::AudioBuffer<float> padBuffers[8]; // Array to hold audio buffers for each pad
  std::atomic<bool> activePads[8]{};
  std::atomic<int> playbackPositions[8]{};

  juce::AudioFormatManager formatManager; // To manage audio formats for loading files
  juce::File defaultPadFiles[8];
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginProcessor)

};
}  // namespace audio_plugin
