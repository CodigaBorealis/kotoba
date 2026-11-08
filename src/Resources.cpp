#include "Kotoba/Core/Resources.hpp"
#include "Kotoba/Core/ErrorCode.hpp"
#include "Kotoba/Core/Exception.hpp"
#include "Kotoba/Utils/Utils.hpp"
#include "Kotoba/Core/Raylib.hpp"
#include <filesystem>
#include <raylib.h>

namespace Kotoba{

    struct Image::Impl{

        explicit Impl(const std::filesystem::path& path){

            if(!std::filesystem::exists(path)) throw ResourceException("Resource not found : " + path.string(), ErrorCode::ResourceNotFound);
            
            if(!supportedImageFormat(path.extension().string())) throw ResourceException("Unsuported image format: " + path.extension().string(), ErrorCode::ResourceInvalidFormat);

            handle = ::LoadImage(path.c_str());

            if(!handle.data) throw ResourceException("Failed to load image: " + path.string(), ErrorCode::ResourceLoadFailed);
        }

        static bool supportedImageFormat(const std::string& extension){

            static constexpr std::array<std::string_view, 9> supported{

                ".PNG",
                ".BMP",
                ".TGA",
                ".JPG",
                ".JPEG",
                ".GIF",
                ".QOI",
                ".PSD",
                ".HDR"
            };

            return isSupportedFormat(extension, supported);
        }

        ~Impl(){

            if(handle.data) ::UnloadImage(handle);
        }

        ::Image handle{};
    };

    struct Texture::Impl{

        explicit Impl(const std::filesystem::path& path){

            if(!std::filesystem::exists(path)) throw ResourceException("Resource not found : " + path.string(), ErrorCode::ResourceNotFound);
            
            if(!supportedTextureFormat(path.extension().string())) throw ResourceException("Unsuported texture format: " + path.extension().string(), ErrorCode::ResourceInvalidFormat);

            handle = ::LoadTexture(path.c_str());

            if(handle.id == 0) throw ResourceException("Failed to load texture: " + path.string(), ErrorCode::ResourceLoadFailed);

        }

        static bool supportedTextureFormat(const std::string& extension){

            static constexpr std::array<std::string_view, 12> supported{

                ".PNG",
                ".BMP",
                ".JPG",
                ".GIF",
                ".PSD",
                ".DDS",
                ".HDR",
                ".KTX",
                ".ASTC",
                ".PKM",
                ".PVR",
                ".QOI"
            };

            return isSupportedFormat(extension, supported);
        }

        ~Impl(){

            if(handle.id != 0) ::UnloadTexture(handle);
        }

        ::Texture2D handle{};
    };

    struct Font::Impl{
        
        explicit Impl(const std::filesystem::path& path){

            if(!std::filesystem::exists(path)) throw ResourceException("Resource not found : " + path.string(), ErrorCode::ResourceNotFound);
            
            if(!supportedFontFormat(path.extension().string())) throw ResourceException("Unsuported font format: " + path.extension().string(), ErrorCode::ResourceInvalidFormat);

            handle = ::LoadFont(path.c_str());

            if(handle.texture.id == 0) throw ResourceException("Failed to load font: " + path.string(), ErrorCode::ResourceLoadFailed);

        }

        static bool supportedFontFormat(const std::string& extension){

            static constexpr std::array<std::string_view, 2> supported{

                ".TTF",
                ".OTF"
            };

            return isSupportedFormat(extension, supported);

        }

        ~Impl(){

            if(handle.texture.id != 0) ::UnloadFont(handle);
        }

        ::Font handle{};
    };
    
    struct Music::Impl{

        explicit Impl(const std::filesystem::path& path){

            if(!std::filesystem::exists(path)) throw ResourceException("Resource not found : " + path.string(), ErrorCode::ResourceNotFound);
            
            if(!supportedMusicFormat(path.extension().string())) throw ResourceException("Unsuported music format: " + path.extension().string(), ErrorCode::ResourceInvalidFormat);

            handle = ::LoadMusicStream(path.c_str());

            if(!handle.ctxData) throw ResourceException("Failed to load music: " + path.string(), ErrorCode::ResourceLoadFailed);

        }

