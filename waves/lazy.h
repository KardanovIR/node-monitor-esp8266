template <typename T>
class Lazy
{
  public:
    Lazy()
    {
        init = false;
    }

    void set(T newValue)
    {
        init = true;
        value = newValue;
    }

    T get()
    {
        return value;
    }

    bool isInit()
    {
        return init;
    }

  private:
    T value;
    bool init;
};