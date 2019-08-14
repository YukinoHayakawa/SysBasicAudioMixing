#include "BasicAudioMixingSystem.hpp"

#include <Usagi/Utility/Functional.hpp>
#include <Usagi/Runtime/Audio/AudioManager.hpp>
#include <Usagi/Runtime/Audio/AudioOutputStream.hpp>

namespace usagi
{
AudioStreamStatus BasicAudioMixingSystem::streamingCallback(
    const ArrayView<std::byte*> &channels,
    const std::size_t frames)
{
    for(std::size_t c = 0; c < channels.size(); ++c)
    {
        memset(channels[c], 0, frames * sizeof(float));
    }
    // for all entities mix their streams
    for(auto &&a : mRegistry)
    {
        std::get<BasicAudioStreamComponent *>(a.second)->mix(channels, frames);
    }
    return AudioStreamStatus::CONTINUE;
}

BasicAudioMixingSystem::BasicAudioMixingSystem(
    AudioManager *audio_manager)
{
    mDevice = audio_manager->defaultOutputDevice().acquireDevice();

    mOutputFormat.format = DataFormat::FLOAT32;
    mOutputFormat.interleaved = false;
    mOutputFormat.num_channels = 2;
    mOutputFormat.sample_rate = 44100;

    mStream = mDevice->createOutputStream(mOutputFormat, partial_apply(
        &BasicAudioMixingSystem::streamingCallback, this
    ));

    mStream->start();
}

void BasicAudioMixingSystem::update(const Clock &clock)
{
}
}
