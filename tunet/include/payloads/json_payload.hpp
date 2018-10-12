//
// Created by Hippolyte Barraud on 10/12/18.
//

#ifndef THUNET_ASUS_KEEPALIVE_JSON_PAYLOAD_HPP
#define THUNET_ASUS_KEEPALIVE_JSON_PAYLOAD_HPP

#include <json/gason.hpp>
#include <boost/system/error_code.hpp>
#include <boost/utility/string_view.hpp>
#include <boost/optional.hpp>

struct json_payload {
    std::string _source;
    JsonAllocator _alloc;
    JsonValue _value;

public:

    json_payload() = delete;

    json_payload(json_payload const &) = delete;

    json_payload(json_payload &&other) = default;
    json_payload &operator=(const json_payload &) = delete;

    json_payload(boost::string_view json, boost::system::error_code &err) noexcept;

    template<typename T>
    boost::optional<T> operator[](boost::string_view) const noexcept { return nullptr; }
};

template<>
boost::optional<double> json_payload::operator[](boost::string_view name) const noexcept;

template<>
boost::optional<boost::string_view> json_payload::operator[](boost::string_view name) const noexcept;

#endif //THUNET_ASUS_KEEPALIVE_JSON_PAYLOAD_HPP
