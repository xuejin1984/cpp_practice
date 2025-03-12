#include <iostream>
#include <optional>

class Handle{
    public:
    std::optional<int> print2nums(int a, int b){
        std::cout << a << std::endl;
        std::cout << b << std::endl;
        return 3;
    }
    
};

template<typename... Args,
            typename Handler = std::optional<int> (Handle::*)(Args...)>
void callHandler(Handler handler, Args... args)
{
    Handle hdl;
    auto ret = (hdl.*handler)(args...);
    std::cout << *ret << std::endl;
}

int main()
{
    callHandler(&Handle::print2nums, 1, 2);
    return 0;
}