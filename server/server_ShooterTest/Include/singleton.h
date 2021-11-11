#pragma once

template<typename T>
class Singleton{
public:
    static T& GetInstance(){
        static T instance;
        return instance;
    }

    Singleton(T&&) = delete;
    Singleton(const T&) = delete;
    void operator= (const T&) = delete;

protected:
    Singleton() {
        //printf("singleton created.\n");
    };
    virtual ~Singleton(){
        //printf("singleton destroyed.\n");
    };
};