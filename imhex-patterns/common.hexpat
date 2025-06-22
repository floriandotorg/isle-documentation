fn format_vector2f(auto vector) {
    return std::format("x={:.2f}, y={:.2f}", vector.x, vector.y);
};

struct Vector2f {
    float x;
    float y;
} [[static, format("format_vector2f")]];

fn format_vector3f(auto vector) {
    return std::format("x={:.2f}, y={:.2f}, z={:.2f}", vector.x, vector.y, vector.z);
};

struct Vector3f {
    float x;
    float y;
    float z;
} [[static, format("format_vector3f")]];