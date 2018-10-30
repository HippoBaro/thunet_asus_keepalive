//
// Created by Hippolyte Barraud on 10/12/18.
//

#include <boost/system/error_code.hpp>
#include <json_object.hpp>

namespace boost {
    inline void throw_exception(std::exception const &) {
        std::abort();
    }

} // namespace boost

json_object::json_object(boost::string_view json, boost::system::error_code &err) noexcept : _source(json) {
    auto begin = const_cast<char *>(_source.data()); //Work-around GCC 6.4 bug
    auto end = &(*(_source.end() - 1));
    int status = jsonParse(begin, &end, &_value, _alloc);
    if (status != JSON_OK) {
        err = boost::system::errc::make_error_code(boost::system::errc::bad_message);
    }
}

json_object::json_object(JsonValue const &val) noexcept : _value(val) {

}

template<>
boost::optional<double> json_object::operator[](boost::string_view name) const noexcept {
    for (auto item : _value) {
        if (std::equal(name.begin(), name.end(), item->key) && item->value.isDouble()) {
            return item->value.toNumber();
        }
    }
    printf("didn't find name in json\n");
    return {};
}

template<>
boost::optional<boost::string_view> json_object::operator[](boost::string_view name) const noexcept {
    for (auto item : _value) {
        if (std::equal(name.begin(), name.end(), item->key) && !item->value.isDouble()) {
            return boost::string_view(item->value.toString());
        }
    }
    return {};
}

template<>
boost::optional<JsonValue> json_object::operator[](boost::string_view name) const noexcept {
    for (auto item : _value) {
        if (std::equal(name.begin(), name.end(), item->key)) {
            return item->value;
        }
    }
    return {};
}