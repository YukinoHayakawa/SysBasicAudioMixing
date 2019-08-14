#pragma once

#include <memory>

#include <Usagi/Core/Component.hpp>
#include <Usagi/Runtime/Audio/AudioBuffer.hpp>
#include <Usagi/Utility/RotateCounter.hpp>
#include <Usagi/Utility/ArrayView.hpp>

namespace usagi
{
struct BasicAudioStreamComponent : Component
{
    const std::type_info & baseType() override
    {
        return typeid(BasicAudioStreamComponent);
    }

    bool playing = false;
    bool loop = false;
    float volume = 1.f;
    // std::string asset_path;
    std::shared_ptr<AudioBuffer> buffer;
    RotateCounter<std::size_t> cursor;

    BasicAudioStreamComponent(
        std::shared_ptr<AudioBuffer> audio_buffer,
        bool playing,
        bool loop,
        float volume)
        : playing(playing)
        , loop(loop)
        , volume(volume)
        , buffer(std::move(audio_buffer))
        , cursor(buffer->frames)
    {
    }

    /**
     * \brief Mix samples onto channels. cursor will be incremented until
     * number of samples reached frame or the stream is ended and not looping.
     * \param channels
     * \param frames
     * \return Number of samples mixed.
     */
    std::size_t mix(
        const ArrayView<std::byte *> &channels,
        std::size_t frames);
};
}