        static bool supportedMusicFormat(const std::string& extension){

            static constexpr std::array<std::string_view, 6> supported{

                ".WAV",
                ".OGG",
                ".MP3",
                ".QOA",
                ".XM",
                ".MOD"
            };

            return isSupportedFormat(extension, supported);
      
        }

        ~Impl(){

            if(handle.ctxData) ::UnloadMusicStream(handle);
        }

        ::Music handle{};
    };

    struct Sound::Impl{

        explicit Impl(const std::filesystem::path& path){

            if(!std::filesystem::exists(path)) throw ResourceException("Resource not found : " + path.string(), ErrorCode::ResourceNotFound);
            
            if(!supportedSoundFormat(path.extension().string())) throw ResourceException("Unsuported sound format: " + path.extension().string(), ErrorCode::ResourceInvalidFormat);

            handle = ::LoadSound(path.c_str());

            if(handle.frameCount == 0) throw ResourceException("Failed to load sound: " + path.string(), ErrorCode::ResourceLoadFailed);
        }

        static bool supportedSoundFormat(const std::string& extension){

            static constexpr std::array<std::string_view, 6> supported{

                ".WAV",
                ".OGG",
                ".MP3",
                ".QOA",
                ".XM",
                ".MOD"
            };

            return isSupportedFormat(extension, supported);       
        }

        ~Impl(){

            if(handle.frameCount > 0) ::UnloadSound(handle);
        }

        ::Sound handle{};
    };

    Image::~Image() = default;

    Image::Image(Image&& other) noexcept = default;

    Image& Image::operator=(Image&& other) noexcept = default;

    Image::Image(const std::filesystem::path& path)
        :
        impl(std::make_unique<Impl>(path))
        {}

    u32 Image::height() const{

        return static_cast<u32>(impl->handle.height);
    }

    u32 Image::width() const{

        return static_cast<u32>(impl->handle.width);
    }

    ::Image& Image::native() noexcept{

        return impl->handle;
    }

    const ::Image& Image::native() const noexcept{

        return impl->handle;
    }

    u32 Texture::height() const{

        return static_cast<u32>(impl->handle.height);
    }

    u32 Texture::width() const{

        return static_cast<u32>(impl->handle.width);
    }

    Texture::~Texture() = default;

    Texture::Texture(Texture&& other) noexcept = default;

    Texture& Texture::operator=(Texture&& other) noexcept = default;

    Texture::Texture(const std::filesystem::path& path)
        :
        impl(std::make_unique<Impl>(path))
        {}

    ::Texture& Texture::native() noexcept{

        return impl->handle;
    }

    const ::Texture& Texture::native() const noexcept{

        return impl->handle;
    }

    Font::~Font() = default;

    Font::Font(Font&& other) noexcept = default;

    Font& Font::operator=(Font&& other) noexcept = default;

    Font::Font(const std::filesystem::path& path)
        :
        impl(std::make_unique<Impl>(path))
        {}
    
    u32 Font::size() const{

        return impl->handle.baseSize;
    }

    ::Font& Font::native() noexcept{

        return impl->handle;
    }

    const ::Font& Font::native() const noexcept{

        return impl->handle;
    }

    Music::~Music() = default;

    Music::Music(Music&& other) noexcept = default;

    Music& Music::operator=(Music&& other) noexcept = default;

    Music::Music(const std::filesystem::path& path)
        :
        impl(std::make_unique<Impl>(path))
        {}

    ::Music& Music::native() noexcept{

        return impl->handle;
    }

    const ::Music& Music::native() const noexcept{

        return impl->handle;
    }

    Sound::~Sound() = default;

    Sound::Sound(Sound&& other) noexcept = default;

    Sound& Sound::operator=(Sound&& other) noexcept = default;

    Sound::Sound(const std::filesystem::path& path)
        :
        impl(std::make_unique<Impl>(path))
        {}

    ::Sound& Sound::native() noexcept{

        return impl->handle;
    }

    const ::Sound& Sound::native() const noexcept{

        return impl->handle;
    }

}