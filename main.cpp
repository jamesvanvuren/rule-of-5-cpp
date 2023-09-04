#include <iostream>
#include <memory>

using namespace std; 

// Placeholder for a class that is expensive to copy.
class WidgetImpl
{
public:

    // Default ctor.
    WidgetImpl();

    WidgetImpl(int data);

    // Copy ctor.
    WidgetImpl(const WidgetImpl & rhs);

    // Move ctor.
    WidgetImpl(WidgetImpl && rhs);

    // Copy assignment operator.
    WidgetImpl & operator=(const WidgetImpl & rhs);

    // Move assignment operator.
    WidgetImpl & operator=(WidgetImpl && rhs);

    // Destructor.
    virtual ~WidgetImpl();

    virtual int getData();

    virtual unique_ptr<WidgetImpl> clone();

private:
    int _data;
};

// Default ctor.
WidgetImpl::WidgetImpl()
{
}

WidgetImpl::WidgetImpl(int data) : _data(data)
{
}

// Copy ctor.
WidgetImpl::WidgetImpl(const WidgetImpl & rhs) : _data(rhs._data)
{
}

// Move ctor.
WidgetImpl::WidgetImpl(WidgetImpl && rhs) : _data(rhs._data)
{
}

// Copy assignment operator.
WidgetImpl & WidgetImpl::operator=(const WidgetImpl & rhs)
{
    if (this != &rhs)
    {
        this->_data = rhs._data;
    }

    return *this;
}

// Move assignment operator.
WidgetImpl & WidgetImpl::operator=(WidgetImpl && rhs)
{
    if (this != &rhs)
    {
        this->_data = rhs._data;
    }

    return *this;
}

// Destructor.
WidgetImpl::~WidgetImpl()
{
}

int WidgetImpl::getData()
{
    return _data;
}

unique_ptr<WidgetImpl> WidgetImpl::clone()
{
    return std::make_unique<WidgetImpl>(this->_data);
}

class Widget
{
public:
    // Default ctor.
    Widget();

    Widget(int data);

    // Copy ctor.
    Widget(const Widget & rhs);

    // Move ctor.
    Widget(Widget && rhs);

    // Copy assignment operator.
    Widget & operator=(const Widget & rhs);

    // Move assignment operator.
    Widget & operator=(Widget && rhs);

    // Destructor.
    ~Widget();

    int getData();

private:
    std::unique_ptr<WidgetImpl> _impl;
};

// Default ctor.
Widget::Widget() : _impl(std::move(std::make_unique<WidgetImpl>()))
{
}

Widget::Widget(int data) : _impl(std::move(std::make_unique<WidgetImpl>(data)))
{
}

// Copy ctor.
Widget::Widget(const Widget & rhs) : _impl(std::move(std::make_unique<WidgetImpl>(*(rhs._impl))))
{
}

// Move ctor.
Widget::Widget(Widget && rhs) : _impl(std::move(rhs._impl))
{
}

// Copy assignment operator.
Widget & Widget::operator=(const Widget & rhs)
{
    if (this != &rhs)
    {
        this->_impl = make_unique<WidgetImpl>(*(rhs._impl));
    }

    return *this;
}

// Move assignment operator.
Widget & Widget::operator=(Widget && rhs)
{
    if (this != &rhs)
    {
        this->_impl = std::move(rhs._impl);
    }

    return *this;
}

// Destructor.
Widget::~Widget()
{
}

int Widget::getData()
{
    return _impl->getData();
}

int main()
{

    // Default ctor.
    Widget widget1;

    Widget widget2(42);

    // Copy ctor.
    Widget widget3(42);
    Widget widget4 = widget3;

    // Move ctor.

    Widget widget5(42);
    // This invokes the move ctor.
    Widget widget6 = std::move(widget5);

    // This invokes only the int ctor.
    Widget widget7 = Widget(42);

    // This invokes the int ctor, then the move ctor.
    Widget widget8 = std::move(Widget(42));

    // Copy assignment operator.
    Widget widget9(42);
    Widget widget10;
    widget10 = widget9;

    // Move assignment operator.
    Widget widget11(42);
    Widget widget12;
    widget12 = std::move(widget11);

    return 0;

}