#include <boost/yaml/json.hpp>


int main()
{
    std::string str;
    while (getline(std::cin, str)) {
        if (str.empty())
            break;

        boost::optional<boost::json::value> value;
        if ((value = boost::json::parse(
                 str, [](std::string const & msg) { std::cout << msg; }))) {
            std::cout << "Parsed value:\n";
            std::cout << *value << std::endl;
        }
    }

    return 0;
}
