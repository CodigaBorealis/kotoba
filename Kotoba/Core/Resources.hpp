#pragma once
#include "Kotoba/Core/Types.hpp"
#include "Kotoba/Utils/Utils.hpp"
#include <array>
#include <cstddef>
#include <filesystem>
#include <memory>
#include <string_view>
#include <algorithm>
#include <string>

struct Image;
struct Texture;
struct Font;
struct Music;
struct Sound;

namespace Kotoba{

    /*
    * @param N The number of supported file extensions
    * @param extension The file extension to check
    * @param supported The array containing the supported file extensions
    * Checks whether a file extension is supported
    * Converts the provided extension to uppercase before comparing it against the supported extensions
    * Returns true if the extension is supported, otherwise false
    */

    template<std::size_t N> bool isSupportedFormat(const std::string& extension, const std::array<std::string_view, N>& supported){

        const std::string normalized{Utils::toUpper(extension)};

        return std::ranges::find(supported, normalized) != supported.end();
    }

    /*
    * Represents an image resource
    * Manages the lifetime of an underlying raylib Image through an implementation pointer
    * Resources are non-copyable but movable
    * Using a resource after it has been moved from results in undefined behavior
    */

    class Image{

        public:

        /*
        * Provides access to the underlying raylib Image
        * Returns a mutable reference to the native Image
        * Using this function on a moved-from resource results in undefined behavior
        */

        [[nodiscard]] ::Image& native() noexcept;

       /*
        * Provides read-only access to the underlying raylib Image
        * Returns a constant reference to the native Image
        * Using this function on a moved-from resource results in undefined behavior
        */

        [[nodiscard]] const ::Image& native() const noexcept;

        [[nodiscard]] bool isValid() const noexcept;
        /*
        * @param path The filesystem path to the image file
        * Constructs an Image by loading the resource from the specified file
        */

        explicit Image(const std::filesystem::path& path);

        Image(const Image&) = delete;
        Image& operator=(const Image&) = delete;
        /*
        * Move constructor
        * Transfers resource ownership from another Image instance
        * The source instance becomes moved-from and must not be used
        */
        Image(Image&&) noexcept;
        /*
        * Move assignment operator
        * Transfers resource ownership from another Image instance
        * The source instance becomes moved-from and must not be used
        */
        Image& operator=(Image&&) noexcept;

        ~Image();

        /*
        * Returns the image width in pixels
        * Using this function on a moved-from resource results in undefined behavior
        */

        u32 width() const;
        /*
        * Returns the image height in pixels
        * Using this function on a moved-from resource results in undefined behavior
        */

        u32 height() const;

        private:

        struct Impl;
        std::unique_ptr<Impl> impl;
    };

    /*
    * Represents a texture resource
    * Manages the lifetime of an underlying raylib Texture through an implementation pointer
    * Resources are non-copyable but movable
    * Using a resource after it has been moved from results in undefined behavior
    */

    class Texture{

        public:

       /*
        * Provides access to the underlying raylib Texture
        * Returns a mutable reference to the native Texture
        * Using this function on a moved-from resource results in undefined behavior
        */

        [[nodiscard]] ::Texture& native() noexcept;

        /*
        * Provides read-only access to the underlying raylib Texture
        * Returns a constant reference to the native Texture
        * Using this function on a moved-from resource results in undefined behavior
        */

        [[nodiscard]] const ::Texture& native() const noexcept;
        [[nodiscard]] bool isValid() const noexcept;

        /*
        * @param path The filesystem path to the texture file
        * Constructs a Texture by loading the resource from the specified file
        */

        explicit Texture(const std::filesystem::path& path);

        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;

       /*
        * Move constructor
        * Transfers resource ownership from another Texture instance
        * The source instance becomes moved-from and must not be used
        */

        Texture(Texture&&) noexcept;
        /*
        * Move assignment operator
        * Transfers resource ownership from another Texture instance
        * The source instance becomes moved-from and must not be used
        */
        Texture& operator=(Texture&&) noexcept;

        ~Texture();
        /*
        * Returns the texture width in pixels
        * Using this function on a moved-from resource results in undefined behavior
        */
        u32 width() const;
        /*
        * Returns the texture height in pixels
        * Using this function on a moved-from resource results in undefined behavior
        */
        u32 height() const;

        private:

        struct Impl;
        std::unique_ptr<Impl> impl;
    };

