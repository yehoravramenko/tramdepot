module;
#include <Unknwn.h>
export module wext;

import std;

export namespace wext
{
template <typename T>
concept ComChild = std::derived_from<T, IUnknown>;

template <ComChild T> class com_ptr
{
  public:
    ~com_ptr() { this->rawPtr->Release(); }

    inline T *get() const { return this->rawPtr; }
    inline T **put() { return &this->rawPtr; }
    inline T *operator->() { return this->rawPtr; }

  private:
    T *rawPtr = nullptr;
};
} // namespace wext