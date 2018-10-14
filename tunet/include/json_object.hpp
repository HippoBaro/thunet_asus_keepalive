//
// Created by Hippolyte Barraud on 10/12/18.
//

#ifndef THUNET_ASUS_KEEPALIVE_JSON_PAYLOAD_HPP
#define THUNET_ASUS_KEEPALIVE_JSON_PAYLOAD_HPP

#include <boost/system/error_code.hpp>
#include <boost/utility/string_view.hpp>
#include <boost/optional.hpp>
#include <json/gason.hpp>

struct json_object {
    std::string _source;
    JsonAllocator _alloc;
    JsonValue _value;

public:

    json_object() = delete;

    json_object(json_object const&) = delete;

    json_object(json_object &&) = default;

    json_object(boost::string_view json, boost::system::error_code &err) noexcept;
    json_object(JsonValue const&) noexcept;

    template<typename T>
    boost::optional<T> operator[](boost::string_view) const noexcept { return nullptr; }
};

template<>
boost::optional<double> json_object::operator[](boost::string_view name) const noexcept;

template<>
boost::optional<boost::string_view> json_object::operator[](boost::string_view name) const noexcept;

template<>
boost::optional<JsonValue> json_object::operator[](boost::string_view name) const noexcept;

#endif //THUNET_ASUS_KEEPALIVE_JSON_PAYLOAD_HPP
