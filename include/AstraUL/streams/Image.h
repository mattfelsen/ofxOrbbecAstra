#ifndef IMAGE_H
#define IMAGE_H

#include <Astra/Astra.h>
#include <stdexcept>
#include <AstraUL/astraul_ctypes.h>
#include <AstraUL/streams/image_capi.h>
#include <iostream>
#include <cstdint>

namespace astra {

    struct RGBPixel : public astra_rgb_pixel_t
    {
        RGBPixel()
            : RGBPixel(0, 0, 0)
        {}

        RGBPixel(uint8_t r, uint8_t g, uint8_t b)
        {
            ::astra_rgb_pixel_t::r = r;
            ::astra_rgb_pixel_t::g = g;
            ::astra_rgb_pixel_t::b = b;
        }
    };

    class ImageStreamMode : private ::astra_imagestream_mode_t
    {
    public:
        ImageStreamMode()
        {}

        ImageStreamMode(std::uint32_t width, std::uint32_t height, std::uint8_t fps, astra_pixel_format_t format)
        {
            set_width(width);
            set_height(height);
            set_fps(fps);
            set_pixelFormat(format);
        }

        ImageStreamMode(const ::astra_imagestream_mode_t& mode)
        {
            *this = mode;
        }

        ImageStreamMode& operator=(const ::astra_imagestream_mode_t& mode)
        {
            set_width(mode.width);
            set_height(mode.height);
            set_fps(mode.fps);
            set_pixelFormat(mode.pixelFormat);

            return *this;
        }

        operator ::astra_imagestream_mode_t*() { return this; }
        operator const ::astra_imagestream_mode_t*() const { return this; }

        std::uint8_t fps() const { return astra_imagestream_mode_t::fps; }
        void set_fps(std::uint8_t fps) { astra_imagestream_mode_t::fps = fps; }

        std::uint8_t bytesPerPixel() const
        {
            std::uint8_t bpp;
            astra_pixelformat_get_bytes_per_pixel(pixelFormat(), &bpp);
            return bpp;
        }

        std::uint32_t width() const { return astra_imagestream_mode_t::width; }
        void set_width(std::uint32_t width) { astra_imagestream_mode_t::width = width; }

        std::uint32_t height() const { return astra_imagestream_mode_t::height; }
        void set_height(std::uint32_t height) { astra_imagestream_mode_t::height = height; }

        astra_pixel_format_t pixelFormat() const { return astra_imagestream_mode_t::pixelFormat; }
        void set_pixelFormat(astra_pixel_format_t format) { astra_imagestream_mode_t::pixelFormat = format; }

        friend std::ostream& operator<<(std::ostream& os, const ImageStreamMode& ism);
    };

    inline bool operator==(const ImageStreamMode& lhs, const ImageStreamMode& rhs)
    {
        return
            lhs.width() == rhs.width() &&
            lhs.height() == rhs.height() &&
            lhs.pixelFormat() == rhs.pixelFormat() &&
            lhs.fps() == rhs.fps() &&
            lhs.bytesPerPixel() && rhs.bytesPerPixel();
    }

    inline bool operator!=(const ImageStreamMode& lhs, const ImageStreamMode& rhs)
    {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const ImageStreamMode& ism)
    {
        os << ism.width()
           << "x"
           << ism.height()
           << "x"
           << static_cast<int>(ism.bytesPerPixel())
           << "@"
           << static_cast<int>(ism.fps())
           << " pf:"
           << ism.pixelFormat();

        return os;
    }

    class ImageStream : public DataStream
    {
    public:
        explicit ImageStream(astra_streamconnection_t connection)
            : DataStream(connection),
              m_imageStream(reinterpret_cast<astra_imagestream_t>(connection))
        {}

        float horizontalFieldOfView()
        {
            float hFov = 0.0f;
            astra_imagestream_get_hfov(m_imageStream, &hFov);

            return hFov;
        }

