#include "BasicAudioStreamComponent.hpp"

namespace usagi
{
std::size_t BasicAudioStreamComponent::mix(
    const ArrayView<std::byte *> &channels,
    const std::size_t frames)
{
    if(!playing) return 0;

    std::size_t written = 0;
    while(written < frames)
    {
        for(std::size_t c = 0; c < channels.size(); ++c)
        {
            const auto ch = reinterpret_cast<float*>(channels[c]);
            ch[written] += volume *
                buffer->channels[c % buffer->channels.size()][cursor];
        }
        ++written;
        ++cursor;
        if(cursor.current() == 0 && !loop)
        {
            playing = false;
            break;
        }
    }
    return written;
}
}
