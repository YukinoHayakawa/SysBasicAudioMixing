#pragma once

#include <memory>

#include <Usagi/Game/CollectionSystem.hpp>
#include <Usagi/Runtime/Audio/AudioDevice.hpp>
#include <Usagi/Runtime/Audio/AudioStreamFormat.hpp>

#include "BasicAudioStreamComponent.hpp"

namespace usagi
{
class AudioManager;

class BasicAudioMixingSystem
    : public CollectionSystem<BasicAudioStreamComponent>
{
    std::shared_ptr<AudioDevice> mDevice;
    std::shared_ptr<AudioOutputStream> mStream;
    AudioStreamFormat mOutputFormat;

    AudioStreamStatus streamingCallback(
        const ArrayView<std::byte*> &channels,
        std::size_t frames
    );

public:
    BasicAudioMixingSystem(AudioManager *audio_manager);
    void update(const Clock &clock) override;

    const std::type_info & type() override
    {
        return typeid(BasicAudioMixingSystem);
    }
};
}
