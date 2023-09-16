#pragma once

#include <unordered_map> 
#include <typeindex>
#include <any>
#include <functional>
#include <memory>
#include <format>


class Container {
public:
    template<class T>
    using Generator = std::function<std::shared_ptr<T>()>;
    template<class T>
    void RegisterFactory(Generator<T> gen) {
        factoryMap[typeid(T)] = gen;
    }
    template<class T>
    std::shared_ptr<T> Resolve() {
        if(const auto i = factoryMap.find(typeid(T); i != factoryMap.end())) {
            return std::any_cast<Generator<T>>(i->second)();
        }
        else {
            throw std::runtime_error { std::format("Could not find generator for type [{}] in factory map!", typeid(T).name()) };y
        }
    }
    static Container& Get() {
        static Container c;
        return c;
    }
private:
    std::unordered_map<std::type_index, std::any> factoryMap;
};