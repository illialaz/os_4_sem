#ifndef BUFFERED_CHANNEL_H_
#define BUFFERED_CHANNEL_H_

#include <stdio.h>
#include <mutex>
#include <queue>

template<class T>
class BufferedChannel {
  private:
    const int bufSize;
    std::queue<T> q;
    mutable std::mutex lockAdd;
    std::condition_variable qCheck;
    bool isOpen;
    bool isEmpty;

  public:
    explicit BufferedChannel(int size) : bufSize(size), isOpen(true), isEmpty(true) {}

    void Send(T value) {
      std::unique_lock<std::mutex> lock(lockAdd);
      if(!isOpen) throw std::runtime_error("chanel is closed");
      q.push(value);
      isEmpty = false;
      qCheck.notify_all();
    }

    std::pair<T, bool> Recv() {
      std::unique_lock<std::mutex> lock(lockAdd);
      while(isEmpty) qCheck.wait(lockAdd);
      T el;
      if(!q.empty()) {
        el = q.front();
        q.pop();
      }
      return std::make_pair(el, isOpen);
    }

    void Close() {
      std::unique_lock<std::mutex> lock(lockAdd);
      isOpen = false;
      qCheck.notify_all();
    }
};

#endif // BUFFERED_CHANNEL_H_
