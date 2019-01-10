class BigInt // Class representing large numbers (somewhat unoptimized implementation)
{
    static const int base = 1000;
    static const int basewidth = 3;
public:
    std::vector<int> v;
    BigInt(int a = 0)
    {
        if(a)
            v.push_back(a);
    }

    BigInt operator+(BigInt b)
    {
        BigInt c;
        int carry = 0;
        v.resize(std::max(b.v.size(), v.size()), 0);
        b.v.resize(std::max(b.v.size(), v.size()), 0);
        for(int i = 0; i < v.size(); i++)
        {
            c.v.push_back((v[i]+b.v[i]+carry) % base);
            carry = (v[i]+b.v[i]+carry)/base;
        }
        if(carry)
            c.v.push_back(carry);
        return c;
    }

    BigInt operator-(BigInt b)
    {
        BigInt c;
        int carry = 0;
        v.resize(std::max(b.v.size(), v.size()), 0);
        b.v.resize(std::max(b.v.size(), v.size()), 0);
        for(int i = 0; i < v.size(); i++)
        {
            int newcarry = 0;
            if(v[i] < (b.v[i]+carry))
                newcarry = 1; 
            c.v.push_back(((base+v[i])-(b.v[i]+carry)) % base);
            carry = newcarry;
        }
        if(c.v.back() == 0)
            c.v.pop_back();
        return c;
    }

    BigInt operator*(int t)
    {
        BigInt c;
        int carry = 0;
        for(int i = 0; i < v.size(); i++)
        {
            c.v.push_back((v[i]*t+carry) % base);
            carry = (v[i]*t+carry)/base;
        }
        if(carry)
            c.v.push_back(carry);
        return c;
    }

    BigInt operator/(int t)
    {
        BigInt c;
        int carry = 0;
        for(int i = v.size()-1; i >= 0; i--)
        {
            int res = (carry+v[i])/t;
            carry = ((carry+v[i])-res*t)*base;
            c.v.push_back(res % base);
        }
        std::reverse(c.v.begin(), c.v.end());
        if(c.v.back() == 0)
            c.v.pop_back();
        return c;
    }

    bool operator==(BigInt b)
    {
        return !(v < b.v) && !(b.v < v);
    }

    bool operator<(BigInt b)
    {
        if(v.size() != b.v.size())
            return v.size() < b.v.size();
        for(int i = v.size()-1; i >= 0; i--)
        {
            if(v[i] != b.v[i])
                return v[i] < b.v[i];
        }
        return false;
    }

    std::string str()
    {
        std::string ret;
        for(int i = v.size()-1; i >= 0; i--)
        {
            std::string s = std::to_string(v[i]);
            ret += (i < v.size()-1 ? std::string(basewidth-s.size(), '0') : "") + s;
        }
        return ret;
    }
    friend BigInt operator*(int b, BigInt);
};

BigInt operator*(int t, BigInt b)
{
    BigInt c;
    int carry = 0;
    for(int i = 0; i < b.v.size(); i++)
    {
        c.v.push_back((b.v[i]*t+carry) % BigInt::base);
        carry = (b.v[i]*t+carry)/BigInt::base;
    }
    if(carry)
        c.v.push_back(carry);
    return c;
}