        float verticalFieldOfView()
        {
            float vFov = 0.0f;
            astra_imagestream_get_vfov(m_imageStream, &vFov);

            return vFov;
        }

        bool mirroring_enabled()
        {
            bool mirroring = false;
            astra_imagestream_get_mirroring(m_imageStream, &mirroring);

            return mirroring;
        }

        void enable_mirroring(bool mirroring)
        {
            astra_imagestream_set_mirroring(m_imageStream, mirroring);
        }

        std::vector<ImageStreamMode> available_modes()
        {
            astra_result_token_t token;
            std::size_t count = 0;
            astra_imagestream_request_modes(m_imageStream, &token, &count);

            std::vector<ImageStreamMode> result;
            result.resize(count);

            astra_imagestream_get_modes_result(m_imageStream,
                                               token,
                                               reinterpret_cast<astra_imagestream_mode_t*>(&result[0]),
                                               count);

            return result;
        }

        void set_mode(const ImageStreamMode& mode)
        {
            astra_imagestream_set_mode(m_imageStream, mode);
        }

    private:
        astra_imagestream_t m_imageStream;
    };

    template<typename TDataType, astra_stream_type_t TStreamType>
    class ImageFrame
    {
    public:
        ImageFrame(astra_imageframe_t frame, astra_pixel_format_t expected_format)
        {
            m_imageFrame = frame;
            if (m_imageFrame)
            {
                astra_imageframe_get_metadata(m_imageFrame, &m_metadata);
                if (m_metadata.pixelFormat != expected_format)
                {
                    //wrong format -- this must be an invalid frame
                    m_imageFrame = nullptr;
                    return;
                }

                astra_imageframe_get_frameindex(m_imageFrame, &m_frameIndex);

                void* voidData = nullptr;
                astra_imageframe_get_data_ptr(m_imageFrame, &voidData, &m_byteLength);
                m_dataPtr = static_cast<TDataType*>(voidData);
            }
        }

        bool is_valid() { return m_imageFrame != nullptr; }

        int resolutionX() { throwIfInvalidFrame(); return m_metadata.width; }
        int resolutionY() { throwIfInvalidFrame(); return m_metadata.height; }

        std::uint8_t bytesPerPixel()
        {
            throwIfInvalidFrame();

            std::uint8_t bpp;
            astra_pixelformat_get_bytes_per_pixel(m_metadata.pixelFormat, &bpp);
            return bpp;
        }

        astra_frame_index_t frameIndex() { throwIfInvalidFrame(); return m_frameIndex; }
        astra_imageframe_t handle() { return m_imageFrame; }

        static astra_stream_type_t streamType() { return TStreamType; }

        const TDataType* data() { throwIfInvalidFrame(); return m_dataPtr; }
        size_t byteLength() { throwIfInvalidFrame(); return m_byteLength; }
        size_t numberOfPixels() { throwIfInvalidFrame(); return m_metadata.width * m_metadata.height; }

        void copy_to(TDataType* buffer)
        {
            throwIfInvalidFrame();
            astra_imageframe_copy_data(m_imageFrame, buffer);
        }

        template<typename TFrameType>
        static TFrameType acquire(astra_reader_frame_t readerFrame,
                                  astra_stream_subtype_t subtype)
        {
            if (readerFrame != nullptr)
            {
                astra_imageframe_t imageFrame;
                astra_reader_get_imageframe(readerFrame, TStreamType, subtype, &imageFrame);

                return TFrameType(imageFrame);
            }

            return TFrameType(nullptr);
        }

    private:
        void throwIfInvalidFrame()
        {
            if (!m_imageFrame)
            {
                throw std::logic_error("Cannot operate on an invalid frame");
            }
        }

        astra_imageframe_t m_imageFrame{nullptr};
        astra_image_metadata_t m_metadata;
        astra_frame_index_t m_frameIndex;

        TDataType* m_dataPtr;

        size_t m_byteLength;
    };
}

#endif // IMAGE_H