    /*
    * Represents a font resource
    * Manages the lifetime of an underlying raylib Font through an implementation pointer
    * Resources are non-copyable but movable
    * Using a resource after it has been moved from results in undefined behavior
    */

    class Font{

        public:

        /*
        * Provides access to the underlying raylib Font
        * Returns a mutable reference to the native Font
        * Using this function on a moved-from resource results in undefined behavior
        */

        [[nodiscard]] ::Font& native() noexcept;

        /*
        * Provides read-only access to the underlying raylib Font
        * Returns a constant reference to the native Font
        * Using this function on a moved-from resource results in undefined behavior
        */

        [[nodiscard]] const ::Font& native() const noexcept;
        [[nodiscard]] bool isValid() const noexcept;

       /*
        * @param path The filesystem path to the font file
        * Constructs a Font by loading the resource from the specified file
        */

        explicit Font(const std::filesystem::path& path);

        Font(const Font&) = delete;
        Font& operator=(const Font&) = delete;

        /*
        * Move constructor
        * Transfers resource ownership from another Font instance
        * The source instance becomes moved-from and must not be used
        */

        Font(Font&&) noexcept;

        /*
        * Move assignment operator
        * Transfers resource ownership from another Font instance
        * The source instance becomes moved-from and must not be used
        */

        Font& operator=(Font&&) noexcept;

        ~Font();

        /*
        * Returns the size of the font
        * Using this function on a moved-from resource results in undefined behavior
        */

        u32 size() const;

        private:

        struct Impl;
        std::unique_ptr<Impl> impl;
    };

    /*
    * Represents a music resource
    * Manages the lifetime of an underlying raylib Music through an implementation pointer
    * Resources are non-copyable but movable
    * Using a resource after it has been moved from results in undefined behavior
    */

    class Music{

        public:

       /*
        * Provides access to the underlying raylib Music
        * Returns a mutable reference to the native Music
        * Using this function on a moved-from resource results in undefined behavior
        */

        [[nodiscard]] ::Music& native() noexcept;

        /*
        * Provides read-only access to the underlying raylib Music
        * Returns a constant reference to the native Music
        * Using this function on a moved-from resource results in undefined behavior
        */

        [[nodiscard]] const ::Music& native() const noexcept;
        [[nodiscard]] bool isValid() const noexcept;

        /*
        * @param path The filesystem path to the music file
        * Constructs a Music resource by loading the specified file
        */

        explicit Music(const std::filesystem::path& path);

        Music(const Music&) = delete;
        Music& operator=(const Music&) = delete;

        /*
        * Move constructor
        * Transfers resource ownership from another Music instance
        * The source instance becomes moved-from and must not be used
        */

        Music(Music&&) noexcept;

        /*
        * Move assignment operator
        * Transfers resource ownership from another Music instance
        * The source instance becomes moved-from and must not be used
        */

        Music& operator=(Music&&) noexcept;

        ~Music();

        private:

        struct Impl;
        std::unique_ptr<Impl> impl;
    };

   /*
    * Represents a sound resource
    * Manages the lifetime of an underlying raylib Sound through an implementation pointer
    * Resources are non-copyable but movable
    * Using a resource after it has been moved from results in undefined behavior
    */

    class Sound{

        public:

        /*
        * Provides access to the underlying raylib Sound
        * Returns a mutable reference to the native Sound
        * Using this function on a moved-from resource results in undefined behavior
        */

        [[nodiscard]] ::Sound& native() noexcept;

        /*
        * Provides read-only access to the underlying raylib Sound
        * Returns a constant reference to the native Sound
        * Using this function on a moved-from resource results in undefined behavior
        */

        [[nodiscard]] const ::Sound& native() const noexcept;
        [[nodiscard]] bool isValid() const noexcept;

        /*
        * @param path The filesystem path to the sound file
        * Constructs a Sound resource by loading the specified file
        */

        explicit Sound(const std::filesystem::path& path);

        Sound(const Sound&) = delete;
        Sound& operator=(const Sound&) = delete;
        /*
        * Move constructor
        * Transfers resource ownership from another Sound instance
        * The source instance becomes moved-from and must not be used
        */
        Sound(Sound&&) noexcept;
        /*
        * Move assignment operator
        * Transfers resource ownership from another Sound instance
        * The source instance becomes moved-from and must not be used
        */
        Sound& operator=(Sound&&) noexcept;

        ~Sound();

        private:

        struct Impl;
        std::unique_ptr<Impl> impl;
    };
}