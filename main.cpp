#include <stdio.h>
#include <chrono>
#include <thread>
#include <functional>
#include <iostream>


struct ToDoItem
{
    std::chrono::time_point<std::chrono::system_clock> timePoint;
    std::string message;
};

struct ToDoList
{
    /* you can change the signature, 
    but the item should be passed as cheaper as possible (only ctor, no copy)
    also this function should be thread safe*/
    void addItem(ToDoItem item){}

    struct NotifierGuard {
        ToDoList& list;
        template<typename F>
        NotifierGuard(ToDoList& list_, F callback)
        : list{ list_ } {
            list.setCallbackNotifier(callback);
        }
        ~NotifierGuard(){
            list.detachCallBack();
        }
    };

private:
    /* this function should be thread safe */
    template<typename F>
    void setCallbackNotifier(F callback){}
    void detachCallBack(){}
    
};

int main()
{
    bool notified = false;
    auto testNotification = 
        [&notified](std::string const& message) mutable
        { notified = true; std::cout << message << std::endl; };
        
    ToDoList list;
    ToDoList::NotifierGuard guard{ list, testNotification };
    list.addItem(
        ToDoItem{ std::chrono::system_clock::now() + std::chrono::seconds{ 5 }
            , "test message"});
    if(notified) {
        std::cout << "Failed. Notification has come too early";
    }
    std::this_thread::sleep_for(std::chrono::seconds{ 10 });
    if(!notified) {
        std::cout << "Failed. Notification hasn't come at all";
    }
    return 0;
}