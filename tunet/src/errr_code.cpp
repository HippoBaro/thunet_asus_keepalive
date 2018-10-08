//
// Created by Hippolyte Barraud on 10/11/18.
//

# include <error_code.hpp>

namespace {

    struct tunet_error_category : boost::system::error_category {
        const char *name() const noexcept override;

        std::string message(int ev) const override;
    };

    const char *tunet_error_category::name() const noexcept {
        return "tunet";
    }

    std::string tunet_error_category::message(int ev) const {
        switch (static_cast<tunet_service_error >(ev)) {
            case tunet_service_error::failed_challenge_retrieval:
                return "Failed to get a valid challenge token. (未能获得有效的挑战令牌。)";
            case tunet_service_error::traffic_duration_exhausted:
                return "The flow or time has been exhausted. (流量或时长已用尽。)";
            case tunet_service_error::billing_policy:
                return "The charging policy condition does not match. (计费策略条件不匹配。)";
            case tunet_service_error::control_policy:
                return "Control policy conditions do not match. (控制策略条件不匹配。)";
            case tunet_service_error::insufficient_balance:
            case tunet_service_error::insufficient_balance_second:
                return "Sorry, your credit is running low. (余额不足。)";
            case tunet_service_error::unknown_user:
                return "The user does not exist. (用户不存在。)";
            case tunet_service_error::connection_interval:
                return "The interval between the two certification is too short. (两次认证的间隔太短。)";
            case tunet_service_error::too_many_attempt:
                return "The number of attempts is too frequent. (尝试次数过于频繁。)";
            case tunet_service_error::wrong_password:
                return "Wrong password. (密码错误。)";
            case tunet_service_error::not_a_dedicated_client:
                return "It is not a dedicated client. (不是专用客户端。)";
            case tunet_service_error::no_network_access:
                return "Users are disabled or have no internet access. (用户被禁用或无联网权限。)";
            case tunet_service_error::mac_binding_error:
                return "MAC binding error. (MAC绑定错误。)";
            case tunet_service_error::nas_binding_error:
                return "NAS PORT binding error. (NAS PORT绑定错误。)";
            case tunet_service_error::connection_number_exceeded:
                return "The number of connections is full. Please login to http://usereg.tsinghua.edu.cn "
                       "and choose to place your IP address offline. (连接数已满，请登录http://usereg.tsi"
                       "nghua.edu.cn，选择下线您的IP地址。)";
            case tunet_service_error::no_eligible_product:
                return "No eligible products were found. (找不到符合条件的产品。)";
            case tunet_service_error::no_eligible_billing:
                return "No eligible billing policy was found. (找不到符合条件的计费策略。)";
            case tunet_service_error::no_eligible_control:
                return "No eligible control strategy was found. (找不到符合条件的控制策略。)";
            case tunet_service_error::malformed_ip:
                return "IP address is abnormal. Please get the address again. (IP地址异常，请重新拿地址。)";
            case tunet_service_error::external_access_refused:
                return "Campus addresses do not allow access to external networks. (校内地址不允许访问外网。)";
            case tunet_service_error::ip_binding_error:
                return "IP address binding error. (IP地址绑定错误。)";
            case tunet_service_error::no_auth_required:
                return "IP address can be directly connected to the Internet without authentication. "
                       "(IP地址无需认证可直接上网。)";
            case tunet_service_error::unknown_ip:
                return "The IP address is not in the IP table. (IP地址不在IP表中。)";
            case tunet_service_error::blacklisted_ip:
                return "IP address is on the blacklist. Please contact the administrator. "
                       "(IP地址在黑名单中，请联系管理员。)";
            case tunet_service_error::third_party_auth_failed:
                return "Third party interface authentication failed. (第三方接口认证失败。)";
            default:
                return "Unknown error code. (未知错误代码。)";
        }
    }

    const tunet_error_category _cat{};

} // anonymous namespace

boost::system::error_code make_error_code(tunet_service_error e) noexcept {
    return {static_cast<int>(e), _cat};
}
