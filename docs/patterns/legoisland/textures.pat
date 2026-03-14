#pragma author xZise
#pragma description Textures from SI files in Lego Island 
#pragma endian little

import std.string;
import type.color;

using Color = type::RGB8 [[hex::inline_visualize("color", r, g, b, 0xff)]];

struct Gif {
    u32 width;
    u32 height;
    u32 num_colors;
    Color colors[num_colors];
    u8 image[width * height];
};

struct NamedGif {
    std::string::SizedString<u32> name;
    Gif gif [[inline]];
};

struct Textures {
    u32 num_images;
    NamedGif images[num_images];
};
