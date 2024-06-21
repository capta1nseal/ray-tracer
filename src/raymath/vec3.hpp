#ifndef _RAYTRACERVEC3_
#define _RAYTRACERVEC3_


#include <concepts>
#include <type_traits>
#include <cmath>
#include <ostream>


/*
3D vector with x, y and z of templated floating point type
sanitize() method provided for value sanity.
Any attempt to divide by zero, including zero length normalization, will result in zero.
*/

template<typename T>
struct is_vec3basis : std::is_floating_point<T> { };


template<typename T>
concept Vec3Basis = is_vec3basis<T>::value;

template<Vec3Basis T>
struct Vec3
{
    T x, y, z;

    Vec3(T initX = T(0.0), T initY = T(0.0), T initZ = T(0.0)) : x(initX), y(initY), z(initZ) {}

    template<Vec3Basis U> Vec3(const Vec3<U>& other)
        : x(other.x), y(other.y), z(other.z) {}

    template<Vec3Basis U> bool operator==(const Vec3<U>& other) const
    { return x == other.x and y == other.y and z == other.z; }

    template<Vec3Basis U = T> bool operator==(U scalar) const
    { return x == scalar and y == scalar and z == scalar; }

    template<Vec3Basis U> auto operator+(const Vec3<U>& other) const
    { return Vec3<std::common_type_t<T, U>>(x + other.x, y + other.y, z + other.z); }

    template<Vec3Basis U = T> auto operator+(U scalar) const
    { return Vec3<std::common_type_t<T, U>>(x + scalar, y + scalar, z + scalar); }

    template<Vec3Basis U> auto operator-(const Vec3<U>& other) const
    { return Vec3<std::common_type_t<T, U>>(x - other.x, y - other.y, z - other.z); }

    template<Vec3Basis U = T> auto operator-(U scalar) const
    { return Vec3<std::common_type_t<T, U>>(x - scalar, y - scalar, z - scalar); }

    Vec3<T> operator-() const { return Vec3<T>(-x, -y, -z); }

    // operator* is dot product. operator% is cross product.
    template<Vec3Basis U> auto operator*(const Vec3<U>& other) const
    { return x * other.x + y * other.y + z * other.z; }

    template<Vec3Basis U = T> auto operator*(U scalar) const
    { return Vec3<std::common_type_t<T, U>>(x * scalar, y * scalar, z * scalar); }

    template<Vec3Basis U = T> auto operator/(U scalar) const
    { return Vec3<std::common_type_t<T, U>>(x / scalar, y / scalar, z / scalar); }

    // operator% is cross product. operator* is dot product.
    template<Vec3Basis U> auto operator%(const Vec3<U>& other) const
    {
        return Vec3<std::common_type_t<T, U>>(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

    template<Vec3Basis U> Vec3& operator+=(const Vec3<U>& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }
    template<Vec3Basis U = T> Vec3& operator+=(U scalar)
    {
        x += scalar;
        y += scalar;
        z += scalar;
        return *this;
    }

    template<Vec3Basis U> Vec3& operator-=(const Vec3<U>& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }
    template<Vec3Basis U = T> Vec3& operator-=(U scalar)
    {
        x -= scalar;
        y -= scalar;
        z -= scalar;
        return *this;
    }

    // multiplicative assignment is an element-wise multiplication by other's elements, not dot product.
    template<Vec3Basis U> Vec3& operator*=(const Vec3<U>& other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    }
    // divisive assignment is an element-wise division by other's elements, not some special operation.
    template<Vec3Basis U> Vec3& operator/=(const Vec3<U>& other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        return *this;
    }

    template<Vec3Basis U = T> Vec3& operator*=(U scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }
    template<Vec3Basis U = T> Vec3& operator/=(U scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    // empty parantheses operator is magnitude
    T operator()() const
    { return std::sqrt(x * x + y * y + z * z); }

    void normalize()
    {
        T length = (*this)();
        if (length == T(0.0) or length == T(1.0)) return;
        length = T(1.0) / length;
        x *= length;
        y *= length;
        z *= length;
    }
    Vec3 normalized() const
    {
        T length = (*this)();

        if (length == T(0.0)) return Vec3();
        if (length == T(1.0)) return *this;

        return (*this) * (T(1.0) / length);
    }

    // normal expected has a dot product with this direction vector <(/=) 0.0
    void reflect(const Vec3<T> normal)
    {
        (*this) = 2.0 * (normal * -(*this)) * normal + (*this);
    }
    // normal expected has a dot product with this direction vector <(/=) 0.0
    template<Vec3Basis U> auto reflected(const Vec3<U> normal)
    {
        return 2.0 * (normal * -(*this)) * normal + (*this);
    }


    void sanitize()
    {
        if (!std::isnormal(x)) x = T(0.0);
        if (!std::isnormal(y)) y = T(0.0);
        if (!std::isnormal(z)) z = T(0.0);
    }
};

template<Vec3Basis T> std::ostream& operator<<(std::ostream& os, const Vec3<T>& vec3)
{
    os << "(" << vec3.x << "," << vec3.y << "," << vec3.z << ")";
    return os;
}

template<Vec3Basis T, Vec3Basis U = T> auto operator*(U scalar, const Vec3<T>& vec3)
{ return vec3 * scalar; }

#endif
