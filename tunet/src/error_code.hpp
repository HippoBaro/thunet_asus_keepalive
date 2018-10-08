//
// Created by Hippolyte Barraud on 10/11/18.
//

#ifndef THUNET_ASUS_KEEPALIVE_ERROR_CODE_HPP
#define THUNET_ASUS_KEEPALIVE_ERROR_CODE_HPP

#include <boost/system/error_code.hpp>

enum class tunet_service_error {
    failed_challenge_retrieval = 2000,
    traffic_duration_exhausted = 3001,
    billing_policy = 3002,
    control_policy = 3003,
    insufficient_balance = 3004,
    unknown_user = 2531,
    connection_interval = 2532,
    too_many_attempt = 2533,
    wrong_password = 2553,
    not_a_dedicated_client = 2601,
    no_network_access = 2606,
    mac_binding_error = 2611,
    nas_binding_error = 2613,
    insufficient_balance_second = 2616,
    connection_number_exceeded = 2620,
    no_eligible_product = 2806,
    no_eligible_billing = 2807,
    no_eligible_control = 2808,
    malformed_ip = 2833,
    external_access_refused = 2840,
    ip_binding_error =2841,
    no_auth_required = 2842,
    unknown_ip = 2843,
    blacklisted_ip = 2844,
    third_party_auth_failed = 2901
};

namespace boost::system {
    template<>
    struct is_error_code_enum<tunet_service_error> : std::true_type {
    };
}

boost::system::error_code make_error_code(tunet_service_error e) noexcept;

#endif //THUNET_ASUS_KEEPALIVE_ERROR_CODE_HPP
