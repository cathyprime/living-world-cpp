#include "record.hpp"

Record::Record(int birth, int death, std::vector<int> ancestors)
    : birth_(birth), death_(death), ancestors_(ancestors){};

Record::operator std::string()
{
    auto d = death_;
    std::string d_str = (d) ? std::to_string(d.value()) : "not dead yet";

    return "date of birth: " + std::to_string(birth_) + ", date of death: " + d_str;
}

void Record::operator+=(const int &rhs)
{
    ancestors_.push_back(rhs);
}

std::ostream &operator<<(std::ostream &os, Record &r)
{
    return os << (std::string)r;
}

std::string operator+(const std::string &str, Record record)
{
    return str + (std::string)record;
}
