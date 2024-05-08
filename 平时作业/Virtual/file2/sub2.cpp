class integral
{
public:
    virtual double value() = 0;
    virtual ~integral() {}
};

class integral_sin : public integral
{
private:
    double lower_limit;
    double upper_limit;
public:
    double value() {
        double result = 0.0;
        double step = (upper_limit - lower_limit) / 10000;
        for (int i = 0; i <= 10000; ++i)
        {
            result += sin(lower_limit + step * i) * step;
        }
        return result;
    }
    friend istream& operator>>(istream& in, integral_sin& sin)
    {
        in >> sin.lower_limit >> sin.upper_limit;
        return in;
    }
};

class integral_cos : public integral
{
private:
    double lower_limit;
    double upper_limit;
public:
    double value() {
        double result = 0.0;
        double step = (upper_limit - lower_limit) / 10000;
        for (int i = 0; i <= 10000; ++i)
        {
            result += cos(lower_limit + step * i) * step;
        }
        return result;
    }
    friend istream& operator>>(istream& in, integral_cos& cos)
    {
        in >> cos.lower_limit >> cos.upper_limit;
        return in;
    }
};

class integral_exp :public integral
{
private:
    double lower_limit;
    double upper_limit;
public:
    double value() {
        double result = 0.0;
        double step = (upper_limit - lower_limit) / 10000;
        for (int i = 0; i <= 10000; ++i)
        {
            result += exp(lower_limit + step * i) * step;
        }
        return result;
    }
    friend istream& operator>>(istream& in, integral_exp& exp)
    {
        in >> exp.lower_limit >> exp.upper_limit;
        return in;
    }
};


