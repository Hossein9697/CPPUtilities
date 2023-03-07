#ifndef SMART_POINTER_UTILITY_HPP
#define SMART_POINTER_UTILITY_HPP

#include <memory>

class SmartPointerUtility
{

public:
    template <class T, class... Types>
    static std::unique_ptr<T> makeUniquePointer(Types&&... Args)
    {
        // return (unique_ptr<T>(new T(forward<Types>(Args)...)));
        return std::make_unique<T>(std::forward<Types>(Args)...);
    }

    template <class T, class... Types>
    static std::shared_ptr<T> makeSharedPointer(Types&&... Args)
    {
        // return (shared_ptr<T>(new T(forward<Types>(Args)...)));
        return std::make_shared<T>(std::forward<Types>(Args)...);
    }
};

#endif // SMART_POINTER_UTILITY_HPP
