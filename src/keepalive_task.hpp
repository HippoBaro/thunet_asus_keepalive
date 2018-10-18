//
// Created by Hippolyte Barraud on 10/14/18.
//

#ifndef THUNET_ASUS_KEEPALIVE_KEEPALIVE_TAKS_HPP
#define THUNET_ASUS_KEEPALIVE_KEEPALIVE_TAKS_HPP


#include <periodic_task.hpp>
#include <user_settings.hpp>

struct keepalive_task : public periodic_task {
    user_settings const& settings;

    keepalive_task(boost::asio::io_context &ioc, user_settings const& settings);

    int task(boost::asio::io_context &ctx) override;

    virtual ~keepalive_task();

    boost::string_view name() override;

private:
    bool login_account(boost::asio::io_context &ioc, boost::string_view username, boost::string_view password,
                       boost::system::error_code &ec);

    user_settings::account_container::const_iterator current_account;
};


#endif //THUNET_ASUS_KEEPALIVE_KEEPALIVE_TAKS_HPP
