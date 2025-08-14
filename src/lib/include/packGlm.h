#ifndef PACK_GLM_H
#define PACK_GLM_H
#include <string>
#include <utility>

/**
 * packGlm<T> 的模板变量.
 * @tparam T packGlm 中 value 的类型.
 */
template <typename T>
struct packGlm
{
private:
    std::string path;
    T value;

public:

    /**
     * packGlm<T> 的隐式有参构造.
     * @param _value packGlm<T> 的 T 类型的值.
     * @param _path packGlm<T> 的当前路径.
     */
    packGlm(const T& _value, std::string _path)
        : path(std::move(_path))
          , value(_value)
    {
    }


    /**
     * packGlm 的显式有参构造函数.
     * @param _path packGlm 的当前路径.
     */
    explicit packGlm(std::string _path) : path(std::move(_path)), value(0.0f)
    {
    }


    /**
     * packGlm 的显式类型转换从 packGlm<T> 到 T
     * @return 返回 packGlm 包含的 T 类型值.
     */
    explicit operator T() const
    {
        return this->value;
    }


    /**
     * packGlm 的显式类型转换从 packGlm<T> 到 std::string.
     * @return 返回 packGlm<T> 包含的 path 的 std::string 类型值.
     */
    explicit operator std::string() const
    {
        return this->path;
    }


    /**
     * packGlm<T> 的 () 运算符重载, 用于设置 packGlm<T> 内部的 value 并返回 packGlm<T>.
     * @param _value 设置值.
     * @return 返回 packGlm<T> 的 *this.
     */
    packGlm& operator ()(const T& _value)
    {
        this->value = _value;
        return *this;
    }
};

struct templateStruct
{
private:
    std::string path;

public:
    explicit operator std::string() const
    {
        return this->path;
    }
};

#endif //PACK_GLM_H
